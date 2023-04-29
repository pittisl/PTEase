/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * aware.h
 *
 * Code generation for function 'aware'
 *
 */

#ifndef AWARE_H
#define AWARE_H

/* Include files */
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "aware_types.h"

/* Variable Declarations */
extern omp_nest_lock_t emlrtNestLockGlobal;

/* Function Declarations */
extern void aware_initialize();
extern void aware_terminate();
extern void get_noise(const double cali_raw[264000], const double test_raw
                      [2160000], double noise[2160000]);
extern void single_calc(const double cali1_raw[264000], const double cali2_raw
  [264000], const double cali3_raw[264000], const double test_raw[273600],
  double b_gamma, double ls, double fc, emxArray_real_T *A, emxArray_real_T *ho,
  double *score);

#endif

/* End of code generation (aware.h) */
