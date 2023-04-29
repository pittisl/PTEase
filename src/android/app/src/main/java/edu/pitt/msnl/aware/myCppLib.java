package edu.pitt.msnl.aware;

public class myCppLib {
    static {
        System.loadLibrary("native-lib");
    }

    public static native double DataProcessingFromJni(
            short[] cali1, short[] cali12, short[] cali13, short[] test,
            double gamma, double ls, double fc, double[] A, double[] ho);

    public static native void GetNoiseLevelFromJni(
            short[] cali1, short[] test, double[] noise);
}
