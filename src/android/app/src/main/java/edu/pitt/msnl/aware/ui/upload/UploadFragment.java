package edu.pitt.msnl.aware.ui.upload;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.lifecycle.ViewModelProviders;

import android.content.DialogInterface;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.provider.Settings;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.RadioGroup;
import android.widget.Spinner;
import android.widget.ToggleButton;

import com.google.android.material.snackbar.Snackbar;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.concurrent.TimeUnit;

import edu.pitt.msnl.aware.CountingRequestBody;
import edu.pitt.msnl.aware.R;
import edu.pitt.msnl.aware.ui.testing.TestingFragment;
import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.MediaType;
import okhttp3.MultipartBody;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;

public class UploadFragment extends Fragment {

    private static final int MAX_TRIAL = 5;
    private static final int[] TRIAL_BUTTON_ID =
            {R.id.trial_1,R.id.trial_2,R.id.trial_3,R.id.trial_4,R.id.trial_5};
    private static final String SERVER_URL =
            "https://soundster.hosiet.me/soundster/api/site/aware/doupload";
    private static final String PROCESSING_URL =
            "https://soundster.hosiet.me/soundster/api/site/aware/dobatchprocess";
    private static final MediaType MEDIA_TYPE_JSON =
            MediaType.parse("application/json; charset=utf-8");
    private static final MediaType MEDIA_TYPE_BINARY =
            MediaType.parse("application/octet-stream");

    private UploadViewModel mViewModel;
    private long total_size = 0;
    private long uploaded_size = 0;

    public static UploadFragment newInstance() {
        return new UploadFragment();
    }

    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.upload_fragment, container, false);
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        mViewModel = ViewModelProviders.of(this).get(UploadViewModel.class);

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

        // Add spinner content
        setSpinner(R.id.info_ethnicity, R.array.ethnicity_array);
        setSpinner(R.id.info_height_unit, R.array.height_array);
        setSpinner(R.id.info_weight_unit, R.array.weight_array);

        // Set Listener for Upload Button
        Button upload = getActivity().findViewById(R.id.confirm_upload_button);
        upload.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                new AlertDialog.Builder(getActivity())
                        .setTitle("Confirmation")
                        .setMessage("Are you sure you want to upload?")
                        .setPositiveButton("YES", new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int whichButton) {
                                try {
                                    uploadFile();
                                } catch(IOException e) {
                                    Log.e("Error", "Upload Failed： "+e.getLocalizedMessage());
                                }
                            }})
                        .setNegativeButton("NO", null).show();
            }
        });
    }

    private void setSpinner(int spinner_id, int content_id) {
        Spinner s = getActivity().findViewById(spinner_id);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(getActivity(),
                content_id, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        s.setAdapter(adapter);
    }

    private void uploadFile() throws IOException {
        OkHttpClient client = new OkHttpClient.Builder()
                .readTimeout(30, TimeUnit.SECONDS)
                .build();

        getActivity().findViewById(R.id.confirm_upload_button).setClickable(false);

        // Get all subject info
        EditText et_name = getActivity().findViewById(R.id.info_name);
        EditText et_age = getActivity().findViewById(R.id.info_age);
        EditText et_height = getActivity().findViewById(R.id.info_height);
        Spinner s_height = getActivity().findViewById(R.id.info_height_unit);
        EditText et_weight = getActivity().findViewById(R.id.info_weight);
        Spinner s_weight = getActivity().findViewById(R.id.info_weight_unit);
        EditText et_remark = getActivity().findViewById(R.id.info_remark);
        Spinner s_ethnicity = getActivity().findViewById(R.id.info_ethnicity);
        RadioGroup rg_gender = getActivity().findViewById(R.id.info_gender);
        RadioGroup rg_chronic = getActivity().findViewById(R.id.info_chronic);
        EditText et_chronic = getActivity().findViewById(R.id.info_chronic_detail);
        String info_gender = "";
        if (rg_gender.getCheckedRadioButtonId() == R.id.info_gender_male)
            info_gender = "male";
        else if (rg_gender.getCheckedRadioButtonId() == R.id.info_gender_female)
            info_gender = "female";
        String info_chronic = "";
        if (rg_chronic.getCheckedRadioButtonId() == R.id.info_chronic_yes)
            info_chronic = "yes:" + strToUrl(et_chronic.getText().toString());
        else if (rg_chronic.getCheckedRadioButtonId() == R.id.info_chronic_no)
            info_chronic = "no";
        Date currentTime = Calendar.getInstance().getTime();
        String android_id = Settings.Secure.getString(getActivity().getContentResolver(), Settings.Secure.ANDROID_ID);
        String full_info = "\"" + strToUrl(et_name.getText().toString()) + ","
                + info_gender + ","
                + strToUrl(et_age.getText().toString()) + ","
                + s_ethnicity.getSelectedItem().toString() + ","
                + strToUrl(et_height.getText().toString()) + s_height.getSelectedItem().toString() + ","
                + strToUrl(et_weight.getText().toString()) + s_weight.getSelectedItem().toString() + ","
                + info_chronic + ","
                + strToUrl(et_remark.getText().toString()) + ","
                + currentTime.toString() + ","
                + android_id + "\"";

        // Get current timestamp
        String ts = String.valueOf(System.currentTimeMillis()/1000);

        // Combine information into json
        String json =
                "{\"FULLINFO\":" + full_info + ","
                        + "\"TIMESTAMP\":" + ts + "}";
        Log.d("UPLOAD","json: "+json);

        // Create http request using okhttp3
        MultipartBody.Builder builder = new MultipartBody.Builder();
        builder.setType(MultipartBody.FORM);

        RequestBody mInfo = RequestBody.create(MEDIA_TYPE_JSON, json);
        builder.addFormDataPart("metadata","metadata",mInfo);

        // Upload files
        File dir = getActivity().getExternalCacheDir();
        /*// Read offset from file as string
        File offset_file_cali = new File(dir, "cali_offset");
        if (!offset_file_cali.exists()) {
            Snackbar.make(getActivity().findViewById(R.id.MainLayout),
                    "Upload failed: No Calibration Offset Information",
                    Snackbar.LENGTH_LONG).show();
            return;
        }
        File offset_file_trial = new File(dir, "trial_offset");
        if (!offset_file_trial.exists()) {
            Snackbar.make(getActivity().findViewById(R.id.MainLayout),
                    "Upload failed: No Trail Offset Information",
                    Snackbar.LENGTH_LONG).show();
            return;
        }
        String offset = "\""+readStringFromFile(offset_file_cali)
                +","+readStringFromFile(offset_file_trial)+"\"";*/

        File cali_file = new File(dir, "cali.pcm");
        uploaded_size = 0;
        if (cali_file.exists()) {
            total_size = cali_file.length();
            CountingRequestBody mFile = new CountingRequestBody(
                    cali_file,
                    "application/octet-stream",
                    new CountingRequestBody.ProgressListener() {
                        @Override
                        public void transferred(long num) {
                            uploaded_size += num;
                            long pct = uploaded_size*100/total_size;
                            ProgressBar pb = getActivity().findViewById(R.id.upload_progress);
                            pb.setProgress((int)pct);
                        }
                    });
            builder.addFormDataPart("realdata",cali_file.getName(),mFile);
        }
        for (int i = 0; i < MAX_TRIAL; i++) {
            ToggleButton toggle = getActivity().findViewById(TRIAL_BUTTON_ID[i]);
            File file = new File(dir, "trial_"+String.valueOf(i+1)+".pcm");
            if (file.exists() && toggle.isChecked()) {
                total_size += file.length();
                CountingRequestBody mFile = new CountingRequestBody(
                        file,
                        "application/octet-stream",
                        new CountingRequestBody.ProgressListener() {
                            @Override
                            public void transferred(long num) {
                                uploaded_size += num;
                                long pct = uploaded_size*100/total_size;
                                ProgressBar pb = getActivity().findViewById(R.id.upload_progress);
                                pb.setProgress((int)pct);
                                if (pct == 100) {
                                    getActivity().runOnUiThread(new Runnable() {
                                        @Override
                                        public void run() {
                                            new AlertDialog.Builder(getActivity())
                                                    .setMessage("Upload Succeeded")
                                                    .setNeutralButton("OK", null).show();
                                        }
                                    });

                                    /*Snackbar.make(getActivity().findViewById(R.id.MainLayout),
                                            "Upload Succeeded",
                                            Snackbar.LENGTH_LONG).show();*/
                                }
                            }
                        });
                builder.addFormDataPart("realdata",file.getName(),mFile);
            }
        }

        // Commit request
        MultipartBody body = builder.build();
        Request request = new Request.Builder()
                .url(SERVER_URL)
                .post(body)
                .build();

        /*Snackbar.make(getActivity().findViewById(R.id.MainLayout),
                "Uploading...",
                Snackbar.LENGTH_INDEFINITE).show();*/

        ProgressBar pb = getActivity().findViewById(R.id.upload_progress);
        pb.setVisibility(View.VISIBLE);
        pb.setProgress(0);

        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(final Call call, final IOException e) {
                // Handle the error
                /*Snackbar.make(getActivity().findViewById(R.id.MainLayout),
                        "Upload Failed: Timeout",
                        Snackbar.LENGTH_LONG).show();*/
                Log.e("UPLOAD", e.toString());
                getActivity().findViewById(R.id.confirm_upload_button).setClickable(true);
            }

            @Override
            public void onResponse(final Call call, final Response response) throws IOException {
                if (!response.isSuccessful()) {
                    new AlertDialog.Builder(getActivity())
                            .setMessage("Upload Failed: Incorrect Input Format")
                            .setNeutralButton("OK", null).show();
                    /*Snackbar.make(getActivity().findViewById(R.id.MainLayout),
                            "Upload Failed: Incorrect Input Format",
                            Snackbar.LENGTH_LONG).show();*/
                }
                else {
                   /* Snackbar.make(getActivity().findViewById(R.id.MainLayout),
                            "Upload Succeeded",
                            Snackbar.LENGTH_LONG).show();*/
                }
                // This is problematic, could cause crash if press back button while uploading
                //getActivity().findViewById(R.id.confirm_upload_button).setClickable(true);
            }
        });

        /*Request proc_request = new Request.Builder()
                .url(PROCESSING_URL)
                .get()
                .build();

        client.newCall(proc_request).enqueue(new Callback() {
            @Override
            public void onFailure(Call call, IOException e) {
                Log.d("UPLOAD", "onFailure: " + e.toString());
            }

            @Override
            public void onResponse(Call call, Response response) throws IOException {
                Log.d("UPLOAD", "onResponse: " + response.body().string());
            }
        });*/
    }

    private void combineFiles() {
        /*// Copy calibration file to head of cache file, so only need to upload one file at one time
        File cali_file = new File(getActivity().getExternalCacheDir(),"cali.pcm");
        if (!cali_file.exists()) {
            new AlertDialog.Builder(getActivity())
                    .setTitle("Attention")
                    .setMessage("Please calibrate first")
                    .setNeutralButton("OK", null).show();
            return;
        }
        try{
            DataInputStream dis = new DataInputStream(new FileInputStream(cali_file));
            byte[] buf = new byte[1024];
            int len = dis.read(buf);
            while(len != -1) {
                dos.write(buf,0, len);
                len = dis.read(buf);
            }
            dis.close();
        } catch(IOException e) {
            Log.e(LOG_TAG, "DataInputStream Creation Failed");
        }*/
    }

    private static String readStringFromFile(File file) {
        String ret = "";
        try{
            InputStream inputStream = new FileInputStream(file);
            InputStreamReader inputStreamReader = new InputStreamReader(inputStream);
            BufferedReader bufferedReader = new BufferedReader(inputStreamReader);
            String receiveString = "";
            StringBuilder stringBuilder = new StringBuilder();

            while ( (receiveString = bufferedReader.readLine()) != null ) {
                stringBuilder.append(receiveString);
            }

            inputStream.close();
            ret = stringBuilder.toString();
        } catch(IOException e) {
            Log.e("UPLOAD", "Read Offset File Failed");
        }
        return ret;
    }

    private static String strToUrl(String str) {
        String url = "";
        try {
            url = URLEncoder.encode(str, "UTF-8");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return url;
    }
}
