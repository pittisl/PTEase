package edu.pitt.msnl.aware;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.util.Arrays;

public class myUtil {
    public static void writeStringToFile (File file, String str) {
        try {
            OutputStream os = new FileOutputStream(file);
            OutputStreamWriter outputStreamWriter = new OutputStreamWriter(os);
            outputStreamWriter.write(str);
            outputStreamWriter.close();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String arrayToString(int[] arr) {
        return Arrays.toString(arr).replaceAll("\\[|\\]|\\s", "");
    }

    public static short[] repeatData (short[] data, int times) {
        short[] data_repeated = new short[data.length * times];
        for(int i = 0; i < data_repeated.length; i++) {
            data_repeated[i] = data[i % data.length];
        }
        return data_repeated;
    }

    public static int findMax(short[] arr) { // return the position of max value in an array
        int max_idx = 0;
        for(int i = 1; i < arr.length; i++) {
            if(arr[i] > arr[max_idx]) {
                max_idx = i;
            }
        }
        return max_idx;
    }

    public static int findMax(double[] arr) { // return the position of max value in an array
        int max_idx = 0;
        for(int i = 1; i < arr.length; i++) {
            if(arr[i] > arr[max_idx]) {
                max_idx = i;
            }
        }
        return max_idx;
    }

    public static double max(double[] arr) { // return the max value of a positive array
        double max = 0;
        for(int i = 0; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }
        return max;
    }

    public static double mean(double[] arr) { // return the mean value of an array
        double sum = 0;
        for(int i = 0; i < arr.length; i++) {
            sum += arr[i];
        }
        return sum/arr.length;
    }
}
