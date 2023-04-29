package edu.pitt.msnl.aware;

import android.util.Log;

import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOError;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class myWavFile {

    private static final String LOG_TAG = "WavFileUtils";
    private static final int HEADER_LEN = 44;
    /*
    public String chunkId = "RIFF";
    public int chunkSize;
    public String fccType = "WAVE";
    public String subChunkId1 = "fmt ";
    public int subChunkSize1 = 16;
    public short formatTag = 1;
    public short channels;
    public int sampleRate;
    public int byteRate;
    public short blockAlign;
    public short sampleBits;
    public String subChunkId2 = "data";
    public int subChunkSize2;
    */
    public int dataSizeInBytes;
    public short[] data;

    public myWavFile(InputStream iStream) {
        try {
            DataInputStream dis = new DataInputStream(iStream);
            dis.skipBytes(HEADER_LEN);              // Skip .wav header
            dataSizeInBytes = dis.available();
            byte[] buffer = new byte[dataSizeInBytes];
            dis.read(buffer);

            ByteBuffer bb = ByteBuffer.wrap(buffer);
            bb.order(ByteOrder.LITTLE_ENDIAN);
            data = new short[dataSizeInBytes/2];
            for (int i = 0; i < data.length; i++) {
                data[i] = bb.getShort();
            }

        } catch (FileNotFoundException e) {
            Log.e(LOG_TAG,"File not found");
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
