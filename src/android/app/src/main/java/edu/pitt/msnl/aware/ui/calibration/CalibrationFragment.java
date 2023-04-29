package edu.pitt.msnl.aware.ui.calibration;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.lifecycle.ViewModelProviders;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.AudioTrack;
import android.media.MediaRecorder;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.os.Environment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.google.android.material.snackbar.Snackbar;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.util.Arrays;
import java.util.Timer;
import java.util.TimerTask;

import edu.pitt.msnl.aware.R;
import edu.pitt.msnl.aware.myWavFile;

import static android.media.AudioRecord.READ_NON_BLOCKING;

public class CalibrationFragment extends Fragment {

    private static final int PERMISSION_REQUEST_CODE = 1;
    private static final int SAMPLE_RATE = 48000;

    private static final int SRC_FILE_ID = R.raw.two_pulses_dense;
    private static final int DEFAULT_VOL = 10;
    private static final String LOG_TAG = "AudioSampling";
    private static final int CALI_TASK_NUM = 2;

    private boolean isSampling = false;
    private boolean nextStage = false;
    private boolean stopThread = false;
    private double countdown = 0;
    private Timer timer;
    private int[] cali_offset = new int[CALI_TASK_NUM];

    private CalibrationViewModel mViewModel;

    public static CalibrationFragment newInstance() {
        return new CalibrationFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.calibration_fragment, container, false);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(CalibrationViewModel.class);

        // Show back button on toolbar
        ((AppCompatActivity) getActivity()).getSupportActionBar().setDisplayHomeAsUpEnabled(true);
        ((AppCompatActivity) getActivity()).getSupportActionBar().setDisplayShowHomeEnabled(true);
        Toolbar toolbar = getActivity().findViewById(R.id.action_bar);
        toolbar.setNavigationOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ((AppCompatActivity) getActivity()).getSupportActionBar().setDisplayHomeAsUpEnabled(false);
                ((AppCompatActivity) getActivity()).getSupportActionBar().setDisplayShowHomeEnabled(false);
                getActivity().onBackPressed();
            }
        });

        // Set instruction text
        String[] ins = getResources().getStringArray(R.array.cali_instructions);
        TextView text = getActivity().findViewById(R.id.text_instruction);
        text.setText(ins[0]);

        // Set listener for start button
        Button button = getActivity().findViewById(R.id.record_button_cali);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Button button = getActivity().findViewById(R.id.record_button_cali);
                button.setClickable(false);
                if (!permissionGranted()) {
                    button.setClickable(true);
                    return;
                }
                Thread thread = new Thread(new Runnable() {
                    @Override
                    public void run() {
                        loopback();
                    }
                });
                thread.start();
            }
        });
    }

    // Playing and Recording
    private void loopback() {
        // Create .PCM Cache File
        if (!isExternalStorageWritable()) {
            Log.e(LOG_TAG,"External storage not writable");
            return;
        }
        File dir = getActivity().getExternalCacheDir();
        if (dir.mkdirs()) {
            Log.i(LOG_TAG, "New directory created");
        }
        File file = new File(dir, "cali.pcm");
        if (file.exists()) {
            if (!file.delete()) {
                Log.e(LOG_TAG, "Failed to delete existing calibration cache file");
            }
        }
        try{
            if(file.createNewFile()) {
                Log.i(LOG_TAG, "New calibration cache file created successfully");
            }
        } catch(IOException e) {
            Log.e(LOG_TAG, "File creation Failed");
        }

        // Prepare the AudioRecord & AudioTrack
        try {
            DataOutputStream dos = new DataOutputStream(new FileOutputStream(file));

            int bufferSize = SAMPLE_RATE * 2; // arbitrary value, the bigger the better

            // Recorder Configuration
            AudioRecord mRecord = new AudioRecord(MediaRecorder.AudioSource.UNPROCESSED,
                    SAMPLE_RATE, AudioFormat.CHANNEL_IN_MONO,
                    AudioFormat.ENCODING_PCM_16BIT, bufferSize);

            if (mRecord.getState() != AudioRecord.STATE_INITIALIZED) {
                Log.e(LOG_TAG, "Audio Record can't initialize!");
                return;
            }

            InputStream iStream = getResources().openRawResource(SRC_FILE_ID);
            myWavFile src = new myWavFile(iStream);

            // Player Configuration
            AudioTrack mTrack = new AudioTrack(AudioManager.STREAM_MUSIC,
                    SAMPLE_RATE, AudioFormat.CHANNEL_OUT_MONO,
                    AudioFormat.ENCODING_PCM_16BIT, src.dataSizeInBytes * 2,
                    AudioTrack.MODE_STATIC);
            mTrack.write(src.data, 0, src.data.length);

            AudioManager mAudioManager = (AudioManager) getActivity().getSystemService(Context.AUDIO_SERVICE);
            int currentVolume = mAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
            int maxVolume = mAudioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
            String[] ins = getResources().getStringArray(R.array.cali_instructions);
            cali_offset = new int[5];

            // Loop for multiple calibration tasks
            for (int stage = 0; stage < CALI_TASK_NUM; stage++) {
                // Set volume to max
                mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC,
                        DEFAULT_VOL, AudioManager.FLAG_REMOVE_SOUND_AND_VIBRATE);

                mRecord.startRecording();
                mTrack.play();
                startTimer();
                isSampling = true;

                Log.i(LOG_TAG, "Recording start");

                short[] buffer = new short[bufferSize*2];
                while (isSampling) {
                    int bufferReadResult = mRecord.read(buffer, 0, bufferSize, READ_NON_BLOCKING);
                    for (int i = 0; i < bufferReadResult; i++){
                        dos.writeShort(buffer[i]);
                    }
                    cali_offset[stage] += bufferReadResult;
                }
                //Reset volume
                mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC,
                        currentVolume, AudioManager.FLAG_REMOVE_SOUND_AND_VIBRATE);

                stopTimer();
                mRecord.stop();
                mTrack.stop();
                // mTrack.reloadStaticData();
                Log.i(LOG_TAG, "Recording stop");
                // Read rest data in buffer
                int bufferReadResult = mRecord.read(buffer, 0, bufferSize, READ_NON_BLOCKING);
                cali_offset[stage] += bufferReadResult;
                for (int i = 0; i < bufferReadResult; i++){
                    dos.writeShort(buffer[i]);
                }
                if (stopThread) {
                    mRecord.release();
                    mTrack.release();
                    dos.close();
                    return;
                }
                // Set instruction text for next task
                nextStage = false;
                TextView text = getActivity().findViewById(R.id.text_instruction);
                text.setText(ins[stage+1]);
                Button button = getActivity().findViewById(R.id.record_button_cali);
                button.setOnClickListener(new View.OnClickListener() {
                    public void onClick(View v) {
                        getActivity().findViewById(R.id.record_button_cali).setClickable(false);
                        nextStage = true;
                    }
                });
                button.setClickable(true);
                while (!nextStage && stage < CALI_TASK_NUM-1) {
                    Thread.sleep(100);
                };
            }

            mRecord.release();
            mTrack.release();
            dos.close();
        } catch (Throwable t) {
            Log.e("Error", "Audio Record and Play Failed： "+t.getLocalizedMessage());
            return;
        }

        // Write segment offset to a cache file
        File offset_file = new File(dir, "cali_offset");
        if (offset_file.exists()) {
            if (!offset_file.delete()) {
                Log.e(LOG_TAG, "Failed to delete existing offset cache file");
            }
        }
        try{
            if(offset_file.createNewFile()) {
                Log.i(LOG_TAG, "New offset cache file created successfully");
            }
        } catch(IOException e) {
            Log.e(LOG_TAG, "File Creation Failed");
        }
        writeStringToFile(offset_file, arrayToString(cali_offset));
        Log.i(LOG_TAG,"cali_offset: "+arrayToString(cali_offset));

        Button button = getActivity().findViewById(R.id.record_button_cali);
        button.setText("RETURN");
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                getActivity().onBackPressed();
            }
        });
    }

    @Override
    public void onStop() {
        stopThread = true;
        isSampling = false;
        super.onStop();
    }

    private void writeStringToFile (File file, String str) {
        try {
            OutputStream os = new FileOutputStream(file);
            OutputStreamWriter outputStreamWriter = new OutputStreamWriter(os);
            outputStreamWriter.write(str);
            outputStreamWriter.close();
        }
        catch (IOException e) {
            Log.e("Exception", "File write failed: " + e.toString());
        }
    }

    private String arrayToString(int[] arr) {
        return Arrays.toString(arr).replaceAll("\\[|\\]|\\s", "");
    }

    private void startTimer() {
        timer = new Timer();
        countdown = 5;
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                TextView text_time = getActivity().findViewById(R.id.record_time_cali);
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

}
