package edu.pitt.msnl.aware.ui.results;

import android.Manifest;
import android.content.Context;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.graphics.DashPathEffect;
import android.graphics.Paint;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.ToggleButton;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.google.android.material.snackbar.Snackbar;
import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.LegendRenderer;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.io.Writer;
import java.util.ArrayList;


import edu.pitt.msnl.aware.R;
import edu.pitt.msnl.aware.myCppLib;
import edu.pitt.msnl.aware.myUtil;
import edu.pitt.msnl.aware.myWavFile;
import edu.pitt.msnl.aware.ui.results.ResultsViewModel;

public class ResultsFragment extends Fragment {

    private static final int PERMISSION_REQUEST_CODE = 1;
    private static final int SAMPLE_RATE = 48000;
    private static final int MAX_TRIAL = 5;
    private static final int[] TRIAL_BUTTON_ID =
            {R.id.trial_1,R.id.trial_2,R.id.trial_3,R.id.trial_4,R.id.trial_5};
    private static final int[][] CURVE_COLOR =
            {{Color.rgb(153,0,0), Color.rgb(204,0,0), Color.rgb(255,0,0)},
            {Color.rgb(0,0,153), Color.rgb(0,0,204), Color.rgb(0,0,255)},
            {Color.rgb(0,153,0), Color.rgb(0,204,0), Color.rgb(0,255,0)},
            {Color.rgb(255,128,0), Color.rgb(255,153,0), Color.rgb(255,204,0)},
            {Color.rgb(102,0,102), Color.rgb(153,0,153), Color.rgb(204,204,204)},};

    private static final String LOG_TAG = "ViewResults";

    private Thread th;
    private boolean stopThread = false;
    double[] score_inhale = new double[3];
    double[] score_exhale = new double[3];

    private ResultsViewModel mViewModel;

    public static ResultsFragment newInstance() {
        return new ResultsFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.results_fragment, container, false);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(ResultsViewModel.class);

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

        // Initialize spinner
        setSpinner(R.id.fc_selection, R.array.fc_array, 5);
        setSpinner(R.id.graph_selection, R.array.graph_array, 2);

        Spinner s = getActivity().findViewById(R.id.graph_selection);
        s.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parentView, View selectedItemView, int position, long id) {
                if (position == 0) {
                    getActivity().findViewById(R.id.graph_results_1).setVisibility(View.VISIBLE);
                    getActivity().findViewById(R.id.graph_results_2).setVisibility(View.INVISIBLE);
                    getActivity().findViewById(R.id.graph_results_3).setVisibility(View.INVISIBLE);
                    ImageView img = getActivity().findViewById(R.id.graph_reference);
                    img.setImageResource(R.drawable.reference_nasal);

                    String str = "N/A";
                    TextView text_score = getActivity().findViewById(R.id.text_score);
                    text_score.setText(str);
                    text_score.setTextColor(Color.rgb(0,0,0));
                }
                else if (position == 1) {
                    getActivity().findViewById(R.id.graph_results_1).setVisibility(View.INVISIBLE);
                    getActivity().findViewById(R.id.graph_results_2).setVisibility(View.VISIBLE);
                    getActivity().findViewById(R.id.graph_results_3).setVisibility(View.INVISIBLE);
                    ImageView img = getActivity().findViewById(R.id.graph_reference);
                    img.setImageResource(R.drawable.reference_exhale);

                    TextView text_score = getActivity().findViewById(R.id.text_score);
                    int score_ave = (int)myUtil.mean(score_inhale);
                    int score_max = (int)myUtil.max(score_inhale);
                    String str = score_ave + " / " + score_max;
                    text_score.setText(str);
                    if (score_max > 80) {
                        text_score.setTextColor(CURVE_COLOR[2][1]);
                    } else if (score_max > 60) {
                        text_score.setTextColor(CURVE_COLOR[3][1]);
                    } else {
                        text_score.setTextColor(CURVE_COLOR[0][1]);
                    }
                }
                else if (position == 2) {
                    getActivity().findViewById(R.id.graph_results_1).setVisibility(View.INVISIBLE);
                    getActivity().findViewById(R.id.graph_results_2).setVisibility(View.INVISIBLE);
                    getActivity().findViewById(R.id.graph_results_3).setVisibility(View.VISIBLE);
                    ImageView img = getActivity().findViewById(R.id.graph_reference);
                    img.setImageResource(R.drawable.reference_exhale);

                    TextView text_score = getActivity().findViewById(R.id.text_score);
                    int score_ave = (int)myUtil.mean(score_exhale);
                    int score_max = (int)myUtil.max(score_exhale);
                    String str = score_ave + " / " + score_max;
                    text_score.setText(str);
                    if (score_max > 80) {
                        text_score.setTextColor(CURVE_COLOR[2][1]);
                    } else if (score_max > 60) {
                        text_score.setTextColor(CURVE_COLOR[3][1]);
                    } else {
                        text_score.setTextColor(CURVE_COLOR[0][1]);
                    }
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parentView) {
                return;
            }
        });

        // Initialize START buttion
        Button start = getActivity().findViewById(R.id.start_processing_button);
        start.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Button start = getActivity().findViewById(R.id.start_processing_button);
                start.setClickable(false);
                if (!permissionGranted()) {
                    start.setClickable(true);
                }
                else {
                    GraphView graph1 = getActivity().findViewById(R.id.graph_results_1);
                    graph1.removeAllSeries();
                    GraphView graph2 = getActivity().findViewById(R.id.graph_results_2);
                    graph2.removeAllSeries();
                    start.setVisibility(View.INVISIBLE);
                    start.setClickable(true);
                    getActivity().findViewById(R.id.text_fc_selection).setVisibility(View.INVISIBLE);
                    getActivity().findViewById(R.id.fc_selection).setVisibility(View.INVISIBLE);
                    stopThread = false;
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            processData();
                        }
                    }).start();
                }
            }
        });

        // Start processing immediately (by default)
        start.setVisibility(View.INVISIBLE);
        start.setClickable(true);
        getActivity().findViewById(R.id.text_fc_selection).setVisibility(View.INVISIBLE);
        getActivity().findViewById(R.id.fc_selection).setVisibility(View.INVISIBLE);
        stopThread = false;
        new Thread(new Runnable() {
            @Override
            public void run() {
                processData();
            }
        }).start();

    }

    @Override
    public void onStop() {
        stopThread = true;
        super.onStop();
    }

    public void processData() {
        if (stopThread) {return;}
        GraphView graph1 = getActivity().findViewById(R.id.graph_results_1);
        graph1.removeAllSeries();
        GraphView graph2 = getActivity().findViewById(R.id.graph_results_2);
        graph2.removeAllSeries();
        GraphView graph3 = getActivity().findViewById(R.id.graph_results_3);
        graph3.removeAllSeries();

        TextView text = getActivity().findViewById(R.id.text_results);
        text.setText("Loading data...");
        TextView text_score = getActivity().findViewById(R.id.text_score);
        text_score.setVisibility(View.VISIBLE);
        Log.i(LOG_TAG, "Start processing data");
        short[] buffer = new short[SAMPLE_RATE*40];
        short[] cali1 = new short[264000];
        short[] cali2 = new short[264000];
        short[] cali3 = new short[264000];
        short[] test = new short[273600];
        File dir = getActivity().getExternalCacheDir();
        File precali_file = new File(dir, "precali.pcm");
        Log.i(LOG_TAG,"Reading File precali.pcm");
        try {
            FileInputStream fis = new FileInputStream(precali_file);
            DataInputStream dis = new DataInputStream(new BufferedInputStream(fis));
            for (int i = 0; dis.available() > 0; i++) {
                buffer[i] = dis.readShort();
            }
            for (int i = 0; i < 264000; i++) {
                cali1[i] = buffer[i];
            }
            dis.close();
        } catch (IOException e) {
            Log.e(LOG_TAG, "File read failed: " + e.toString());
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Alert")
                            .setMessage("Failed to read pre-calibration file")
                            .setNeutralButton("OK", null).show();
                }
            });
            return;
        }

        if (stopThread) {return;}
        File cali_file = new File(dir, "cali.pcm");
        Log.i(LOG_TAG,"Reading File cali.pcm");
        try {
            FileInputStream fis = new FileInputStream(cali_file);
            DataInputStream dis = new DataInputStream(new BufferedInputStream(fis));
            for (int i = 0; dis.available() > 0; i++) {
                buffer[i] = dis.readShort();
            }
            for (int i = 0; i < 264000; i++) {
                cali2[i] = buffer[i];
            }
            for (int i = 0; i < 264000; i++) {
                cali3[i] = buffer[i+288000];
            }
            dis.close();
        } catch (IOException e) {
            Log.e(LOG_TAG, "File read failed: " + e.toString());
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    new AlertDialog.Builder(getActivity())
                            .setTitle("Alert")
                            .setMessage("Failed to read calibration file")
                            .setNeutralButton("OK", null).show();
                }
            });
            return;
        }

        double gamma = 1e-3;
        double ls = 40;

        if (stopThread) {return;}
        Spinner s = getActivity().findViewById(R.id.fc_selection);
        double fc = Double.valueOf(s.getSelectedItem().toString());
        Log.i(LOG_TAG, "Cut-off frequency selected: "+fc);

        Bundle arg = getArguments();
        int n = 0;
        for (int i = 0; i < MAX_TRIAL; i++) {
            if (stopThread) {return;}
            if (arg != null && arg.getInt("which_trial") != i+1) {continue;}
            ToggleButton toggle = getActivity().findViewById(TRIAL_BUTTON_ID[i]);
            File file = new File(dir, "trial_"+String.valueOf(i+1)+".pcm");
            if (file.exists() && toggle.isChecked()) {
                try {
                    n = n+1;
                    Log.i(LOG_TAG,"Reading File "+"trial_"+String.valueOf(i+1)+".pcm");
                    FileInputStream fis = new FileInputStream(file);
                    DataInputStream dis = new DataInputStream(new BufferedInputStream(fis));

                    /*dis.skipBytes(21*SAMPLE_RATE);*/
                    test = new short[273600];
                    for (int k = 0; k < 273600; k++) {
                        test[k] = dis.readShort();
                    }
                    dis.skipBytes(21*SAMPLE_RATE-273600*2);
                    text.setText("Processing...");
                    double[] A = new double[194];
                    double[] ho = new double[194];
                    //double[] tmp = new double[264000];
                    myCppLib.DataProcessingFromJni(
                            cali1, cali2, cali3, test, gamma, ls, fc, A, ho); // tmp is for debugging
                    if (stopThread) {dis.close(); return;}
                    text.setText("Drawing...");
                    displayResults(A, R.id.graph_results_1, CURVE_COLOR[n][0],
                            "trial "+(i+1));
                    text.setText("Loading data...");

                    int test_size = dis.available()/2;
                    for (int j = 0; j < 6; j++) {
                        test = new short[273600];
                        for (int k = 0; k < 273600; k++) {
                            test[k] = dis.readShort();
                        }
                        dis.skipBytes((test_size/6-273600)*2);
                        if (j == 0 || j == 2 || j == 4) {
                            text.setText("Processing...");
                            A = new double[194];
                            ho = new double[194];
                            //tmp = new double[264000];
                            score_inhale[j/2] = myCppLib.DataProcessingFromJni(
                                    cali1, cali2, cali3, test, gamma, ls, fc, A, ho); // tmp is for debugging
                            if (stopThread) {dis.close(); return;}
                            text.setText("Drawing...");
                            displayResults(A, R.id.graph_results_2, CURVE_COLOR[n][j/2],
                                    "trial "+(i+1)+"_"+(j/2+1));
                            text.setText("Loading data...");
                        }
                        if (j == 1 || j == 3 || j == 5) {
                            text.setText("Processing...");
                            A = new double[194];
                            ho = new double[194];
                            //tmp = new double[264000];
                            score_exhale[j/2] = myCppLib.DataProcessingFromJni(
                                    cali1, cali2, cali3, test, gamma, ls, fc, A, ho); // tmp is for debugging
                            if (stopThread) {dis.close(); return;}
                            text.setText("Drawing...");
                            displayResults(A, R.id.graph_results_3, CURVE_COLOR[n][j/2],
                                    "trial "+(i+1)+"_"+(j/2+1));
                            text.setText("Loading data...");
                        }
                    }
                    dis.close();

                    // Display similarity score between results and reference curve
                    Spinner s_g = getActivity().findViewById(R.id.graph_selection);
                    if (s_g.getSelectedItem().toString().equals("Inhale")) {
                        int score_ave = (int)myUtil.mean(score_inhale);
                        int score_max = (int)myUtil.max(score_inhale);
                        String str = score_ave + " / " + score_max;
                        text_score.setText(str);
                        if (score_max > 80) {
                            text_score.setTextColor(CURVE_COLOR[2][1]);
                        } else if (score_max > 60) {
                            text_score.setTextColor(CURVE_COLOR[3][1]);
                        } else {
                            text_score.setTextColor(CURVE_COLOR[0][1]);
                        }
                    }
                    else if (s_g.getSelectedItem().toString().equals("Exhale")) {
                        int score_ave = (int)myUtil.mean(score_exhale);
                        int score_max = (int)myUtil.max(score_exhale);
                        String str = score_ave + " / " + score_max;
                        text_score.setText(str);
                        if (score_max > 80) {
                            text_score.setTextColor(CURVE_COLOR[2][1]);
                        } else if (score_max > 60) {
                            text_score.setTextColor(CURVE_COLOR[3][1]);
                        } else {
                            text_score.setTextColor(CURVE_COLOR[0][1]);
                        }
                    }

                } catch (Exception e) {
                    Log.e(LOG_TAG, "Trial processing failed: " + e.toString());

                    Writer writer = new StringWriter();
                    e.printStackTrace(new PrintWriter(writer));
                    writeLog(writer.toString());

                    getActivity().runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            new AlertDialog.Builder(getActivity())
                                    .setTitle("Alert")
                                    .setMessage("Trial processing failed")
                                    .setNeutralButton("OK", null).show();
                        }
                    });
                }
            }
        }

        text.setText("");
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                getActivity().findViewById(R.id.start_processing_button).setVisibility(View.VISIBLE);
                getActivity().findViewById(R.id.text_fc_selection).setVisibility(View.VISIBLE);
                getActivity().findViewById(R.id.fc_selection).setVisibility(View.VISIBLE);
            }
        });

    }

    public void displayResults(double[] results, int graph_id, int color, String legend) {
        Log.i(LOG_TAG,"Get ready to display results");
        GraphView graph = getActivity().findViewById(graph_id);
        graph.getViewport().setXAxisBoundsManual(true);
        graph.getViewport().setYAxisBoundsManual(true);
        graph.getViewport().setScalable(true);
        graph.getViewport().setScalableY(true);

        ArrayList<DataPoint> list = new ArrayList<>();
        for (int i = 0; i < results.length; i++) {
            list.add(new DataPoint((double)list.size()/SAMPLE_RATE*34600/2-10, results[i]));
        }
        DataPoint[] points = list.toArray(new DataPoint[0]);
        LineGraphSeries<DataPoint> series = new LineGraphSeries<>(points);

        /*Paint paint = new Paint();
        paint.setStyle(Paint.Style.STROKE);
        paint.setStrokeWidth(10);
        paint.setPathEffect(new DashPathEffect(new float[]{8, 5}, 0));*/
        series.setColor(color);
        series.setTitle(legend);

        graph.getLegendRenderer().setVisible(true);
        graph.getLegendRenderer().setAlign(LegendRenderer.LegendAlign.TOP);
        graph.getLegendRenderer().setTextSize(28f);
        graph.getLegendRenderer().setBackgroundColor(Color.TRANSPARENT);
        graph.getViewport().setMinX(0);
        graph.getViewport().setMaxX(40);
        graph.getViewport().setMinY(0);
        graph.getViewport().setMaxY(10);
        graph.addSeries(series);

    }

    public void displayResults(short[] results, int graph_id, int color, String legend) {
        GraphView graph = getActivity().findViewById(graph_id);
        graph.getViewport().setXAxisBoundsManual(true);
        graph.getViewport().setYAxisBoundsManual(true);
        graph.getViewport().setScalable(true);
        graph.getViewport().setScalableY(true);

        ArrayList<DataPoint> list = new ArrayList<>();
        for (int i = 0; i < results.length; i++) {
            list.add(new DataPoint(i, results[i]));
        }
        DataPoint[] points = list.toArray(new DataPoint[0]);
        LineGraphSeries<DataPoint> series = new LineGraphSeries<>(points);

        /*Paint paint = new Paint();
        paint.setStyle(Paint.Style.STROKE);
        paint.setStrokeWidth(10);
        paint.setPathEffect(new DashPathEffect(new float[]{8, 5}, 0));*/
        series.setColor(color);
        series.setTitle(legend);

        graph.getLegendRenderer().setVisible(true);
        graph.getLegendRenderer().setAlign(LegendRenderer.LegendAlign.TOP);
        graph.getLegendRenderer().setTextSize(28f);
        graph.getLegendRenderer().setBackgroundColor(Color.TRANSPARENT);
        /*graph.getViewport().setMinX(0);
        graph.getViewport().setMaxX(40);
        graph.getViewport().setMinY(0);
        graph.getViewport().setMaxY(10);*/
        graph.addSeries(series);

    }

    private void setSpinner(int spinner_id, int content_id, int default_selection) {
        Spinner s = getActivity().findViewById(spinner_id);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(getActivity(),
                content_id, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        s.setAdapter(adapter);
        s.setSelection(default_selection);
    }

    private void writeLog(String str) {
        File dir = getActivity().getExternalCacheDir();
        if (dir.mkdirs()) {
            Log.i(LOG_TAG, "New directory created");
        }
        File file = new File(dir, "log.txt");
        if (file.exists()) {
            if (!file.delete()) {
                Log.e(LOG_TAG, "Failed to delete existing cache file");
            }
        }
        try {
            if (file.createNewFile()) {
                Log.i(LOG_TAG, "New cache file created successfully");
            }
            DataOutputStream dos = new DataOutputStream(new FileOutputStream(file));
            dos.writeChars(str);
        }
        catch (Exception e) {
            Log.e(LOG_TAG, "Failed to write log to file: " + e.toString());
        }
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
