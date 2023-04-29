package edu.pitt.msnl.aware.ui.testing;

import androidx.appcompat.app.AlertDialog;
import androidx.constraintlayout.widget.ConstraintLayout;
import androidx.constraintlayout.widget.ConstraintSet;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.FragmentTransaction;
import androidx.lifecycle.ViewModelProviders;

import android.Manifest;
import android.app.Activity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.AudioTrack;
import android.media.MediaRecorder;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.os.Environment;
import android.os.ParcelFileDescriptor;
import android.os.Process;
import android.provider.OpenableColumns;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.google.android.material.snackbar.Snackbar;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Timer;
import java.util.TimerTask;

import edu.pitt.msnl.aware.R;
import edu.pitt.msnl.aware.myCppLib;
import edu.pitt.msnl.aware.myWavFile;
import edu.pitt.msnl.aware.myUtil;
import edu.pitt.msnl.aware.ui.calibration.CalibrationFragment;
import edu.pitt.msnl.aware.ui.results.ResultsFragment;
import edu.pitt.msnl.aware.ui.upload.UploadFragment;

import static android.media.AudioRecord.READ_NON_BLOCKING;

public class TestingFragment extends Fragment {

    private static final int PERMISSION_REQUEST_CODE = 1;
    private static final int REQUEST_CREATE_RECORD_FILE = 1;
    private static final int SAMPLE_RATE = 48000;

    private static final int SRC_FILE_ID = R.raw.pulse_dense;
    private static final int DEFAULT_VOL = 10;
    private static final String DEFAULT_FILE_NAME = "AudioRecord.pcm";
    private static final boolean THROAT_BUTTON_ENABLED = false;
    private static final String LOG_TAG = "AudioSampling";
    private static final int ORAL_REPEAT_NUM = 3;
    private static final int MAX_TRIAL = 5;
    private static final int[] TRIAL_BUTTON_ID =
            {R.id.trial_1,R.id.trial_2,R.id.trial_3,R.id.trial_4,R.id.trial_5};

    private TestingViewModel mViewModel;

    private final Object threadLock = new Object();
    private boolean isSampling = false;
    private boolean isStoppedManually = false;
    private boolean needSaving = false;
    private boolean needWriting = true;
    private boolean nextStage = false;
    private int countdown = 0;
    private Timer timer;
    private myWavFile src;
    private int trial = 1;
    private short[] buffer;
    private int data_length;
    private ArrayList<Integer> timestamp_throat_toggle;

    public static TestingFragment newInstance() {
        return new TestingFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.testing_fragment, container, false);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(TestingViewModel.class);

        // Set Listener for START/STOP Button
        ToggleButton toggle = getActivity().findViewById(R.id.record_button);
        toggle.setVisibility(View.INVISIBLE);
        toggle.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            // Called when press the OFF/ON toggle button
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                ToggleButton toggle = getActivity().findViewById(R.id.record_button);
                if (isChecked) {
                    // The toggle is checked
                    toggle.setChecked(false);
                    toggle.setClickable(false);
                    if (!permissionGranted()) {
                        toggle.setClickable(true);
                    } else {
                        toggle.setChecked(true);
                        newTrial();
                    }
                } else if (isSampling) {
                    // The toggle is unchecked
                    toggle.setChecked(true);
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Confirmation")
                            .setMessage("Are your sure you want to stop recording and discard current trial?")
                            .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                                public void onClick(DialogInterface dialog, int whichButton) {
                                    isStoppedManually = true;
                                    isSampling = false;
                                    ToggleButton toggle = getActivity().findViewById(R.id.record_button);
                                    toggle.setChecked(false);
                                    toggle.setClickable(true);
                                }
                            })
                            .setNegativeButton("Cancel", null).show();
                } else {
                    //toggle.setChecked(true);
                }
            }
        });

        // Set Listener for Add Button
        Button add = getActivity().findViewById(R.id.add_button);
        add.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if (trial > MAX_TRIAL) {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Attention")
                            .setMessage("Number of trials reaches upper limit. Please upload first or start a new test")
                            .setNeutralButton("OK", null).show();
                    return;
                }
                getActivity().findViewById(R.id.record_button).setVisibility(View.VISIBLE);
                getActivity().findViewById(R.id.add_button).setVisibility(View.INVISIBLE);
                getActivity().findViewById(R.id.graph).setVisibility(View.INVISIBLE);
                getActivity().findViewById(R.id.text_test).setVisibility(View.VISIBLE);
                TextView text_ins = getActivity().findViewById(R.id.text_test);
                String[] ins = getResources().getStringArray(R.array.trial_instructions);
                text_ins.setText(ins[0]);
            }
        });

        // Set listener for Continue button
        Button button_continue = getActivity().findViewById(R.id.continue_button);
        button_continue.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                getActivity().findViewById(R.id.continue_button).setVisibility(View.INVISIBLE);
                nextStage = true;
            }
        });

        // Set Listener for DELETE Button
        Button delete = getActivity().findViewById(R.id.delete_button);
        delete.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                int[] selected_files = getSelectedFiles();
                String msg = "";
                for (int i = 0; i < 5; i++) {
                    if (selected_files[i] == 1) {
                        msg = msg + " " + String.valueOf(i+1);
                    }
                }
                if (msg.equals("")) {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Confirmation")
                            .setMessage("No trials selected")
                            .setNeutralButton("OK", null).show();
                } else {
                    msg = "Trial" + msg + " will be deleted.";
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Confirmation")
                            .setMessage(msg)
                            .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                                public void onClick(DialogInterface dialog, int whichButton) {
                                    deleteTrialFiles(getSelectedFiles());
                                }
                            })
                            .setNegativeButton("Cancel", null).show();
                }
            }
        });

        // Set Listener for Upload Button
        Button upload = getActivity().findViewById(R.id.upload_button);
        upload.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if (!isNetworkAvailable()) {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Attention")
                            .setMessage("No internet connection")
                            .setNeutralButton("OK", null).show();
                    return;
                }
                File cali_file = new File(getActivity().getExternalCacheDir(),"cali.pcm");
                int[] selected_files = getSelectedFiles();
                String msg = "";
                for (int i = 0; i < 5; i++) {
                    if (selected_files[i] == 1) {
                        msg = msg + " " + String.valueOf(i+1);
                    }
                }
                if (!cali_file.exists()) {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Attention")
                            .setMessage("Calibration data not found")
                            .setNeutralButton("OK", null).show();
                } else if (msg.equals("")) {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Attention")
                            .setMessage("No trials selected")
                            .setNeutralButton("OK", null).show();
                } else {
                    msg = "Trial" + msg + " will be uploaded.";
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Confirmation")
                            .setMessage(msg)
                            .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                                public void onClick(DialogInterface dialog, int whichButton) {
                                    switchToUploadFragment();
                                }
                            })
                            .setNegativeButton("Cancel", null).show();
                }

            }
        });

        // Set Listener for Calibration Button
        Button calibration = getActivity().findViewById(R.id.cali_button);
        calibration.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                switchToCalibrationFragment();
            }
        });

        // Set Listener for New Test Button
        Button new_test = getActivity().findViewById(R.id.new_button);
        new_test.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                boolean no_trials = true;
                for (int i = 0; i < MAX_TRIAL; i++) {
                    File file = new File(getActivity().getExternalCacheDir(),
                            "trial_"+String.valueOf(i+1)+".pcm");
                    if (file.exists()) {
                        no_trials = false;
                    }
                }
                if (no_trials) {
                    newTest();
                } else {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Attention")
                            .setMessage("Trials not uploaded or saved will be lost.")
                            .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                                public void onClick(DialogInterface dialog, int whichButton) {
                                    newTest();
                                }
                            })
                            .setNegativeButton("Cancel", null).show();
                }
            }
        });

        // Set Listener for Throat Status Button
        if (THROAT_BUTTON_ENABLED) {
            TextView text_throat = getActivity().findViewById(R.id.text_throat);
            text_throat.setVisibility(View.VISIBLE);
            ToggleButton toggle_throat = getActivity().findViewById(R.id.throat_button);
            toggle_throat.setVisibility(View.VISIBLE);
            toggle_throat.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
                // Called when press the OFF/ON toggle button
                public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                    // TBD
                    timestamp_throat_toggle.add(data_length);
                }
            });
        }

        // Set Listener for SAVE Button
        Button save = getActivity().findViewById(R.id.save_button);
        save.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                saveAudioFile();
            }
        });

        // Set Listener for Result Button
        Button results = getActivity().findViewById(R.id.results_button);
        results.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                File precali_file = new File(getActivity().getExternalCacheDir(),"precali.pcm");
                File cali_file = new File(getActivity().getExternalCacheDir(),"cali.pcm");
                int[] selected_files = getSelectedFiles();
                String msg = "";
                for (int i = 0; i < 5; i++) {
                    if (selected_files[i] == 1) {
                        msg = msg + " " + String.valueOf(i+1);
                    }
                }
                if (!precali_file.exists()) {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Attention")
                            .setMessage("Pre-calibration (long-tube calibration) data not found")
                            .setNeutralButton("OK", null).show();
                } else if (!cali_file.exists()) {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Attention")
                            .setMessage("Calibration data not found")
                            .setNeutralButton("OK", null).show();
                } else if (msg.equals("")) {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Attention")
                            .setMessage("No trials selected")
                            .setNeutralButton("OK", null).show();
                } else {
                    msg = "Trial" + msg + " will be processed.";
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Confirmation")
                            .setMessage(msg)
                            .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                                public void onClick(DialogInterface dialog, int whichButton) {
                                    switchToResultsFragment();
                                }
                            })
                            .setNegativeButton("Cancel", null).show();
                }
            }
        });

        // Check existing trials
        trial = 1;
        for (int i = 0; i < MAX_TRIAL; i++) {
            File file = new File(getActivity().getExternalCacheDir(),
                    "trial_"+String.valueOf(i+1)+".pcm");
            if (file.exists()) {
                ToggleButton toggle_trial = getActivity().findViewById(TRIAL_BUTTON_ID[i]);
                toggle_trial.setEnabled(true);
                toggle_trial.setChecked(true);
                trial = i+2;
            }
        }
        setTrianglePosition(trial);

        /*if (trial != 1) {
            File dir = getActivity().getExternalCacheDir();
            File file = new File(dir, "trial_"+String.valueOf(trial-1)+".pcm");
            checkNoiseLevel(file);
        }*/
        // Keep Screen On
        getActivity().getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }

    private void switchToCalibrationFragment() {
        CalibrationFragment calibration = CalibrationFragment.newInstance();
        FragmentTransaction ft = getFragmentManager().beginTransaction();
        ft.add(R.id.fragment_container, calibration);
        ft.addToBackStack(null);
        ft.hide(this);
        ft.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_FADE);
        ft.commit();
    }

    private void switchToUploadFragment() {
        UploadFragment upload = UploadFragment.newInstance();
        FragmentTransaction ft = getFragmentManager().beginTransaction();
        ft.add(R.id.fragment_container, upload);
        ft.addToBackStack(null);
        ft.hide(this);
        ft.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_FADE);
        ft.commit();
    }

    private void switchToResultsFragment() {  // process selected trials
        ResultsFragment results = ResultsFragment.newInstance();
        FragmentTransaction ft = getFragmentManager().beginTransaction();
        ft.add(R.id.fragment_container, results);
        ft.addToBackStack(null);
        ft.hide(this);
        ft.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_FADE);
        ft.commit();
    }

    private void switchToResultsFragment(int which_trial) { // process certain single trial
        ResultsFragment results = ResultsFragment.newInstance();
        Bundle arg = new Bundle();
        arg.putInt("which_trial", which_trial);
        results.setArguments(arg);
        FragmentTransaction ft = getFragmentManager().beginTransaction();
        ft.add(R.id.fragment_container, results);
        ft.addToBackStack(null);
        ft.hide(this);
        ft.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_FADE);
        ft.commit();
    }

    // Start A new whole test
    private void newTest() {
        File cali_file = new File(getActivity().getExternalCacheDir(),"cali.pcm");
        if (!cali_file.exists()) {
            new AlertDialog.Builder(getActivity())
                    .setTitle("Attention")
                    .setMessage("Please calibrate first")
                    .setNeutralButton("OK", null).show();
            return;
        }
        trial = 1;
        // Delete all trials and reset buttons
        int[] all_trials = new int[MAX_TRIAL];
        Arrays.fill(all_trials,1);
        deleteTrialFiles(all_trials);
        ToggleButton toggle = getActivity().findViewById(R.id.record_button);
        toggle.setVisibility(View.VISIBLE);
        getActivity().findViewById(R.id.add_button).setVisibility(View.INVISIBLE);
        getActivity().findViewById(R.id.graph).setVisibility(View.INVISIBLE);
        TextView text = getActivity().findViewById(R.id.text_test);
        text.setVisibility(View.VISIBLE);
        String[] ins = getResources().getStringArray(R.array.trial_instructions);
        text.setText(ins[0]);
    }

    // Start a new trial
    private void newTrial() {
        try {
            Thread thread = new Thread(new Runnable() {
                @Override
                public void run() {
                    synchronized (threadLock) {
                        android.os.Process.setThreadPriority(Process.THREAD_PRIORITY_AUDIO);
                        loopback();
                    }
                }
            });
            thread.start();
        }catch(Exception e) {
            e.printStackTrace();
        }
    }

    // Playing and Recording
    private void loopback() {
        try {
            // Create a new cache file
            if (!isExternalStorageWritable()) {
                Log.e(LOG_TAG,"External storage not writable");
                return;
            }
            File dir = getActivity().getExternalCacheDir();
            if (dir.mkdirs()) {
                Log.i(LOG_TAG, "New directory created");
            }
            File file = new File(dir, "trial_"+String.valueOf(trial)+".pcm");
            if (file.exists()) {
                if (!file.delete()) {
                    Log.e(LOG_TAG, "Failed to delete existing cache file");
                }
            }
            if(file.createNewFile()) {
                Log.i(LOG_TAG, "New cache file created successfully");
            }
            DataOutputStream dos = new DataOutputStream(new FileOutputStream(file));

            // Change button status
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    getActivity().findViewById(R.id.delete_button).setEnabled(false);
                    getActivity().findViewById(R.id.new_button).setEnabled(false);
                    getActivity().findViewById(R.id.cali_button).setEnabled(false);
                    getActivity().findViewById(R.id.upload_button).setEnabled(false);
                    getActivity().findViewById(R.id.save_button).setEnabled(false);
                    getActivity().findViewById(R.id.results_button).setEnabled(false);
                    getActivity().findViewById(TRIAL_BUTTON_ID[trial-1]).setEnabled(true);
                    getActivity().findViewById(TRIAL_BUTTON_ID[trial-1]).setClickable(false);
                }
            });

            // Recorder Initialization
            int bufferSize = SAMPLE_RATE * 2;
            AudioRecord mRecord = new AudioRecord(MediaRecorder.AudioSource.UNPROCESSED,
                    SAMPLE_RATE, AudioFormat.CHANNEL_IN_MONO,
                    AudioFormat.ENCODING_PCM_16BIT, bufferSize);
            if (mRecord.getState() != AudioRecord.STATE_INITIALIZED) {
                Log.e(LOG_TAG, "AudioRecord not initialized!");
                return;
            }

            // Player Initialization
            InputStream iStream = getResources().openRawResource(SRC_FILE_ID);
            src = new myWavFile(iStream);
            AudioTrack mTrack = new AudioTrack(AudioManager.STREAM_MUSIC,
                    SAMPLE_RATE, AudioFormat.CHANNEL_OUT_MONO,
                    AudioFormat.ENCODING_PCM_16BIT, src.dataSizeInBytes * 2,
                    AudioTrack.MODE_STATIC);
            /*if (mTrack.getState() != AudioTrack.STATE_INITIALIZED) {
                Log.e(LOG_TAG, "AudioTrack not initialized!");
                return;
            }*/
            mTrack.write(myUtil.repeatData(src.data,2), 0, src.data.length*2);

            // Set default volume
            AudioManager mAudioManager = (AudioManager) getActivity().getSystemService(Context.AUDIO_SERVICE);
            int currentVolume = mAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
            mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC,
                    DEFAULT_VOL, AudioManager.FLAG_REMOVE_SOUND_AND_VIBRATE);

            // Get text box id
            TextView text_ins = getActivity().findViewById(R.id.text_test);
            String[] ins = getResources().getStringArray(R.array.trial_instructions);

            //----------------------- Stage 1 Start --------------------------
            // Start
            enableThroatButton(true);
            text_ins.setText(ins[1]);
            Thread.sleep(1000);

            mRecord.startRecording();
            mTrack.play();
            startTimer(10);
            isSampling = true;
            isStoppedManually = false;
            needSaving = false;
            Log.i(LOG_TAG, "Recording start");

            // Enable START/STOP button
            ToggleButton toggle = getActivity().findViewById(R.id.record_button);
            toggle.findViewById(R.id.record_button).setClickable(true);

            // Read data from buffer
            data_length = 0;
            timestamp_throat_toggle = new ArrayList<Integer>();
            buffer = new short[bufferSize];
            while (isSampling) {
                /*if (needWriting) {
                    mTrack.write(src.data, 0, src.data.length);
                    needWriting = false;
                }*/
                int bufferReadResult = mRecord.read(buffer, 0, bufferSize, READ_NON_BLOCKING);
                data_length = data_length + bufferReadResult;
                for (int i = 0; i < bufferReadResult; i++){
                    dos.writeShort(buffer[i]);
                }
            }
            Log.i(LOG_TAG, "Recording stop");
            enableThroatButton(false);
            stopTimer();
            mRecord.stop();
            mTrack.stop();
            if (isStoppedManually) {
                isStoppedManually = false;
                mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC,
                        currentVolume, AudioManager.FLAG_REMOVE_SOUND_AND_VIBRATE);
                mRecord.release();
                mTrack.release();
                dos.close();
                toggle.setClickable(true);
                deleteTrialFiles(getCurrentFile());
                text_ins.setText(ins[6]);
                TextView text_time = getActivity().findViewById(R.id.record_time);
                text_time.setText("");
                getActivity().runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        getActivity().findViewById(R.id.record_button).setVisibility(View.INVISIBLE);
                        getActivity().findViewById(R.id.add_button).setVisibility(View.VISIBLE);
                        getActivity().findViewById(R.id.delete_button).setEnabled(true);
                        getActivity().findViewById(R.id.new_button).setEnabled(true);
                        getActivity().findViewById(R.id.cali_button).setEnabled(true);
                        getActivity().findViewById(R.id.upload_button).setEnabled(true);
                        getActivity().findViewById(R.id.save_button).setEnabled(true);
                        getActivity().findViewById(R.id.results_button).setEnabled(true);
                    }
                });
                return;
            }
            //----------------------- Stage 1 finish --------------------------
            text_ins.setText(ins[2]);
            nextStage = false;
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    getActivity().findViewById(R.id.record_button).setVisibility(View.INVISIBLE);
                    getActivity().findViewById(R.id.continue_button).setVisibility(View.VISIBLE);
                }
            });
            while (!nextStage && !isStoppedManually) {
                Thread.sleep(100);
            };
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    getActivity().findViewById(R.id.record_button).setVisibility(View.VISIBLE);
                    getActivity().findViewById(R.id.continue_button).setVisibility(View.INVISIBLE);
                }
            });
            if (isStoppedManually) {
                isStoppedManually = false;
                mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC,
                        currentVolume, AudioManager.FLAG_REMOVE_SOUND_AND_VIBRATE);
                mRecord.release();
                mTrack.release();
                dos.close();
                toggle.setClickable(true);
                deleteTrialFiles(getCurrentFile());
                text_ins.setText(ins[6]);
                TextView text_time = getActivity().findViewById(R.id.record_time);
                text_time.setText("");
                getActivity().runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        getActivity().findViewById(R.id.record_button).setVisibility(View.INVISIBLE);
                        getActivity().findViewById(R.id.add_button).setVisibility(View.VISIBLE);
                        getActivity().findViewById(R.id.delete_button).setEnabled(true);
                        getActivity().findViewById(R.id.new_button).setEnabled(true);
                        getActivity().findViewById(R.id.cali_button).setEnabled(true);
                        getActivity().findViewById(R.id.upload_button).setEnabled(true);
                        getActivity().findViewById(R.id.save_button).setEnabled(true);
                        getActivity().findViewById(R.id.results_button).setEnabled(true);
                    }
                });
                return;
            }
            //----------------------- Stage 2 Start --------------------------
            mTrack.release();
            mTrack = new AudioTrack(AudioManager.STREAM_MUSIC,
                    SAMPLE_RATE, AudioFormat.CHANNEL_OUT_MONO,
                    AudioFormat.ENCODING_PCM_16BIT, src.dataSizeInBytes * 2,
                    AudioTrack.MODE_STATIC);
            mTrack.write(src.data, 0, src.data.length);

            toggle.setClickable(false);
            for (int stage = 0; stage < ORAL_REPEAT_NUM; stage++) {
                enableThroatButton(true);
                text_ins.setText(ins[3]);
                Thread.sleep(1000);

                mRecord.startRecording();
                mTrack.play();
                startTimer(5);
                if (!isStoppedManually) {
                    isSampling = true;
                }
                else {
                    isSampling = false;
                }

                Log.i(LOG_TAG, "Recording start");
                toggle.setClickable(true);

                short[] buffer = new short[bufferSize*2];
                while (isSampling) {
                    int bufferReadResult = mRecord.read(buffer, 0, bufferSize, READ_NON_BLOCKING);
                    for (int i = 0; i < bufferReadResult; i++){
                        dos.writeShort(buffer[i]);
                    }
                }
                stopTimer();
                mRecord.stop();
                mTrack.stop();
                // mTrack.reloadStaticData();
                Log.i(LOG_TAG, "Recording stop");

                if (isStoppedManually) {
                    isStoppedManually = false;
                    mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC,
                            currentVolume, AudioManager.FLAG_REMOVE_SOUND_AND_VIBRATE);

                    mRecord.release();
                    mTrack.release();
                    dos.close();
                    toggle.setClickable(true);
                    deleteTrialFiles(getCurrentFile());
                    text_ins.setText(ins[6]);
                    TextView text_time = getActivity().findViewById(R.id.record_time);
                    text_time.setText("");
                    getActivity().runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            getActivity().findViewById(R.id.record_button).setVisibility(View.INVISIBLE);
                            getActivity().findViewById(R.id.add_button).setVisibility(View.VISIBLE);
                            getActivity().findViewById(R.id.delete_button).setEnabled(true);
                            getActivity().findViewById(R.id.new_button).setEnabled(true);
                            getActivity().findViewById(R.id.cali_button).setEnabled(true);
                            getActivity().findViewById(R.id.upload_button).setEnabled(true);
                            getActivity().findViewById(R.id.save_button).setEnabled(true);
                            getActivity().findViewById(R.id.results_button).setEnabled(true);
                        }
                    });
                    return;
                }

                //------------------Inhale finish, exhale start----------------------
                text_ins.setText(ins[4]);
                Thread.sleep(1000);

                mRecord.startRecording();
                mTrack.play();
                startTimer(5);
                if (!isStoppedManually) {
                    isSampling = true;
                }
                else {
                    isSampling = false;
                }

                Log.i(LOG_TAG, "Recording start");

                while (isSampling) {
                    int bufferReadResult = mRecord.read(buffer, 0, bufferSize, READ_NON_BLOCKING);
                    for (int i = 0; i < bufferReadResult; i++){
                        dos.writeShort(buffer[i]);
                    }
                }
                stopTimer();
                mRecord.stop();
                mTrack.stop();
                // mTrack.reloadStaticData();
                Log.i(LOG_TAG, "Recording stop");

                if (isStoppedManually) {
                    isStoppedManually = false;
                    mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC,
                            currentVolume, AudioManager.FLAG_REMOVE_SOUND_AND_VIBRATE);

                    mRecord.release();
                    mTrack.release();
                    dos.close();
                    toggle.setClickable(true);
                    deleteTrialFiles(getCurrentFile());
                    text_ins.setText(ins[6]);
                    TextView text_time = getActivity().findViewById(R.id.record_time);
                    text_time.setText("");
                    getActivity().runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            getActivity().findViewById(R.id.record_button).setVisibility(View.INVISIBLE);
                            getActivity().findViewById(R.id.add_button).setVisibility(View.VISIBLE);
                            getActivity().findViewById(R.id.delete_button).setEnabled(true);
                            getActivity().findViewById(R.id.new_button).setEnabled(true);
                            getActivity().findViewById(R.id.cali_button).setEnabled(true);
                            getActivity().findViewById(R.id.upload_button).setEnabled(true);
                            getActivity().findViewById(R.id.save_button).setEnabled(true);
                            getActivity().findViewById(R.id.results_button).setEnabled(true);
                        }
                    });
                    return;
                }
            }
            //----------------------- Stage 2 finish --------------------------
            text_ins.setText(ins[5]);
            //Reset volume
            mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC,
                    currentVolume, AudioManager.FLAG_REMOVE_SOUND_AND_VIBRATE);

            mRecord.release();
            mTrack.release();
            dos.close();

            //-------------------------- Check noise level-----------------------------
            checkNoiseLevel(file);
            /*new Thread(new Runnable() {
                @Override
                public void run() {
                    synchronized (threadLock) {
                        File dir = getActivity().getExternalCacheDir();

                    }
                }
            }).start();*/

            // Reset toggle buttons
            toggle.setChecked(false);
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    ToggleButton trial_button = getActivity().findViewById(TRIAL_BUTTON_ID[trial-1]);
                    trial_button.setChecked(true);
                    trial_button.setClickable(true);
                    trial++;
                    setTrianglePosition(trial);
                }
            });

        } catch (Throwable t) {
            Log.e("Error", "Audio loopback failed： "+t.getLocalizedMessage());
            ToggleButton toggle = getActivity().findViewById(R.id.record_button);
            toggle.setChecked(false);
            toggle.setClickable(true);
            return;
        }

        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                getActivity().findViewById(R.id.record_button).setVisibility(View.INVISIBLE);
                getActivity().findViewById(R.id.add_button).setVisibility(View.VISIBLE);
                getActivity().findViewById(R.id.delete_button).setEnabled(true);
                getActivity().findViewById(R.id.new_button).setEnabled(true);
                getActivity().findViewById(R.id.cali_button).setEnabled(true);
                getActivity().findViewById(R.id.upload_button).setEnabled(true);
                getActivity().findViewById(R.id.save_button).setEnabled(true);
                getActivity().findViewById(R.id.results_button).setEnabled(true);
            }
        });

    }

    private void checkNoiseLevel(File file) {
        File dir = getActivity().getExternalCacheDir();
        File precali_file = new File(dir, "precali.pcm");
        if (!precali_file.exists() || !file.exists()) {return;}
        try {
            FileInputStream fis = new FileInputStream(precali_file);
            DataInputStream dis = new DataInputStream(new BufferedInputStream(fis));
            short[] cali = new short[264000];
            for (int i = 0; i < cali.length; i++) {
                cali[i] = dis.readShort();
            }
            dis.close();

            fis = new FileInputStream(file);
            dis = new DataInputStream(new BufferedInputStream(fis));
            short[] test = new short[2160000];
            for (int i = 0; i < test.length; i++) {
                test[i] = dis.readShort();
            }
            dis.close();

            double[] noise = new double[2160000];
            myCppLib.GetNoiseLevelFromJni(cali, test, noise);

            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    getActivity().findViewById(R.id.graph).setVisibility(View.VISIBLE);
                    getActivity().findViewById(R.id.text_test).setVisibility(View.INVISIBLE);
                }
            });

            GraphView graph = getActivity().findViewById(R.id.graph);
            graph.removeAllSeries();
            graph.getViewport().setXAxisBoundsManual(true);
            graph.getViewport().setYAxisBoundsManual(true);
            graph.getViewport().setScalable(true);
            graph.getViewport().setScalableY(true);

            graph.getViewport().setMinX(0);
            graph.getViewport().setMaxX(45);
            graph.getViewport().setMinY(-1);
            graph.getViewport().setMaxY(1);

            ArrayList<DataPoint> list = new ArrayList<>();
            for (int i = 0; i < test.length; i++) {
                list.add(new DataPoint((double)i/SAMPLE_RATE, (double)test[i]/32768));
            }
            DataPoint[] points = list.toArray(new DataPoint[0]);
            LineGraphSeries<DataPoint> series = new LineGraphSeries<>(points);
            graph.addSeries(series);

            list = new ArrayList<>();
            for (int i = 0; i < noise.length; i++) {
                list.add(new DataPoint((double)i/SAMPLE_RATE, noise[i]));
            }
            points = list.toArray(new DataPoint[0]);
            series = new LineGraphSeries<>(points);
            series.setColor(Color.rgb(153,0,0));
            graph.addSeries(series);

            if (noise[myUtil.findMax(noise)] > 0.7*cali[myUtil.findMax(cali)]/32768) {
                getActivity().runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        new AlertDialog.Builder(getActivity())
                                .setTitle("Noise level NOT acceptable")
                                .setMessage("Do you still want to keep this trial?")
                                .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                                    public void onClick(DialogInterface dialog, int whichButton) {
                                        switchToResultsFragment(trial-1);
                                    }
                                })
                                .setNegativeButton("No", new DialogInterface.OnClickListener() {
                                    public void onClick(DialogInterface dialog, int whichButton) {
                                        deleteTrialFiles(getLastFile());
                                    }
                                }).show();
                    }
                });
            }
            else {
                getActivity().runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        new AlertDialog.Builder(getActivity())
                                .setTitle("Noise level acceptable")
                                .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                                    public void onClick(DialogInterface dialog, int whichButton) {
                                        switchToResultsFragment(trial-1);
                                    }
                                }).show();
                    }
                });
            }


        } catch (Throwable t) {
            t.printStackTrace();
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Data corrupted")
                            .setMessage("Do you want to discard this trial?")
                            .setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                                public void onClick(DialogInterface dialog, int whichButton) {
                                    deleteTrialFiles(getLastFile());
                                }
                            })
                            .setNegativeButton("No", null).show();
                }
            });
        }

    }

    private int[] getCurrentFile () {
        int[] ret = new int[MAX_TRIAL];
        ret[trial-1] = 1;
        return ret;
    }

    private int[] getLastFile () {
        int[] ret = new int[MAX_TRIAL];
        ret[trial-2] = 1;
        return ret;
    }

    private int[] getSelectedFiles () {
        int[] ret = new int[MAX_TRIAL];
        for (int i = 0; i < MAX_TRIAL; i++) {
            ToggleButton toggle = getActivity().findViewById(TRIAL_BUTTON_ID[i]);
            File file = new File(getActivity().getExternalCacheDir(),
                    "trial_"+String.valueOf(i+1)+".pcm");
            if (file.exists() && toggle.isChecked()) {
                ret[i] = 1;
            }
        }
        return ret;
    }

    private void setTrianglePosition (int i) {
        if (i > MAX_TRIAL) {
            i = MAX_TRIAL;
        }
        ImageView img = getActivity().findViewById(R.id.triangle);
        img.setVisibility(View.VISIBLE);
        ConstraintLayout layout = getActivity().findViewById(R.id.layout_trial);
        ConstraintSet constraints = new ConstraintSet();
        constraints.clone(layout);
        constraints.connect(R.id.triangle, ConstraintSet.LEFT, TRIAL_BUTTON_ID[i-1], ConstraintSet.LEFT, 0);
        constraints.connect(R.id.triangle, ConstraintSet.RIGHT, TRIAL_BUTTON_ID[i-1], ConstraintSet.RIGHT, 0);
        constraints.connect(R.id.triangle, ConstraintSet.TOP, TRIAL_BUTTON_ID[i-1], ConstraintSet.BOTTOM, 0);
        constraints.applyTo(layout);
    }

    private void deleteTrialFiles(int[] file_selected) {
        File dir = getActivity().getExternalCacheDir();
        for (int i = 0; i < MAX_TRIAL; i++) {
            File file = new File(dir, "trial_"+String.valueOf(i+1)+".pcm");
            if (file.exists() && file_selected[i]==1) {
                if (!file.delete()) {
                    Log.e(LOG_TAG, "Failed to delete existing cache file");
                }
            }
        }
        for (int i = trial-1; i >= 0; i--) {
            File file = new File(dir, "trial_"+String.valueOf(i+1)+".pcm");
            if (!file.exists()) {
                trial = i+1;
            } else {
                break;
            }
        }
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                setTrianglePosition(trial);
                for (int i = 0; i < MAX_TRIAL; i++) {
                    File file = new File(getActivity().getExternalCacheDir(),
                            "trial_"+String.valueOf(i+1)+".pcm");
                    if (file.exists()) {
                        ToggleButton toggle_trial = getActivity().findViewById(TRIAL_BUTTON_ID[i]);
                        toggle_trial.setEnabled(true);
                        toggle_trial.setChecked(true);
                    }
                    else {
                        ToggleButton toggle_trial = getActivity().findViewById(TRIAL_BUTTON_ID[i]);
                        toggle_trial.setEnabled(false);
                        toggle_trial.setChecked(false);
                    }
                }
            }
        });
    }

    private void saveAudioFile() {
        // Call Intent.ACTION_CREATE_DOCUMENT to let user select the saving directory
        Log.i(LOG_TAG, "Saving File");
        Intent intent = new Intent(Intent.ACTION_CREATE_DOCUMENT);
        intent.addCategory(Intent.CATEGORY_OPENABLE);
        intent.setType("application/octet-stream");
        intent.putExtra(Intent.EXTRA_TITLE, DEFAULT_FILE_NAME);
        startActivityForResult(intent, REQUEST_CREATE_RECORD_FILE);
        needSaving = false;
        // Copy from cache file to final file is in onActivityResult
        // (requestCode == REQUEST_CREATE_RECORD_FILE)
    }

    @Override
    public void onActivityResult(int requestCode, int resultCode,
                                 Intent resultData) {
        super.onActivityResult(requestCode, resultCode, resultData);
        if (requestCode == REQUEST_CREATE_RECORD_FILE
                && resultCode == Activity.RESULT_OK) {
            // The result data contains a URI for the document or directory that
            // the user selected.
            if (resultData != null) {
                Uri uri = resultData.getData();
                Log.i(LOG_TAG, uri.toString());

                // Copy the record file from cache to directory indicated by this uri
                try {
                    ParcelFileDescriptor pfd = getActivity().getContentResolver().
                            openFileDescriptor(uri, "w");
                    FileOutputStream fos =
                            new FileOutputStream(pfd.getFileDescriptor());
                    File cacheFile =
                            new File(getActivity().getExternalCacheDir(),
                                    "trial_"+String.valueOf(trial)+".pcm");
                    FileInputStream fis =
                            new FileInputStream(cacheFile);
                    byte[] buf = new byte[1024];
                    int len = fis.read(buf);
                    while(len != -1) {
                        fos.write(buf,0, len);
                        len = fis.read(buf);
                    }
                    fis.close();
                    fos.close();
                    pfd.close();

                    Snackbar.make(getActivity().findViewById(R.id.MainLayout),
                            "Saved as " + getFileName(uri),
                            Snackbar.LENGTH_LONG).show();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    // Get file name from uri
    private String getFileName(Uri uri) {
        String result = null;
        if (uri.getScheme().equals("content")) {
            Cursor cursor = getActivity().getContentResolver().query(uri, null, null, null, null);
            try {
                if (cursor != null && cursor.moveToFirst()) {
                    result = cursor.getString(cursor.getColumnIndex(OpenableColumns.DISPLAY_NAME));
                }
            } finally {
                cursor.close();
            }
        }
        if (result == null) {
            result = uri.getPath();
            int cut = result.lastIndexOf('/');
            if (cut != -1) {
                result = result.substring(cut + 1);
            }
        }
        return result;
    }

    // Set up timer
    private void startTimer(int sec) {
        timer = new Timer();
        countdown = sec;
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                TextView text_time = getActivity().findViewById(R.id.record_time);
                text_time.setTextColor(getActivity().getColor(R.color.colorAccent));

                if (countdown < 0) {
                    isSampling = false;
                    text_time.setText("");
                }
                else {
                    text_time.setTextColor(getActivity().getColor(R.color.colorAccent));
                    text_time.setText((int) countdown + "s");
                    countdown = countdown - 1;
                }

            }
        }, 0, 1000);
    }
    private void stopTimer() {
        timer.cancel();
    }

    private void enableThroatButton(boolean enable) {
        if (THROAT_BUTTON_ENABLED && enable) {
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    ToggleButton toggle = getActivity().findViewById(R.id.throat_button);
                    toggle.setEnabled(true);
                }
            });
        }
        else if (THROAT_BUTTON_ENABLED && !enable) {
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    ToggleButton toggle = getActivity().findViewById(R.id.throat_button);
                    toggle.setEnabled(false);
                }
            });
        }
    }

    // External Storage Check
    public boolean isExternalStorageWritable() {
        String state = Environment.getExternalStorageState();
        return Environment.MEDIA_MOUNTED.equals(state);
    }

    // Permission Check
    public boolean permissionGranted() {
        if (ContextCompat.checkSelfPermission(getActivity(), Manifest.permission.RECORD_AUDIO)
                != PackageManager.PERMISSION_GRANTED ||
                ContextCompat.checkSelfPermission(getActivity(), Manifest.permission.WRITE_EXTERNAL_STORAGE)
                        != PackageManager.PERMISSION_GRANTED) {
            // Permission is not granted
            ActivityCompat.requestPermissions(getActivity(),
                    new String[]{
                            Manifest.permission.RECORD_AUDIO,
                            Manifest.permission.WRITE_EXTERNAL_STORAGE
                    },
                    PERMISSION_REQUEST_CODE);
            return false;
        } else {
            // Permission is granted
            return true;
        }
    }
    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (grantResults.length > 0 &&
                (grantResults[0] == PackageManager.PERMISSION_DENIED ||
                        grantResults[1] == PackageManager.PERMISSION_DENIED)) {
            Log.e("Error","Permission Denied");
            Snackbar.make(getActivity().findViewById(R.id.MainLayout), R.string.need_permissions, Snackbar.LENGTH_LONG)
                    .show();
        }
    }

    private boolean isNetworkAvailable() {
        ConnectivityManager connectivityManager
                = (ConnectivityManager) getActivity().getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo activeNetworkInfo = connectivityManager.getActiveNetworkInfo();
        return activeNetworkInfo != null && activeNetworkInfo.isConnected();
    }

}
