//
// Created by Eric on 2/2/2020.
// Recently updated on 2/11/2022
//
#include <android/log.h>
#include <jni.h>
#include <string>
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "aware_types.h"
#include "aware.h"
#include "aware_emxAPI.h"
#include "rt_nonfinite.h"

extern "C" JNIEXPORT jdouble JNICALL
Java_edu_pitt_msnl_aware_myCppLib_DataProcessingFromJni(
        JNIEnv *env,
        jobject /* this */,
        jshortArray input_cali1_raw,
        jshortArray input_cali2_raw,
        jshortArray input_cali3_raw,
        jshortArray input_test_raw,
        jdouble gamma,
        jdouble ls,
        jdouble fc,
        jdoubleArray output_A,
        jdoubleArray output_ho) {

    emxArray_real_T *A;
    emxArray_real_T *ho;
    static double cali1_raw[264000];
    static double cali2_raw[264000];
    static double cali3_raw[264000];
    static double test_raw[273600];
    double score;
    emxInitArray_real_T(&A, 1);
    emxInitArray_real_T(&ho, 1);
    /* Initialize function 'single_calc' input arguments. */

    /* Initialize function input argument 'cali1_raw'. */
    // Convert JNI data type (jArray) to MATLAB-C data type (emxArray)

    int cali1_len = env->GetArrayLength(input_cali1_raw);
    jshort *cali1_buff = env->GetShortArrayElements(input_cali1_raw, 0); // Get local copy of array elements
    for (int i = 0; i < cali1_len; i++) {
        cali1_raw[i] = (double)cali1_buff[i]/32768;
    }
    env->ReleaseShortArrayElements(input_cali1_raw, cali1_buff, 0); // Delete local copy of array elements
    /* Initialize function input argument 'cali2_raw'. */
    jsize cali2_len = env->GetArrayLength(input_cali2_raw);
    jshort *cali2_buff = env->GetShortArrayElements(input_cali2_raw, 0); // Get local copy of array elements
    for (int i = 0; i < cali2_len; i++) {
        cali2_raw[i] = (double)cali2_buff[i]/32768;
    }
    env->ReleaseShortArrayElements(input_cali2_raw, cali2_buff, 0); // Delete local copy of array elements

    /* Initialize function input argument 'cali3_raw'. */
    jsize cali3_len = env->GetArrayLength(input_cali3_raw);
    jshort *cali3_buff = env->GetShortArrayElements(input_cali3_raw, 0); // Get local copy of array elements
    for (int i = 0; i < cali3_len; i++) {
        cali3_raw[i] = (double)cali3_buff[i]/32768;
    }
    env->ReleaseShortArrayElements(input_cali3_raw, cali3_buff, 0); // Delete local copy of array elements

    /* Initialize function input argument 'test_raw'. */
    jsize test_len = env->GetArrayLength(input_test_raw);
    jshort *test_buff = env->GetShortArrayElements(input_test_raw, 0); // Get local copy of array elements
    for (int i = 0; i < test_len; i++) {
        test_raw[i] = (double)test_buff[i]/32768;
    }
    env->ReleaseShortArrayElements(input_test_raw, test_buff, 0); // Delete local copy of array elements

    /* Call the entry-point 'single_calc'. */
    single_calc(cali1_raw, cali2_raw, cali3_raw, test_raw, gamma,
                ls, fc, A, ho, &score);

    // Convert MATLAB-C result to JNI
    int A_len = *(A->size);
    jdouble *A_buff = env->GetDoubleArrayElements(output_A, 0);
    for (int i = 0; i < A_len; i++) {
        A_buff[i] = A->data[i];
    }
    env->SetDoubleArrayRegion(output_A, 0, A_len, A_buff);
    env->ReleaseDoubleArrayElements(output_A, A_buff, 0); // Delete local copy of array elements

    int ho_len = *(ho->size);
    jdouble *ho_buff = env->GetDoubleArrayElements(output_ho, 0);
    for (int i = 0; i < ho_len; i++) {
        ho_buff[i] = ho->data[i];
    }
    env->SetDoubleArrayRegion(output_ho, 0, ho_len, ho_buff);
    env->ReleaseDoubleArrayElements(output_ho, ho_buff, 0); // Delete local copy of array elements

    /*int tmp_len = cali1_len;
    jdouble *tmp_buff = env->GetDoubleArrayElements(output_tmp, 0);
    for (int i = 0; i < tmp_len; i++) {
        tmp_buff[i] = test_raw[i];
    }
    env->SetDoubleArrayRegion(output_tmp, 0, tmp_len, tmp_buff);
    env->ReleaseDoubleArrayElements(output_tmp, tmp_buff, 0); // Delete local copy of array elements*/

    emxDestroyArray_real_T(ho);
    emxDestroyArray_real_T(A);

    aware_terminate();

    return score;
}


extern "C" JNIEXPORT void JNICALL
Java_edu_pitt_msnl_aware_myCppLib_GetNoiseLevelFromJni(
        JNIEnv *env,
        jobject /* this */,
        jshortArray input_cali1_raw,
        jshortArray input_test_raw,
        jdoubleArray output_noise) {

    static double cali1_raw[264000];
    static double test_raw[2160000];
    static double noise[2160000];
    /* Initialize function 'single_calc' input arguments. */

    /* Initialize function input argument 'cali1_raw'. */
    int cali1_len = env->GetArrayLength(input_cali1_raw);
    jshort *cali1_buff = env->GetShortArrayElements(input_cali1_raw, 0); // Get local copy of array elements
    for (int i = 0; i < cali1_len; i++) {
        cali1_raw[i] = (double)cali1_buff[i]/32768;
    }
    env->ReleaseShortArrayElements(input_cali1_raw, cali1_buff, 0); // Delete local copy of array elements

    /* Initialize function input argument 'test_raw'. */
    jsize test_len = env->GetArrayLength(input_test_raw);
    jshort *test_buff = env->GetShortArrayElements(input_test_raw, 0); // Get local copy of array elements
    for (int i = 0; i < test_len; i++) {
        test_raw[i] = (double)test_buff[i]/32768;
    }
    env->ReleaseShortArrayElements(input_test_raw, test_buff, 0); // Delete local copy of array elements

    /* Call the entry-point 'single_calc'. */
    get_noise(cali1_raw, test_raw, noise);

    // Convert MATLAB-C result to JNI

    int noise_len = test_len;
    jdouble *noise_buff = env->GetDoubleArrayElements(output_noise, 0);
    for (int i = 0; i < noise_len; i++) {
        noise_buff[i] = noise[i];
    }
    env->SetDoubleArrayRegion(output_noise, 0, noise_len, noise_buff);
    env->ReleaseDoubleArrayElements(output_noise, noise_buff, 0); // Delete local copy of array elements

    aware_terminate();
}
