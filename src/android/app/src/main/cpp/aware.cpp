/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * aware.cpp
 *
 * Code generation for function 'aware'
 *
 */

/* Include files */
#include "aware.h"
#include "aware_emxutil.h"
#include "rt_nonfinite.h"
#include <cmath>
#include <cstring>
#include <math.h>

/* Type Definitions */
struct cell_wrap_12
{
  unsigned int f1[8];
};

struct dsp_FIRFilter_0
{
  int S0_isInitialized;
  double W0_states[200];
  double P0_InitialStates;
  double P1_Coefficients[201];
};

struct dspcodegen_FIRFilter_3
{
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  dsp_FIRFilter_0 cSFunObject;
};

struct dsp_LowpassFilter
{
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_12 inputVarSize[1];
  int NumChannels;
  dspcodegen_FIRFilter_3 *FilterObj;
};

/* Variable Definitions */
omp_nest_lock_t emlrtNestLockGlobal;
static const double dv[84] = { 0.89419281716303, 0.93180331390361371,
  0.96747362449037722, 1.002301967500955, 1.0373865615129807, 1.0738256251040879,
  1.1130856642879761, 1.1665930517166609, 1.2566391762682381, 1.4059522704838079,
  1.6360949979203072, 1.9679423989751368, 2.4012888572138595, 2.8329274285455726,
  3.1283813715652218, 3.2052216174067909, 3.1086238090291975, 2.9024721595437479,
  2.6317622548895785, 2.3169526862226903, 1.9773503521258027, 1.638682624306576,
  1.3312030827722134, 1.0790507851318831, 0.86916016207959146, 0.674678665972019,
  0.479214997740399, 0.29752921781296893, 0.15002320194568508,
  0.050043336630470225, 0.0, 0.0013769261673677313, 0.055899207100393644,
  0.16549471940921268, 0.33114698110927909, 0.546813550277168,
  0.80330267648560882, 1.0838876221883962, 1.3446202677198476,
  1.5356787823263165, 1.636503304724449, 1.6808301496039268, 1.7081606270835041,
  1.7549258397132128, 1.8544866824743647, 2.0302699743712456, 2.2154870478210915,
  2.2947291848057536, 2.1831575447935667, 1.9331651461661798, 1.6349489041855589,
  1.3559074991311379, 1.1125708982725082, 0.91462851019731106,
  0.77313170636752471, 0.70075289045848344, 0.70802945601686762,
  0.77957936412644946, 0.88329836137880013, 0.99115548086301075,
  1.098658708830639, 1.2092271836750372, 1.3197069455924124, 1.4092003651988692,
  1.4542184458519603, 1.448949131641192, 1.4126552892821684, 1.3661046023962355,
  1.3240547486160383, 1.2966368910631187, 1.2938246473047919, 1.3253354506740362,
  1.4007807573433522, 1.5237614244222137, 1.6781774218706875, 1.8440530454510968,
  2.0133807790570057, 2.1984400161907645, 2.4128997892435033, 2.6590559568414034,
  2.9287786873404813, 3.2135526368325595, 3.5048624614094686, 3.79419281716303 };

static boolean_T isInitialized_aware = false;

/* Function Declarations */
static void LPHPFilterBase_stepImpl(dsp_LowpassFilter *obj, const
  emxArray_real_T *u, emxArray_real_T *y);
static void SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1);
static void align_ave(const double x_raw[264000], const emxArray_real_T *x_ref,
                      emxArray_real_T *output);
static void align_dense(const double x_raw[273600], const emxArray_real_T *x_ref,
  emxArray_real_T *output);
static void b_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1);
static void b_bluestein(const emxArray_creal_T *x, int nfft, int nRows, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  costabinv, const emxArray_real_T *sintabinv, const emxArray_creal_T *wwc,
  emxArray_creal_T *y);
static void b_dobluesteinfft(const emxArray_creal_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y);
static void b_fft(const emxArray_real_T *x, double varargin_1, emxArray_creal_T *
                  y);
static void b_findpeaks(const double Yin[271200], emxArray_real_T *Ypk,
  emxArray_real_T *Xpk);
static void b_generate_twiddle_tables(int nRows, boolean_T useRadix2,
  emxArray_real_T *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv);
static void b_r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y);
static void b_sortIdx(emxArray_int32_T *x, emxArray_int32_T *idx);
static void bluestein(const emxArray_real_T *x, int nfft, int nRows, const
                      emxArray_real_T *costab, const emxArray_real_T *sintab,
                      const emxArray_real_T *costabinv, const emxArray_real_T
                      *sintabinv, const emxArray_creal_T *wwc, emxArray_creal_T *
                      y);
static void c_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1);
static void c_findPeaksSeparatedByMoreThanM(const double y[264000], const double
  x[264000], const emxArray_int32_T *iPk, emxArray_int32_T *idx);
static void c_findpeaks(const double Yin[2160000], double varargin_4,
  emxArray_real_T *Ypk, emxArray_real_T *Xpk);
static void c_matlabCodegenHandle_matlabCod(dsp_LowpassFilter *obj);
static void compute(const emxArray_real_T *cali1, const emxArray_real_T *cali2,
                    const emxArray_real_T *cali3, const emxArray_real_T *test,
                    double b_gamma, double ls, double fc, emxArray_real_T *A,
                    emxArray_real_T *ho, double *score);
static void crosscorr(const emxArray_real_T *x, const emxArray_real_T *y, double
                      maxlag, emxArray_real_T *c);
static void d_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1);
static void d_findPeaksSeparatedByMoreThanM(const double y[271200], const double
  x[271200], const emxArray_int32_T *iPk, emxArray_int32_T *idx);
static void d_findpeaks(const double Yin[264000], emxArray_real_T *Ypk,
  emxArray_real_T *Xpk);
static int div_s32_floor(int numerator, int denominator);
static void do_vectors(const emxArray_int32_T *a, const emxArray_int32_T *b,
  emxArray_int32_T *c, emxArray_int32_T *ia, emxArray_int32_T *ib);
static void dobluesteinfft(const emxArray_real_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y);
static void e_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1);
static void e_findPeaksSeparatedByMoreThanM(const double y[2160000], const
  double x[2160000], const emxArray_int32_T *iPk, emxArray_int32_T *idx);
static void e_findpeaks(const double Yin[280800], emxArray_real_T *Ypk,
  emxArray_real_T *Xpk);
static void f_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1);
static void f_findPeaksSeparatedByMoreThanM(const double y[280800], const double
  x[280800], const emxArray_int32_T *iPk, emxArray_int32_T *idx);
static void fft(const emxArray_real_T *x, double varargin_1, emxArray_creal_T *y);
static void fftshift(emxArray_real_T *x);
static void findpeaks(const double Yin[264000], emxArray_real_T *Ypk,
                      emxArray_real_T *Xpk);
static void g_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1);
static void generate_twiddle_tables(int nRows, boolean_T useRadix2,
  emxArray_real_T *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv);
static void getAllPeaksCodegen(const double y[264000], emxArray_int32_T *iPk,
  emxArray_int32_T *iInf, emxArray_int32_T *iInflect);
static void get_algo_sizes(int n1, boolean_T useRadix2, int *N2blue, int *nRows);
static void ifft(const emxArray_creal_T *x, emxArray_creal_T *y);
static void inverse(const emxArray_real_T *Rx, emxArray_real_T *A);
static double mFindDelay(const emxArray_real_T *x, const emxArray_real_T *y);
static void mLowpass(const emxArray_real_T *x, double Fc, emxArray_real_T *y);
static void mean(const emxArray_real_T *x, emxArray_real_T *y);
static void merge(emxArray_int32_T *idx, emxArray_int32_T *x, int offset, int np,
                  int nq, emxArray_int32_T *iwork, emxArray_int32_T *xwork);
static void merge_block(emxArray_int32_T *idx, emxArray_int32_T *x, int offset,
  int n, int preSortLevel, emxArray_int32_T *iwork, emxArray_int32_T *xwork);
static void merge_pow2_block(emxArray_int32_T *idx, emxArray_int32_T *x, int
  offset);
static void mydtw(const double y[85], double *dist, double ix_data[], int
                  ix_size[1], double iy_data[], int iy_size[1]);
static void r2br_r2dit_trig(const emxArray_real_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y);
static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y);
static void removeSmallPeaks(const double y[264000], const emxArray_int32_T
  *iFinite, double minH, emxArray_int32_T *iPk);
static double rt_hypotd_snf(double u0, double u1);
static double rt_powd_snf(double u0, double u1);
static double rt_roundd_snf(double u);
static void sort(emxArray_int32_T *x);
static void sortIdx(const emxArray_real_T *x, emxArray_int32_T *idx);
static void xcorr(const emxArray_real_T *x, const emxArray_real_T *varargin_1,
                  emxArray_real_T *c);

/* Function Definitions */
static void LPHPFilterBase_stepImpl(dsp_LowpassFilter *obj, const
  emxArray_real_T *u, emxArray_real_T *y)
{
  dspcodegen_FIRFilter_3 *b_obj;
  emxArray_real_T *U0;
  dsp_FIRFilter_0 *c_obj;
  int frameSize;
  int loop_ub;
  int i;
  double acc1;
  int j;
  double acc2;
  b_obj = obj->FilterObj;
  if (b_obj->isInitialized != 1) {
    b_obj->isSetupComplete = false;
    b_obj->isInitialized = 1;
    b_obj->isSetupComplete = true;

    /* System object Initialization function: dsp.FIRFilter */
    for (frameSize = 0; frameSize < 200; frameSize++) {
      b_obj->cSFunObject.W0_states[frameSize] =
        b_obj->cSFunObject.P0_InitialStates;
    }
  }

  emxInit_real_T(&U0, 2);
  c_obj = &b_obj->cSFunObject;
  frameSize = U0->size[0] * U0->size[1];
  U0->size[0] = u->size[0];
  U0->size[1] = 1;
  emxEnsureCapacity_real_T(U0, frameSize);
  loop_ub = u->size[0];
  for (frameSize = 0; frameSize < loop_ub; frameSize++) {
    U0->data[frameSize] = u->data[frameSize];
  }

  /* System object Outputs function: dsp.FIRFilter */
  frameSize = y->size[0] * y->size[1];
  y->size[0] = U0->size[0];
  y->size[1] = U0->size[1];
  emxEnsureCapacity_real_T(y, frameSize);
  frameSize = u->size[0];
  loop_ub = u->size[0];
  if (loop_ub >= 200) {
    loop_ub = 200;
  }

  /* Consume delay line and beginning of input samples */
  i = 0;
  emxFree_real_T(&U0);
  while (i < loop_ub) {
    acc1 = 0.0;
    for (j = 0; j < i + 1; j++) {
      acc2 = u->data[i - j] * c_obj->P1_Coefficients[j];
      acc1 += acc2;
    }

    for (j = 0; j < 200 - i; j++) {
      acc2 = c_obj->W0_states[j] * c_obj->P1_Coefficients[(i + j) + 1];
      acc1 += acc2;
    }

    y->data[i] = acc1;
    i++;
  }

  if (u->size[0] <= 200) {
    /* Update delay line for next frame */
    for (i = 199 - u->size[0]; i >= 0; i--) {
      c_obj->W0_states[frameSize + i] = c_obj->W0_states[i];
    }

    for (i = 0; i < frameSize; i++) {
      c_obj->W0_states[(frameSize - i) - 1] = u->data[i];
    }
  } else {
    /* Consume remaining input samples */
    for (i = 200; i < frameSize; i++) {
      acc1 = 0.0;
      for (j = 0; j < 201; j++) {
        acc2 = u->data[i - j] * c_obj->P1_Coefficients[j];
        acc1 += acc2;
      }

      y->data[i] = acc1;
    }

    /* Update delay line for next frame */
    for (i = 0; i < 200; i++) {
      c_obj->W0_states[199 - i] = u->data[(frameSize + i) - 200];
    }
  }
}

static void SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1)
{
  unsigned int inSize[8];
  cell_wrap_12 varSizes[1];
  int i;
  boolean_T exitg1;
  static const double b_dv[201] = { 0.000504489671235352, -9.323052890024346E-6,
    -6.0479102225299767E-5, -0.00013300837724653509, -0.00020870167033352327,
    -0.00026591353072751023, -0.00028420000273894397, -0.00024942167324744943,
    -0.00015814055837986267, -2.0138451931628116E-5, 0.00014183177374954117,
    0.00029541258529665435, 0.00040478093027254659, 0.00043850784655388378,
    0.00037753466834528478, 0.00022141681607069162, -8.8559205064590316E-6,
    -0.00027257956813772269, -0.00051580633939570886, -0.00068170540127424312,
    -0.000722951197554537, -0.000613579620353241, -0.00035755812523342249,
    8.272697527819238E-6, 0.000418236003686078, 0.00078877024014748051,
    0.00103467029803899, 0.001087621096898123, 0.00091317348083003018,
    0.00052222645327836036, -2.6137594983222722E-5, -0.00063204973163371344,
    -0.0011719815417330008, -0.0015229047286136421, -0.0015889560685361814,
    -0.0013250585499185433, -0.00075204120500414848, 4.0904187972216019E-5,
    0.00090825751182437931, 0.0016735612762447595, 0.0021640282167619432,
    0.0022478274606930028, 0.0018662983934208965, 0.0010536875041986795,
    -6.1021844640584217E-5, -0.0012722900861332521, -0.0023342302675695985,
    -0.0030088272581810997, -0.0031170337546009685, -0.0025821613737366175,
    -0.0014556606396815043, 8.1775504138281626E-5, 0.0017462599065421146,
    0.0032008699046441043, 0.0041215207475679416, 0.0042661100543275269,
    0.00353271158755521, 0.0019936527782200416, -0.00010378452450906514,
    -0.0023731279733692329, -0.0043566931955620726, -0.005614456650686904,
    -0.0058171919881188977, -0.0048249315561522954, -0.0027332304253221348,
    0.00012514318918996315, 0.003227349369154908, 0.0059510464030321491,
    0.0076936327191975667, 0.0079982901949139668, 0.00666170388581501,
    0.0037998999454264882, -0.00014490841137852322, -0.0044631633887132561,
    -0.0082965867927023047, -0.010798226948774236, -0.011305746140631366,
    -0.00949470616231986, -0.0054796595524126933, 0.00016174040748818326,
    0.006453610554709539, 0.012171599019940908, 0.016056901820857849,
    0.017060017149517045, 0.014571299825717461, 0.0085943580317436631,
    -0.00017462836483632526, -0.010384304076646381, -0.020185552942464973,
    -0.027491097974181283, -0.030300247204673603, -0.027038022639586521,
    -0.01685238511583402, 0.00018271180196007309, 0.022997455921982504,
    0.049608010130108328, 0.077344121859433124, 0.10319233478181529,
    0.12420475303876564, 0.13791131976069132, 0.14267167350736554,
    0.13791131976069132, 0.12420475303876564, 0.10319233478181529,
    0.077344121859433124, 0.049608010130108328, 0.022997455921982504,
    0.00018271180196007309, -0.01685238511583402, -0.027038022639586521,
    -0.030300247204673603, -0.027491097974181283, -0.020185552942464973,
    -0.010384304076646381, -0.00017462836483632526, 0.0085943580317436631,
    0.014571299825717461, 0.017060017149517045, 0.016056901820857849,
    0.012171599019940908, 0.006453610554709539, 0.00016174040748818326,
    -0.0054796595524126933, -0.00949470616231986, -0.011305746140631366,
    -0.010798226948774236, -0.0082965867927023047, -0.0044631633887132561,
    -0.00014490841137852322, 0.0037998999454264882, 0.00666170388581501,
    0.0079982901949139668, 0.0076936327191975667, 0.0059510464030321491,
    0.003227349369154908, 0.00012514318918996315, -0.0027332304253221348,
    -0.0048249315561522954, -0.0058171919881188977, -0.005614456650686904,
    -0.0043566931955620726, -0.0023731279733692329, -0.00010378452450906514,
    0.0019936527782200416, 0.00353271158755521, 0.0042661100543275269,
    0.0041215207475679416, 0.0032008699046441043, 0.0017462599065421146,
    8.1775504138281626E-5, -0.0014556606396815043, -0.0025821613737366175,
    -0.0031170337546009685, -0.0030088272581810997, -0.0023342302675695985,
    -0.0012722900861332521, -6.1021844640584217E-5, 0.0010536875041986795,
    0.0018662983934208965, 0.0022478274606930028, 0.0021640282167619432,
    0.0016735612762447595, 0.00090825751182437931, 4.0904187972216019E-5,
    -0.00075204120500414848, -0.0013250585499185433, -0.0015889560685361814,
    -0.0015229047286136421, -0.0011719815417330008, -0.00063204973163371344,
    -2.6137594983222722E-5, 0.00052222645327836036, 0.00091317348083003018,
    0.001087621096898123, 0.00103467029803899, 0.00078877024014748051,
    0.000418236003686078, 8.272697527819238E-6, -0.00035755812523342249,
    -0.000613579620353241, -0.000722951197554537, -0.00068170540127424312,
    -0.00051580633939570886, -0.00027257956813772269, -8.8559205064590316E-6,
    0.00022141681607069162, 0.00037753466834528478, 0.00043850784655388378,
    0.00040478093027254659, 0.00029541258529665435, 0.00014183177374954117,
    -2.0138451931628116E-5, -0.00015814055837986267, -0.00024942167324744943,
    -0.00028420000273894397, -0.00026591353072751023, -0.00020870167033352327,
    -0.00013300837724653509, -6.0479102225299767E-5, -9.323052890024346E-6,
    0.000504489671235352 };

  dspcodegen_FIRFilter_3 *b_obj;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    varSizes[0].f1[0] = static_cast<unsigned int>(varargin_1->size[0]);
    varSizes[0].f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes[0].f1[i + 2] = 1U;
    }

    obj->inputVarSize[0] = varSizes[0];
    iobj_0->isInitialized = 0;

    /* System object Constructor function: dsp.FIRFilter */
    iobj_0->cSFunObject.P0_InitialStates = 0.0;
    for (i = 0; i < 201; i++) {
      iobj_0->cSFunObject.P1_Coefficients[i] = b_dv[i];
    }

    iobj_0->matlabCodegenIsDeleted = false;
    obj->FilterObj = iobj_0;
    obj->NumChannels = 1;
    obj->isSetupComplete = true;
    b_obj = obj->FilterObj;
    if (b_obj->isInitialized == 1) {
      /* System object Initialization function: dsp.FIRFilter */
      for (i = 0; i < 200; i++) {
        b_obj->cSFunObject.W0_states[i] = b_obj->cSFunObject.P0_InitialStates;
      }
    }
  }

  inSize[0] = static_cast<unsigned int>(varargin_1->size[0]);
  inSize[1] = 1U;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1U;
  }

  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != inSize[i]) {
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = inSize[i];
      }

      exitg1 = true;
    } else {
      i++;
    }
  }

  LPHPFilterBase_stepImpl(obj, varargin_1, varargout_1);
}

static void align_ave(const double x_raw[264000], const emxArray_real_T *x_ref,
                      emxArray_real_T *output)
{
  int i;
  int loop_ub;
  static double b_x_raw[271200];
  emxArray_real_T *unusedU0;
  emxArray_real_T *locs;
  int i1;
  emxArray_real_T *c_x_raw;
  double d;
  int b_i;
  int c_i;
  emxArray_real_T *b_output;
  boolean_T exitg1;
  double b_d;
  double d1;
  double d2;
  int i2;
  i = output->size[0] * output->size[1];
  output->size[0] = x_ref->size[0];
  output->size[1] = 2;
  emxEnsureCapacity_real_T(output, i);
  loop_ub = x_ref->size[0] << 1;
  for (i = 0; i < loop_ub; i++) {
    output->data[i] = 0.0;
  }

  std::memset(&b_x_raw[0], 0, 7200U * sizeof(double));
  std::memcpy(&b_x_raw[7200], &x_raw[0], 264000U * sizeof(double));
  emxInit_real_T(&unusedU0, 1);
  emxInit_real_T(&locs, 1);
  b_findpeaks(b_x_raw, unusedU0, locs);
  emxFree_real_T(&unusedU0);
  if ((locs->data[0] - 7200.0) + 1.0 > locs->data[0] + 9600.0) {
    i = 0;
    i1 = 0;
  } else {
    i = static_cast<int>((locs->data[0] - 7200.0) + 1.0) - 1;
    i1 = static_cast<int>(locs->data[0] + 9600.0);
  }

  emxInit_real_T(&c_x_raw, 1);
  loop_ub = i1 - i;
  i1 = c_x_raw->size[0];
  c_x_raw->size[0] = loop_ub;
  emxEnsureCapacity_real_T(c_x_raw, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    c_x_raw->data[i1] = b_x_raw[i + i1];
  }

  d = mFindDelay(x_ref, c_x_raw);
  b_i = 0;
  c_i = 0;
  emxFree_real_T(&c_x_raw);
  emxInit_real_T(&b_output, 1);
  exitg1 = false;
  while ((!exitg1) && (c_i < 12)) {
    b_i = c_i;
    b_d = static_cast<double>(c_i) * 0.4;
    d1 = locs->data[0] + (b_d + 0.05) * 48000.0;
    if (rt_roundd_snf((d1 + static_cast<double>(x_ref->size[0])) + d) <=
        271200.0) {
      b_d = locs->data[0] + (b_d - 0.15) * 48000.0;
      d2 = rt_roundd_snf((b_d + 1.0) + d);
      if (d2 > rt_roundd_snf((b_d + static_cast<double>(x_ref->size[0])) + d)) {
        i = 1;
      } else {
        i = static_cast<int>(d2);
      }

      b_d = rt_roundd_snf((d1 + 1.0) + d);
      if (b_d > rt_roundd_snf((d1 + static_cast<double>(x_ref->size[0])) + d)) {
        i1 = 1;
      } else {
        i1 = static_cast<int>(b_d);
      }

      loop_ub = output->size[0] - 1;
      i2 = b_output->size[0];
      b_output->size[0] = output->size[0];
      emxEnsureCapacity_real_T(b_output, i2);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        b_output->data[i2] = output->data[i2] + b_x_raw[(i + i2) - 1];
      }

      loop_ub = b_output->size[0];
      for (i = 0; i < loop_ub; i++) {
        output->data[i] = b_output->data[i];
      }

      loop_ub = output->size[0] - 1;
      i = b_output->size[0];
      b_output->size[0] = output->size[0];
      emxEnsureCapacity_real_T(b_output, i);
      for (i = 0; i <= loop_ub; i++) {
        b_output->data[i] = output->data[i + output->size[0]] + b_x_raw[(i1 + i)
          - 1];
      }

      loop_ub = b_output->size[0];
      for (i = 0; i < loop_ub; i++) {
        output->data[i + output->size[0]] = b_output->data[i];
      }

      c_i++;
    } else {
      exitg1 = true;
    }
  }

  emxFree_real_T(&locs);
  loop_ub = output->size[0] - 1;
  i = b_output->size[0];
  b_output->size[0] = output->size[0];
  emxEnsureCapacity_real_T(b_output, i);
  for (i = 0; i <= loop_ub; i++) {
    b_output->data[i] = output->data[i] / (static_cast<double>(b_i) + 1.0);
  }

  loop_ub = b_output->size[0];
  for (i = 0; i < loop_ub; i++) {
    output->data[i] = b_output->data[i];
  }

  loop_ub = output->size[0] - 1;
  i = b_output->size[0];
  b_output->size[0] = output->size[0];
  emxEnsureCapacity_real_T(b_output, i);
  for (i = 0; i <= loop_ub; i++) {
    b_output->data[i] = output->data[i + output->size[0]] / (static_cast<double>
      (b_i) + 1.0);
  }

  loop_ub = b_output->size[0];
  for (i = 0; i < loop_ub; i++) {
    output->data[i + output->size[0]] = b_output->data[i];
  }

  emxFree_real_T(&b_output);
}

static void align_dense(const double x_raw[273600], const emxArray_real_T *x_ref,
  emxArray_real_T *output)
{
  int i;
  int loop_ub;
  static double b_x_raw[280800];
  emxArray_real_T *unusedU0;
  emxArray_real_T *locs;
  int i1;
  emxArray_real_T *c_x_raw;
  double d;
  int b_i;
  boolean_T exitg1;
  double b_d;
  double d1;
  i = output->size[0] * output->size[1];
  output->size[0] = x_ref->size[0];
  output->size[1] = 25;
  emxEnsureCapacity_real_T(output, i);
  loop_ub = x_ref->size[0] * 25;
  for (i = 0; i < loop_ub; i++) {
    output->data[i] = 0.0;
  }

  std::memset(&b_x_raw[0], 0, 7200U * sizeof(double));
  std::memcpy(&b_x_raw[7200], &x_raw[0], 273600U * sizeof(double));
  emxInit_real_T(&unusedU0, 1);
  emxInit_real_T(&locs, 1);
  e_findpeaks(b_x_raw, unusedU0, locs);
  emxFree_real_T(&unusedU0);
  if ((locs->data[0] - 7200.0) + 1.0 > locs->data[0] + 9600.0) {
    i = 0;
    i1 = 0;
  } else {
    i = static_cast<int>((locs->data[0] - 7200.0) + 1.0) - 1;
    i1 = static_cast<int>(locs->data[0] + 9600.0);
  }

  emxInit_real_T(&c_x_raw, 1);
  loop_ub = i1 - i;
  i1 = c_x_raw->size[0];
  c_x_raw->size[0] = loop_ub;
  emxEnsureCapacity_real_T(c_x_raw, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    c_x_raw->data[i1] = b_x_raw[i + i1];
  }

  d = mFindDelay(x_ref, c_x_raw);
  b_i = 0;
  emxFree_real_T(&c_x_raw);
  exitg1 = false;
  while ((!exitg1) && (b_i < 25)) {
    b_d = locs->data[0] + (static_cast<double>(b_i) * 0.2 - 0.15) * 48000.0;
    if (rt_roundd_snf((b_d + static_cast<double>(x_ref->size[0])) + d) >
        280800.0) {
      exitg1 = true;
    } else {
      d1 = rt_roundd_snf((b_d + 1.0) + d);
      if (!(d1 < 1.0)) {
        b_d = rt_roundd_snf((b_d + static_cast<double>(x_ref->size[0])) + d);
        if (d1 > b_d) {
          i = 0;
          i1 = 0;
        } else {
          i = static_cast<int>(d1) - 1;
          i1 = static_cast<int>(b_d);
        }

        loop_ub = i1 - i;
        for (i1 = 0; i1 < loop_ub; i1++) {
          output->data[i1 + output->size[0] * b_i] = b_x_raw[i + i1];
        }
      }

      b_i++;
    }
  }

  emxFree_real_T(&locs);
}

static void b_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1)
{
  unsigned int inSize[8];
  cell_wrap_12 varSizes[1];
  int i;
  boolean_T exitg1;
  static const double b_dv[201] = { 0.00052858000364218449,
    3.4736530250019275E-5, -2.958198051011631E-5, -0.00012151880328055831,
    -0.00021397324387974605, -0.00027510853405845082, -0.0002774586184423497,
    -0.00020717007446464139, -7.0534731401224984E-5, 0.00010462261109567417,
    0.00027391495990988085, 0.00038716549517134644, 0.00040257478069239116,
    0.00030050218816140667, 9.2665092503576408E-5, -0.00017664570209611981,
    -0.00043881223787493542, -0.0006174558183647355, -0.00064956226659858567,
    -0.00050556582730731958, -0.0002023763794427823, 0.00019535975845390324,
    0.000587626041754124, 0.000863150285854106, 0.00092975011464161393,
    0.00074292746045769823, 0.00032429266236651185, -0.00023665564969886166,
    -0.00079983618616277991, -0.0012082312458772467, -0.0013301556485530185,
    -0.0010991213403548211, -0.0005397506505899326, 0.00022909725716708444,
    0.0010173152475095404, 0.0016089566876856649, 0.0018196649685198157,
    0.0015512743116793699, 0.00082801485875734059, -0.00019765750169780429,
    -0.0012742830266630186, -0.0021110213695182969, -0.0024540961318021324,
    -0.0021604844451526112, -0.0012481631064846733, 9.3240319146187039E-5,
    0.0015380979414815954, 0.0027012612979609727, 0.0032381149989908417,
    0.0029428590808414663, 0.0018178446506710068, 9.227734775955108E-5,
    -0.001819453649949008, -0.0034138859272871266, -0.0042276653604282682,
    -0.0039674926812807362, -0.002605464286561453, -0.00041075546805794029,
    0.0020966277107126066, 0.0042643699469473136, 0.0054728780343700394,
    0.0053062153444462367, 0.0036832090399359046, 0.00090978887510051855,
    -0.0023685215164984956, -0.0053099920373007358, -0.00708587809449843,
    -0.0071050831601981715, -0.0051954368901325643, -0.0016891868112036174,
    0.0026187570856420865, 0.0066402177972501126, 0.0092573651943949863,
    0.0096192469098899062, 0.00739579291901863, 0.0029182662149492551,
    -0.0028415334891216935, -0.0084632687816982369, -0.012407660540676589,
    -0.013411413775287429, -0.010851720095222729, -0.0049834487388273532,
    0.0030245997289171083, 0.011284287828371554, 0.017588662880227528,
    0.019940280235102841, 0.017090822289085136, 0.0089623761922558911,
    -0.0031622207957711927, -0.016747412494808163, -0.028414482634034417,
    -0.034586378020874518, -0.032242975186912944, -0.019628479681519241,
    0.0032467769356015761, 0.034431778466472544, 0.0702442181766189,
    0.10584037857070916, 0.13604406689168383, 0.15627488532461881,
    0.16339090397629547, 0.15627488532461881, 0.13604406689168383,
    0.10584037857070916, 0.0702442181766189, 0.034431778466472544,
    0.0032467769356015761, -0.019628479681519241, -0.032242975186912944,
    -0.034586378020874518, -0.028414482634034417, -0.016747412494808163,
    -0.0031622207957711927, 0.0089623761922558911, 0.017090822289085136,
    0.019940280235102841, 0.017588662880227528, 0.011284287828371554,
    0.0030245997289171083, -0.0049834487388273532, -0.010851720095222729,
    -0.013411413775287429, -0.012407660540676589, -0.0084632687816982369,
    -0.0028415334891216935, 0.0029182662149492551, 0.00739579291901863,
    0.0096192469098899062, 0.0092573651943949863, 0.0066402177972501126,
    0.0026187570856420865, -0.0016891868112036174, -0.0051954368901325643,
    -0.0071050831601981715, -0.00708587809449843, -0.0053099920373007358,
    -0.0023685215164984956, 0.00090978887510051855, 0.0036832090399359046,
    0.0053062153444462367, 0.0054728780343700394, 0.0042643699469473136,
    0.0020966277107126066, -0.00041075546805794029, -0.002605464286561453,
    -0.0039674926812807362, -0.0042276653604282682, -0.0034138859272871266,
    -0.001819453649949008, 9.227734775955108E-5, 0.0018178446506710068,
    0.0029428590808414663, 0.0032381149989908417, 0.0027012612979609727,
    0.0015380979414815954, 9.3240319146187039E-5, -0.0012481631064846733,
    -0.0021604844451526112, -0.0024540961318021324, -0.0021110213695182969,
    -0.0012742830266630186, -0.00019765750169780429, 0.00082801485875734059,
    0.0015512743116793699, 0.0018196649685198157, 0.0016089566876856649,
    0.0010173152475095404, 0.00022909725716708444, -0.0005397506505899326,
    -0.0010991213403548211, -0.0013301556485530185, -0.0012082312458772467,
    -0.00079983618616277991, -0.00023665564969886166, 0.00032429266236651185,
    0.00074292746045769823, 0.00092975011464161393, 0.000863150285854106,
    0.000587626041754124, 0.00019535975845390324, -0.0002023763794427823,
    -0.00050556582730731958, -0.00064956226659858567, -0.0006174558183647355,
    -0.00043881223787493542, -0.00017664570209611981, 9.2665092503576408E-5,
    0.00030050218816140667, 0.00040257478069239116, 0.00038716549517134644,
    0.00027391495990988085, 0.00010462261109567417, -7.0534731401224984E-5,
    -0.00020717007446464139, -0.0002774586184423497, -0.00027510853405845082,
    -0.00021397324387974605, -0.00012151880328055831, -2.958198051011631E-5,
    3.4736530250019275E-5, 0.00052858000364218449 };

  dspcodegen_FIRFilter_3 *b_obj;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    varSizes[0].f1[0] = static_cast<unsigned int>(varargin_1->size[0]);
    varSizes[0].f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes[0].f1[i + 2] = 1U;
    }

    obj->inputVarSize[0] = varSizes[0];
    iobj_0->isInitialized = 0;

    /* System object Constructor function: dsp.FIRFilter */
    iobj_0->cSFunObject.P0_InitialStates = 0.0;
    for (i = 0; i < 201; i++) {
      iobj_0->cSFunObject.P1_Coefficients[i] = b_dv[i];
    }

    iobj_0->matlabCodegenIsDeleted = false;
    obj->FilterObj = iobj_0;
    obj->NumChannels = 1;
    obj->isSetupComplete = true;
    b_obj = obj->FilterObj;
    if (b_obj->isInitialized == 1) {
      /* System object Initialization function: dsp.FIRFilter */
      for (i = 0; i < 200; i++) {
        b_obj->cSFunObject.W0_states[i] = b_obj->cSFunObject.P0_InitialStates;
      }
    }
  }

  inSize[0] = static_cast<unsigned int>(varargin_1->size[0]);
  inSize[1] = 1U;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1U;
  }

  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != inSize[i]) {
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = inSize[i];
      }

      exitg1 = true;
    } else {
      i++;
    }
  }

  LPHPFilterBase_stepImpl(obj, varargin_1, varargout_1);
}

static void b_bluestein(const emxArray_creal_T *x, int nfft, int nRows, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  costabinv, const emxArray_real_T *sintabinv, const emxArray_creal_T *wwc,
  emxArray_creal_T *y)
{
  emxArray_creal_T *fv;
  int minNrowsNx;
  int denom_re_tmp;
  int xidx;
  int k;
  emxArray_creal_T *b_fv;
  double im;
  double y_tmp_im;
  emxInit_creal_T(&fv, 1);
  minNrowsNx = x->size[0];
  if (nRows < minNrowsNx) {
    minNrowsNx = nRows;
  }

  denom_re_tmp = fv->size[0];
  fv->size[0] = nRows;
  emxEnsureCapacity_creal_T(fv, denom_re_tmp);
  if (nRows > x->size[0]) {
    denom_re_tmp = fv->size[0];
    fv->size[0] = nRows;
    emxEnsureCapacity_creal_T(fv, denom_re_tmp);
    for (denom_re_tmp = 0; denom_re_tmp < nRows; denom_re_tmp++) {
      fv->data[denom_re_tmp].re = 0.0;
      fv->data[denom_re_tmp].im = 0.0;
    }
  }

  denom_re_tmp = y->size[0];
  y->size[0] = fv->size[0];
  emxEnsureCapacity_creal_T(y, denom_re_tmp);
  xidx = fv->size[0];
  for (denom_re_tmp = 0; denom_re_tmp < xidx; denom_re_tmp++) {
    y->data[denom_re_tmp] = fv->data[denom_re_tmp];
  }

  xidx = 0;
  for (k = 0; k < minNrowsNx; k++) {
    denom_re_tmp = (nRows + k) - 1;
    y->data[k].re = wwc->data[denom_re_tmp].re * x->data[xidx].re + wwc->
      data[denom_re_tmp].im * x->data[xidx].im;
    y->data[k].im = wwc->data[denom_re_tmp].re * x->data[xidx].im - wwc->
      data[denom_re_tmp].im * x->data[xidx].re;
    xidx++;
  }

  denom_re_tmp = minNrowsNx + 1;
  for (k = denom_re_tmp; k <= nRows; k++) {
    y->data[k - 1].re = 0.0;
    y->data[k - 1].im = 0.0;
  }

  emxInit_creal_T(&b_fv, 1);
  r2br_r2dit_trig_impl(y, nfft, costab, sintab, fv);
  r2br_r2dit_trig_impl(wwc, nfft, costab, sintab, b_fv);
  denom_re_tmp = b_fv->size[0];
  b_fv->size[0] = fv->size[0];
  emxEnsureCapacity_creal_T(b_fv, denom_re_tmp);
  xidx = fv->size[0];
  for (denom_re_tmp = 0; denom_re_tmp < xidx; denom_re_tmp++) {
    im = fv->data[denom_re_tmp].re * b_fv->data[denom_re_tmp].im + fv->
      data[denom_re_tmp].im * b_fv->data[denom_re_tmp].re;
    b_fv->data[denom_re_tmp].re = fv->data[denom_re_tmp].re * b_fv->
      data[denom_re_tmp].re - fv->data[denom_re_tmp].im * b_fv->
      data[denom_re_tmp].im;
    b_fv->data[denom_re_tmp].im = im;
  }

  b_r2br_r2dit_trig(b_fv, nfft, costabinv, sintabinv, fv);
  xidx = 0;
  denom_re_tmp = wwc->size[0];
  emxFree_creal_T(&b_fv);
  for (k = nRows; k <= denom_re_tmp; k++) {
    im = wwc->data[k - 1].re * fv->data[k - 1].re + wwc->data[k - 1].im *
      fv->data[k - 1].im;
    y_tmp_im = wwc->data[k - 1].re * fv->data[k - 1].im - wwc->data[k - 1].im *
      fv->data[k - 1].re;
    y->data[xidx].re = im;
    y->data[xidx].im = y_tmp_im;
    y->data[xidx].re = im;
    y->data[xidx].im = y_tmp_im;
    if (y->data[xidx].im == 0.0) {
      y_tmp_im = y->data[xidx].re / static_cast<double>(nRows);
      im = 0.0;
    } else if (y->data[xidx].re == 0.0) {
      y_tmp_im = 0.0;
      im = y->data[xidx].im / static_cast<double>(nRows);
    } else {
      y_tmp_im = y->data[xidx].re / static_cast<double>(nRows);
      im = y->data[xidx].im / static_cast<double>(nRows);
    }

    y->data[xidx].re = y_tmp_im;
    y->data[xidx].im = im;
    xidx++;
  }

  emxFree_creal_T(&fv);
}

static void b_dobluesteinfft(const emxArray_creal_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y)
{
  emxArray_creal_T *wwc;
  int nInt2m1;
  int rt;
  int idx;
  int nInt2;
  int k;
  int b_y;
  double nt_im;
  double nt_re;
  emxInit_creal_T(&wwc, 1);
  nInt2m1 = (n1 + n1) - 1;
  rt = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal_T(wwc, rt);
  idx = n1;
  rt = 0;
  wwc->data[n1 - 1].re = 1.0;
  wwc->data[n1 - 1].im = 0.0;
  nInt2 = n1 << 1;
  for (k = 0; k <= n1 - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }

    nt_im = 3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
      (n1);
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = std::cos(nt_im);
      nt_im = std::sin(nt_im);
    }

    wwc->data[idx - 2].re = nt_re;
    wwc->data[idx - 2].im = -nt_im;
    idx--;
  }

  idx = 0;
  rt = nInt2m1 - 1;
  for (k = rt; k >= n1; k--) {
    wwc->data[k] = wwc->data[idx];
    idx++;
  }

  b_bluestein(x, N2, n1, costab, sintab, costab, sintabinv, wwc, y);
  emxFree_creal_T(&wwc);
}

static void b_fft(const emxArray_real_T *x, double varargin_1, emxArray_creal_T *
                  y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxArray_creal_T *b_y;
  boolean_T guard1 = false;
  int i;
  boolean_T useRadix2;
  int N2blue;
  int nRows;
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  emxInit_creal_T(&b_y, 1);
  guard1 = false;
  if (x->size[0] == 0) {
    guard1 = true;
  } else {
    i = static_cast<int>(varargin_1);
    if (i == 0) {
      guard1 = true;
    } else {
      useRadix2 = ((i & (i - 1)) == 0);
      get_algo_sizes(static_cast<int>(varargin_1), useRadix2, &N2blue, &nRows);
      generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
      if (useRadix2) {
        r2br_r2dit_trig(x, i, costab, sintab, b_y);
        i = y->size[0];
        y->size[0] = b_y->size[0];
        emxEnsureCapacity_creal_T(y, i);
        N2blue = b_y->size[0];
        for (i = 0; i < N2blue; i++) {
          y->data[i] = b_y->data[i];
        }
      } else {
        dobluesteinfft(x, N2blue, i, costab, sintab, sintabinv, b_y);
        i = y->size[0];
        y->size[0] = b_y->size[0];
        emxEnsureCapacity_creal_T(y, i);
        N2blue = b_y->size[0];
        for (i = 0; i < N2blue; i++) {
          y->data[i] = b_y->data[i];
        }
      }
    }
  }

  if (guard1) {
    N2blue = static_cast<int>(varargin_1);
    i = b_y->size[0];
    b_y->size[0] = N2blue;
    emxEnsureCapacity_creal_T(b_y, i);
    if (N2blue > x->size[0]) {
      i = b_y->size[0];
      b_y->size[0] = N2blue;
      emxEnsureCapacity_creal_T(b_y, i);
      for (i = 0; i < N2blue; i++) {
        b_y->data[i].re = 0.0;
        b_y->data[i].im = 0.0;
      }
    }

    i = y->size[0];
    y->size[0] = b_y->size[0];
    emxEnsureCapacity_creal_T(y, i);
    N2blue = b_y->size[0];
    for (i = 0; i < N2blue; i++) {
      y->data[i] = b_y->data[i];
    }
  }

  emxFree_creal_T(&b_y);
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

static void b_findpeaks(const double Yin[271200], emxArray_real_T *Ypk,
  emxArray_real_T *Xpk)
{
  emxArray_int32_T *iInflect;
  emxArray_int32_T *iFinite;
  emxArray_int32_T *iInfinite;
  int k;
  int nPk;
  int nInf;
  char dir;
  int kfirst;
  double ykfirst;
  boolean_T isinfykfirst;
  double yk;
  boolean_T isinfyk;
  char previousdir;
  emxArray_int32_T *c;
  emxArray_int32_T *ia;
  emxArray_int32_T *ib;
  emxArray_int32_T *idx;
  static double b_dv[271200];
  emxArray_int32_T *iPk;
  emxInit_int32_T(&iInflect, 1);
  emxInit_int32_T(&iFinite, 1);
  emxInit_int32_T(&iInfinite, 1);
  k = iFinite->size[0];
  iFinite->size[0] = 271200;
  emxEnsureCapacity_int32_T(iFinite, k);
  k = iInfinite->size[0];
  iInfinite->size[0] = 271200;
  emxEnsureCapacity_int32_T(iInfinite, k);
  nPk = -1;
  nInf = -1;
  dir = 'n';
  kfirst = -1;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 0; k < 271200; k++) {
    yk = Yin[k];
    if (rtIsNaN(Yin[k])) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(Yin[k]) && (Yin[k] > 0.0)) {
      isinfyk = true;
      nInf++;
      iInfinite->data[nInf] = k + 1;
    } else {
      isinfyk = false;
    }

    if (yk != ykfirst) {
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
      } else if (yk < ykfirst) {
        dir = 'd';
        if (('d' != previousdir) && (previousdir == 'i')) {
          nPk++;
          iFinite->data[nPk] = kfirst + 1;
        }
      } else {
        dir = 'i';
      }

      ykfirst = yk;
      kfirst = k;
      isinfykfirst = isinfyk;
    }
  }

  if (1 > nPk + 1) {
    kfirst = -1;
  } else {
    kfirst = nPk;
  }

  k = iInflect->size[0];
  iInflect->size[0] = kfirst + 1;
  emxEnsureCapacity_int32_T(iInflect, k);
  for (k = 0; k <= kfirst; k++) {
    iInflect->data[k] = iFinite->data[k];
  }

  k = iFinite->size[0];
  iFinite->size[0] = iInflect->size[0];
  emxEnsureCapacity_int32_T(iFinite, k);
  kfirst = iInflect->size[0];
  for (k = 0; k < kfirst; k++) {
    iFinite->data[k] = iInflect->data[k];
  }

  if (1 > nInf + 1) {
    kfirst = -1;
  } else {
    kfirst = nInf;
  }

  k = iInflect->size[0];
  iInflect->size[0] = kfirst + 1;
  emxEnsureCapacity_int32_T(iInflect, k);
  for (k = 0; k <= kfirst; k++) {
    iInflect->data[k] = iInfinite->data[k];
  }

  k = iInfinite->size[0];
  iInfinite->size[0] = iInflect->size[0];
  emxEnsureCapacity_int32_T(iInfinite, k);
  kfirst = iInflect->size[0];
  for (k = 0; k < kfirst; k++) {
    iInfinite->data[k] = iInflect->data[k];
  }

  k = iInflect->size[0];
  iInflect->size[0] = iFinite->size[0];
  emxEnsureCapacity_int32_T(iInflect, k);
  nPk = 0;
  kfirst = iFinite->size[0];
  for (k = 0; k < kfirst; k++) {
    ykfirst = Yin[iFinite->data[k] - 1];
    if (ykfirst > 0.1) {
      if ((Yin[iFinite->data[k] - 2] > Yin[iFinite->data[k]]) || rtIsNaN
          (Yin[iFinite->data[k]])) {
        yk = Yin[iFinite->data[k] - 2];
      } else {
        yk = Yin[iFinite->data[k]];
      }

      if (ykfirst - yk >= 0.0) {
        nPk++;
        iInflect->data[nPk - 1] = iFinite->data[k];
      }
    }
  }

  emxFree_int32_T(&iFinite);
  emxInit_int32_T(&c, 1);
  emxInit_int32_T(&ia, 1);
  emxInit_int32_T(&ib, 1);
  k = iInflect->size[0];
  if (1 > nPk) {
    iInflect->size[0] = 0;
  } else {
    iInflect->size[0] = nPk;
  }

  emxEnsureCapacity_int32_T(iInflect, k);
  do_vectors(iInflect, iInfinite, c, ia, ib);
  emxFree_int32_T(&iInfinite);
  emxFree_int32_T(&ib);
  emxFree_int32_T(&ia);
  emxFree_int32_T(&iInflect);
  for (k = 0; k < 271200; k++) {
    b_dv[k] = static_cast<double>(k) + 1.0;
  }

  emxInit_int32_T(&idx, 1);
  d_findPeaksSeparatedByMoreThanM(Yin, b_dv, c, idx);
  emxInit_int32_T(&iPk, 1);
  if (idx->size[0] > 271200) {
    k = iPk->size[0];
    iPk->size[0] = 271200;
    emxEnsureCapacity_int32_T(iPk, k);
    for (k = 0; k < 271200; k++) {
      iPk->data[k] = idx->data[k];
    }

    k = idx->size[0];
    idx->size[0] = iPk->size[0];
    emxEnsureCapacity_int32_T(idx, k);
    kfirst = iPk->size[0];
    for (k = 0; k < kfirst; k++) {
      idx->data[k] = iPk->data[k];
    }
  }

  k = iPk->size[0];
  iPk->size[0] = idx->size[0];
  emxEnsureCapacity_int32_T(iPk, k);
  kfirst = idx->size[0];
  for (k = 0; k < kfirst; k++) {
    iPk->data[k] = c->data[idx->data[k] - 1];
  }

  emxFree_int32_T(&c);
  emxFree_int32_T(&idx);
  k = Ypk->size[0];
  Ypk->size[0] = iPk->size[0];
  emxEnsureCapacity_real_T(Ypk, k);
  kfirst = iPk->size[0];
  for (k = 0; k < kfirst; k++) {
    Ypk->data[k] = Yin[iPk->data[k] - 1];
  }

  k = Xpk->size[0];
  Xpk->size[0] = iPk->size[0];
  emxEnsureCapacity_real_T(Xpk, k);
  kfirst = iPk->size[0];
  for (k = 0; k < kfirst; k++) {
    Xpk->data[k] = iPk->data[k];
  }

  emxFree_int32_T(&iPk);
}

static void b_generate_twiddle_tables(int nRows, boolean_T useRadix2,
  emxArray_real_T *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  int n;
  int i;
  int nd2;
  int k;
  emxInit_real_T(&costab1q, 2);
  e = 6.2831853071795862 / static_cast<double>(nRows);
  n = nRows / 2 / 2;
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i);
  costab1q->data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q->data[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
  }

  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q->data[k] = std::sin(e * static_cast<double>(n - k));
  }

  costab1q->data[n] = 0.0;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    i = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i);
    for (k = 0; k < n; k++) {
      sintabinv->data[k + 1] = costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      sintabinv->data[k] = costab1q->data[k - n];
    }

    for (k = 0; k < n; k++) {
      costab->data[k + 1] = costab1q->data[k + 1];
      sintab->data[k + 1] = -costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab->data[k + 1] = costab1q->data[k + 1];
      sintab->data[k + 1] = costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = costab1q->data[k - n];
    }

    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }

  emxFree_real_T(&costab1q);
}

static void b_r2br_r2dit_trig(const emxArray_creal_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y)
{
  int j;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int iDelta2;
  int ix;
  int ju;
  int iy;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  j = x->size[0];
  if (j >= n1_unsigned) {
    j = n1_unsigned;
  }

  nRowsM2 = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  iDelta2 = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iDelta2);
  if (n1_unsigned > x->size[0]) {
    iDelta2 = y->size[0];
    y->size[0] = n1_unsigned;
    emxEnsureCapacity_creal_T(y, iDelta2);
    for (iDelta2 = 0; iDelta2 < n1_unsigned; iDelta2++) {
      y->data[iDelta2].re = 0.0;
      y->data[iDelta2].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= j - 2; i++) {
    y->data[iy] = x->data[ix];
    iDelta2 = n1_unsigned;
    tst = true;
    while (tst) {
      iDelta2 >>= 1;
      ju ^= iDelta2;
      tst = ((ju & iDelta2) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (n1_unsigned > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      twid_re = y->data[i].re;
      twid_im = y->data[i].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y->data[i].re = twid_re;
      y->data[i].im = twid_im;
    }
  }

  iy = 2;
  iDelta2 = 4;
  ix = ((nRowsD4 - 1) << 2) + 1;
  while (nRowsD4 > 0) {
    for (i = 0; i < ix; i += iDelta2) {
      temp_re_tmp = i + iy;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - y->data[temp_re_tmp].re;
      y->data[temp_re_tmp].im = y->data[i].im - y->data[temp_re_tmp].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    ju = 1;
    for (j = nRowsD4; j < nRowsD2; j += nRowsD4) {
      twid_re = costab->data[j];
      twid_im = sintab->data[j];
      i = ju;
      nRowsM2 = ju + ix;
      while (i < nRowsM2) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += iDelta2;
      }

      ju++;
    }

    nRowsD4 /= 2;
    iy = iDelta2;
    iDelta2 += iDelta2;
    ix -= iy;
  }

  if (y->size[0] > 1) {
    twid_re = 1.0 / static_cast<double>(y->size[0]);
    iy = y->size[0];
    for (iDelta2 = 0; iDelta2 < iy; iDelta2++) {
      y->data[iDelta2].re *= twid_re;
      y->data[iDelta2].im *= twid_re;
    }
  }
}

static void b_sortIdx(emxArray_int32_T *x, emxArray_int32_T *idx)
{
  int i3;
  int x4_tmp;
  emxArray_int32_T *iwork;
  int n;
  int b_n;
  int x4[4];
  int idx4[4];
  emxArray_int32_T *xwork;
  int nQuartets;
  int j;
  int nDone;
  int i;
  int i4;
  signed char perm[4];
  int i1;
  int i2;
  i3 = x->size[0];
  x4_tmp = idx->size[0];
  idx->size[0] = i3;
  emxEnsureCapacity_int32_T(idx, x4_tmp);
  for (x4_tmp = 0; x4_tmp < i3; x4_tmp++) {
    idx->data[x4_tmp] = 0;
  }

  if (x->size[0] != 0) {
    emxInit_int32_T(&iwork, 1);
    n = x->size[0];
    b_n = x->size[0] - 1;
    x4[0] = 0;
    idx4[0] = 0;
    x4[1] = 0;
    idx4[1] = 0;
    x4[2] = 0;
    idx4[2] = 0;
    x4[3] = 0;
    idx4[3] = 0;
    x4_tmp = iwork->size[0];
    iwork->size[0] = i3;
    emxEnsureCapacity_int32_T(iwork, x4_tmp);
    for (x4_tmp = 0; x4_tmp < i3; x4_tmp++) {
      iwork->data[x4_tmp] = 0;
    }

    emxInit_int32_T(&xwork, 1);
    x4_tmp = xwork->size[0];
    xwork->size[0] = x->size[0];
    emxEnsureCapacity_int32_T(xwork, x4_tmp);
    i3 = xwork->size[0];
    for (x4_tmp = 0; x4_tmp < i3; x4_tmp++) {
      xwork->data[x4_tmp] = 0;
    }

    nQuartets = x->size[0] >> 2;
    for (j = 0; j < nQuartets; j++) {
      i = j << 2;
      idx4[0] = i + 1;
      idx4[1] = i + 2;
      idx4[2] = i + 3;
      idx4[3] = i + 4;
      x4[0] = x->data[i];
      i3 = x->data[i + 1];
      x4[1] = i3;
      i4 = x->data[i + 2];
      x4[2] = i4;
      x4_tmp = x->data[i + 3];
      x4[3] = x4_tmp;
      if (x->data[i] <= i3) {
        i1 = 1;
        i2 = 2;
      } else {
        i1 = 2;
        i2 = 1;
      }

      if (i4 <= x4_tmp) {
        i3 = 3;
        i4 = 4;
      } else {
        i3 = 4;
        i4 = 3;
      }

      x4_tmp = x4[i1 - 1];
      nDone = x4[i3 - 1];
      if (x4_tmp <= nDone) {
        x4_tmp = x4[i2 - 1];
        if (x4_tmp <= nDone) {
          perm[0] = static_cast<signed char>(i1);
          perm[1] = static_cast<signed char>(i2);
          perm[2] = static_cast<signed char>(i3);
          perm[3] = static_cast<signed char>(i4);
        } else if (x4_tmp <= x4[i4 - 1]) {
          perm[0] = static_cast<signed char>(i1);
          perm[1] = static_cast<signed char>(i3);
          perm[2] = static_cast<signed char>(i2);
          perm[3] = static_cast<signed char>(i4);
        } else {
          perm[0] = static_cast<signed char>(i1);
          perm[1] = static_cast<signed char>(i3);
          perm[2] = static_cast<signed char>(i4);
          perm[3] = static_cast<signed char>(i2);
        }
      } else {
        nDone = x4[i4 - 1];
        if (x4_tmp <= nDone) {
          if (x4[i2 - 1] <= nDone) {
            perm[0] = static_cast<signed char>(i3);
            perm[1] = static_cast<signed char>(i1);
            perm[2] = static_cast<signed char>(i2);
            perm[3] = static_cast<signed char>(i4);
          } else {
            perm[0] = static_cast<signed char>(i3);
            perm[1] = static_cast<signed char>(i1);
            perm[2] = static_cast<signed char>(i4);
            perm[3] = static_cast<signed char>(i2);
          }
        } else {
          perm[0] = static_cast<signed char>(i3);
          perm[1] = static_cast<signed char>(i4);
          perm[2] = static_cast<signed char>(i1);
          perm[3] = static_cast<signed char>(i2);
        }
      }

      i1 = perm[0] - 1;
      idx->data[i] = idx4[i1];
      i2 = perm[1] - 1;
      idx->data[i + 1] = idx4[i2];
      i3 = perm[2] - 1;
      idx->data[i + 2] = idx4[i3];
      i4 = perm[3] - 1;
      idx->data[i + 3] = idx4[i4];
      x->data[i] = x4[i1];
      x->data[i + 1] = x4[i2];
      x->data[i + 2] = x4[i3];
      x->data[i + 3] = x4[i4];
    }

    nDone = nQuartets << 2;
    i4 = b_n - nDone;
    if (i4 + 1 > 0) {
      for (x4_tmp = 0; x4_tmp <= i4; x4_tmp++) {
        i3 = nDone + x4_tmp;
        idx4[x4_tmp] = i3 + 1;
        x4[x4_tmp] = x->data[i3];
      }

      perm[1] = 0;
      perm[2] = 0;
      perm[3] = 0;
      if (i4 + 1 == 1) {
        perm[0] = 1;
      } else if (i4 + 1 == 2) {
        if (x4[0] <= x4[1]) {
          perm[0] = 1;
          perm[1] = 2;
        } else {
          perm[0] = 2;
          perm[1] = 1;
        }
      } else if (x4[0] <= x4[1]) {
        if (x4[1] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 2;
          perm[2] = 3;
        } else if (x4[0] <= x4[2]) {
          perm[0] = 1;
          perm[1] = 3;
          perm[2] = 2;
        } else {
          perm[0] = 3;
          perm[1] = 1;
          perm[2] = 2;
        }
      } else if (x4[0] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 1;
        perm[2] = 3;
      } else if (x4[1] <= x4[2]) {
        perm[0] = 2;
        perm[1] = 3;
        perm[2] = 1;
      } else {
        perm[0] = 3;
        perm[1] = 2;
        perm[2] = 1;
      }

      for (x4_tmp = 0; x4_tmp <= i4; x4_tmp++) {
        i1 = perm[x4_tmp] - 1;
        i2 = nDone + x4_tmp;
        idx->data[i2] = idx4[i1];
        x->data[i2] = x4[i1];
      }
    }

    i3 = 2;
    if (n > 1) {
      if (n >= 256) {
        i3 = n >> 8;
        for (i4 = 0; i4 < i3; i4++) {
          merge_pow2_block(idx, x, i4 << 8);
        }

        i3 <<= 8;
        i4 = n - i3;
        if (i4 > 0) {
          merge_block(idx, x, i3, i4, 2, iwork, xwork);
        }

        i3 = 8;
      }

      merge_block(idx, x, 0, n, i3, iwork, xwork);
    }

    emxFree_int32_T(&xwork);
    emxFree_int32_T(&iwork);
  }
}

static void bluestein(const emxArray_real_T *x, int nfft, int nRows, const
                      emxArray_real_T *costab, const emxArray_real_T *sintab,
                      const emxArray_real_T *costabinv, const emxArray_real_T
                      *sintabinv, const emxArray_creal_T *wwc, emxArray_creal_T *
                      y)
{
  int minNrowsNx;
  int a_re_tmp;
  int xidx;
  int k;
  emxArray_creal_T *fv;
  emxArray_creal_T *b_fv;
  double im;
  minNrowsNx = x->size[0];
  if (nRows < minNrowsNx) {
    minNrowsNx = nRows;
  }

  a_re_tmp = y->size[0];
  y->size[0] = nRows;
  emxEnsureCapacity_creal_T(y, a_re_tmp);
  if (nRows > x->size[0]) {
    a_re_tmp = y->size[0];
    y->size[0] = nRows;
    emxEnsureCapacity_creal_T(y, a_re_tmp);
    for (a_re_tmp = 0; a_re_tmp < nRows; a_re_tmp++) {
      y->data[a_re_tmp].re = 0.0;
      y->data[a_re_tmp].im = 0.0;
    }
  }

  xidx = 0;
  for (k = 0; k < minNrowsNx; k++) {
    a_re_tmp = (nRows + k) - 1;
    y->data[k].re = wwc->data[a_re_tmp].re * x->data[xidx];
    y->data[k].im = wwc->data[a_re_tmp].im * -x->data[xidx];
    xidx++;
  }

  a_re_tmp = minNrowsNx + 1;
  for (k = a_re_tmp; k <= nRows; k++) {
    y->data[k - 1].re = 0.0;
    y->data[k - 1].im = 0.0;
  }

  emxInit_creal_T(&fv, 1);
  emxInit_creal_T(&b_fv, 1);
  r2br_r2dit_trig_impl(y, nfft, costab, sintab, fv);
  r2br_r2dit_trig_impl(wwc, nfft, costab, sintab, b_fv);
  a_re_tmp = b_fv->size[0];
  b_fv->size[0] = fv->size[0];
  emxEnsureCapacity_creal_T(b_fv, a_re_tmp);
  xidx = fv->size[0];
  for (a_re_tmp = 0; a_re_tmp < xidx; a_re_tmp++) {
    im = fv->data[a_re_tmp].re * b_fv->data[a_re_tmp].im + fv->data[a_re_tmp].im
      * b_fv->data[a_re_tmp].re;
    b_fv->data[a_re_tmp].re = fv->data[a_re_tmp].re * b_fv->data[a_re_tmp].re -
      fv->data[a_re_tmp].im * b_fv->data[a_re_tmp].im;
    b_fv->data[a_re_tmp].im = im;
  }

  b_r2br_r2dit_trig(b_fv, nfft, costabinv, sintabinv, fv);
  xidx = 0;
  a_re_tmp = wwc->size[0];
  emxFree_creal_T(&b_fv);
  for (k = nRows; k <= a_re_tmp; k++) {
    y->data[xidx].re = wwc->data[k - 1].re * fv->data[k - 1].re + wwc->data[k -
      1].im * fv->data[k - 1].im;
    y->data[xidx].im = wwc->data[k - 1].re * fv->data[k - 1].im - wwc->data[k -
      1].im * fv->data[k - 1].re;
    xidx++;
  }

  emxFree_creal_T(&fv);
}

static void c_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1)
{
  unsigned int inSize[8];
  cell_wrap_12 varSizes[1];
  int i;
  boolean_T exitg1;
  static const double b_dv[201] = { 0.0004601909232419399,
    0.00024512817754334683, -0.00010894899700275049, 1.7787096375480365E-5,
    -0.00028447267936516706, -0.00018612857215221534, -0.00030266318149454574,
    -8.4634572385681566E-5, -1.0541079307223541E-6, 0.00026586693661405185,
    0.00034224120005005228, 0.00042265115080399539, 0.00026842570640368759,
    7.2432175039010115E-5, -0.00024442716727750405, -0.00046707130287899034,
    -0.00059992675511320436, -0.00050117765730489454, -0.00024103565016007821,
    0.00016542649815662496, 0.00054702160408216446, 0.00080293472386970392,
    0.00079450583187648538, 0.00051712221286267937, 1.3468580772189826E-5,
    -0.00054878822094487224, -0.00099355149883922824, -0.0011381211998548323,
    -0.00090654223989934386, -0.00032794451183452332, 0.00042786183328932239,
    0.0011223991551029919, 0.0015015759477942044, 0.0014024580258877879,
    0.00080439900690228085, -0.00013530092693132923, -0.0011284903658474877,
    -0.0018341008780561046, -0.0019791572176802289, -0.0014546843338779903,
    -0.00037539438285982488, 0.00094200083155430016, 0.0020651898255886385,
    0.0025877778169775935, 0.002270250246701059, 0.0011410524106148887,
    -0.00048917823260357892, -0.0021067001871706856, -0.0031539654036339161,
    -0.0032168936924832424, -0.00218177152058645, -0.00030166029707744796,
    0.0018562646954695076, 0.0035772879820450743, 0.0042308298910938942,
    0.0034949112374553768, 0.0014944305974102863, -0.0012008908925206293,
    -0.003731557041047313, -0.0052161672890271441, -0.0050510840050989308,
    -0.003141837182545073, 1.8390971177878025E-5, 0.0034638753024331878,
    0.0060427820997277174, 0.0067929579977716609, 0.0052871552780851868,
    0.0018279271249860213, -0.0025875359150974607, -0.0065414256162513815,
    -0.0086373702953245687, -0.0079766109852478281, -0.0045110089007698107,
    0.0008574295321834034, 0.0064877556446874748, 0.010480820755812376,
    0.01129470451018165, 0.0083026678163978119, 0.0021022736026320319,
    -0.0055518620715592406, -0.012207937238474289, -0.015458864266378341,
    -0.013752954719279908, -0.0070165823450612811, 0.0031334619130527889,
    0.013702049054729189, 0.021112425703244633, 0.022292430004626676,
    0.015746286621870696, 0.0022828395119217628, -0.014856652929929248,
    -0.030573050674830005, -0.039091042559012537, -0.03546940490333958,
    -0.01704594514656281, 0.015586365934210431, 0.058371374233241895,
    0.10445562167405839, 0.14560229812622486, 0.17402159299209566,
    0.18416403021700883, 0.17402159299209566, 0.14560229812622486,
    0.10445562167405839, 0.058371374233241895, 0.015586365934210431,
    -0.01704594514656281, -0.03546940490333958, -0.039091042559012537,
    -0.030573050674830005, -0.014856652929929248, 0.0022828395119217628,
    0.015746286621870696, 0.022292430004626676, 0.021112425703244633,
    0.013702049054729189, 0.0031334619130527889, -0.0070165823450612811,
    -0.013752954719279908, -0.015458864266378341, -0.012207937238474289,
    -0.0055518620715592406, 0.0021022736026320319, 0.0083026678163978119,
    0.01129470451018165, 0.010480820755812376, 0.0064877556446874748,
    0.0008574295321834034, -0.0045110089007698107, -0.0079766109852478281,
    -0.0086373702953245687, -0.0065414256162513815, -0.0025875359150974607,
    0.0018279271249860213, 0.0052871552780851868, 0.0067929579977716609,
    0.0060427820997277174, 0.0034638753024331878, 1.8390971177878025E-5,
    -0.003141837182545073, -0.0050510840050989308, -0.0052161672890271441,
    -0.003731557041047313, -0.0012008908925206293, 0.0014944305974102863,
    0.0034949112374553768, 0.0042308298910938942, 0.0035772879820450743,
    0.0018562646954695076, -0.00030166029707744796, -0.00218177152058645,
    -0.0032168936924832424, -0.0031539654036339161, -0.0021067001871706856,
    -0.00048917823260357892, 0.0011410524106148887, 0.002270250246701059,
    0.0025877778169775935, 0.0020651898255886385, 0.00094200083155430016,
    -0.00037539438285982488, -0.0014546843338779903, -0.0019791572176802289,
    -0.0018341008780561046, -0.0011284903658474877, -0.00013530092693132923,
    0.00080439900690228085, 0.0014024580258877879, 0.0015015759477942044,
    0.0011223991551029919, 0.00042786183328932239, -0.00032794451183452332,
    -0.00090654223989934386, -0.0011381211998548323, -0.00099355149883922824,
    -0.00054878822094487224, 1.3468580772189826E-5, 0.00051712221286267937,
    0.00079450583187648538, 0.00080293472386970392, 0.00054702160408216446,
    0.00016542649815662496, -0.00024103565016007821, -0.00050117765730489454,
    -0.00059992675511320436, -0.00046707130287899034, -0.00024442716727750405,
    7.2432175039010115E-5, 0.00026842570640368759, 0.00042265115080399539,
    0.00034224120005005228, 0.00026586693661405185, -1.0541079307223541E-6,
    -8.4634572385681566E-5, -0.00030266318149454574, -0.00018612857215221534,
    -0.00028447267936516706, 1.7787096375480365E-5, -0.00010894899700275049,
    0.00024512817754334683, 0.0004601909232419399 };

  dspcodegen_FIRFilter_3 *b_obj;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    varSizes[0].f1[0] = static_cast<unsigned int>(varargin_1->size[0]);
    varSizes[0].f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes[0].f1[i + 2] = 1U;
    }

    obj->inputVarSize[0] = varSizes[0];
    iobj_0->isInitialized = 0;

    /* System object Constructor function: dsp.FIRFilter */
    iobj_0->cSFunObject.P0_InitialStates = 0.0;
    for (i = 0; i < 201; i++) {
      iobj_0->cSFunObject.P1_Coefficients[i] = b_dv[i];
    }

    iobj_0->matlabCodegenIsDeleted = false;
    obj->FilterObj = iobj_0;
    obj->NumChannels = 1;
    obj->isSetupComplete = true;
    b_obj = obj->FilterObj;
    if (b_obj->isInitialized == 1) {
      /* System object Initialization function: dsp.FIRFilter */
      for (i = 0; i < 200; i++) {
        b_obj->cSFunObject.W0_states[i] = b_obj->cSFunObject.P0_InitialStates;
      }
    }
  }

  inSize[0] = static_cast<unsigned int>(varargin_1->size[0]);
  inSize[1] = 1U;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1U;
  }

  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != inSize[i]) {
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = inSize[i];
      }

      exitg1 = true;
    } else {
      i++;
    }
  }

  LPHPFilterBase_stepImpl(obj, varargin_1, varargout_1);
}

static void c_findPeaksSeparatedByMoreThanM(const double y[264000], const double
  x[264000], const emxArray_int32_T *iPk, emxArray_int32_T *idx)
{
  emxArray_real_T *locs_temp;
  int i;
  int loop_ub;
  emxArray_int32_T *c_sortIdx;
  emxArray_int32_T *r;
  emxArray_boolean_T *idelete;
  emxArray_boolean_T *r1;
  int b_i;
  int end;
  emxArray_int32_T *r2;
  int i1;
  if (iPk->size[0] == 0) {
    idx->size[0] = 0;
  } else {
    emxInit_real_T(&locs_temp, 1);
    i = locs_temp->size[0];
    locs_temp->size[0] = iPk->size[0];
    emxEnsureCapacity_real_T(locs_temp, i);
    loop_ub = iPk->size[0];
    for (i = 0; i < loop_ub; i++) {
      locs_temp->data[i] = y[iPk->data[i] - 1];
    }

    emxInit_int32_T(&c_sortIdx, 1);
    emxInit_int32_T(&r, 1);
    sortIdx(locs_temp, r);
    i = c_sortIdx->size[0];
    c_sortIdx->size[0] = r->size[0];
    emxEnsureCapacity_int32_T(c_sortIdx, i);
    loop_ub = r->size[0];
    for (i = 0; i < loop_ub; i++) {
      c_sortIdx->data[i] = r->data[i];
    }

    i = locs_temp->size[0];
    locs_temp->size[0] = c_sortIdx->size[0];
    emxEnsureCapacity_real_T(locs_temp, i);
    loop_ub = c_sortIdx->size[0];
    for (i = 0; i < loop_ub; i++) {
      locs_temp->data[i] = x[iPk->data[c_sortIdx->data[i] - 1] - 1];
    }

    emxInit_boolean_T(&idelete, 1);
    i = idelete->size[0];
    idelete->size[0] = c_sortIdx->size[0];
    emxEnsureCapacity_boolean_T(idelete, i);
    loop_ub = c_sortIdx->size[0];
    for (i = 0; i < loop_ub; i++) {
      idelete->data[i] = false;
    }

    i = c_sortIdx->size[0];
    emxInit_boolean_T(&r1, 1);
    for (b_i = 0; b_i < i; b_i++) {
      if (!idelete->data[b_i]) {
        end = r1->size[0];
        r1->size[0] = locs_temp->size[0];
        emxEnsureCapacity_boolean_T(r1, end);
        loop_ub = locs_temp->size[0];
        for (end = 0; end < loop_ub; end++) {
          i1 = iPk->data[c_sortIdx->data[b_i] - 1] - 1;
          r1->data[end] = ((locs_temp->data[end] >= x[i1] - 19200.0) &&
                           (locs_temp->data[end] <= x[i1] + 19200.0));
        }

        loop_ub = idelete->size[0];
        for (end = 0; end < loop_ub; end++) {
          idelete->data[end] = (idelete->data[end] || r1->data[end]);
        }

        idelete->data[b_i] = false;
      }
    }

    emxFree_boolean_T(&r1);
    emxFree_real_T(&locs_temp);
    end = idelete->size[0] - 1;
    loop_ub = 0;
    for (b_i = 0; b_i <= end; b_i++) {
      if (!idelete->data[b_i]) {
        loop_ub++;
      }
    }

    emxInit_int32_T(&r2, 1);
    i = r2->size[0];
    r2->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(r2, i);
    loop_ub = 0;
    for (b_i = 0; b_i <= end; b_i++) {
      if (!idelete->data[b_i]) {
        r2->data[loop_ub] = b_i + 1;
        loop_ub++;
      }
    }

    emxFree_boolean_T(&idelete);
    i = r->size[0];
    r->size[0] = r2->size[0];
    emxEnsureCapacity_int32_T(r, i);
    loop_ub = r2->size[0];
    for (i = 0; i < loop_ub; i++) {
      r->data[i] = c_sortIdx->data[r2->data[i] - 1];
    }

    emxFree_int32_T(&r2);
    emxFree_int32_T(&c_sortIdx);
    sort(r);
    i = idx->size[0];
    idx->size[0] = r->size[0];
    emxEnsureCapacity_int32_T(idx, i);
    loop_ub = r->size[0];
    for (i = 0; i < loop_ub; i++) {
      idx->data[i] = r->data[i];
    }

    emxFree_int32_T(&r);
  }
}

static void c_findpeaks(const double Yin[2160000], double varargin_4,
  emxArray_real_T *Ypk, emxArray_real_T *Xpk)
{
  emxArray_int32_T *iInflect;
  emxArray_int32_T *iFinite;
  emxArray_int32_T *iInfinite;
  int k;
  int nPk;
  int nInf;
  char dir;
  int kfirst;
  double ykfirst;
  boolean_T isinfykfirst;
  double yk;
  boolean_T isinfyk;
  char previousdir;
  emxArray_int32_T *iPk;
  emxArray_int32_T *c;
  emxArray_int32_T *idx;
  static double b_dv[2160000];
  emxArray_int32_T *b_iPk;
  emxInit_int32_T(&iInflect, 1);
  emxInit_int32_T(&iFinite, 1);
  emxInit_int32_T(&iInfinite, 1);
  k = iFinite->size[0];
  iFinite->size[0] = 2160000;
  emxEnsureCapacity_int32_T(iFinite, k);
  k = iInfinite->size[0];
  iInfinite->size[0] = 2160000;
  emxEnsureCapacity_int32_T(iInfinite, k);
  nPk = -1;
  nInf = -1;
  dir = 'n';
  kfirst = -1;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 0; k < 2160000; k++) {
    yk = Yin[k];
    if (rtIsNaN(Yin[k])) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(Yin[k]) && (Yin[k] > 0.0)) {
      isinfyk = true;
      nInf++;
      iInfinite->data[nInf] = k + 1;
    } else {
      isinfyk = false;
    }

    if (yk != ykfirst) {
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
      } else if (yk < ykfirst) {
        dir = 'd';
        if (('d' != previousdir) && (previousdir == 'i')) {
          nPk++;
          iFinite->data[nPk] = kfirst + 1;
        }
      } else {
        dir = 'i';
      }

      ykfirst = yk;
      kfirst = k;
      isinfykfirst = isinfyk;
    }
  }

  if (1 > nPk + 1) {
    kfirst = -1;
  } else {
    kfirst = nPk;
  }

  k = iInflect->size[0];
  iInflect->size[0] = kfirst + 1;
  emxEnsureCapacity_int32_T(iInflect, k);
  for (k = 0; k <= kfirst; k++) {
    iInflect->data[k] = iFinite->data[k];
  }

  k = iFinite->size[0];
  iFinite->size[0] = iInflect->size[0];
  emxEnsureCapacity_int32_T(iFinite, k);
  kfirst = iInflect->size[0];
  for (k = 0; k < kfirst; k++) {
    iFinite->data[k] = iInflect->data[k];
  }

  if (1 > nInf + 1) {
    kfirst = -1;
  } else {
    kfirst = nInf;
  }

  k = iInflect->size[0];
  iInflect->size[0] = kfirst + 1;
  emxEnsureCapacity_int32_T(iInflect, k);
  for (k = 0; k <= kfirst; k++) {
    iInflect->data[k] = iInfinite->data[k];
  }

  k = iInfinite->size[0];
  iInfinite->size[0] = iInflect->size[0];
  emxEnsureCapacity_int32_T(iInfinite, k);
  kfirst = iInflect->size[0];
  for (k = 0; k < kfirst; k++) {
    iInfinite->data[k] = iInflect->data[k];
  }

  emxInit_int32_T(&iPk, 1);
  k = iPk->size[0];
  iPk->size[0] = iFinite->size[0];
  emxEnsureCapacity_int32_T(iPk, k);
  nPk = 0;
  kfirst = iFinite->size[0];
  for (k = 0; k < kfirst; k++) {
    ykfirst = Yin[iFinite->data[k] - 1];
    if (ykfirst > varargin_4) {
      if ((Yin[iFinite->data[k] - 2] > Yin[iFinite->data[k]]) || rtIsNaN
          (Yin[iFinite->data[k]])) {
        yk = Yin[iFinite->data[k] - 2];
      } else {
        yk = Yin[iFinite->data[k]];
      }

      if (ykfirst - yk >= 0.0) {
        nPk++;
        iPk->data[nPk - 1] = iFinite->data[k];
      }
    }
  }

  emxInit_int32_T(&c, 1);
  k = iPk->size[0];
  if (1 > nPk) {
    iPk->size[0] = 0;
  } else {
    iPk->size[0] = nPk;
  }

  emxEnsureCapacity_int32_T(iPk, k);
  do_vectors(iPk, iInfinite, c, iInflect, iFinite);
  emxFree_int32_T(&iInfinite);
  emxFree_int32_T(&iFinite);
  emxFree_int32_T(&iPk);
  emxFree_int32_T(&iInflect);
  for (k = 0; k < 2160000; k++) {
    b_dv[k] = static_cast<double>(k) + 1.0;
  }

  emxInit_int32_T(&idx, 1);
  e_findPeaksSeparatedByMoreThanM(Yin, b_dv, c, idx);
  emxInit_int32_T(&b_iPk, 1);
  if (idx->size[0] > 2160000) {
    k = b_iPk->size[0];
    b_iPk->size[0] = 2160000;
    emxEnsureCapacity_int32_T(b_iPk, k);
    for (k = 0; k < 2160000; k++) {
      b_iPk->data[k] = idx->data[k];
    }

    k = idx->size[0];
    idx->size[0] = b_iPk->size[0];
    emxEnsureCapacity_int32_T(idx, k);
    kfirst = b_iPk->size[0];
    for (k = 0; k < kfirst; k++) {
      idx->data[k] = b_iPk->data[k];
    }
  }

  k = b_iPk->size[0];
  b_iPk->size[0] = idx->size[0];
  emxEnsureCapacity_int32_T(b_iPk, k);
  kfirst = idx->size[0];
  for (k = 0; k < kfirst; k++) {
    b_iPk->data[k] = c->data[idx->data[k] - 1];
  }

  emxFree_int32_T(&c);
  emxFree_int32_T(&idx);
  k = Ypk->size[0];
  Ypk->size[0] = b_iPk->size[0];
  emxEnsureCapacity_real_T(Ypk, k);
  kfirst = b_iPk->size[0];
  for (k = 0; k < kfirst; k++) {
    Ypk->data[k] = Yin[b_iPk->data[k] - 1];
  }

  k = Xpk->size[0];
  Xpk->size[0] = b_iPk->size[0];
  emxEnsureCapacity_real_T(Xpk, k);
  kfirst = b_iPk->size[0];
  for (k = 0; k < kfirst; k++) {
    Xpk->data[k] = b_iPk->data[k];
  }

  emxFree_int32_T(&b_iPk);
}

static void c_matlabCodegenHandle_matlabCod(dsp_LowpassFilter *obj)
{
  dspcodegen_FIRFilter_3 *b_obj;
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        b_obj = obj->FilterObj;
        if (b_obj->isInitialized == 1) {
          b_obj->isInitialized = 2;
        }

        obj->NumChannels = -1;
      }
    }
  }
}

static void compute(const emxArray_real_T *cali1, const emxArray_real_T *cali2,
                    const emxArray_real_T *cali3, const emxArray_real_T *test,
                    double b_gamma, double ls, double fc, emxArray_real_T *A,
                    emxArray_real_T *ho, double *score)
{
  emxArray_real_T *b_cali1;
  int loop_ub;
  int i;
  emxArray_creal_T *X;
  emxArray_creal_T *Y1;
  emxArray_creal_T *Y2;
  emxArray_real_T *h2;
  int nx;
  int k;
  emxArray_real_T *y;
  emxArray_creal_T *Y;
  emxArray_creal_T *r;
  double b_r;
  emxArray_real_T *r1;
  double X_im;
  double br;
  emxArray_real_T *h1;
  emxArray_real_T *b_ho;
  double tail;
  int i1;
  emxArray_real_T *b_y;
  emxArray_creal_T *D;
  double ar;
  double ai;
  emxArray_real_T *ho_list;
  double head;
  double Y1_re;
  double Y1_im;
  double b_Y1_re;
  double b_Y1_im;
  double Y1_re_tmp;
  double Y1_im_tmp;
  double c_Y1_re;
  double c_Y1_im;
  double d_Y1_re;
  emxArray_real_T *r2;
  double c_y[85];
  boolean_T exitg1;
  double ix_data[169];
  int ix_size[1];
  double iy_data[169];
  int iy_size[1];
  double x_data[169];
  static const double w[84] = { 0.00033546262790251185, 0.00047148945157974036,
    0.00065778833628695322, 0.00091093357046006672, 0.0012521997064553919,
    0.0017086253257975435, 0.0023142295376756888, 0.0031113751364731427,
    0.0041522612718683594, 0.0055005145771752752, 0.0072328310160072688,
    0.0094406015591651828, 0.012231433824900113, 0.015730460003243442,
    0.020081300127452323, 0.025446530828967, 0.032007495236220915,
    0.039963282023239365, 0.0495287032596804, 0.0609311140501642,
    0.0744059440391564, 0.090190853159685447, 0.10851848209843293,
    0.12960784126658714, 0.15365446867062066, 0.18081958353647981,
    0.21121856390443045, 0.24490917633742343, 0.28188007692128375,
    0.3220401767624777, 0.36520951401377877, 0.41111229050718745,
    0.45937270815367626, 0.50951417431374191, 0.56096233507002591,
    0.61305224273982761, 0.6650397745775618, 0.71611720244767008,
    0.7654325804246771, 0.81211238334313562, 0.85528661024692287,
    0.89411537866055091, 0.92781589369246076, 0.95568859279783025,
    0.97714125153803022, 0.99170989223645167, 0.99907546522247848,
    0.99907546522247848, 0.99170989223645167, 0.97714125153803022,
    0.95568859279783025, 0.92781589369246076, 0.89411537866055091,
    0.85528661024692287, 0.81211238334313562, 0.7654325804246771,
    0.71611720244767008, 0.6650397745775618, 0.61305224273982761,
    0.56096233507002591, 0.50951417431374191, 0.45937270815367626,
    0.41111229050718745, 0.36520951401377877, 0.3220401767624777,
    0.28188007692128375, 0.24490917633742343, 0.21121856390443045,
    0.18081958353647981, 0.15365446867062066, 0.12960784126658714,
    0.10851848209843293, 0.090190853159685447, 0.0744059440391564,
    0.0609311140501642, 0.0495287032596804, 0.039963282023239365,
    0.032007495236220915, 0.025446530828967, 0.020081300127452323,
    0.015730460003243442, 0.012231433824900113, 0.0094406015591651828,
    0.0072328310160072688 };

  emxInit_real_T(&b_cali1, 1);

  /*  Crop Raw Signal */
  /*  Estimate source reflection Hs and attenuation Hc */
  loop_ub = cali1->size[0];
  i = b_cali1->size[0];
  b_cali1->size[0] = cali1->size[0];
  emxEnsureCapacity_real_T(b_cali1, i);
  for (i = 0; i < loop_ub; i++) {
    b_cali1->data[i] = cali1->data[i];
  }

  emxInit_creal_T(&X, 1);
  b_fft(b_cali1, static_cast<double>(cali1->size[0]), X);
  loop_ub = cali2->size[0];
  i = b_cali1->size[0];
  b_cali1->size[0] = cali2->size[0];
  emxEnsureCapacity_real_T(b_cali1, i);
  for (i = 0; i < loop_ub; i++) {
    b_cali1->data[i] = cali2->data[i];
  }

  emxInit_creal_T(&Y1, 1);
  b_fft(b_cali1, static_cast<double>(cali1->size[0]), Y1);
  loop_ub = cali3->size[0];
  i = b_cali1->size[0];
  b_cali1->size[0] = cali3->size[0];
  emxEnsureCapacity_real_T(b_cali1, i);
  for (i = 0; i < loop_ub; i++) {
    b_cali1->data[i] = cali3->data[i];
  }

  emxInit_creal_T(&Y2, 1);
  emxInit_real_T(&h2, 1);
  b_fft(b_cali1, static_cast<double>(cali1->size[0]), Y2);
  nx = X->size[0];
  i = h2->size[0];
  h2->size[0] = X->size[0];
  emxEnsureCapacity_real_T(h2, i);
  for (k = 0; k < nx; k++) {
    h2->data[k] = rt_hypotd_snf(X->data[k].re, X->data[k].im);
  }

  emxInit_real_T(&y, 1);
  i = y->size[0];
  y->size[0] = h2->size[0];
  emxEnsureCapacity_real_T(y, i);
  nx = h2->size[0];
  for (k = 0; k < nx; k++) {
    y->data[k] = rt_powd_snf(h2->data[k], 2.0);
  }

  emxInit_creal_T(&Y, 1);
  i = Y->size[0];
  Y->size[0] = X->size[0];
  emxEnsureCapacity_creal_T(Y, i);
  loop_ub = X->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_r = X->data[i].re * Y1->data[i].re - -X->data[i].im * Y1->data[i].im;
    X_im = X->data[i].re * Y1->data[i].im + -X->data[i].im * Y1->data[i].re;
    br = y->data[i] + b_gamma;
    if (X_im == 0.0) {
      Y->data[i].re = b_r / br;
      Y->data[i].im = 0.0;
    } else if (b_r == 0.0) {
      Y->data[i].re = 0.0;
      Y->data[i].im = X_im / br;
    } else {
      Y->data[i].re = b_r / br;
      Y->data[i].im = X_im / br;
    }
  }

  emxInit_creal_T(&r, 1);
  emxInit_real_T(&r1, 1);
  ifft(Y, r);
  i = r1->size[0];
  r1->size[0] = r->size[0];
  emxEnsureCapacity_real_T(r1, i);
  loop_ub = r->size[0];
  for (i = 0; i < loop_ub; i++) {
    r1->data[i] = r->data[i].re;
  }

  emxInit_real_T(&h1, 1);
  emxInit_real_T(&b_ho, 1);
  fftshift(r1);
  mLowpass(r1, fc, b_ho);
  fftshift(b_ho);
  i = h1->size[0];
  h1->size[0] = b_ho->size[0];
  emxEnsureCapacity_real_T(h1, i);
  loop_ub = b_ho->size[0];
  for (i = 0; i < loop_ub; i++) {
    h1->data[i] = b_ho->data[i];
  }

  nx = X->size[0];
  i = h2->size[0];
  h2->size[0] = X->size[0];
  emxEnsureCapacity_real_T(h2, i);
  for (k = 0; k < nx; k++) {
    h2->data[k] = rt_hypotd_snf(X->data[k].re, X->data[k].im);
  }

  i = y->size[0];
  y->size[0] = h2->size[0];
  emxEnsureCapacity_real_T(y, i);
  nx = h2->size[0];
  for (k = 0; k < nx; k++) {
    y->data[k] = rt_powd_snf(h2->data[k], 2.0);
  }

  i = Y->size[0];
  Y->size[0] = X->size[0];
  emxEnsureCapacity_creal_T(Y, i);
  loop_ub = X->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_r = X->data[i].re * Y2->data[i].re - -X->data[i].im * Y2->data[i].im;
    X_im = X->data[i].re * Y2->data[i].im + -X->data[i].im * Y2->data[i].re;
    br = y->data[i] + b_gamma;
    if (X_im == 0.0) {
      Y->data[i].re = b_r / br;
      Y->data[i].im = 0.0;
    } else if (b_r == 0.0) {
      Y->data[i].re = 0.0;
      Y->data[i].im = X_im / br;
    } else {
      Y->data[i].re = b_r / br;
      Y->data[i].im = X_im / br;
    }
  }

  ifft(Y, r);
  i = r1->size[0];
  r1->size[0] = r->size[0];
  emxEnsureCapacity_real_T(r1, i);
  loop_ub = r->size[0];
  for (i = 0; i < loop_ub; i++) {
    r1->data[i] = r->data[i].re;
  }

  fftshift(r1);
  mLowpass(r1, fc, b_ho);
  fftshift(b_ho);
  i = h2->size[0];
  h2->size[0] = b_ho->size[0];
  emxEnsureCapacity_real_T(h2, i);
  loop_ub = b_ho->size[0];
  for (i = 0; i < loop_ub; i++) {
    h2->data[i] = b_ho->data[i];
  }

  b_r = rt_roundd_snf((ls - 10.0) * 2.0 / 34300.0 * 48000.0);
  tail = rt_roundd_snf((2.0 * ls - 10.0) * 2.0 / 34300.0 * 48000.0);
  if (b_r + 1.0 > tail) {
    i = 0;
    nx = 0;
    k = 0;
    i1 = 0;
  } else {
    i = static_cast<int>(b_r + 1.0) - 1;
    nx = static_cast<int>(tail);
    k = i;
    i1 = nx;
  }

  loop_ub = nx - i;
  nx = y->size[0];
  y->size[0] = loop_ub;
  emxEnsureCapacity_real_T(y, nx);
  for (nx = 0; nx < loop_ub; nx++) {
    y->data[nx] = h1->data[i + nx];
  }

  i = h1->size[0];
  h1->size[0] = y->size[0];
  emxEnsureCapacity_real_T(h1, i);
  loop_ub = y->size[0];
  for (i = 0; i < loop_ub; i++) {
    h1->data[i] = y->data[i];
  }

  loop_ub = i1 - k;
  i = y->size[0];
  y->size[0] = loop_ub;
  emxEnsureCapacity_real_T(y, i);
  for (i = 0; i < loop_ub; i++) {
    y->data[i] = -h2->data[k + i];
  }

  i = h2->size[0];
  h2->size[0] = y->size[0];
  emxEnsureCapacity_real_T(h2, i);
  loop_ub = y->size[0];
  for (i = 0; i < loop_ub; i++) {
    h2->data[i] = y->data[i];
  }

  emxInit_real_T(&b_y, 2);
  b_r = mFindDelay(h1, h2);

  /*  gain = abs(fft(-h2(head+1*delta:tail+1*delta)))./abs(fft(h1(head:tail))); */
  /*  gain(1:2) = 1;  */
  /*  gain(end) = 1; */
  /*  gain(24:end-22) = 1; */
  /*  gain = smooth(gain,3); */
  /*  gain = interp1(1:length(gain), gain, (1:N)/N*length(gain), 'spline'); */
  emxFree_real_T(&h1);
  if (cali1->size[0] < 1) {
    b_y->size[0] = 1;
    b_y->size[1] = 0;
  } else {
    i = b_y->size[0] * b_y->size[1];
    b_y->size[0] = 1;
    b_y->size[1] = cali1->size[0];
    emxEnsureCapacity_real_T(b_y, i);
    loop_ub = cali1->size[0] - 1;
    for (i = 0; i <= loop_ub; i++) {
      b_y->data[i] = static_cast<double>(i) + 1.0;
    }
  }

  emxInit_creal_T(&D, 1);
  i = D->size[0];
  D->size[0] = b_y->size[1];
  emxEnsureCapacity_creal_T(D, i);
  loop_ub = b_y->size[1];
  for (i = 0; i < loop_ub; i++) {
    ar = -0.0 * b_y->data[i];
    ai = -6.2831853071795862 * b_y->data[i];
    if (ai == 0.0) {
      br = ar / static_cast<double>(cali1->size[0]);
      X_im = 0.0;
    } else if (ar == 0.0) {
      br = 0.0;
      X_im = ai / static_cast<double>(cali1->size[0]);
    } else {
      br = rtNaN;
      X_im = ai / static_cast<double>(cali1->size[0]);
    }

    D->data[i].re = b_r * br;
    D->data[i].im = b_r * X_im;
  }

  i = b_cali1->size[0];
  b_cali1->size[0] = b_y->size[1];
  emxEnsureCapacity_real_T(b_cali1, i);
  loop_ub = b_y->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_cali1->data[i] = b_y->data[i];
  }

  emxFree_real_T(&b_y);
  nx = b_cali1->size[0];
  for (k = 0; k < nx; k++) {
    if (D->data[k].im == 0.0) {
      D->data[k].re = std::exp(D->data[k].re);
      D->data[k].im = 0.0;
    } else if (rtIsInf(D->data[k].im) && rtIsInf(D->data[k].re) && (D->data[k].
                re < 0.0)) {
      D->data[k].re = 0.0;
      D->data[k].im = 0.0;
    } else {
      b_r = std::exp(D->data[k].re / 2.0);
      D->data[k].re = b_r * (b_r * std::cos(D->data[k].im));
      D->data[k].im = b_r * (b_r * std::sin(D->data[k].im));
    }
  }

  emxInit_real_T(&ho_list, 1);

  /*  Hc = (conj(den).*num)./(abs(den).^2+gamma); */
  /*  HcHs = (conj(den).*num)./(abs(den).^2+gamma); */
  /*  Object Reconstruction */
  head = (static_cast<double>(cali1->size[0]) / 2.0 + -28.0) + 1.0;
  tail = static_cast<double>(cali1->size[0]) / 2.0 + 166.0;
  loop_ub = static_cast<int>((tail - head) + 1.0);
  i = ho_list->size[0];
  ho_list->size[0] = loop_ub;
  emxEnsureCapacity_real_T(ho_list, i);
  for (i = 0; i < loop_ub; i++) {
    ho_list->data[i] = 0.0;
  }

  i = A->size[0];
  A->size[0] = loop_ub;
  emxEnsureCapacity_real_T(A, i);
  for (i = 0; i < loop_ub; i++) {
    A->data[i] = 0.0;
  }

  loop_ub = test->size[0];
  i = b_cali1->size[0];
  b_cali1->size[0] = test->size[0];
  emxEnsureCapacity_real_T(b_cali1, i);
  for (i = 0; i < loop_ub; i++) {
    b_cali1->data[i] = test->data[i];
  }

  b_fft(b_cali1, static_cast<double>(cali1->size[0]), Y);
  i = D->size[0];
  D->size[0] = X->size[0];
  emxEnsureCapacity_creal_T(D, i);
  loop_ub = X->size[0];
  emxFree_real_T(&b_cali1);
  for (i = 0; i < loop_ub; i++) {
    Y1_re = Y1->data[i].re + (Y2->data[i].re * D->data[i].re - Y2->data[i].im *
      D->data[i].im);
    Y1_im = Y1->data[i].im + (Y2->data[i].re * D->data[i].im + Y2->data[i].im *
      D->data[i].re);
    b_Y1_re = Y1->data[i].re * Y2->data[i].re - Y1->data[i].im * Y2->data[i].im;
    b_Y1_im = Y1->data[i].re * Y2->data[i].im + Y1->data[i].im * Y2->data[i].re;
    br = D->data[i].re + 1.0;
    X_im = D->data[i].im;
    Y1_re_tmp = Y1->data[i].re - Y2->data[i].re;
    Y1_im_tmp = Y1->data[i].im - Y2->data[i].im;
    c_Y1_re = Y1_re_tmp * D->data[i].re - Y1_im_tmp * D->data[i].im;
    c_Y1_im = Y1_re_tmp * D->data[i].im + Y1_im_tmp * D->data[i].re;
    d_Y1_re = c_Y1_re * X->data[i].re - c_Y1_im * X->data[i].im;
    c_Y1_im = c_Y1_re * X->data[i].im + c_Y1_im * X->data[i].re;
    ar = (Y1_re * X->data[i].re - Y1_im * X->data[i].im) - (b_Y1_re * br -
      b_Y1_im * X_im);
    ai = (Y1_re * X->data[i].im + Y1_im * X->data[i].re) - (b_Y1_re * X_im +
      b_Y1_im * br);
    if (c_Y1_im == 0.0) {
      if (ai == 0.0) {
        Y1_re = ar / d_Y1_re;
        Y1_im = 0.0;
      } else if (ar == 0.0) {
        Y1_re = 0.0;
        Y1_im = ai / d_Y1_re;
      } else {
        Y1_re = ar / d_Y1_re;
        Y1_im = ai / d_Y1_re;
      }
    } else if (d_Y1_re == 0.0) {
      if (ar == 0.0) {
        Y1_re = ai / c_Y1_im;
        Y1_im = 0.0;
      } else if (ai == 0.0) {
        Y1_re = 0.0;
        Y1_im = -(ar / c_Y1_im);
      } else {
        Y1_re = ai / c_Y1_im;
        Y1_im = -(ar / c_Y1_im);
      }
    } else {
      br = std::abs(d_Y1_re);
      b_r = std::abs(c_Y1_im);
      if (br > b_r) {
        X_im = c_Y1_im / d_Y1_re;
        b_r = d_Y1_re + X_im * c_Y1_im;
        Y1_re = (ar + X_im * ai) / b_r;
        Y1_im = (ai - X_im * ar) / b_r;
      } else if (b_r == br) {
        if (d_Y1_re > 0.0) {
          X_im = 0.5;
        } else {
          X_im = -0.5;
        }

        if (c_Y1_im > 0.0) {
          b_r = 0.5;
        } else {
          b_r = -0.5;
        }

        Y1_re = (ar * X_im + ai * b_r) / br;
        Y1_im = (ai * X_im - ar * b_r) / br;
      } else {
        X_im = d_Y1_re / c_Y1_im;
        b_r = c_Y1_im + X_im * d_Y1_re;
        Y1_re = (X_im * ar + ai) / b_r;
        Y1_im = (X_im * ai - ar) / b_r;
      }
    }

    br = D->data[i].re + 1.0;
    X_im = D->data[i].im;
    b_Y1_re = Y1_re_tmp * D->data[i].re - Y1_im_tmp * D->data[i].im;
    b_Y1_im = Y1_re_tmp * D->data[i].im + Y1_im_tmp * D->data[i].re;
    ar = ((Y1->data[i].re * D->data[i].re - Y1->data[i].im * D->data[i].im) +
          Y2->data[i].re) - (X->data[i].re * br - X->data[i].im * X_im);
    ai = ((Y1->data[i].re * D->data[i].im + Y1->data[i].im * D->data[i].re) +
          Y2->data[i].im) - (X->data[i].re * X_im + X->data[i].im * br);
    if (b_Y1_im == 0.0) {
      if (ai == 0.0) {
        c_Y1_re = ar / b_Y1_re;
        b_Y1_im = 0.0;
      } else if (ar == 0.0) {
        c_Y1_re = 0.0;
        b_Y1_im = ai / b_Y1_re;
      } else {
        c_Y1_re = ar / b_Y1_re;
        b_Y1_im = ai / b_Y1_re;
      }
    } else if (b_Y1_re == 0.0) {
      if (ar == 0.0) {
        c_Y1_re = ai / b_Y1_im;
        b_Y1_im = 0.0;
      } else if (ai == 0.0) {
        c_Y1_re = 0.0;
        b_Y1_im = -(ar / b_Y1_im);
      } else {
        c_Y1_re = ai / b_Y1_im;
        b_Y1_im = -(ar / b_Y1_im);
      }
    } else {
      br = std::abs(b_Y1_re);
      b_r = std::abs(b_Y1_im);
      if (br > b_r) {
        X_im = b_Y1_im / b_Y1_re;
        b_r = b_Y1_re + X_im * b_Y1_im;
        c_Y1_re = (ar + X_im * ai) / b_r;
        b_Y1_im = (ai - X_im * ar) / b_r;
      } else if (b_r == br) {
        if (b_Y1_re > 0.0) {
          X_im = 0.5;
        } else {
          X_im = -0.5;
        }

        if (b_Y1_im > 0.0) {
          b_r = 0.5;
        } else {
          b_r = -0.5;
        }

        c_Y1_re = (ar * X_im + ai * b_r) / br;
        b_Y1_im = (ai * X_im - ar * b_r) / br;
      } else {
        X_im = b_Y1_re / b_Y1_im;
        b_r = b_Y1_im + X_im * b_Y1_re;
        c_Y1_re = (X_im * ar + ai) / b_r;
        b_Y1_im = (X_im * ai - ar) / b_r;
      }
    }

    D->data[i].re = (X->data[i].re * Y1_re - X->data[i].im * Y1_im) + (Y->data[i]
      .re * c_Y1_re - Y->data[i].im * b_Y1_im);
    D->data[i].im = (X->data[i].re * Y1_im + X->data[i].im * Y1_re) + (Y->data[i]
      .re * b_Y1_im + Y->data[i].im * c_Y1_re);
  }

  emxFree_creal_T(&Y2);
  emxFree_creal_T(&Y1);
  nx = D->size[0];
  i = h2->size[0];
  h2->size[0] = D->size[0];
  emxEnsureCapacity_real_T(h2, i);
  for (k = 0; k < nx; k++) {
    h2->data[k] = rt_hypotd_snf(D->data[k].re, D->data[k].im);
  }

  i = y->size[0];
  y->size[0] = h2->size[0];
  emxEnsureCapacity_real_T(y, i);
  nx = h2->size[0];
  for (k = 0; k < nx; k++) {
    y->data[k] = rt_powd_snf(h2->data[k], 2.0);
  }

  emxFree_real_T(&h2);
  i = Y->size[0];
  Y->size[0] = D->size[0];
  emxEnsureCapacity_creal_T(Y, i);
  loop_ub = D->size[0];
  for (i = 0; i < loop_ub; i++) {
    b_r = Y->data[i].re - X->data[i].re;
    X_im = Y->data[i].im - X->data[i].im;
    b_Y1_re = D->data[i].re * b_r - -D->data[i].im * X_im;
    b_r = D->data[i].re * X_im + -D->data[i].im * b_r;
    br = y->data[i] + b_gamma;
    if (b_r == 0.0) {
      Y->data[i].re = b_Y1_re / br;
      Y->data[i].im = 0.0;
    } else if (b_Y1_re == 0.0) {
      Y->data[i].re = 0.0;
      Y->data[i].im = b_r / br;
    } else {
      Y->data[i].re = b_Y1_re / br;
      Y->data[i].im = b_r / br;
    }
  }

  emxFree_real_T(&y);
  emxFree_creal_T(&D);
  emxFree_creal_T(&X);
  ifft(Y, r);
  i = r1->size[0];
  r1->size[0] = r->size[0];
  emxEnsureCapacity_real_T(r1, i);
  loop_ub = r->size[0];
  emxFree_creal_T(&Y);
  for (i = 0; i < loop_ub; i++) {
    r1->data[i] = r->data[i].re;
  }

  emxFree_creal_T(&r);
  fftshift(r1);
  mLowpass(r1, fc, ho);
  fftshift(ho);
  fftshift(ho);

  /*      hh = ho(N/2-667:N/2+667); */
  /*      [ho,~] = WienerNoiseReduction(ho,fs,8000); */
  /*      hh = ho; */
  emxFree_real_T(&r1);
  if (head > tail) {
    i = 0;
    nx = 0;
  } else {
    i = static_cast<int>(head) - 1;
    nx = static_cast<int>(tail);
  }

  loop_ub = nx - i;
  nx = b_ho->size[0];
  b_ho->size[0] = loop_ub;
  emxEnsureCapacity_real_T(b_ho, nx);
  for (nx = 0; nx < loop_ub; nx++) {
    b_ho->data[nx] = ho->data[i + nx];
  }

  i = ho->size[0];
  ho->size[0] = b_ho->size[0];
  emxEnsureCapacity_real_T(ho, i);
  loop_ub = b_ho->size[0];
  for (i = 0; i < loop_ub; i++) {
    ho->data[i] = b_ho->data[i];
  }

  emxFree_real_T(&b_ho);
  b_r = ho->data[0];
  for (k = 0; k < 20; k++) {
    b_r += ho->data[k + 1];
  }

  b_r /= 21.0;
  loop_ub = ho->size[0];
  for (i = 0; i < loop_ub; i++) {
    ho->data[i] -= b_r;
  }

  loop_ub = ho->size[0];
  for (i = 0; i < loop_ub; i++) {
    ho_list->data[i] = ho->data[i];
  }

  emxInit_real_T(&r2, 1);

  /* cm^2 */
  inverse(ho, r2);
  loop_ub = r2->size[0];
  for (i = 0; i < loop_ub; i++) {
    A->data[i] = r2->data[i];
  }

  emxFree_real_T(&r2);
  i = ho->size[0];
  ho->size[0] = ho_list->size[0];
  emxEnsureCapacity_real_T(ho, i);
  loop_ub = ho_list->size[0];
  for (i = 0; i < loop_ub; i++) {
    ho->data[i] = ho_list->data[i];
  }

  emxFree_real_T(&ho_list);
  for (nx = 0; nx < 85; nx++) {
    c_y[nx] = A->data[nx + 33];
  }

  if (!rtIsNaN(c_y[20])) {
    nx = 1;
  } else {
    nx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= 65)) {
      if (!rtIsNaN(c_y[k + 19])) {
        nx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (nx == 0) {
    b_r = c_y[20];
  } else {
    b_r = c_y[nx + 19];
    i = nx + 1;
    for (k = i; k < 66; k++) {
      X_im = c_y[k + 19];
      if (b_r > X_im) {
        b_r = X_im;
      }
    }
  }

  for (i = 0; i < 85; i++) {
    c_y[i] -= b_r;
  }

  mydtw(c_y, &b_r, ix_data, ix_size, iy_data, iy_size);
  nx = ix_size[0];
  loop_ub = ix_size[0];
  for (i = 0; i < loop_ub; i++) {
    x_data[i] = dv[static_cast<int>(ix_data[i]) - 1] - c_y[static_cast<int>
      (iy_data[i]) - 1];
  }

  for (k = 0; k < nx; k++) {
    iy_data[k] = std::abs(x_data[k]);
  }

  nx = ix_size[0];
  loop_ub = ix_size[0];
  for (i = 0; i < loop_ub; i++) {
    x_data[i] = iy_data[i] * w[static_cast<int>(ix_data[i]) - 1];
  }

  b_r = x_data[0];
  for (k = 2; k <= nx; k++) {
    b_r += x_data[k - 1];
  }

  b_r = 110.0 / (0.037 * b_r + 1.0);
  if (!(b_r < 100.0)) {
    b_r = 100.0;
  }

  *score = rt_roundd_snf(b_r);
}

static void crosscorr(const emxArray_real_T *x, const emxArray_real_T *y, double
                      maxlag, emxArray_real_T *c)
{
  int ihi;
  int m;
  double mxl;
  double tdops;
  int ceilLog2;
  double m2;
  int n;
  int c0;
  emxArray_creal_T *r;
  emxArray_creal_T *r1;
  int i;
  emxArray_real_T *c1;
  emxArray_creal_T *r2;
  emxArray_real_T *r3;
  ihi = x->size[0];
  m = y->size[0];
  if (ihi > m) {
    m = ihi;
  }

  mxl = static_cast<double>(m) - 1.0;
  if (maxlag < mxl) {
    mxl = maxlag;
  }

  tdops = frexp(static_cast<double>(static_cast<int>(std::abs(2.0 * static_cast<
    double>(m) - 1.0))), &ceilLog2);
  if (tdops == 0.5) {
    ceilLog2--;
  }

  m2 = rt_powd_snf(2.0, static_cast<double>(ceilLog2));
  ihi = x->size[0];
  m = y->size[0];
  if (ihi > m) {
    m = ihi;
  }

  ihi = x->size[0];
  n = y->size[0];
  if (ihi < n) {
    n = ihi;
  }

  c0 = (n << 1) - 1;
  if (mxl <= static_cast<double>(n) - 1.0) {
    tdops = mxl * ((static_cast<double>(c0) - mxl) - 1.0);
    if (mxl <= m - n) {
      tdops += static_cast<double>(c0) + mxl * static_cast<double>(c0);
    } else {
      tdops += (static_cast<double>(c0) + static_cast<double>(m - n) *
                static_cast<double>(c0)) + (mxl - static_cast<double>(m - n)) *
        (((static_cast<double>(m) - mxl) + static_cast<double>(n)) - 2.0);
    }
  } else if (mxl <= static_cast<double>(m) - 1.0) {
    tdops = (static_cast<double>(n) - 1.0) * (static_cast<double>(n) - 1.0);
    if (mxl <= m - n) {
      tdops += static_cast<double>(c0) + mxl * static_cast<double>(c0);
    } else {
      tdops += (static_cast<double>(c0) + static_cast<double>(m - n) *
                static_cast<double>(c0)) + (mxl - static_cast<double>(m - n)) *
        (((static_cast<double>(m) - mxl) + static_cast<double>(n)) - 2.0);
    }
  } else {
    tdops = 2.0 * static_cast<double>(m) * static_cast<double>(n) - (
      static_cast<double>(m + n) - 1.0);
  }

  if (tdops < m2 * (15.0 * static_cast<double>(ceilLog2) + 6.0)) {
    m = x->size[0];
    n = y->size[0];
    ihi = x->size[0];
    c0 = y->size[0];
    if (ihi > c0) {
      c0 = ihi;
    }

    m2 = static_cast<double>(c0) - 1.0;
    if (mxl < m2) {
      m2 = mxl;
    }

    ihi = static_cast<int>(2.0 * m2 + 1.0);
    i = c->size[0];
    c->size[0] = ihi;
    emxEnsureCapacity_real_T(c, i);
    for (i = 0; i < ihi; i++) {
      c->data[i] = 0.0;
    }

    i = static_cast<int>(m2 + 1.0);
    for (c0 = 0; c0 < i; c0++) {
      ihi = m - c0;
      if (ihi >= n) {
        ihi = n;
      }

      tdops = 0.0;
      for (ceilLog2 = 0; ceilLog2 < ihi; ceilLog2++) {
        tdops += y->data[ceilLog2] * x->data[c0 + ceilLog2];
      }

      c->data[static_cast<int>((m2 + static_cast<double>(c0)) + 1.0) - 1] =
        tdops;
    }

    i = static_cast<int>(m2);
    for (c0 = 0; c0 < i; c0++) {
      ihi = static_cast<int>(static_cast<double>(n) - (static_cast<double>(c0) +
        1.0));
      if (m < ihi) {
        ihi = m;
      }

      tdops = 0.0;
      for (ceilLog2 = 0; ceilLog2 < ihi; ceilLog2++) {
        tdops += y->data[(c0 + ceilLog2) + 1] * x->data[ceilLog2];
      }

      c->data[static_cast<int>((m2 - (static_cast<double>(c0) + 1.0)) + 1.0) - 1]
        = tdops;
    }
  } else {
    emxInit_creal_T(&r, 1);
    emxInit_creal_T(&r1, 1);
    fft(x, m2, r);
    fft(y, m2, r1);
    ihi = r->size[0];
    for (i = 0; i < ihi; i++) {
      tdops = r->data[i].re * -r1->data[i].im + r->data[i].im * r1->data[i].re;
      r->data[i].re = r->data[i].re * r1->data[i].re - r->data[i].im * -r1->
        data[i].im;
      r->data[i].im = tdops;
    }

    emxFree_creal_T(&r1);
    emxInit_real_T(&c1, 1);
    emxInit_creal_T(&r2, 1);
    ifft(r, r2);
    i = c1->size[0];
    c1->size[0] = r2->size[0];
    emxEnsureCapacity_real_T(c1, i);
    ihi = r2->size[0];
    emxFree_creal_T(&r);
    for (i = 0; i < ihi; i++) {
      c1->data[i] = r2->data[i].re;
    }

    emxFree_creal_T(&r2);
    emxInit_real_T(&r3, 2);
    if (mxl < 1.0) {
      r3->size[0] = 1;
      r3->size[1] = 0;
    } else {
      i = r3->size[0] * r3->size[1];
      r3->size[0] = 1;
      ihi = static_cast<int>(std::floor(mxl - 1.0));
      r3->size[1] = ihi + 1;
      emxEnsureCapacity_real_T(r3, i);
      for (i = 0; i <= ihi; i++) {
        r3->data[i] = static_cast<double>(i) + 1.0;
      }
    }

    if (1.0 > mxl + 1.0) {
      ihi = 0;
    } else {
      ihi = static_cast<int>(mxl + 1.0);
    }

    m2 -= mxl;
    i = c->size[0];
    c->size[0] = r3->size[1] + ihi;
    emxEnsureCapacity_real_T(c, i);
    c0 = r3->size[1];
    for (i = 0; i < c0; i++) {
      c->data[i] = c1->data[static_cast<int>(m2 + r3->data[i]) - 1];
    }

    for (i = 0; i < ihi; i++) {
      c->data[i + r3->size[1]] = c1->data[i];
    }

    emxFree_real_T(&r3);
    emxFree_real_T(&c1);
  }
}

static void d_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1)
{
  unsigned int inSize[8];
  cell_wrap_12 varSizes[1];
  int i;
  boolean_T exitg1;
  static const double b_dv[201] = { 0.00014476520152196308,
    0.00052916499631356782, -7.8877413543547792E-5, -4.1339029785394418E-5,
    -0.00019398826101959008, -0.00024705033507139941, -0.00021790281013994275,
    -8.3731213456896651E-5, 0.00011109412421242728, 0.00029126489040063696,
    0.00037297343522887477, 0.0003029824307028114, 8.7552956575278858E-5,
    -0.00020066331049444018, -0.00044505311943042171, -0.00053074211346558074,
    -0.00039629965552872979, -6.8940880223698319E-5, 0.00033493682880182928,
    0.00064891985709853318, 0.00072333475850638342, 0.00049353217196176718,
    1.9562086605359735E-5, -0.00052402485017701928, -0.00091006280287847,
    -0.00095150328166592054, -0.000587989301152848, 7.2473131505266538E-5,
    0.00078034598466051263, 0.0012362018876740219, 0.0012146900534269808,
    0.00067052114253843568, -0.00022163357773964513, -0.0011179888320140734,
    -0.0016351550393318725, -0.0015107928997335535, -0.00072933412427754344,
    0.00044516644189130912, 0.0015529104388343705, 0.0021149463244976149,
    0.0018360712470102249, 0.00074962843922711357, -0.00076369051742062157,
    -0.0021035940264028247, -0.0026842674884089137, -0.0021851474920354347,
    -0.00071299509577576309, 0.0012023215810142136, 0.0027923551613008718,
    0.0033534401845295059, 0.0025511016978865412, 0.00059635852484850457,
    -0.00179272993075602, -0.0036477558875180984, -0.0041362037651912608,
    -0.0029256588191030248, -0.0003700385606371528, 0.0025769179395778059,
    0.0047090284431152481, 0.0050529662365590864, 0.0032994628863515754,
    -5.9273503763053568E-6, -0.0036143208623445732, -0.0060343667051478067,
    -0.0061368515443609543, -0.0036624269248825034, 0.0005890551635148037,
    0.0049957510589252905, 0.0077172414440901506, 0.007445585630515934,
    0.0040041420270786948, -0.0014696606893194095, -0.0068727001243323914,
    -0.0099210270670526176, -0.0090869406891204325, -0.0043143245122639852,
    0.0028057275460746738, 0.0095252806774975881, 0.012960910318799621,
    0.011280169549772382, 0.0045832768782292062, -0.004913506858729268,
    -0.01354378201300363, -0.017530204131667438, -0.014531971020395494,
    -0.0048023365576505489, 0.0085530595452189013, 0.020429457265571913,
    0.025491939630303051, 0.020291195069462625, 0.0049642865019480153,
    -0.016166567469611662, -0.035448204974608731, -0.044061650001681829,
    -0.034874707826971184, -0.0050637033628783516, 0.042405324886559619,
    0.099019629600460249, 0.15272585160653926, 0.19115467112227902,
    0.2050972224367833, 0.19115467112227902, 0.15272585160653926,
    0.099019629600460249, 0.042405324886559619, -0.0050637033628783516,
    -0.034874707826971184, -0.044061650001681829, -0.035448204974608731,
    -0.016166567469611662, 0.0049642865019480153, 0.020291195069462625,
    0.025491939630303051, 0.020429457265571913, 0.0085530595452189013,
    -0.0048023365576505489, -0.014531971020395494, -0.017530204131667438,
    -0.01354378201300363, -0.004913506858729268, 0.0045832768782292062,
    0.011280169549772382, 0.012960910318799621, 0.0095252806774975881,
    0.0028057275460746738, -0.0043143245122639852, -0.0090869406891204325,
    -0.0099210270670526176, -0.0068727001243323914, -0.0014696606893194095,
    0.0040041420270786948, 0.007445585630515934, 0.0077172414440901506,
    0.0049957510589252905, 0.0005890551635148037, -0.0036624269248825034,
    -0.0061368515443609543, -0.0060343667051478067, -0.0036143208623445732,
    -5.9273503763053568E-6, 0.0032994628863515754, 0.0050529662365590864,
    0.0047090284431152481, 0.0025769179395778059, -0.0003700385606371528,
    -0.0029256588191030248, -0.0041362037651912608, -0.0036477558875180984,
    -0.00179272993075602, 0.00059635852484850457, 0.0025511016978865412,
    0.0033534401845295059, 0.0027923551613008718, 0.0012023215810142136,
    -0.00071299509577576309, -0.0021851474920354347, -0.0026842674884089137,
    -0.0021035940264028247, -0.00076369051742062157, 0.00074962843922711357,
    0.0018360712470102249, 0.0021149463244976149, 0.0015529104388343705,
    0.00044516644189130912, -0.00072933412427754344, -0.0015107928997335535,
    -0.0016351550393318725, -0.0011179888320140734, -0.00022163357773964513,
    0.00067052114253843568, 0.0012146900534269808, 0.0012362018876740219,
    0.00078034598466051263, 7.2473131505266538E-5, -0.000587989301152848,
    -0.00095150328166592054, -0.00091006280287847, -0.00052402485017701928,
    1.9562086605359735E-5, 0.00049353217196176718, 0.00072333475850638342,
    0.00064891985709853318, 0.00033493682880182928, -6.8940880223698319E-5,
    -0.00039629965552872979, -0.00053074211346558074, -0.00044505311943042171,
    -0.00020066331049444018, 8.7552956575278858E-5, 0.0003029824307028114,
    0.00037297343522887477, 0.00029126489040063696, 0.00011109412421242728,
    -8.3731213456896651E-5, -0.00021790281013994275, -0.00024705033507139941,
    -0.00019398826101959008, -4.1339029785394418E-5, -7.8877413543547792E-5,
    0.00052916499631356782, 0.00014476520152196308 };

  dspcodegen_FIRFilter_3 *b_obj;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    varSizes[0].f1[0] = static_cast<unsigned int>(varargin_1->size[0]);
    varSizes[0].f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes[0].f1[i + 2] = 1U;
    }

    obj->inputVarSize[0] = varSizes[0];
    iobj_0->isInitialized = 0;

    /* System object Constructor function: dsp.FIRFilter */
    iobj_0->cSFunObject.P0_InitialStates = 0.0;
    for (i = 0; i < 201; i++) {
      iobj_0->cSFunObject.P1_Coefficients[i] = b_dv[i];
    }

    iobj_0->matlabCodegenIsDeleted = false;
    obj->FilterObj = iobj_0;
    obj->NumChannels = 1;
    obj->isSetupComplete = true;
    b_obj = obj->FilterObj;
    if (b_obj->isInitialized == 1) {
      /* System object Initialization function: dsp.FIRFilter */
      for (i = 0; i < 200; i++) {
        b_obj->cSFunObject.W0_states[i] = b_obj->cSFunObject.P0_InitialStates;
      }
    }
  }

  inSize[0] = static_cast<unsigned int>(varargin_1->size[0]);
  inSize[1] = 1U;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1U;
  }

  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != inSize[i]) {
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = inSize[i];
      }

      exitg1 = true;
    } else {
      i++;
    }
  }

  LPHPFilterBase_stepImpl(obj, varargin_1, varargout_1);
}

static void d_findPeaksSeparatedByMoreThanM(const double y[271200], const double
  x[271200], const emxArray_int32_T *iPk, emxArray_int32_T *idx)
{
  emxArray_real_T *locs_temp;
  int i;
  int loop_ub;
  emxArray_int32_T *c_sortIdx;
  emxArray_int32_T *r;
  emxArray_boolean_T *idelete;
  emxArray_boolean_T *r1;
  int b_i;
  int end;
  emxArray_int32_T *r2;
  int i1;
  if (iPk->size[0] == 0) {
    idx->size[0] = 0;
  } else {
    emxInit_real_T(&locs_temp, 1);
    i = locs_temp->size[0];
    locs_temp->size[0] = iPk->size[0];
    emxEnsureCapacity_real_T(locs_temp, i);
    loop_ub = iPk->size[0];
    for (i = 0; i < loop_ub; i++) {
      locs_temp->data[i] = y[iPk->data[i] - 1];
    }

    emxInit_int32_T(&c_sortIdx, 1);
    emxInit_int32_T(&r, 1);
    sortIdx(locs_temp, r);
    i = c_sortIdx->size[0];
    c_sortIdx->size[0] = r->size[0];
    emxEnsureCapacity_int32_T(c_sortIdx, i);
    loop_ub = r->size[0];
    for (i = 0; i < loop_ub; i++) {
      c_sortIdx->data[i] = r->data[i];
    }

    i = locs_temp->size[0];
    locs_temp->size[0] = c_sortIdx->size[0];
    emxEnsureCapacity_real_T(locs_temp, i);
    loop_ub = c_sortIdx->size[0];
    for (i = 0; i < loop_ub; i++) {
      locs_temp->data[i] = x[iPk->data[c_sortIdx->data[i] - 1] - 1];
    }

    emxInit_boolean_T(&idelete, 1);
    i = idelete->size[0];
    idelete->size[0] = c_sortIdx->size[0];
    emxEnsureCapacity_boolean_T(idelete, i);
    loop_ub = c_sortIdx->size[0];
    for (i = 0; i < loop_ub; i++) {
      idelete->data[i] = false;
    }

    i = c_sortIdx->size[0];
    emxInit_boolean_T(&r1, 1);
    for (b_i = 0; b_i < i; b_i++) {
      if (!idelete->data[b_i]) {
        end = r1->size[0];
        r1->size[0] = locs_temp->size[0];
        emxEnsureCapacity_boolean_T(r1, end);
        loop_ub = locs_temp->size[0];
        for (end = 0; end < loop_ub; end++) {
          i1 = iPk->data[c_sortIdx->data[b_i] - 1] - 1;
          r1->data[end] = ((locs_temp->data[end] >= x[i1] - 7200.0) &&
                           (locs_temp->data[end] <= x[i1] + 7200.0));
        }

        loop_ub = idelete->size[0];
        for (end = 0; end < loop_ub; end++) {
          idelete->data[end] = (idelete->data[end] || r1->data[end]);
        }

        idelete->data[b_i] = false;
      }
    }

    emxFree_boolean_T(&r1);
    emxFree_real_T(&locs_temp);
    end = idelete->size[0] - 1;
    loop_ub = 0;
    for (b_i = 0; b_i <= end; b_i++) {
      if (!idelete->data[b_i]) {
        loop_ub++;
      }
    }

    emxInit_int32_T(&r2, 1);
    i = r2->size[0];
    r2->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(r2, i);
    loop_ub = 0;
    for (b_i = 0; b_i <= end; b_i++) {
      if (!idelete->data[b_i]) {
        r2->data[loop_ub] = b_i + 1;
        loop_ub++;
      }
    }

    emxFree_boolean_T(&idelete);
    i = r->size[0];
    r->size[0] = r2->size[0];
    emxEnsureCapacity_int32_T(r, i);
    loop_ub = r2->size[0];
    for (i = 0; i < loop_ub; i++) {
      r->data[i] = c_sortIdx->data[r2->data[i] - 1];
    }

    emxFree_int32_T(&r2);
    emxFree_int32_T(&c_sortIdx);
    sort(r);
    i = idx->size[0];
    idx->size[0] = r->size[0];
    emxEnsureCapacity_int32_T(idx, i);
    loop_ub = r->size[0];
    for (i = 0; i < loop_ub; i++) {
      idx->data[i] = r->data[i];
    }

    emxFree_int32_T(&r);
  }
}

static void d_findpeaks(const double Yin[264000], emxArray_real_T *Ypk,
  emxArray_real_T *Xpk)
{
  emxArray_int32_T *iPk;
  emxArray_int32_T *iFinite;
  emxArray_int32_T *iInfinite;
  emxArray_int32_T *iInflect;
  int i;
  int loop_ub;
  emxArray_int32_T *c;
  emxArray_int32_T *ia;
  emxArray_int32_T *ib;
  emxArray_int32_T *idx;
  static double b_dv[264000];
  emxInit_int32_T(&iPk, 1);
  emxInit_int32_T(&iFinite, 1);
  emxInit_int32_T(&iInfinite, 1);
  emxInit_int32_T(&iInflect, 1);
  getAllPeaksCodegen(Yin, iFinite, iInfinite, iInflect);
  removeSmallPeaks(Yin, iFinite, 0.1, iInflect);
  i = iPk->size[0];
  iPk->size[0] = iInflect->size[0];
  emxEnsureCapacity_int32_T(iPk, i);
  loop_ub = iInflect->size[0];
  emxFree_int32_T(&iFinite);
  for (i = 0; i < loop_ub; i++) {
    iPk->data[i] = iInflect->data[i];
  }

  emxFree_int32_T(&iInflect);
  emxInit_int32_T(&c, 1);
  emxInit_int32_T(&ia, 1);
  emxInit_int32_T(&ib, 1);
  do_vectors(iPk, iInfinite, c, ia, ib);
  emxFree_int32_T(&ib);
  emxFree_int32_T(&ia);
  emxFree_int32_T(&iInfinite);
  for (i = 0; i < 264000; i++) {
    b_dv[i] = static_cast<double>(i) + 1.0;
  }

  emxInit_int32_T(&idx, 1);
  c_findPeaksSeparatedByMoreThanM(Yin, b_dv, c, idx);
  if (idx->size[0] > 264000) {
    i = iPk->size[0];
    iPk->size[0] = 264000;
    emxEnsureCapacity_int32_T(iPk, i);
    for (i = 0; i < 264000; i++) {
      iPk->data[i] = idx->data[i];
    }

    i = idx->size[0];
    idx->size[0] = iPk->size[0];
    emxEnsureCapacity_int32_T(idx, i);
    loop_ub = iPk->size[0];
    for (i = 0; i < loop_ub; i++) {
      idx->data[i] = iPk->data[i];
    }
  }

  i = iPk->size[0];
  iPk->size[0] = idx->size[0];
  emxEnsureCapacity_int32_T(iPk, i);
  loop_ub = idx->size[0];
  for (i = 0; i < loop_ub; i++) {
    iPk->data[i] = c->data[idx->data[i] - 1];
  }

  emxFree_int32_T(&c);
  emxFree_int32_T(&idx);
  i = Ypk->size[0];
  Ypk->size[0] = iPk->size[0];
  emxEnsureCapacity_real_T(Ypk, i);
  loop_ub = iPk->size[0];
  for (i = 0; i < loop_ub; i++) {
    Ypk->data[i] = Yin[iPk->data[i] - 1];
  }

  i = Xpk->size[0];
  Xpk->size[0] = iPk->size[0];
  emxEnsureCapacity_real_T(Xpk, i);
  loop_ub = iPk->size[0];
  for (i = 0; i < loop_ub; i++) {
    Xpk->data[i] = iPk->data[i];
  }

  emxFree_int32_T(&iPk);
}

static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~static_cast<unsigned int>(numerator) + 1U;
    } else {
      absNumerator = static_cast<unsigned int>(numerator);
    }

    if (denominator < 0) {
      absDenominator = ~static_cast<unsigned int>(denominator) + 1U;
    } else {
      absDenominator = static_cast<unsigned int>(denominator);
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -static_cast<int>(tempAbsQuotient);
    } else {
      quotient = static_cast<int>(tempAbsQuotient);
    }
  }

  return quotient;
}

static void do_vectors(const emxArray_int32_T *a, const emxArray_int32_T *b,
  emxArray_int32_T *c, emxArray_int32_T *ia, emxArray_int32_T *ib)
{
  int na;
  int nb;
  int ncmax;
  int iafirst;
  int nc;
  int nia;
  int nib;
  int ialast;
  int ibfirst;
  int iblast;
  int b_ialast;
  int ak;
  int b_iblast;
  int bk;
  na = a->size[0];
  nb = b->size[0];
  ncmax = a->size[0] + b->size[0];
  iafirst = c->size[0];
  c->size[0] = ncmax;
  emxEnsureCapacity_int32_T(c, iafirst);
  iafirst = ia->size[0];
  ia->size[0] = a->size[0];
  emxEnsureCapacity_int32_T(ia, iafirst);
  iafirst = ib->size[0];
  ib->size[0] = b->size[0];
  emxEnsureCapacity_int32_T(ib, iafirst);
  nc = -1;
  nia = -1;
  nib = 0;
  iafirst = 1;
  ialast = 0;
  ibfirst = 0;
  iblast = 0;
  while ((ialast + 1 <= na) && (iblast + 1 <= nb)) {
    b_ialast = ialast + 1;
    ak = a->data[ialast];
    while ((b_ialast < a->size[0]) && (a->data[b_ialast] == ak)) {
      b_ialast++;
    }

    ialast = b_ialast - 1;
    b_iblast = iblast + 1;
    bk = b->data[iblast];
    while ((b_iblast < b->size[0]) && (b->data[b_iblast] == bk)) {
      b_iblast++;
    }

    iblast = b_iblast - 1;
    if (ak == bk) {
      nc++;
      c->data[nc] = ak;
      nia++;
      ia->data[nia] = iafirst;
      ialast = b_ialast;
      iafirst = b_ialast + 1;
      iblast = b_iblast;
      ibfirst = b_iblast;
    } else if (ak < bk) {
      nc++;
      nia++;
      c->data[nc] = ak;
      ia->data[nia] = iafirst;
      ialast = b_ialast;
      iafirst = b_ialast + 1;
    } else {
      nc++;
      nib++;
      c->data[nc] = bk;
      ib->data[nib - 1] = ibfirst + 1;
      iblast = b_iblast;
      ibfirst = b_iblast;
    }
  }

  while (ialast + 1 <= na) {
    b_ialast = ialast + 1;
    while ((b_ialast < a->size[0]) && (a->data[b_ialast] == a->data[ialast])) {
      b_ialast++;
    }

    nc++;
    nia++;
    c->data[nc] = a->data[ialast];
    ia->data[nia] = iafirst;
    ialast = b_ialast;
    iafirst = b_ialast + 1;
  }

  while (iblast + 1 <= nb) {
    b_iblast = iblast + 1;
    while ((b_iblast < b->size[0]) && (b->data[b_iblast] == b->data[iblast])) {
      b_iblast++;
    }

    nc++;
    nib++;
    c->data[nc] = b->data[iblast];
    ib->data[nib - 1] = ibfirst + 1;
    iblast = b_iblast;
    ibfirst = b_iblast;
  }

  if (a->size[0] > 0) {
    iafirst = ia->size[0];
    if (1 > nia + 1) {
      ia->size[0] = 0;
    } else {
      ia->size[0] = nia + 1;
    }

    emxEnsureCapacity_int32_T(ia, iafirst);
  }

  if (b->size[0] > 0) {
    iafirst = ib->size[0];
    if (1 > nib) {
      ib->size[0] = 0;
    } else {
      ib->size[0] = nib;
    }

    emxEnsureCapacity_int32_T(ib, iafirst);
  }

  if (ncmax > 0) {
    iafirst = c->size[0];
    if (1 > nc + 1) {
      c->size[0] = 0;
    } else {
      c->size[0] = nc + 1;
    }

    emxEnsureCapacity_int32_T(c, iafirst);
  }
}

static void dobluesteinfft(const emxArray_real_T *x, int N2, int n1, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, const emxArray_real_T *
  sintabinv, emxArray_creal_T *y)
{
  emxArray_creal_T *wwc;
  int nInt2m1;
  int rt;
  int idx;
  int nInt2;
  int k;
  int b_y;
  double nt_im;
  double nt_re;
  emxInit_creal_T(&wwc, 1);
  nInt2m1 = (n1 + n1) - 1;
  rt = wwc->size[0];
  wwc->size[0] = nInt2m1;
  emxEnsureCapacity_creal_T(wwc, rt);
  idx = n1;
  rt = 0;
  wwc->data[n1 - 1].re = 1.0;
  wwc->data[n1 - 1].im = 0.0;
  nInt2 = n1 << 1;
  for (k = 0; k <= n1 - 2; k++) {
    b_y = ((k + 1) << 1) - 1;
    if (nInt2 - rt <= b_y) {
      rt += b_y - nInt2;
    } else {
      rt += b_y;
    }

    nt_im = -3.1415926535897931 * static_cast<double>(rt) / static_cast<double>
      (n1);
    if (nt_im == 0.0) {
      nt_re = 1.0;
      nt_im = 0.0;
    } else {
      nt_re = std::cos(nt_im);
      nt_im = std::sin(nt_im);
    }

    wwc->data[idx - 2].re = nt_re;
    wwc->data[idx - 2].im = -nt_im;
    idx--;
  }

  idx = 0;
  rt = nInt2m1 - 1;
  for (k = rt; k >= n1; k--) {
    wwc->data[k] = wwc->data[idx];
    idx++;
  }

  bluestein(x, N2, n1, costab, sintab, costab, sintabinv, wwc, y);
  emxFree_creal_T(&wwc);
}

static void e_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1)
{
  unsigned int inSize[8];
  cell_wrap_12 varSizes[1];
  int i;
  boolean_T exitg1;
  static const double b_dv[201] = { 4.5308658018300949E-6,
    0.00054417571927841443, 4.280577992702194E-5, -5.939065662359578E-5,
    -0.0001799465729618677, -0.00024205083550391502, -0.00019260929797991423,
    -3.2302307817890735E-5, 0.00017483396215843322, 0.00032585860597183786,
    0.00032934404918802726, 0.00015794270853135766, -0.00012568111430786677,
    -0.0003880903810392215, -0.00048598937456427688, -0.00034194034683974404,
    4.0519433935787593E-6, 0.00039856058475433312, 0.00064020334675744459,
    0.0005800415813462345, 0.00020795094328719308, -0.00032308969013353364,
    -0.00075601647635254929, -0.000851557939203354, -0.00051644668041640144,
    0.00012906152390749126, 0.00078757227274918343, 0.0011184230848812237,
    0.00091042854153795621, 0.00020746294026061608, -0.00068444846132304578,
    -0.001325943265079701, -0.0013572781292618995, -0.00069386516202246478,
    0.00039934337175996095, 0.0014065776392449012, 0.0018005781936853784,
    0.0013134952426196033, 0.0001024291237341414, -0.0012870155316121036,
    -0.0021612280976142689, -0.0020199419982757593, -0.00083273097849398718,
    0.00089819738703064667, 0.0023424362333379174, 0.0027343207302932653,
    0.0017710948126571564, -0.00018735810557940364, -0.0022385966961820944,
    -0.0033465368242691605, -0.0028574236476842786, -0.00086929049797467961,
    0.0017474072198739759, 0.0037209259472634477, 0.0039881877766308142,
    0.0022548752437126247, -0.00078395115289711008, -0.003705917477625231,
    -0.0050168713947473373, -0.003902757773574482, -0.00070503887782255245,
    0.0031464773125312873, 0.0057585280812674309, 0.0056911353473429226,
    0.0027287931147142357, -0.0018970973432789644, -0.0059969931789797008,
    -0.0074414892967213956, -0.0052440221036838073, -0.00016806993349272503,
    0.0054913312828660989, 0.0089192563872037972, 0.0081520137164836567,
    0.0031531101292516231, -0.0039746296361726175, -0.0098317568115264455,
    -0.01130232994858371, -0.007155328895466103, 0.0011304978545032874,
    0.0098108658476812986, 0.014503254214259199, 0.01231745342275966,
    0.0034893350875223193, -0.0083463844691331647, -0.017538179806017747,
    -0.018975715827754674, -0.010720635657150517, 0.0045571650093293586,
    0.020186227936743326, 0.02812941495291137, 0.022687661706255906,
    0.0037053440054508791, -0.022244686060073161, -0.043487907167367862,
    -0.047329944071269225, -0.025143193536404422, 0.023550483632146624,
    0.08975786374115384, 0.15720723625275243, 0.207439898532024,
    0.22600205530192385, 0.207439898532024, 0.15720723625275243,
    0.08975786374115384, 0.023550483632146624, -0.025143193536404422,
    -0.047329944071269225, -0.043487907167367862, -0.022244686060073161,
    0.0037053440054508791, 0.022687661706255906, 0.02812941495291137,
    0.020186227936743326, 0.0045571650093293586, -0.010720635657150517,
    -0.018975715827754674, -0.017538179806017747, -0.0083463844691331647,
    0.0034893350875223193, 0.01231745342275966, 0.014503254214259199,
    0.0098108658476812986, 0.0011304978545032874, -0.007155328895466103,
    -0.01130232994858371, -0.0098317568115264455, -0.0039746296361726175,
    0.0031531101292516231, 0.0081520137164836567, 0.0089192563872037972,
    0.0054913312828660989, -0.00016806993349272503, -0.0052440221036838073,
    -0.0074414892967213956, -0.0059969931789797008, -0.0018970973432789644,
    0.0027287931147142357, 0.0056911353473429226, 0.0057585280812674309,
    0.0031464773125312873, -0.00070503887782255245, -0.003902757773574482,
    -0.0050168713947473373, -0.003705917477625231, -0.00078395115289711008,
    0.0022548752437126247, 0.0039881877766308142, 0.0037209259472634477,
    0.0017474072198739759, -0.00086929049797467961, -0.0028574236476842786,
    -0.0033465368242691605, -0.0022385966961820944, -0.00018735810557940364,
    0.0017710948126571564, 0.0027343207302932653, 0.0023424362333379174,
    0.00089819738703064667, -0.00083273097849398718, -0.0020199419982757593,
    -0.0021612280976142689, -0.0012870155316121036, 0.0001024291237341414,
    0.0013134952426196033, 0.0018005781936853784, 0.0014065776392449012,
    0.00039934337175996095, -0.00069386516202246478, -0.0013572781292618995,
    -0.001325943265079701, -0.00068444846132304578, 0.00020746294026061608,
    0.00091042854153795621, 0.0011184230848812237, 0.00078757227274918343,
    0.00012906152390749126, -0.00051644668041640144, -0.000851557939203354,
    -0.00075601647635254929, -0.00032308969013353364, 0.00020795094328719308,
    0.0005800415813462345, 0.00064020334675744459, 0.00039856058475433312,
    4.0519433935787593E-6, -0.00034194034683974404, -0.00048598937456427688,
    -0.0003880903810392215, -0.00012568111430786677, 0.00015794270853135766,
    0.00032934404918802726, 0.00032585860597183786, 0.00017483396215843322,
    -3.2302307817890735E-5, -0.00019260929797991423, -0.00024205083550391502,
    -0.0001799465729618677, -5.939065662359578E-5, 4.280577992702194E-5,
    0.00054417571927841443, 4.5308658018300949E-6 };

  dspcodegen_FIRFilter_3 *b_obj;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    varSizes[0].f1[0] = static_cast<unsigned int>(varargin_1->size[0]);
    varSizes[0].f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes[0].f1[i + 2] = 1U;
    }

    obj->inputVarSize[0] = varSizes[0];
    iobj_0->isInitialized = 0;

    /* System object Constructor function: dsp.FIRFilter */
    iobj_0->cSFunObject.P0_InitialStates = 0.0;
    for (i = 0; i < 201; i++) {
      iobj_0->cSFunObject.P1_Coefficients[i] = b_dv[i];
    }

    iobj_0->matlabCodegenIsDeleted = false;
    obj->FilterObj = iobj_0;
    obj->NumChannels = 1;
    obj->isSetupComplete = true;
    b_obj = obj->FilterObj;
    if (b_obj->isInitialized == 1) {
      /* System object Initialization function: dsp.FIRFilter */
      for (i = 0; i < 200; i++) {
        b_obj->cSFunObject.W0_states[i] = b_obj->cSFunObject.P0_InitialStates;
      }
    }
  }

  inSize[0] = static_cast<unsigned int>(varargin_1->size[0]);
  inSize[1] = 1U;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1U;
  }

  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != inSize[i]) {
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = inSize[i];
      }

      exitg1 = true;
    } else {
      i++;
    }
  }

  LPHPFilterBase_stepImpl(obj, varargin_1, varargout_1);
}

static void e_findPeaksSeparatedByMoreThanM(const double y[2160000], const
  double x[2160000], const emxArray_int32_T *iPk, emxArray_int32_T *idx)
{
  emxArray_real_T *locs_temp;
  int i;
  int loop_ub;
  emxArray_int32_T *c_sortIdx;
  emxArray_boolean_T *idelete;
  emxArray_boolean_T *r;
  int b_i;
  int end;
  emxArray_int32_T *r1;
  int i1;
  if (iPk->size[0] == 0) {
    idx->size[0] = 0;
  } else {
    emxInit_real_T(&locs_temp, 1);
    i = locs_temp->size[0];
    locs_temp->size[0] = iPk->size[0];
    emxEnsureCapacity_real_T(locs_temp, i);
    loop_ub = iPk->size[0];
    for (i = 0; i < loop_ub; i++) {
      locs_temp->data[i] = y[iPk->data[i] - 1];
    }

    emxInit_int32_T(&c_sortIdx, 1);
    sortIdx(locs_temp, c_sortIdx);
    i = locs_temp->size[0];
    locs_temp->size[0] = c_sortIdx->size[0];
    emxEnsureCapacity_real_T(locs_temp, i);
    loop_ub = c_sortIdx->size[0];
    for (i = 0; i < loop_ub; i++) {
      locs_temp->data[i] = x[iPk->data[c_sortIdx->data[i] - 1] - 1];
    }

    emxInit_boolean_T(&idelete, 1);
    i = idelete->size[0];
    idelete->size[0] = c_sortIdx->size[0];
    emxEnsureCapacity_boolean_T(idelete, i);
    loop_ub = c_sortIdx->size[0];
    for (i = 0; i < loop_ub; i++) {
      idelete->data[i] = false;
    }

    i = c_sortIdx->size[0];
    emxInit_boolean_T(&r, 1);
    for (b_i = 0; b_i < i; b_i++) {
      if (!idelete->data[b_i]) {
        end = r->size[0];
        r->size[0] = locs_temp->size[0];
        emxEnsureCapacity_boolean_T(r, end);
        loop_ub = locs_temp->size[0];
        for (end = 0; end < loop_ub; end++) {
          i1 = iPk->data[c_sortIdx->data[b_i] - 1] - 1;
          r->data[end] = ((locs_temp->data[end] >= x[i1] - 7200.0) &&
                          (locs_temp->data[end] <= x[i1] + 7200.0));
        }

        loop_ub = idelete->size[0];
        for (end = 0; end < loop_ub; end++) {
          idelete->data[end] = (idelete->data[end] || r->data[end]);
        }

        idelete->data[b_i] = false;
      }
    }

    emxFree_boolean_T(&r);
    emxFree_real_T(&locs_temp);
    end = idelete->size[0] - 1;
    loop_ub = 0;
    for (b_i = 0; b_i <= end; b_i++) {
      if (!idelete->data[b_i]) {
        loop_ub++;
      }
    }

    emxInit_int32_T(&r1, 1);
    i = r1->size[0];
    r1->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(r1, i);
    loop_ub = 0;
    for (b_i = 0; b_i <= end; b_i++) {
      if (!idelete->data[b_i]) {
        r1->data[loop_ub] = b_i + 1;
        loop_ub++;
      }
    }

    emxFree_boolean_T(&idelete);
    i = idx->size[0];
    idx->size[0] = r1->size[0];
    emxEnsureCapacity_int32_T(idx, i);
    loop_ub = r1->size[0];
    for (i = 0; i < loop_ub; i++) {
      idx->data[i] = c_sortIdx->data[r1->data[i] - 1];
    }

    emxFree_int32_T(&r1);
    emxFree_int32_T(&c_sortIdx);
    sort(idx);
  }
}

static void e_findpeaks(const double Yin[280800], emxArray_real_T *Ypk,
  emxArray_real_T *Xpk)
{
  emxArray_int32_T *iInflect;
  emxArray_int32_T *iFinite;
  emxArray_int32_T *iInfinite;
  int k;
  int nPk;
  int nInf;
  char dir;
  int kfirst;
  double ykfirst;
  boolean_T isinfykfirst;
  double yk;
  boolean_T isinfyk;
  char previousdir;
  emxArray_int32_T *c;
  emxArray_int32_T *ia;
  emxArray_int32_T *ib;
  emxArray_int32_T *idx;
  static double b_dv[280800];
  emxArray_int32_T *iPk;
  emxInit_int32_T(&iInflect, 1);
  emxInit_int32_T(&iFinite, 1);
  emxInit_int32_T(&iInfinite, 1);
  k = iFinite->size[0];
  iFinite->size[0] = 280800;
  emxEnsureCapacity_int32_T(iFinite, k);
  k = iInfinite->size[0];
  iInfinite->size[0] = 280800;
  emxEnsureCapacity_int32_T(iInfinite, k);
  nPk = -1;
  nInf = -1;
  dir = 'n';
  kfirst = -1;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 0; k < 280800; k++) {
    yk = Yin[k];
    if (rtIsNaN(Yin[k])) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(Yin[k]) && (Yin[k] > 0.0)) {
      isinfyk = true;
      nInf++;
      iInfinite->data[nInf] = k + 1;
    } else {
      isinfyk = false;
    }

    if (yk != ykfirst) {
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
      } else if (yk < ykfirst) {
        dir = 'd';
        if (('d' != previousdir) && (previousdir == 'i')) {
          nPk++;
          iFinite->data[nPk] = kfirst + 1;
        }
      } else {
        dir = 'i';
      }

      ykfirst = yk;
      kfirst = k;
      isinfykfirst = isinfyk;
    }
  }

  if (1 > nPk + 1) {
    kfirst = -1;
  } else {
    kfirst = nPk;
  }

  k = iInflect->size[0];
  iInflect->size[0] = kfirst + 1;
  emxEnsureCapacity_int32_T(iInflect, k);
  for (k = 0; k <= kfirst; k++) {
    iInflect->data[k] = iFinite->data[k];
  }

  k = iFinite->size[0];
  iFinite->size[0] = iInflect->size[0];
  emxEnsureCapacity_int32_T(iFinite, k);
  kfirst = iInflect->size[0];
  for (k = 0; k < kfirst; k++) {
    iFinite->data[k] = iInflect->data[k];
  }

  if (1 > nInf + 1) {
    kfirst = -1;
  } else {
    kfirst = nInf;
  }

  k = iInflect->size[0];
  iInflect->size[0] = kfirst + 1;
  emxEnsureCapacity_int32_T(iInflect, k);
  for (k = 0; k <= kfirst; k++) {
    iInflect->data[k] = iInfinite->data[k];
  }

  k = iInfinite->size[0];
  iInfinite->size[0] = iInflect->size[0];
  emxEnsureCapacity_int32_T(iInfinite, k);
  kfirst = iInflect->size[0];
  for (k = 0; k < kfirst; k++) {
    iInfinite->data[k] = iInflect->data[k];
  }

  k = iInflect->size[0];
  iInflect->size[0] = iFinite->size[0];
  emxEnsureCapacity_int32_T(iInflect, k);
  nPk = 0;
  kfirst = iFinite->size[0];
  for (k = 0; k < kfirst; k++) {
    ykfirst = Yin[iFinite->data[k] - 1];
    if (ykfirst > 0.25) {
      if ((Yin[iFinite->data[k] - 2] > Yin[iFinite->data[k]]) || rtIsNaN
          (Yin[iFinite->data[k]])) {
        yk = Yin[iFinite->data[k] - 2];
      } else {
        yk = Yin[iFinite->data[k]];
      }

      if (ykfirst - yk >= 0.0) {
        nPk++;
        iInflect->data[nPk - 1] = iFinite->data[k];
      }
    }
  }

  emxFree_int32_T(&iFinite);
  emxInit_int32_T(&c, 1);
  emxInit_int32_T(&ia, 1);
  emxInit_int32_T(&ib, 1);
  k = iInflect->size[0];
  if (1 > nPk) {
    iInflect->size[0] = 0;
  } else {
    iInflect->size[0] = nPk;
  }

  emxEnsureCapacity_int32_T(iInflect, k);
  do_vectors(iInflect, iInfinite, c, ia, ib);
  emxFree_int32_T(&iInfinite);
  emxFree_int32_T(&ib);
  emxFree_int32_T(&ia);
  emxFree_int32_T(&iInflect);
  for (k = 0; k < 280800; k++) {
    b_dv[k] = static_cast<double>(k) + 1.0;
  }

  emxInit_int32_T(&idx, 1);
  f_findPeaksSeparatedByMoreThanM(Yin, b_dv, c, idx);
  emxInit_int32_T(&iPk, 1);
  if (idx->size[0] > 280800) {
    k = iPk->size[0];
    iPk->size[0] = 280800;
    emxEnsureCapacity_int32_T(iPk, k);
    for (k = 0; k < 280800; k++) {
      iPk->data[k] = idx->data[k];
    }

    k = idx->size[0];
    idx->size[0] = iPk->size[0];
    emxEnsureCapacity_int32_T(idx, k);
    kfirst = iPk->size[0];
    for (k = 0; k < kfirst; k++) {
      idx->data[k] = iPk->data[k];
    }
  }

  k = iPk->size[0];
  iPk->size[0] = idx->size[0];
  emxEnsureCapacity_int32_T(iPk, k);
  kfirst = idx->size[0];
  for (k = 0; k < kfirst; k++) {
    iPk->data[k] = c->data[idx->data[k] - 1];
  }

  emxFree_int32_T(&c);
  emxFree_int32_T(&idx);
  k = Ypk->size[0];
  Ypk->size[0] = iPk->size[0];
  emxEnsureCapacity_real_T(Ypk, k);
  kfirst = iPk->size[0];
  for (k = 0; k < kfirst; k++) {
    Ypk->data[k] = Yin[iPk->data[k] - 1];
  }

  k = Xpk->size[0];
  Xpk->size[0] = iPk->size[0];
  emxEnsureCapacity_real_T(Xpk, k);
  kfirst = iPk->size[0];
  for (k = 0; k < kfirst; k++) {
    Xpk->data[k] = iPk->data[k];
  }

  emxFree_int32_T(&iPk);
}

static void f_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1)
{
  unsigned int inSize[8];
  cell_wrap_12 varSizes[1];
  int i;
  boolean_T exitg1;
  static const double b_dv[201] = { -7.8196494978457467E-5,
    0.0005223293015998757, 0.00011743335539330082, -4.1861816076124677E-5,
    -0.00017664027197777181, -0.00023736599884955687, -0.00016725589982047187,
    1.9813233698008422E-5, 0.00022916766188992713, 0.0003320674043562436,
    0.00024391714337651161, -1.2692815641919353E-5, -0.00030388251594248476,
    -0.00045160588718627469, -0.00034002551737650154, 1.1079449195308364E-6,
    0.00039295516301170397, 0.00059814001318252955, 0.00046158920567996285,
    1.9679132606150015E-5, -0.00049567002939567549, -0.00077499326067334215,
    -0.00061375765421455421, -5.3537814840177767E-5, 0.00061175172302874539,
    0.00098574803466226725, 0.00080201199957975983, 0.00010471504084097112,
    -0.00074074437497463413, -0.0012342158034588449, -0.0010324374913399704,
    -0.00017812285699741174, 0.000881883795454136, 0.0015245057584137164,
    0.0013119109985668567, 0.00027951022921373503, -0.001034060083546922,
    -0.0018611587938098613, -0.0016483363445152395, -0.00041565388145135964,
    0.0011958105989782659, 0.0022493668621081956, 0.0020509897192433593,
    0.00059462433227147171, -0.0013653305034408345, -0.0026953170785103064,
    -0.0025310450264324565, -0.0008261845468000783, 0.0015404972974471542,
    0.0032067250347525469, 0.0031023849530990868, 0.0011224065588481781,
    -0.0017189075611319766, -0.0037936651266748185, -0.0037828725529000778,
    -0.0014986489240371673, 0.0018979249985503696, 0.0044698838870751833,
    0.00459638941644433, 0.0019751459862607295, -0.0020747380467965016,
    -0.0052549347239500381, -0.0055762008678731552, -0.0025796756904313584,
    0.0022464256755318, 0.0061777799916414942, 0.0067707347209002957,
    0.0033522218674538959, -0.0024100291504751663, -0.0072831733865171945,
    -0.0082540161037794237, -0.0043535554612266388, 0.0025626276667775538,
    0.0086436912421857942, 0.0101457593688336, 0.0056821187392066767,
    -0.0027014153291123068, -0.010384273594582766, -0.012653390222182499,
    -0.0075102736044488187, 0.0028237769541212361, 0.012737692781888667,
    0.016170089064707526, 0.010171791913422342, -0.0029273601552652112,
    -0.016188662084291709, -0.021540868598057292, -0.014410929891849287,
    0.003010141200691774, 0.021932193971910176, 0.030967141878616392,
    0.022295751552864593, -0.003070482406932213, -0.033903186202695224,
    -0.052529342543044248, -0.0425154155791845, 0.0031071790123606649,
    0.077042010378890913, 0.15898017068311085, 0.22281199518232708,
    0.24688050608505452, 0.22281199518232708, 0.15898017068311085,
    0.077042010378890913, 0.0031071790123606649, -0.0425154155791845,
    -0.052529342543044248, -0.033903186202695224, -0.003070482406932213,
    0.022295751552864593, 0.030967141878616392, 0.021932193971910176,
    0.003010141200691774, -0.014410929891849287, -0.021540868598057292,
    -0.016188662084291709, -0.0029273601552652112, 0.010171791913422342,
    0.016170089064707526, 0.012737692781888667, 0.0028237769541212361,
    -0.0075102736044488187, -0.012653390222182499, -0.010384273594582766,
    -0.0027014153291123068, 0.0056821187392066767, 0.0101457593688336,
    0.0086436912421857942, 0.0025626276667775538, -0.0043535554612266388,
    -0.0082540161037794237, -0.0072831733865171945, -0.0024100291504751663,
    0.0033522218674538959, 0.0067707347209002957, 0.0061777799916414942,
    0.0022464256755318, -0.0025796756904313584, -0.0055762008678731552,
    -0.0052549347239500381, -0.0020747380467965016, 0.0019751459862607295,
    0.00459638941644433, 0.0044698838870751833, 0.0018979249985503696,
    -0.0014986489240371673, -0.0037828725529000778, -0.0037936651266748185,
    -0.0017189075611319766, 0.0011224065588481781, 0.0031023849530990868,
    0.0032067250347525469, 0.0015404972974471542, -0.0008261845468000783,
    -0.0025310450264324565, -0.0026953170785103064, -0.0013653305034408345,
    0.00059462433227147171, 0.0020509897192433593, 0.0022493668621081956,
    0.0011958105989782659, -0.00041565388145135964, -0.0016483363445152395,
    -0.0018611587938098613, -0.001034060083546922, 0.00027951022921373503,
    0.0013119109985668567, 0.0015245057584137164, 0.000881883795454136,
    -0.00017812285699741174, -0.0010324374913399704, -0.0012342158034588449,
    -0.00074074437497463413, 0.00010471504084097112, 0.00080201199957975983,
    0.00098574803466226725, 0.00061175172302874539, -5.3537814840177767E-5,
    -0.00061375765421455421, -0.00077499326067334215, -0.00049567002939567549,
    1.9679132606150015E-5, 0.00046158920567996285, 0.00059814001318252955,
    0.00039295516301170397, 1.1079449195308364E-6, -0.00034002551737650154,
    -0.00045160588718627469, -0.00030388251594248476, -1.2692815641919353E-5,
    0.00024391714337651161, 0.0003320674043562436, 0.00022916766188992713,
    1.9813233698008422E-5, -0.00016725589982047187, -0.00023736599884955687,
    -0.00017664027197777181, -4.1861816076124677E-5, 0.00011743335539330082,
    0.0005223293015998757, -7.8196494978457467E-5 };

  dspcodegen_FIRFilter_3 *b_obj;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    varSizes[0].f1[0] = static_cast<unsigned int>(varargin_1->size[0]);
    varSizes[0].f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes[0].f1[i + 2] = 1U;
    }

    obj->inputVarSize[0] = varSizes[0];
    iobj_0->isInitialized = 0;

    /* System object Constructor function: dsp.FIRFilter */
    iobj_0->cSFunObject.P0_InitialStates = 0.0;
    for (i = 0; i < 201; i++) {
      iobj_0->cSFunObject.P1_Coefficients[i] = b_dv[i];
    }

    iobj_0->matlabCodegenIsDeleted = false;
    obj->FilterObj = iobj_0;
    obj->NumChannels = 1;
    obj->isSetupComplete = true;
    b_obj = obj->FilterObj;
    if (b_obj->isInitialized == 1) {
      /* System object Initialization function: dsp.FIRFilter */
      for (i = 0; i < 200; i++) {
        b_obj->cSFunObject.W0_states[i] = b_obj->cSFunObject.P0_InitialStates;
      }
    }
  }

  inSize[0] = static_cast<unsigned int>(varargin_1->size[0]);
  inSize[1] = 1U;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1U;
  }

  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != inSize[i]) {
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = inSize[i];
      }

      exitg1 = true;
    } else {
      i++;
    }
  }

  LPHPFilterBase_stepImpl(obj, varargin_1, varargout_1);
}

static void f_findPeaksSeparatedByMoreThanM(const double y[280800], const double
  x[280800], const emxArray_int32_T *iPk, emxArray_int32_T *idx)
{
  emxArray_real_T *locs_temp;
  int i;
  int loop_ub;
  emxArray_int32_T *c_sortIdx;
  emxArray_int32_T *r;
  emxArray_boolean_T *idelete;
  emxArray_boolean_T *r1;
  int b_i;
  int end;
  emxArray_int32_T *r2;
  int i1;
  if (iPk->size[0] == 0) {
    idx->size[0] = 0;
  } else {
    emxInit_real_T(&locs_temp, 1);
    i = locs_temp->size[0];
    locs_temp->size[0] = iPk->size[0];
    emxEnsureCapacity_real_T(locs_temp, i);
    loop_ub = iPk->size[0];
    for (i = 0; i < loop_ub; i++) {
      locs_temp->data[i] = y[iPk->data[i] - 1];
    }

    emxInit_int32_T(&c_sortIdx, 1);
    emxInit_int32_T(&r, 1);
    sortIdx(locs_temp, r);
    i = c_sortIdx->size[0];
    c_sortIdx->size[0] = r->size[0];
    emxEnsureCapacity_int32_T(c_sortIdx, i);
    loop_ub = r->size[0];
    for (i = 0; i < loop_ub; i++) {
      c_sortIdx->data[i] = r->data[i];
    }

    i = locs_temp->size[0];
    locs_temp->size[0] = c_sortIdx->size[0];
    emxEnsureCapacity_real_T(locs_temp, i);
    loop_ub = c_sortIdx->size[0];
    for (i = 0; i < loop_ub; i++) {
      locs_temp->data[i] = x[iPk->data[c_sortIdx->data[i] - 1] - 1];
    }

    emxInit_boolean_T(&idelete, 1);
    i = idelete->size[0];
    idelete->size[0] = c_sortIdx->size[0];
    emxEnsureCapacity_boolean_T(idelete, i);
    loop_ub = c_sortIdx->size[0];
    for (i = 0; i < loop_ub; i++) {
      idelete->data[i] = false;
    }

    i = c_sortIdx->size[0];
    emxInit_boolean_T(&r1, 1);
    for (b_i = 0; b_i < i; b_i++) {
      if (!idelete->data[b_i]) {
        end = r1->size[0];
        r1->size[0] = locs_temp->size[0];
        emxEnsureCapacity_boolean_T(r1, end);
        loop_ub = locs_temp->size[0];
        for (end = 0; end < loop_ub; end++) {
          i1 = iPk->data[c_sortIdx->data[b_i] - 1] - 1;
          r1->data[end] = ((locs_temp->data[end] >= x[i1] - 7200.0) &&
                           (locs_temp->data[end] <= x[i1] + 7200.0));
        }

        loop_ub = idelete->size[0];
        for (end = 0; end < loop_ub; end++) {
          idelete->data[end] = (idelete->data[end] || r1->data[end]);
        }

        idelete->data[b_i] = false;
      }
    }

    emxFree_boolean_T(&r1);
    emxFree_real_T(&locs_temp);
    end = idelete->size[0] - 1;
    loop_ub = 0;
    for (b_i = 0; b_i <= end; b_i++) {
      if (!idelete->data[b_i]) {
        loop_ub++;
      }
    }

    emxInit_int32_T(&r2, 1);
    i = r2->size[0];
    r2->size[0] = loop_ub;
    emxEnsureCapacity_int32_T(r2, i);
    loop_ub = 0;
    for (b_i = 0; b_i <= end; b_i++) {
      if (!idelete->data[b_i]) {
        r2->data[loop_ub] = b_i + 1;
        loop_ub++;
      }
    }

    emxFree_boolean_T(&idelete);
    i = r->size[0];
    r->size[0] = r2->size[0];
    emxEnsureCapacity_int32_T(r, i);
    loop_ub = r2->size[0];
    for (i = 0; i < loop_ub; i++) {
      r->data[i] = c_sortIdx->data[r2->data[i] - 1];
    }

    emxFree_int32_T(&r2);
    emxFree_int32_T(&c_sortIdx);
    sort(r);
    i = idx->size[0];
    idx->size[0] = r->size[0];
    emxEnsureCapacity_int32_T(idx, i);
    loop_ub = r->size[0];
    for (i = 0; i < loop_ub; i++) {
      idx->data[i] = r->data[i];
    }

    emxFree_int32_T(&r);
  }
}

static void fft(const emxArray_real_T *x, double varargin_1, emxArray_creal_T *y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  boolean_T guard1 = false;
  int i;
  boolean_T useRadix2;
  int N2blue;
  int nRows;
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  guard1 = false;
  if (x->size[0] == 0) {
    guard1 = true;
  } else {
    i = static_cast<int>(varargin_1);
    if (i == 0) {
      guard1 = true;
    } else {
      useRadix2 = ((i & (i - 1)) == 0);
      get_algo_sizes(static_cast<int>(varargin_1), useRadix2, &N2blue, &nRows);
      generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
      if (useRadix2) {
        r2br_r2dit_trig(x, i, costab, sintab, y);
      } else {
        dobluesteinfft(x, N2blue, i, costab, sintab, sintabinv, y);
      }
    }
  }

  if (guard1) {
    N2blue = static_cast<int>(varargin_1);
    i = y->size[0];
    y->size[0] = N2blue;
    emxEnsureCapacity_creal_T(y, i);
    if (N2blue > x->size[0]) {
      i = y->size[0];
      y->size[0] = N2blue;
      emxEnsureCapacity_creal_T(y, i);
      for (i = 0; i < N2blue; i++) {
        y->data[i].re = 0.0;
        y->data[i].im = 0.0;
      }
    }
  }

  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

static void fftshift(emxArray_real_T *x)
{
  int i2;
  int vlend2;
  int vspread;
  int midoffset;
  int i;
  int i1;
  int j;
  int ia;
  int ib;
  double xtmp;
  int k;
  int ic;
  i2 = x->size[0];
  if (i2 > 1) {
    vlend2 = i2 / 2;
    vspread = i2 - 1;
    midoffset = vlend2 - 1;
    if (vlend2 << 1 == i2) {
      i2 = 0;
      for (i = 0; i < 1; i++) {
        i1 = i2;
        i2 += vspread;
        for (j = 0; j < 1; j++) {
          i1++;
          i2++;
          ia = i1 - 1;
          ib = i1 + midoffset;
          for (k = 0; k < vlend2; k++) {
            xtmp = x->data[ia];
            x->data[ia] = x->data[ib];
            x->data[ib] = xtmp;
            ia++;
            ib++;
          }
        }
      }
    } else {
      i2 = 0;
      for (i = 0; i < 1; i++) {
        i1 = i2;
        i2 += vspread;
        for (j = 0; j < 1; j++) {
          i1++;
          i2++;
          ia = i1 - 1;
          ib = i1 + midoffset;
          xtmp = x->data[ib];
          for (k = 0; k < vlend2; k++) {
            ic = ib + 1;
            x->data[ib] = x->data[ia];
            x->data[ia] = x->data[ic];
            ia++;
            ib = ic;
          }

          x->data[ib] = xtmp;
        }
      }
    }
  }
}

static void findpeaks(const double Yin[264000], emxArray_real_T *Ypk,
                      emxArray_real_T *Xpk)
{
  emxArray_int32_T *iPk;
  emxArray_int32_T *iFinite;
  emxArray_int32_T *iInfinite;
  emxArray_int32_T *iInflect;
  int i;
  int loop_ub;
  emxArray_int32_T *c;
  emxArray_int32_T *ia;
  emxArray_int32_T *ib;
  emxArray_int32_T *idx;
  static double b_dv[264000];
  emxInit_int32_T(&iPk, 1);
  emxInit_int32_T(&iFinite, 1);
  emxInit_int32_T(&iInfinite, 1);
  emxInit_int32_T(&iInflect, 1);
  getAllPeaksCodegen(Yin, iFinite, iInfinite, iInflect);
  removeSmallPeaks(Yin, iFinite, 0.13, iInflect);
  i = iPk->size[0];
  iPk->size[0] = iInflect->size[0];
  emxEnsureCapacity_int32_T(iPk, i);
  loop_ub = iInflect->size[0];
  emxFree_int32_T(&iFinite);
  for (i = 0; i < loop_ub; i++) {
    iPk->data[i] = iInflect->data[i];
  }

  emxFree_int32_T(&iInflect);
  emxInit_int32_T(&c, 1);
  emxInit_int32_T(&ia, 1);
  emxInit_int32_T(&ib, 1);
  do_vectors(iPk, iInfinite, c, ia, ib);
  emxFree_int32_T(&ib);
  emxFree_int32_T(&ia);
  emxFree_int32_T(&iInfinite);
  for (i = 0; i < 264000; i++) {
    b_dv[i] = static_cast<double>(i) + 1.0;
  }

  emxInit_int32_T(&idx, 1);
  c_findPeaksSeparatedByMoreThanM(Yin, b_dv, c, idx);
  if (idx->size[0] > 264000) {
    i = iPk->size[0];
    iPk->size[0] = 264000;
    emxEnsureCapacity_int32_T(iPk, i);
    for (i = 0; i < 264000; i++) {
      iPk->data[i] = idx->data[i];
    }

    i = idx->size[0];
    idx->size[0] = iPk->size[0];
    emxEnsureCapacity_int32_T(idx, i);
    loop_ub = iPk->size[0];
    for (i = 0; i < loop_ub; i++) {
      idx->data[i] = iPk->data[i];
    }
  }

  i = iPk->size[0];
  iPk->size[0] = idx->size[0];
  emxEnsureCapacity_int32_T(iPk, i);
  loop_ub = idx->size[0];
  for (i = 0; i < loop_ub; i++) {
    iPk->data[i] = c->data[idx->data[i] - 1];
  }

  emxFree_int32_T(&c);
  emxFree_int32_T(&idx);
  i = Ypk->size[0];
  Ypk->size[0] = iPk->size[0];
  emxEnsureCapacity_real_T(Ypk, i);
  loop_ub = iPk->size[0];
  for (i = 0; i < loop_ub; i++) {
    Ypk->data[i] = Yin[iPk->data[i] - 1];
  }

  i = Xpk->size[0];
  Xpk->size[0] = iPk->size[0];
  emxEnsureCapacity_real_T(Xpk, i);
  loop_ub = iPk->size[0];
  for (i = 0; i < loop_ub; i++) {
    Xpk->data[i] = iPk->data[i];
  }

  emxFree_int32_T(&iPk);
}

static void g_SystemCore_parenReference(dsp_LowpassFilter *obj, const
  emxArray_real_T *varargin_1, dspcodegen_FIRFilter_3 *iobj_0, emxArray_real_T
  *varargout_1)
{
  unsigned int inSize[8];
  cell_wrap_12 varSizes[1];
  int i;
  boolean_T exitg1;
  static const double b_dv[201] = { -0.00013626720817041483,
    0.00049448076680896674, 0.00016610606854087926, -1.8198255374938377E-5,
    -0.00017280730957161243, -0.00023355368463338642, -0.00014034322269266386,
    7.2000999015227858E-5, 0.00027122742331104564, 0.00030791813220552248,
    0.00012556399923716212, -0.00017980404461020452, -0.00040455976178166967,
    -0.000370636109444955, -6.147335976354129E-5, 0.00034017005433405721,
    0.00055581418931059234, 0.00040100236278430273, -6.5970347707871427E-5,
    -0.000551599356646665, -0.00070758219907965391, -0.00037618309298903952,
    0.00026958256308229562, 0.0008070323867711758, 0.00083633490730812326,
    0.00027163706902628206, -0.00055745713427640914, -0.0010910149455538635,
    -0.00091225941045954841, -6.3379515345195816E-5, 0.00093015765380891947,
    0.0013784690326412738, 0.00090054240564262848, -0.00026908705352053094,
    -0.0013781964290504971, -0.0016343993064635116, -0.00076359773745454272,
    0.00073950370389688888, 0.0018799862474485514, 0.0018145458975664173,
    0.00046405580752853048, -0.001351536253300406, -0.00240048623519067,
    -0.0018669853622803681, 3.1712357253501369E-5, 0.0020957085072990443,
    0.0028907001300012528, 0.0017345714858281623, -0.00074984058046900391,
    -0.0029468655866379911, -0.0032880615715103608, -0.0013579639093209404,
    0.0017053470764279231, 0.0038623636254055643, 0.0035175589573239303,
    0.00067882581717276205, -0.0028990377567977396, -0.0047810270474893928,
    -0.0034931931884489152, 0.00035742383292101547, 0.00431530831246122,
    0.0056226516485884167, 0.0031189794916321369, -0.0018001884288824579,
    -0.0059211600343740227, -0.00628739118264683, -0.0022880651490105267,
    0.0036949480698332347, 0.0076666457089045546, 0.0066535559360701227,
    0.00087729513391441856, -0.0060895097104323925, -0.0094868308330704355,
    -0.0065706611658242764, 0.0012682439937881898, 0.0090499512465050825,
    0.011305206723753085, 0.0058404588351841638, -0.0043734385680146894,
    -0.012697514484438845, -0.013038340755672076, -0.0041670540077388867,
    0.0088286197534708059, 0.017298370667787062, 0.014601412391582184,
    0.0010178846965982638, -0.015454612306344978, -0.023516485911075038,
    -0.015914177936384968, 0.0048305284776777374, 0.026407983845270468,
    0.033331981318164471, 0.01690684477419736, -0.017319448697243608,
    -0.049706062249164518, -0.055344299211790855, -0.017525326058478737,
    0.061372466303181515, 0.15802413321569342, 0.23721024700283391,
    0.26773539152892573, 0.23721024700283391, 0.15802413321569342,
    0.061372466303181515, -0.017525326058478737, -0.055344299211790855,
    -0.049706062249164518, -0.017319448697243608, 0.01690684477419736,
    0.033331981318164471, 0.026407983845270468, 0.0048305284776777374,
    -0.015914177936384968, -0.023516485911075038, -0.015454612306344978,
    0.0010178846965982638, 0.014601412391582184, 0.017298370667787062,
    0.0088286197534708059, -0.0041670540077388867, -0.013038340755672076,
    -0.012697514484438845, -0.0043734385680146894, 0.0058404588351841638,
    0.011305206723753085, 0.0090499512465050825, 0.0012682439937881898,
    -0.0065706611658242764, -0.0094868308330704355, -0.0060895097104323925,
    0.00087729513391441856, 0.0066535559360701227, 0.0076666457089045546,
    0.0036949480698332347, -0.0022880651490105267, -0.00628739118264683,
    -0.0059211600343740227, -0.0018001884288824579, 0.0031189794916321369,
    0.0056226516485884167, 0.00431530831246122, 0.00035742383292101547,
    -0.0034931931884489152, -0.0047810270474893928, -0.0028990377567977396,
    0.00067882581717276205, 0.0035175589573239303, 0.0038623636254055643,
    0.0017053470764279231, -0.0013579639093209404, -0.0032880615715103608,
    -0.0029468655866379911, -0.00074984058046900391, 0.0017345714858281623,
    0.0028907001300012528, 0.0020957085072990443, 3.1712357253501369E-5,
    -0.0018669853622803681, -0.00240048623519067, -0.001351536253300406,
    0.00046405580752853048, 0.0018145458975664173, 0.0018799862474485514,
    0.00073950370389688888, -0.00076359773745454272, -0.0016343993064635116,
    -0.0013781964290504971, -0.00026908705352053094, 0.00090054240564262848,
    0.0013784690326412738, 0.00093015765380891947, -6.3379515345195816E-5,
    -0.00091225941045954841, -0.0010910149455538635, -0.00055745713427640914,
    0.00027163706902628206, 0.00083633490730812326, 0.0008070323867711758,
    0.00026958256308229562, -0.00037618309298903952, -0.00070758219907965391,
    -0.000551599356646665, -6.5970347707871427E-5, 0.00040100236278430273,
    0.00055581418931059234, 0.00034017005433405721, -6.147335976354129E-5,
    -0.000370636109444955, -0.00040455976178166967, -0.00017980404461020452,
    0.00012556399923716212, 0.00030791813220552248, 0.00027122742331104564,
    7.2000999015227858E-5, -0.00014034322269266386, -0.00023355368463338642,
    -0.00017280730957161243, -1.8198255374938377E-5, 0.00016610606854087926,
    0.00049448076680896674, -0.00013626720817041483 };

  dspcodegen_FIRFilter_3 *b_obj;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    varSizes[0].f1[0] = static_cast<unsigned int>(varargin_1->size[0]);
    varSizes[0].f1[1] = 1U;
    for (i = 0; i < 6; i++) {
      varSizes[0].f1[i + 2] = 1U;
    }

    obj->inputVarSize[0] = varSizes[0];
    iobj_0->isInitialized = 0;

    /* System object Constructor function: dsp.FIRFilter */
    iobj_0->cSFunObject.P0_InitialStates = 0.0;
    for (i = 0; i < 201; i++) {
      iobj_0->cSFunObject.P1_Coefficients[i] = b_dv[i];
    }

    iobj_0->matlabCodegenIsDeleted = false;
    obj->FilterObj = iobj_0;
    obj->NumChannels = 1;
    obj->isSetupComplete = true;
    b_obj = obj->FilterObj;
    if (b_obj->isInitialized == 1) {
      /* System object Initialization function: dsp.FIRFilter */
      for (i = 0; i < 200; i++) {
        b_obj->cSFunObject.W0_states[i] = b_obj->cSFunObject.P0_InitialStates;
      }
    }
  }

  inSize[0] = static_cast<unsigned int>(varargin_1->size[0]);
  inSize[1] = 1U;
  for (i = 0; i < 6; i++) {
    inSize[i + 2] = 1U;
  }

  i = 0;
  exitg1 = false;
  while ((!exitg1) && (i < 8)) {
    if (obj->inputVarSize[0].f1[i] != inSize[i]) {
      for (i = 0; i < 8; i++) {
        obj->inputVarSize[0].f1[i] = inSize[i];
      }

      exitg1 = true;
    } else {
      i++;
    }
  }

  LPHPFilterBase_stepImpl(obj, varargin_1, varargout_1);
}

static void generate_twiddle_tables(int nRows, boolean_T useRadix2,
  emxArray_real_T *costab, emxArray_real_T *sintab, emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  int n;
  int i;
  int nd2;
  int k;
  emxInit_real_T(&costab1q, 2);
  e = 6.2831853071795862 / static_cast<double>(nRows);
  n = nRows / 2 / 2;
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i);
  costab1q->data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q->data[k + 1] = std::cos(e * (static_cast<double>(k) + 1.0));
  }

  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q->data[k] = std::sin(e * static_cast<double>(n - k));
  }

  costab1q->data[n] = 0.0;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    i = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i);
    for (k = 0; k < n; k++) {
      sintabinv->data[k + 1] = costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      sintabinv->data[k] = costab1q->data[k - n];
    }

    for (k = 0; k < n; k++) {
      costab->data[k + 1] = costab1q->data[k + 1];
      sintab->data[k + 1] = -costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    costab->data[0] = 1.0;
    sintab->data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab->data[k + 1] = costab1q->data[k + 1];
      sintab->data[k + 1] = -costab1q->data[(n - k) - 1];
    }

    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab->data[k] = -costab1q->data[nd2 - k];
      sintab->data[k] = -costab1q->data[k - n];
    }

    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }

  emxFree_real_T(&costab1q);
}

static void getAllPeaksCodegen(const double y[264000], emxArray_int32_T *iPk,
  emxArray_int32_T *iInf, emxArray_int32_T *iInflect)
{
  int nPk;
  int nInf;
  int nInflect;
  char dir;
  int kfirst;
  double ykfirst;
  boolean_T isinfykfirst;
  int k;
  double yk;
  emxArray_int32_T *b_iPk;
  boolean_T isinfyk;
  char previousdir;
  nPk = iPk->size[0];
  iPk->size[0] = 264000;
  emxEnsureCapacity_int32_T(iPk, nPk);
  nPk = iInf->size[0];
  iInf->size[0] = 264000;
  emxEnsureCapacity_int32_T(iInf, nPk);
  nPk = iInflect->size[0];
  iInflect->size[0] = 264000;
  emxEnsureCapacity_int32_T(iInflect, nPk);
  nPk = -1;
  nInf = -1;
  nInflect = -1;
  dir = 'n';
  kfirst = 0;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (k = 0; k < 264000; k++) {
    yk = y[k];
    if (rtIsNaN(y[k])) {
      yk = rtInf;
      isinfyk = true;
    } else if (rtIsInf(y[k]) && (y[k] > 0.0)) {
      isinfyk = true;
      nInf++;
      iInf->data[nInf] = k + 1;
    } else {
      isinfyk = false;
    }

    if (yk != ykfirst) {
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
        if (kfirst >= 1) {
          nInflect++;
          iInflect->data[nInflect] = kfirst;
        }
      } else if (yk < ykfirst) {
        dir = 'd';
        if ('d' != previousdir) {
          nInflect++;
          iInflect->data[nInflect] = kfirst;
          if (previousdir == 'i') {
            nPk++;
            iPk->data[nPk] = kfirst;
          }
        }
      } else {
        dir = 'i';
        if ('i' != previousdir) {
          nInflect++;
          iInflect->data[nInflect] = kfirst;
        }
      }

      ykfirst = yk;
      kfirst = k + 1;
      isinfykfirst = isinfyk;
    }
  }

  if ((!isinfykfirst) && ((nInflect + 1 == 0) || (iInflect->data[nInflect] <
        264000))) {
    nInflect++;
    iInflect->data[nInflect] = 264000;
  }

  emxInit_int32_T(&b_iPk, 1);
  if (1 > nPk + 1) {
    kfirst = -1;
  } else {
    kfirst = nPk;
  }

  nPk = b_iPk->size[0];
  b_iPk->size[0] = kfirst + 1;
  emxEnsureCapacity_int32_T(b_iPk, nPk);
  for (nPk = 0; nPk <= kfirst; nPk++) {
    b_iPk->data[nPk] = iPk->data[nPk];
  }

  nPk = iPk->size[0];
  iPk->size[0] = b_iPk->size[0];
  emxEnsureCapacity_int32_T(iPk, nPk);
  kfirst = b_iPk->size[0];
  for (nPk = 0; nPk < kfirst; nPk++) {
    iPk->data[nPk] = b_iPk->data[nPk];
  }

  if (1 > nInf + 1) {
    kfirst = -1;
  } else {
    kfirst = nInf;
  }

  nPk = b_iPk->size[0];
  b_iPk->size[0] = kfirst + 1;
  emxEnsureCapacity_int32_T(b_iPk, nPk);
  for (nPk = 0; nPk <= kfirst; nPk++) {
    b_iPk->data[nPk] = iInf->data[nPk];
  }

  nPk = iInf->size[0];
  iInf->size[0] = b_iPk->size[0];
  emxEnsureCapacity_int32_T(iInf, nPk);
  kfirst = b_iPk->size[0];
  for (nPk = 0; nPk < kfirst; nPk++) {
    iInf->data[nPk] = b_iPk->data[nPk];
  }

  if (1 > nInflect + 1) {
    kfirst = -1;
  } else {
    kfirst = nInflect;
  }

  nPk = b_iPk->size[0];
  b_iPk->size[0] = kfirst + 1;
  emxEnsureCapacity_int32_T(b_iPk, nPk);
  for (nPk = 0; nPk <= kfirst; nPk++) {
    b_iPk->data[nPk] = iInflect->data[nPk];
  }

  nPk = iInflect->size[0];
  iInflect->size[0] = b_iPk->size[0];
  emxEnsureCapacity_int32_T(iInflect, nPk);
  kfirst = b_iPk->size[0];
  for (nPk = 0; nPk < kfirst; nPk++) {
    iInflect->data[nPk] = b_iPk->data[nPk];
  }

  emxFree_int32_T(&b_iPk);
}

static void get_algo_sizes(int n1, boolean_T useRadix2, int *N2blue, int *nRows)
{
  int n;
  int pmax;
  int pmin;
  boolean_T exitg1;
  int k;
  int pow2p;
  *N2blue = 1;
  if (useRadix2) {
    *nRows = n1;
  } else {
    n = (n1 + n1) - 1;
    pmax = 31;
    if (n <= 1) {
      pmax = 0;
    } else {
      pmin = 0;
      exitg1 = false;
      while ((!exitg1) && (pmax - pmin > 1)) {
        k = (pmin + pmax) >> 1;
        pow2p = 1 << k;
        if (pow2p == n) {
          pmax = k;
          exitg1 = true;
        } else if (pow2p > n) {
          pmax = k;
        } else {
          pmin = k;
        }
      }
    }

    *N2blue = 1 << pmax;
    *nRows = *N2blue;
  }
}

static void ifft(const emxArray_creal_T *x, emxArray_creal_T *y)
{
  emxArray_creal_T *b_y;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  boolean_T useRadix2;
  int N2blue;
  int nRows;
  emxInit_creal_T(&b_y, 1);
  if (x->size[0] == 0) {
    y->size[0] = 0;
  } else {
    emxInit_real_T(&costab, 2);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    useRadix2 = ((x->size[0] & (x->size[0] - 1)) == 0);
    get_algo_sizes(x->size[0], useRadix2, &N2blue, &nRows);
    b_generate_twiddle_tables(nRows, useRadix2, costab, sintab, sintabinv);
    if (useRadix2) {
      b_r2br_r2dit_trig(x, x->size[0], costab, sintab, b_y);
      N2blue = y->size[0];
      y->size[0] = b_y->size[0];
      emxEnsureCapacity_creal_T(y, N2blue);
      nRows = b_y->size[0];
      for (N2blue = 0; N2blue < nRows; N2blue++) {
        y->data[N2blue] = b_y->data[N2blue];
      }
    } else {
      b_dobluesteinfft(x, N2blue, x->size[0], costab, sintab, sintabinv, y);
    }

    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
  }

  emxFree_creal_T(&b_y);
}

static void inverse(const emxArray_real_T *Rx, emxArray_real_T *A)
{
  emxArray_real_T *x;
  int nsample;
  int i;
  int loop_ub;
  emxArray_real_T *y;
  emxArray_real_T *r;
  int b_i;
  boolean_T guard1 = false;
  boolean_T exitg1;
  double d;
  emxInit_real_T(&x, 2);

  /* INVERSE is a function that solves the inverse problem of acoustic plane */
  /* wave propagation in duct */
  /*    Syntax: A=inverse(Rx) or A=inverse(Rx,A0) or A=inverse(Tx,Rx,A0) */
  /*    Tx: Transmitted signal */
  /*    Rx: Reflected signal */
  /*    A: Cross-sectional area of duct, function of position */
  /*    A0: Initial cross-sectional area of duct */
  nsample = Rx->size[0] - 2;
  i = x->size[0] * x->size[1];
  x->size[0] = Rx->size[0];
  x->size[1] = Rx->size[0];
  emxEnsureCapacity_real_T(x, i);
  loop_ub = Rx->size[0] * Rx->size[0];
  for (i = 0; i < loop_ub; i++) {
    x->data[i] = 0.0;
  }

  emxInit_real_T(&y, 2);
  i = y->size[0] * y->size[1];
  y->size[0] = Rx->size[0];
  y->size[1] = Rx->size[0];
  emxEnsureCapacity_real_T(y, i);
  loop_ub = Rx->size[0] * Rx->size[0];
  for (i = 0; i < loop_ub; i++) {
    y->data[i] = 0.0;
  }

  emxInit_real_T(&r, 2);
  i = r->size[0] * r->size[1];
  r->size[0] = 1;
  r->size[1] = Rx->size[0];
  emxEnsureCapacity_real_T(r, i);
  loop_ub = Rx->size[0];
  for (i = 0; i < loop_ub; i++) {
    r->data[i] = 0.0;
  }

  x->data[0] = 1.0;
  loop_ub = Rx->size[0];
  for (i = 0; i < loop_ub; i++) {
    y->data[i] = Rx->data[i];
  }

  r->data[0] = -y->data[0] / x->data[0];
  i = A->size[0];
  A->size[0] = Rx->size[0];
  emxEnsureCapacity_real_T(A, i);
  loop_ub = Rx->size[0];
  for (i = 0; i < loop_ub; i++) {
    A->data[i] = 1.2;
  }

  b_i = 0;
  guard1 = false;
  exitg1 = false;
  while ((!exitg1) && (b_i <= nsample)) {
    i = nsample - b_i;
    for (loop_ub = 0; loop_ub <= i; loop_ub++) {
      x->data[loop_ub + x->size[0] * (b_i + 1)] = x->data[loop_ub + x->size[0] *
        b_i] / (1.0 - r->data[b_i]) + y->data[loop_ub + y->size[0] * b_i] *
        r->data[b_i] / (1.0 - r->data[b_i]);
      y->data[loop_ub + y->size[0] * (b_i + 1)] = x->data[(loop_ub + x->size[0] *
        b_i) + 1] * r->data[b_i] / (1.0 - r->data[b_i]) + y->data[(loop_ub +
        y->size[0] * b_i) + 1] / (1.0 - r->data[b_i]);
    }

    r->data[b_i + 1] = -y->data[y->size[0] * (b_i + 1)] / x->data[x->size[0] *
      (b_i + 1)];
    if (A->data[b_i] < 0.2) {
      guard1 = true;
      exitg1 = true;
    } else {
      d = r->data[b_i + 1];
      if (std::abs(d) >= 1.0) {
        guard1 = true;
        exitg1 = true;
      } else {
        A->data[b_i + 1] = A->data[b_i] * (d + 1.0) / (1.0 - d);
        b_i++;
        guard1 = false;
      }
    }
  }

  if (guard1) {
    if (b_i + 2 > A->size[0]) {
      i = -1;
      nsample = 0;
    } else {
      i = b_i;
      nsample = A->size[0];
    }

    d = A->data[b_i];
    loop_ub = (nsample - i) - 1;
    for (nsample = 0; nsample < loop_ub; nsample++) {
      A->data[(i + nsample) + 1] = d;
    }
  }

  emxFree_real_T(&r);
  emxFree_real_T(&y);
  emxFree_real_T(&x);
}

static double mFindDelay(const emxArray_real_T *x, const emxArray_real_T *y)
{
  emxArray_real_T *c;
  int n;
  int i;
  double m;
  int k;
  boolean_T exitg1;
  int b_i;
  int exitg2;
  int idx;
  double ex;
  emxInit_real_T(&c, 1);

  /* MYFINDDELAY Summary of this function goes here */
  /*    Detailed explanation goes here */
  xcorr(y, x, c);
  n = c->size[0];
  if (c->size[0] <= 2) {
    if (c->size[0] == 1) {
      m = c->data[0];
      i = 1;
    } else if ((c->data[0] < c->data[1]) || (rtIsNaN(c->data[0]) && (!rtIsNaN
                 (c->data[1])))) {
      m = c->data[1];
      i = 2;
    } else {
      m = c->data[0];
      i = 1;
    }
  } else {
    if (!rtIsNaN(c->data[0])) {
      i = 1;
    } else {
      i = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= c->size[0])) {
        if (!rtIsNaN(c->data[k - 1])) {
          i = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (i == 0) {
      m = c->data[0];
      i = 1;
    } else {
      m = c->data[i - 1];
      b_i = i + 1;
      for (k = b_i; k <= n; k++) {
        if (m < c->data[k - 1]) {
          m = c->data[k - 1];
          i = k;
        }
      }
    }
  }

  do {
    exitg2 = 0;
    if (1 > i - 50) {
      b_i = 0;
    } else {
      b_i = i - 50;
    }

    if (b_i <= 2) {
      if (b_i == 1) {
        ex = c->data[0];
      } else if ((c->data[0] < c->data[1]) || (rtIsNaN(c->data[0]) && (!rtIsNaN
                   (c->data[1])))) {
        ex = c->data[1];
      } else {
        ex = c->data[0];
      }
    } else {
      if (!rtIsNaN(c->data[0])) {
        idx = 1;
      } else {
        idx = 0;
        k = 2;
        exitg1 = false;
        while ((!exitg1) && (k <= b_i)) {
          if (!rtIsNaN(c->data[k - 1])) {
            idx = k;
            exitg1 = true;
          } else {
            k++;
          }
        }
      }

      if (idx == 0) {
        ex = c->data[0];
      } else {
        ex = c->data[idx - 1];
        n = idx + 1;
        for (k = n; k <= b_i; k++) {
          if (ex < c->data[k - 1]) {
            ex = c->data[k - 1];
          }
        }
      }
    }

    if (ex > 0.6 * m) {
      if (1 > i - 50) {
        b_i = 0;
      } else {
        b_i = i - 50;
      }

      if (b_i <= 2) {
        if (b_i == 1) {
          m = c->data[0];
          i = 1;
        } else if ((c->data[0] < c->data[1]) || (rtIsNaN(c->data[0]) &&
                    (!rtIsNaN(c->data[1])))) {
          m = c->data[1];
          i = 2;
        } else {
          m = c->data[0];
          i = 1;
        }
      } else {
        if (!rtIsNaN(c->data[0])) {
          i = 1;
        } else {
          i = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= b_i)) {
            if (!rtIsNaN(c->data[k - 1])) {
              i = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }

        if (i == 0) {
          m = c->data[0];
          i = 1;
        } else {
          m = c->data[i - 1];
          n = i + 1;
          for (k = n; k <= b_i; k++) {
            if (m < c->data[k - 1]) {
              m = c->data[k - 1];
              i = k;
            }
          }
        }
      }
    } else {
      exitg2 = 1;
    }
  } while (exitg2 == 0);

  emxFree_real_T(&c);
  n = x->size[0];
  idx = y->size[0];
  if (n > idx) {
    idx = n;
  }

  return i - idx;
}

static void mLowpass(const emxArray_real_T *x, double Fc, emxArray_real_T *y)
{
  dspcodegen_FIRFilter_3 lobj_7;
  dsp_LowpassFilter LPF;
  dspcodegen_FIRFilter_3 lobj_8;
  dsp_LowpassFilter b_LPF;
  dspcodegen_FIRFilter_3 lobj_9;
  dsp_LowpassFilter c_LPF;
  dspcodegen_FIRFilter_3 lobj_10;
  dsp_LowpassFilter d_LPF;
  dspcodegen_FIRFilter_3 lobj_11;
  dsp_LowpassFilter e_LPF;
  dspcodegen_FIRFilter_3 lobj_12;
  dsp_LowpassFilter f_LPF;
  dspcodegen_FIRFilter_3 lobj_13;
  dsp_LowpassFilter g_LPF;
  emxArray_real_T *x_filtered;
  int i;
  int loop_ub;
  int i1;
  double b_x_filtered[100];
  lobj_7.matlabCodegenIsDeleted = true;
  LPF.matlabCodegenIsDeleted = true;
  lobj_8.matlabCodegenIsDeleted = true;
  b_LPF.matlabCodegenIsDeleted = true;
  lobj_9.matlabCodegenIsDeleted = true;
  c_LPF.matlabCodegenIsDeleted = true;
  lobj_10.matlabCodegenIsDeleted = true;
  d_LPF.matlabCodegenIsDeleted = true;
  lobj_11.matlabCodegenIsDeleted = true;
  e_LPF.matlabCodegenIsDeleted = true;
  lobj_12.matlabCodegenIsDeleted = true;
  f_LPF.matlabCodegenIsDeleted = true;
  lobj_13.matlabCodegenIsDeleted = true;
  g_LPF.matlabCodegenIsDeleted = true;
  emxInit_real_T(&x_filtered, 2);
  if (Fc < 3250.0) {
    g_LPF.isInitialized = 0;
    g_LPF.NumChannels = -1;
    g_LPF.matlabCodegenIsDeleted = false;
    SystemCore_parenReference(&g_LPF, x, &lobj_13, x_filtered);
    i = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, i);
    loop_ub = x->size[0];
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = 0.0;
    }

    i = x_filtered->size[0] * x_filtered->size[1];
    if (101 > i) {
      i1 = 0;
      i = 0;
    } else {
      i1 = 100;
    }

    loop_ub = i - i1;
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = x_filtered->data[i1 + i];
    }

    if (x->size[0] - 99 > y->size[0]) {
      i = -1;
      i1 = 0;
    } else {
      i = x->size[0] - 101;
      i1 = y->size[0];
    }

    for (loop_ub = 0; loop_ub < 100; loop_ub++) {
      b_x_filtered[loop_ub] = x_filtered->data[loop_ub];
    }

    loop_ub = (i1 - i) - 1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      y->data[(i + i1) + 1] = b_x_filtered[i1];
    }
  } else if ((Fc >= 3250.0) && (Fc < 3750.0)) {
    f_LPF.isInitialized = 0;
    f_LPF.NumChannels = -1;
    f_LPF.matlabCodegenIsDeleted = false;
    b_SystemCore_parenReference(&f_LPF, x, &lobj_12, x_filtered);
    i = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, i);
    loop_ub = x->size[0];
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = 0.0;
    }

    i = x_filtered->size[0] * x_filtered->size[1];
    if (101 > i) {
      i1 = 0;
      i = 0;
    } else {
      i1 = 100;
    }

    loop_ub = i - i1;
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = x_filtered->data[i1 + i];
    }

    if (x->size[0] - 99 > y->size[0]) {
      i = -1;
      i1 = 0;
    } else {
      i = x->size[0] - 101;
      i1 = y->size[0];
    }

    for (loop_ub = 0; loop_ub < 100; loop_ub++) {
      b_x_filtered[loop_ub] = x_filtered->data[loop_ub];
    }

    loop_ub = (i1 - i) - 1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      y->data[(i + i1) + 1] = b_x_filtered[i1];
    }
  } else if ((Fc >= 3750.0) && (Fc < 4250.0)) {
    e_LPF.isInitialized = 0;
    e_LPF.NumChannels = -1;
    e_LPF.matlabCodegenIsDeleted = false;
    c_SystemCore_parenReference(&e_LPF, x, &lobj_11, x_filtered);
    i = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, i);
    loop_ub = x->size[0];
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = 0.0;
    }

    i = x_filtered->size[0] * x_filtered->size[1];
    if (101 > i) {
      i1 = 0;
      i = 0;
    } else {
      i1 = 100;
    }

    loop_ub = i - i1;
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = x_filtered->data[i1 + i];
    }

    if (x->size[0] - 99 > y->size[0]) {
      i = -1;
      i1 = 0;
    } else {
      i = x->size[0] - 101;
      i1 = y->size[0];
    }

    for (loop_ub = 0; loop_ub < 100; loop_ub++) {
      b_x_filtered[loop_ub] = x_filtered->data[loop_ub];
    }

    loop_ub = (i1 - i) - 1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      y->data[(i + i1) + 1] = b_x_filtered[i1];
    }
  } else if ((Fc >= 4250.0) && (Fc < 4750.0)) {
    d_LPF.isInitialized = 0;
    d_LPF.NumChannels = -1;
    d_LPF.matlabCodegenIsDeleted = false;
    d_SystemCore_parenReference(&d_LPF, x, &lobj_10, x_filtered);
    i = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, i);
    loop_ub = x->size[0];
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = 0.0;
    }

    i = x_filtered->size[0] * x_filtered->size[1];
    if (101 > i) {
      i1 = 0;
      i = 0;
    } else {
      i1 = 100;
    }

    loop_ub = i - i1;
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = x_filtered->data[i1 + i];
    }

    if (x->size[0] - 99 > y->size[0]) {
      i = -1;
      i1 = 0;
    } else {
      i = x->size[0] - 101;
      i1 = y->size[0];
    }

    for (loop_ub = 0; loop_ub < 100; loop_ub++) {
      b_x_filtered[loop_ub] = x_filtered->data[loop_ub];
    }

    loop_ub = (i1 - i) - 1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      y->data[(i + i1) + 1] = b_x_filtered[i1];
    }
  } else if ((Fc >= 4750.0) && (Fc < 5250.0)) {
    c_LPF.isInitialized = 0;
    c_LPF.NumChannels = -1;
    c_LPF.matlabCodegenIsDeleted = false;
    e_SystemCore_parenReference(&c_LPF, x, &lobj_9, x_filtered);
    i = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, i);
    loop_ub = x->size[0];
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = 0.0;
    }

    i = x_filtered->size[0] * x_filtered->size[1];
    if (101 > i) {
      i1 = 0;
      i = 0;
    } else {
      i1 = 100;
    }

    loop_ub = i - i1;
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = x_filtered->data[i1 + i];
    }

    if (x->size[0] - 99 > y->size[0]) {
      i = -1;
      i1 = 0;
    } else {
      i = x->size[0] - 101;
      i1 = y->size[0];
    }

    for (loop_ub = 0; loop_ub < 100; loop_ub++) {
      b_x_filtered[loop_ub] = x_filtered->data[loop_ub];
    }

    loop_ub = (i1 - i) - 1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      y->data[(i + i1) + 1] = b_x_filtered[i1];
    }
  } else if ((Fc >= 5250.0) && (Fc < 5750.0)) {
    b_LPF.isInitialized = 0;
    b_LPF.NumChannels = -1;
    b_LPF.matlabCodegenIsDeleted = false;
    f_SystemCore_parenReference(&b_LPF, x, &lobj_8, x_filtered);
    i = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, i);
    loop_ub = x->size[0];
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = 0.0;
    }

    i = x_filtered->size[0] * x_filtered->size[1];
    if (101 > i) {
      i1 = 0;
      i = 0;
    } else {
      i1 = 100;
    }

    loop_ub = i - i1;
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = x_filtered->data[i1 + i];
    }

    if (x->size[0] - 99 > y->size[0]) {
      i = -1;
      i1 = 0;
    } else {
      i = x->size[0] - 101;
      i1 = y->size[0];
    }

    for (loop_ub = 0; loop_ub < 100; loop_ub++) {
      b_x_filtered[loop_ub] = x_filtered->data[loop_ub];
    }

    loop_ub = (i1 - i) - 1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      y->data[(i + i1) + 1] = b_x_filtered[i1];
    }
  } else {
    LPF.isInitialized = 0;
    LPF.NumChannels = -1;
    LPF.matlabCodegenIsDeleted = false;
    g_SystemCore_parenReference(&LPF, x, &lobj_7, x_filtered);
    i = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, i);
    loop_ub = x->size[0];
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = 0.0;
    }

    i = x_filtered->size[0] * x_filtered->size[1];
    if (101 > i) {
      i1 = 0;
      i = 0;
    } else {
      i1 = 100;
    }

    loop_ub = i - i1;
    for (i = 0; i < loop_ub; i++) {
      y->data[i] = x_filtered->data[i1 + i];
    }

    if (x->size[0] - 99 > y->size[0]) {
      i = -1;
      i1 = 0;
    } else {
      i = x->size[0] - 101;
      i1 = y->size[0];
    }

    for (loop_ub = 0; loop_ub < 100; loop_ub++) {
      b_x_filtered[loop_ub] = x_filtered->data[loop_ub];
    }

    loop_ub = (i1 - i) - 1;
    for (i1 = 0; i1 < loop_ub; i1++) {
      y->data[(i + i1) + 1] = b_x_filtered[i1];
    }
  }

  emxFree_real_T(&x_filtered);
  c_matlabCodegenHandle_matlabCod(&g_LPF);
  if (!lobj_13.matlabCodegenIsDeleted) {
    lobj_13.matlabCodegenIsDeleted = true;
    if (lobj_13.isInitialized == 1) {
      lobj_13.isInitialized = 2;
    }
  }

  c_matlabCodegenHandle_matlabCod(&f_LPF);
  if (!lobj_12.matlabCodegenIsDeleted) {
    lobj_12.matlabCodegenIsDeleted = true;
    if (lobj_12.isInitialized == 1) {
      lobj_12.isInitialized = 2;
    }
  }

  c_matlabCodegenHandle_matlabCod(&e_LPF);
  if (!lobj_11.matlabCodegenIsDeleted) {
    lobj_11.matlabCodegenIsDeleted = true;
    if (lobj_11.isInitialized == 1) {
      lobj_11.isInitialized = 2;
    }
  }

  c_matlabCodegenHandle_matlabCod(&d_LPF);
  if (!lobj_10.matlabCodegenIsDeleted) {
    lobj_10.matlabCodegenIsDeleted = true;
    if (lobj_10.isInitialized == 1) {
      lobj_10.isInitialized = 2;
    }
  }

  c_matlabCodegenHandle_matlabCod(&c_LPF);
  if (!lobj_9.matlabCodegenIsDeleted) {
    lobj_9.matlabCodegenIsDeleted = true;
    if (lobj_9.isInitialized == 1) {
      lobj_9.isInitialized = 2;
    }
  }

  c_matlabCodegenHandle_matlabCod(&b_LPF);
  if (!lobj_8.matlabCodegenIsDeleted) {
    lobj_8.matlabCodegenIsDeleted = true;
    if (lobj_8.isInitialized == 1) {
      lobj_8.isInitialized = 2;
    }
  }

  c_matlabCodegenHandle_matlabCod(&LPF);
  if (!lobj_7.matlabCodegenIsDeleted) {
    lobj_7.matlabCodegenIsDeleted = true;
    if (lobj_7.isInitialized == 1) {
      lobj_7.isInitialized = 2;
    }
  }
}

static void mean(const emxArray_real_T *x, emxArray_real_T *y)
{
  int vstride;
  int k;
  int j;
  int xoffset;
  if (x->size[0] == 0) {
    y->size[0] = 0;
  } else {
    vstride = x->size[0];
    k = y->size[0];
    y->size[0] = x->size[0];
    emxEnsureCapacity_real_T(y, k);
    for (j = 0; j < vstride; j++) {
      y->data[j] = x->data[j];
    }

    for (k = 0; k < 24; k++) {
      xoffset = (k + 1) * vstride;
      for (j = 0; j < vstride; j++) {
        y->data[j] += x->data[xoffset + j];
      }
    }
  }

  j = y->size[0];
  for (k = 0; k < j; k++) {
    y->data[k] /= 25.0;
  }
}

static void merge(emxArray_int32_T *idx, emxArray_int32_T *x, int offset, int np,
                  int nq, emxArray_int32_T *iwork, emxArray_int32_T *xwork)
{
  int n_tmp;
  int iout;
  int p;
  int i;
  int q;
  int exitg1;
  if (nq != 0) {
    n_tmp = np + nq;
    for (iout = 0; iout < n_tmp; iout++) {
      i = offset + iout;
      iwork->data[iout] = idx->data[i];
      xwork->data[iout] = x->data[i];
    }

    p = 0;
    q = np;
    iout = offset - 1;
    do {
      exitg1 = 0;
      iout++;
      if (xwork->data[p] <= xwork->data[q]) {
        idx->data[iout] = iwork->data[p];
        x->data[iout] = xwork->data[p];
        if (p + 1 < np) {
          p++;
        } else {
          exitg1 = 1;
        }
      } else {
        idx->data[iout] = iwork->data[q];
        x->data[iout] = xwork->data[q];
        if (q + 1 < n_tmp) {
          q++;
        } else {
          q = iout - p;
          for (iout = p + 1; iout <= np; iout++) {
            i = q + iout;
            idx->data[i] = iwork->data[iout - 1];
            x->data[i] = xwork->data[iout - 1];
          }

          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }
}

static void merge_block(emxArray_int32_T *idx, emxArray_int32_T *x, int offset,
  int n, int preSortLevel, emxArray_int32_T *iwork, emxArray_int32_T *xwork)
{
  int nPairs;
  int bLen;
  int tailOffset;
  int nTail;
  nPairs = n >> preSortLevel;
  bLen = 1 << preSortLevel;
  while (nPairs > 1) {
    if ((nPairs & 1) != 0) {
      nPairs--;
      tailOffset = bLen * nPairs;
      nTail = n - tailOffset;
      if (nTail > bLen) {
        merge(idx, x, offset + tailOffset, bLen, nTail - bLen, iwork, xwork);
      }
    }

    tailOffset = bLen << 1;
    nPairs >>= 1;
    for (nTail = 0; nTail < nPairs; nTail++) {
      merge(idx, x, offset + nTail * tailOffset, bLen, bLen, iwork, xwork);
    }

    bLen = tailOffset;
  }

  if (n > bLen) {
    merge(idx, x, offset, bLen, n - bLen, iwork, xwork);
  }
}

static void merge_pow2_block(emxArray_int32_T *idx, emxArray_int32_T *x, int
  offset)
{
  int b;
  int bLen;
  int bLen2;
  int nPairs;
  int k;
  int blockOffset;
  int j;
  int p;
  int iout;
  int q;
  int iwork[256];
  int xwork[256];
  int exitg1;
  for (b = 0; b < 6; b++) {
    bLen = 1 << (b + 2);
    bLen2 = bLen << 1;
    nPairs = 256 >> (b + 3);
    for (k = 0; k < nPairs; k++) {
      blockOffset = offset + k * bLen2;
      for (j = 0; j < bLen2; j++) {
        iout = blockOffset + j;
        iwork[j] = idx->data[iout];
        xwork[j] = x->data[iout];
      }

      p = 0;
      q = bLen;
      iout = blockOffset - 1;
      do {
        exitg1 = 0;
        iout++;
        if (xwork[p] <= xwork[q]) {
          idx->data[iout] = iwork[p];
          x->data[iout] = xwork[p];
          if (p + 1 < bLen) {
            p++;
          } else {
            exitg1 = 1;
          }
        } else {
          idx->data[iout] = iwork[q];
          x->data[iout] = xwork[q];
          if (q + 1 < bLen2) {
            q++;
          } else {
            iout -= p;
            for (j = p + 1; j <= bLen; j++) {
              q = iout + j;
              idx->data[q] = iwork[j - 1];
              x->data[q] = xwork[j - 1];
            }

            exitg1 = 1;
          }
        }
      } while (exitg1 == 0);
    }
  }
}

static void mydtw(const double y[85], double *dist, double ix_data[], int
                  ix_size[1], double iy_data[], int iy_size[1])
{
  double C[7140];
  int i;
  int j;
  double ix[169];
  signed char iy[169];
  double b_i;
  int cj_tmp;
  int k;
  double ci;
  double varargin_1[3];
  int idx;
  double x_data[3];
  int cj_tmp_tmp;
  int b_cj_tmp;
  boolean_T exitg1;

  /* ------------------------------------------------------------------------- */
  /*  w = gausswin(length(x)+15,2); */
  /*  w = w(1:end-15); */
  std::memset(&C[0], 0, 7140U * sizeof(double));
  C[0] = std::abs(0.89419281716303 - y[0]);
  for (i = 0; i < 84; i++) {
    for (j = 0; j < 85; j++) {
      if ((i + 1 != 1) || (j + 1 != 1)) {
        b_i = ((static_cast<double>(i) + 1.0) - 1.0) * 84.0 / 83.0;
        if (((static_cast<double>(j) + 1.0) - 1.0 > b_i + 10.0) || ((
              static_cast<double>(j) + 1.0) - 1.0 < b_i - 10.0)) {
          C[i + 84 * j] = rtNaN;
        } else if (i + 1 == 1) {
          C[84 * j] = C[84 * (j - 1)] + std::abs(0.89419281716303 - y[j]);
        } else if (j + 1 == 1) {
          C[i] = C[i - 1] + std::abs(dv[i] - y[0]);
        } else {
          cj_tmp = i + 84 * j;
          ci = C[cj_tmp - 1];
          varargin_1[0] = ci;
          idx = i + 84 * (j - 1);
          varargin_1[1] = C[idx];
          b_i = C[idx - 1];
          varargin_1[2] = b_i;
          x_data[0] = ci;
          x_data[1] = C[idx];
          x_data[2] = b_i;
          if (!rtIsNaN(ci)) {
            idx = 1;
          } else {
            idx = 0;
            k = 2;
            exitg1 = false;
            while ((!exitg1) && (k < 4)) {
              if (!rtIsNaN(x_data[k - 1])) {
                idx = k;
                exitg1 = true;
              } else {
                k++;
              }
            }
          }

          if (idx != 0) {
            ci = varargin_1[idx - 1];
            idx++;
            for (k = idx; k < 4; k++) {
              b_i = varargin_1[k - 1];
              if (ci > b_i) {
                ci = b_i;
              }
            }
          }

          C[cj_tmp] = ci + std::abs(dv[i] - y[j]);
        }
      }
    }
  }

  /* ------------------------------------------------------------------------- */
  /*  pre-allocate to the maximum warping path size. */
  std::memset(&ix[0], 0, 169U * sizeof(double));
  std::memset(&iy[0], 0, 169U * sizeof(signed char));
  ix[0] = 84.0;
  iy[0] = 85;
  b_i = 84.0;
  j = 83;
  k = 0;
  while ((b_i > 1.0) || (j + 2 > 1)) {
    if (j + 2 == 1) {
      b_i--;
    } else if (b_i == 1.0) {
      j--;
    } else {
      /*  trace back to the origin, ignoring any NaN value */
      /*  prefer i in a tie between i and j */
      idx = static_cast<int>(b_i - 1.0);
      i = 84 * (j + 1);
      ci = C[(idx + i) - 1];
      cj_tmp = static_cast<int>(b_i);
      cj_tmp_tmp = cj_tmp + 84 * j;
      b_cj_tmp = cj_tmp_tmp - 1;
      b_i -= static_cast<double>((C[(cj_tmp + i) - 2] <= C[b_cj_tmp]) ||
        (C[cj_tmp_tmp - 2] <= C[b_cj_tmp]) || (C[b_cj_tmp] != C[b_cj_tmp]));
      j -= ((C[b_cj_tmp] < ci) || (C[(idx + 84 * j) - 1] <= ci) || (ci != ci));
    }

    k++;
    ix[k] = b_i;
    iy[k] = static_cast<signed char>(j + 2);
  }

  idx = div_s32_floor(-k, -1);
  cj_tmp = idx + 1;
  ix_size[0] = cj_tmp;
  iy_size[0] = cj_tmp;
  for (cj_tmp = 0; cj_tmp <= idx; cj_tmp++) {
    i = k - cj_tmp;
    ix_data[cj_tmp] = ix[i];
    iy_data[cj_tmp] = iy[i];
  }

  *dist = C[7139];
}

static void r2br_r2dit_trig(const emxArray_real_T *x, int n1_unsigned, const
  emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T *y)
{
  int istart;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  int ihi;
  istart = x->size[0];
  if (istart >= n1_unsigned) {
    istart = n1_unsigned;
  }

  nRowsM2 = n1_unsigned - 2;
  nRowsD2 = n1_unsigned / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, iy);
  if (n1_unsigned > x->size[0]) {
    iy = y->size[0];
    y->size[0] = n1_unsigned;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < n1_unsigned; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= istart - 2; i++) {
    y->data[iy].re = x->data[ix];
    y->data[iy].im = 0.0;
    iy = n1_unsigned;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy].re = x->data[ix];
  y->data[iy].im = 0.0;
  if (n1_unsigned > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      twid_re = y->data[i].re;
      twid_im = y->data[i].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y->data[i].re = twid_re;
      y->data[i].im = twid_im;
    }
  }

  iy = 2;
  ix = 4;
  ju = ((nRowsD4 - 1) << 2) + 1;
  while (nRowsD4 > 0) {
    for (i = 0; i < ju; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - y->data[temp_re_tmp].re;
      y->data[temp_re_tmp].im = y->data[i].im - y->data[temp_re_tmp].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    istart = 1;
    for (nRowsM2 = nRowsD4; nRowsM2 < nRowsD2; nRowsM2 += nRowsD4) {
      twid_re = costab->data[nRowsM2];
      twid_im = sintab->data[nRowsM2];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    nRowsD4 /= 2;
    iy = ix;
    ix += ix;
    ju -= iy;
  }
}

static void r2br_r2dit_trig_impl(const emxArray_creal_T *x, int unsigned_nRows,
  const emxArray_real_T *costab, const emxArray_real_T *sintab, emxArray_creal_T
  *y)
{
  int istart;
  int nRowsM2;
  int nRowsD2;
  int nRowsD4;
  int iy;
  int ix;
  int ju;
  int i;
  boolean_T tst;
  double temp_re;
  double temp_im;
  double twid_re;
  double twid_im;
  int temp_re_tmp;
  int ihi;
  istart = x->size[0];
  if (istart >= unsigned_nRows) {
    istart = unsigned_nRows;
  }

  nRowsM2 = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  nRowsD4 = nRowsD2 / 2;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, iy);
  if (unsigned_nRows > x->size[0]) {
    iy = y->size[0];
    y->size[0] = unsigned_nRows;
    emxEnsureCapacity_creal_T(y, iy);
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y->data[iy].re = 0.0;
      y->data[iy].im = 0.0;
    }
  }

  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i <= istart - 2; i++) {
    y->data[iy] = x->data[ix];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y->data[iy] = x->data[ix];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      temp_re = y->data[i + 1].re;
      temp_im = y->data[i + 1].im;
      twid_re = y->data[i].re;
      twid_im = y->data[i].im;
      y->data[i + 1].re = y->data[i].re - y->data[i + 1].re;
      y->data[i + 1].im = y->data[i].im - y->data[i + 1].im;
      twid_re += temp_re;
      twid_im += temp_im;
      y->data[i].re = twid_re;
      y->data[i].im = twid_im;
    }
  }

  iy = 2;
  ix = 4;
  ju = ((nRowsD4 - 1) << 2) + 1;
  while (nRowsD4 > 0) {
    for (i = 0; i < ju; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y->data[temp_re_tmp].re;
      temp_im = y->data[temp_re_tmp].im;
      y->data[temp_re_tmp].re = y->data[i].re - y->data[temp_re_tmp].re;
      y->data[temp_re_tmp].im = y->data[i].im - y->data[temp_re_tmp].im;
      y->data[i].re += temp_re;
      y->data[i].im += temp_im;
    }

    istart = 1;
    for (nRowsM2 = nRowsD4; nRowsM2 < nRowsD2; nRowsM2 += nRowsD4) {
      twid_re = costab->data[nRowsM2];
      twid_im = sintab->data[nRowsM2];
      i = istart;
      ihi = istart + ju;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y->data[temp_re_tmp].re - twid_im * y->
          data[temp_re_tmp].im;
        temp_im = twid_re * y->data[temp_re_tmp].im + twid_im * y->
          data[temp_re_tmp].re;
        y->data[temp_re_tmp].re = y->data[i].re - temp_re;
        y->data[temp_re_tmp].im = y->data[i].im - temp_im;
        y->data[i].re += temp_re;
        y->data[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    nRowsD4 /= 2;
    iy = ix;
    ix += ix;
    ju -= iy;
  }
}

static void removeSmallPeaks(const double y[264000], const emxArray_int32_T
  *iFinite, double minH, emxArray_int32_T *iPk)
{
  int n;
  int nPk;
  int k;
  double d;
  double b_y;
  n = iPk->size[0];
  iPk->size[0] = iFinite->size[0];
  emxEnsureCapacity_int32_T(iPk, n);
  nPk = 0;
  n = iFinite->size[0];
  for (k = 0; k < n; k++) {
    d = y[iFinite->data[k] - 1];
    if (d > minH) {
      if ((y[iFinite->data[k] - 2] > y[iFinite->data[k]]) || rtIsNaN(y
           [iFinite->data[k]])) {
        b_y = y[iFinite->data[k] - 2];
      } else {
        b_y = y[iFinite->data[k]];
      }

      if (d - b_y >= 0.0) {
        nPk++;
        iPk->data[nPk - 1] = iFinite->data[k];
      }
    }
  }

  n = iPk->size[0];
  if (1 > nPk) {
    iPk->size[0] = 0;
  } else {
    iPk->size[0] = nPk;
  }

  emxEnsureCapacity_int32_T(iPk, n);
}

static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0);
  } else if (a > y) {
    y /= a;
    y = a * std::sqrt(y * y + 1.0);
  } else {
    if (!rtIsNaN(y)) {
      y = a * 1.4142135623730951;
    }
  }

  return y;
}

static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

static double rt_roundd_snf(double u)
{
  double y;
  if (std::abs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = std::floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = std::ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

static void sort(emxArray_int32_T *x)
{
  int dim;
  emxArray_int32_T *vwork;
  int j;
  int vlen;
  int vstride;
  int k;
  emxArray_int32_T *b_vwork;
  dim = 0;
  if (x->size[0] != 1) {
    dim = -1;
  }

  emxInit_int32_T(&vwork, 1);
  if (dim + 2 <= 1) {
    j = x->size[0];
  } else {
    j = 1;
  }

  vlen = j - 1;
  vstride = vwork->size[0];
  vwork->size[0] = j;
  emxEnsureCapacity_int32_T(vwork, vstride);
  vstride = 1;
  for (k = 0; k <= dim; k++) {
    vstride *= x->size[0];
  }

  emxInit_int32_T(&b_vwork, 1);
  for (j = 0; j < vstride; j++) {
    for (k = 0; k <= vlen; k++) {
      vwork->data[k] = x->data[j + k * vstride];
    }

    b_sortIdx(vwork, b_vwork);
    for (k = 0; k <= vlen; k++) {
      x->data[j + k * vstride] = vwork->data[k];
    }
  }

  emxFree_int32_T(&b_vwork);
  emxFree_int32_T(&vwork);
}

static void sortIdx(const emxArray_real_T *x, emxArray_int32_T *idx)
{
  int n;
  int i;
  int loop_ub;
  emxArray_int32_T *iwork;
  double d;
  int b_i;
  int i2;
  int j;
  int pEnd;
  int p;
  int q;
  int qEnd;
  int kEnd;
  n = x->size[0] + 1;
  i = idx->size[0];
  idx->size[0] = x->size[0];
  emxEnsureCapacity_int32_T(idx, i);
  loop_ub = x->size[0];
  for (i = 0; i < loop_ub; i++) {
    idx->data[i] = 0;
  }

  emxInit_int32_T(&iwork, 1);
  i = iwork->size[0];
  iwork->size[0] = x->size[0];
  emxEnsureCapacity_int32_T(iwork, i);
  i = x->size[0] - 1;
  for (loop_ub = 1; loop_ub <= i; loop_ub += 2) {
    d = x->data[loop_ub - 1];
    if ((d >= x->data[loop_ub]) || rtIsNaN(d)) {
      idx->data[loop_ub - 1] = loop_ub;
      idx->data[loop_ub] = loop_ub + 1;
    } else {
      idx->data[loop_ub - 1] = loop_ub + 1;
      idx->data[loop_ub] = loop_ub;
    }
  }

  if ((x->size[0] & 1) != 0) {
    idx->data[x->size[0] - 1] = x->size[0];
  }

  b_i = 2;
  while (b_i < n - 1) {
    i2 = b_i << 1;
    j = 1;
    for (pEnd = b_i + 1; pEnd < n; pEnd = qEnd + b_i) {
      p = j - 1;
      q = pEnd;
      qEnd = j + i2;
      if (qEnd > n) {
        qEnd = n;
      }

      loop_ub = 0;
      kEnd = qEnd - j;
      while (loop_ub + 1 <= kEnd) {
        d = x->data[idx->data[p] - 1];
        i = idx->data[q - 1];
        if ((d >= x->data[i - 1]) || rtIsNaN(d)) {
          iwork->data[loop_ub] = idx->data[p];
          p++;
          if (p + 1 == pEnd) {
            while (q < qEnd) {
              loop_ub++;
              iwork->data[loop_ub] = idx->data[q - 1];
              q++;
            }
          }
        } else {
          iwork->data[loop_ub] = i;
          q++;
          if (q == qEnd) {
            while (p + 1 < pEnd) {
              loop_ub++;
              iwork->data[loop_ub] = idx->data[p];
              p++;
            }
          }
        }

        loop_ub++;
      }

      for (loop_ub = 0; loop_ub < kEnd; loop_ub++) {
        idx->data[(j + loop_ub) - 1] = iwork->data[loop_ub];
      }

      j = qEnd;
    }

    b_i = i2;
  }

  emxFree_int32_T(&iwork);
}

static void xcorr(const emxArray_real_T *x, const emxArray_real_T *varargin_1,
                  emxArray_real_T *c)
{
  emxArray_real_T *c1;
  int maxval;
  int i;
  emxInit_real_T(&c1, 1);
  if (x->size[0] > varargin_1->size[0]) {
    maxval = x->size[0] - 1;
  } else {
    maxval = varargin_1->size[0] - 1;
  }

  crosscorr(x, varargin_1, static_cast<double>(maxval + 1) - 1.0, c1);
  i = c->size[0];
  c->size[0] = (maxval << 1) + 1;
  emxEnsureCapacity_real_T(c, i);
  maxval <<= 1;
  for (i = 0; i <= maxval; i++) {
    c->data[i] = 0.0;
  }

  maxval = c1->size[0];
  for (i = 0; i < maxval; i++) {
    c->data[i] = c1->data[i];
  }

  emxFree_real_T(&c1);
}

void aware_initialize()
{
  rt_InitInfAndNaN();
  omp_init_nest_lock(&emlrtNestLockGlobal);
  isInitialized_aware = true;
}

void aware_terminate()
{
  omp_destroy_nest_lock(&emlrtNestLockGlobal);
  isInitialized_aware = false;
}

void get_noise(const double cali_raw[264000], const double test_raw[2160000],
               double noise[2160000])
{
  emxArray_real_T *unusedU0;
  emxArray_real_T *locs;
  int i;
  int k;
  emxArray_real_T *b_cali_raw;
  int idx;
  emxArray_real_T *c_cali_raw;
  boolean_T b;
  boolean_T exitg1;
  double ndbl;
  emxArray_real_T *b_locs;
  emxArray_real_T *unusedU1;
  double apnd;
  emxArray_real_T *x;
  int b_i;
  double cdiff;
  double u0;
  double u1;
  int x_tmp;
  int n;
  if (isInitialized_aware == false) {
    aware_initialize();
  }

  emxInit_real_T(&unusedU0, 1);
  emxInit_real_T(&locs, 1);
  findpeaks(cali_raw, unusedU0, locs);
  emxFree_real_T(&unusedU0);
  if ((locs->data[0] - 5280.0) + 1.0 > locs->data[0] + 9120.0) {
    i = 0;
    k = 0;
  } else {
    i = static_cast<int>((locs->data[0] - 5280.0) + 1.0) - 1;
    k = static_cast<int>(locs->data[0] + 9120.0);
  }

  emxFree_real_T(&locs);
  emxInit_real_T(&b_cali_raw, 1);
  idx = k - i;
  k = b_cali_raw->size[0];
  b_cali_raw->size[0] = idx;
  emxEnsureCapacity_real_T(b_cali_raw, k);
  for (k = 0; k < idx; k++) {
    b_cali_raw->data[k] = cali_raw[i + k];
  }

  emxInit_real_T(&c_cali_raw, 2);
  align_ave(cali_raw, b_cali_raw, c_cali_raw);

  /*  xc = xcorr(test,cali); */
  /*  xc = xc(length(test):end); */
  b = rtIsNaN(test_raw[0]);
  emxFree_real_T(&c_cali_raw);
  emxFree_real_T(&b_cali_raw);
  if (!b) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= 2160000)) {
      if (!rtIsNaN(test_raw[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    ndbl = test_raw[0];
  } else {
    ndbl = test_raw[idx - 1];
    i = idx + 1;
    for (k = i; k < 2160001; k++) {
      apnd = test_raw[k - 1];
      if (ndbl < apnd) {
        ndbl = apnd;
      }
    }
  }

  emxInit_real_T(&b_locs, 1);
  emxInit_real_T(&unusedU1, 1);
  c_findpeaks(test_raw, ndbl * 0.5, unusedU1, b_locs);
  if (b_locs->size[0] < 200) {
    if (!b) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= 2160000)) {
        if (!rtIsNaN(test_raw[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ndbl = test_raw[0];
    } else {
      ndbl = test_raw[idx - 1];
      i = idx + 1;
      for (k = i; k < 2160001; k++) {
        apnd = test_raw[k - 1];
        if (ndbl < apnd) {
          ndbl = apnd;
        }
      }
    }

    c_findpeaks(test_raw, ndbl * 0.4, unusedU1, b_locs);
  }

  if (b_locs->size[0] < 200) {
    if (!b) {
      idx = 1;
    } else {
      idx = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= 2160000)) {
        if (!rtIsNaN(test_raw[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }

    if (idx == 0) {
      ndbl = test_raw[0];
    } else {
      ndbl = test_raw[idx - 1];
      i = idx + 1;
      for (k = i; k < 2160001; k++) {
        apnd = test_raw[k - 1];
        if (ndbl < apnd) {
          ndbl = apnd;
        }
      }
    }

    c_findpeaks(test_raw, ndbl * 0.3, unusedU1, b_locs);
  }

  emxFree_real_T(&unusedU1);
  std::memset(&noise[0], 0, 2160000U * sizeof(double));
  i = b_locs->size[0];
  emxInit_real_T(&x, 2);
  for (b_i = 0; b_i < i; b_i++) {
    if (rtIsNaN((b_locs->data[b_i] + 1.0) - 5280.0) || rtIsNaN(b_locs->data[b_i]
         - 480.0)) {
      k = x->size[0] * x->size[1];
      x->size[0] = 1;
      x->size[1] = 1;
      emxEnsureCapacity_real_T(x, k);
      x->data[0] = rtNaN;
    } else if (b_locs->data[b_i] - 480.0 < (b_locs->data[b_i] + 1.0) - 5280.0) {
      x->size[0] = 1;
      x->size[1] = 0;
    } else if ((rtIsInf((b_locs->data[b_i] + 1.0) - 5280.0) || rtIsInf
                (b_locs->data[b_i] - 480.0)) && ((b_locs->data[b_i] + 1.0) -
                5280.0 == b_locs->data[b_i] - 480.0)) {
      k = x->size[0] * x->size[1];
      x->size[0] = 1;
      x->size[1] = 1;
      emxEnsureCapacity_real_T(x, k);
      x->data[0] = rtNaN;
    } else if (std::floor((b_locs->data[b_i] + 1.0) - 5280.0) == (b_locs->
                data[b_i] + 1.0) - 5280.0) {
      k = x->size[0] * x->size[1];
      x->size[0] = 1;
      idx = static_cast<int>(std::floor((b_locs->data[b_i] - 480.0) -
        ((b_locs->data[b_i] + 1.0) - 5280.0)));
      x->size[1] = idx + 1;
      emxEnsureCapacity_real_T(x, k);
      for (k = 0; k <= idx; k++) {
        x->data[k] = ((b_locs->data[b_i] + 1.0) - 5280.0) + static_cast<double>
          (k);
      }
    } else {
      ndbl = std::floor(((b_locs->data[b_i] - 480.0) - ((b_locs->data[b_i] + 1.0)
        - 5280.0)) + 0.5);
      apnd = ((b_locs->data[b_i] + 1.0) - 5280.0) + ndbl;
      cdiff = apnd - (b_locs->data[b_i] - 480.0);
      u0 = std::abs((b_locs->data[b_i] + 1.0) - 5280.0);
      u1 = std::abs(b_locs->data[b_i] - 480.0);
      if ((u0 > u1) || rtIsNaN(u1)) {
        u1 = u0;
      }

      if (std::abs(cdiff) < 4.4408920985006262E-16 * u1) {
        ndbl++;
        apnd = b_locs->data[b_i] - 480.0;
      } else if (cdiff > 0.0) {
        apnd = ((b_locs->data[b_i] + 1.0) - 5280.0) + (ndbl - 1.0);
      } else {
        ndbl++;
      }

      if (ndbl >= 0.0) {
        n = static_cast<int>(ndbl);
      } else {
        n = 0;
      }

      k = x->size[0] * x->size[1];
      x->size[0] = 1;
      x->size[1] = n;
      emxEnsureCapacity_real_T(x, k);
      if (n > 0) {
        x->data[0] = (b_locs->data[b_i] + 1.0) - 5280.0;
        if (n > 1) {
          x->data[n - 1] = apnd;
          idx = (n - 1) / 2;
          for (k = 0; k <= idx - 2; k++) {
            x_tmp = k + 1;
            x->data[k + 1] = ((b_locs->data[b_i] + 1.0) - 5280.0) + static_cast<
              double>(x_tmp);
            x->data[(n - k) - 2] = apnd - static_cast<double>(x_tmp);
          }

          if (idx << 1 == n - 1) {
            x->data[idx] = (((b_locs->data[b_i] + 1.0) - 5280.0) + apnd) / 2.0;
          } else {
            x->data[idx] = ((b_locs->data[b_i] + 1.0) - 5280.0) + static_cast<
              double>(idx);
            x->data[idx + 1] = apnd - static_cast<double>(idx);
          }
        }
      }
    }

    idx = x->size[0] * x->size[1];
    for (k = 0; k < idx; k++) {
      x_tmp = static_cast<int>(x->data[k]) - 1;
      noise[x_tmp] = test_raw[x_tmp];
    }
  }

  emxFree_real_T(&x);
  emxFree_real_T(&b_locs);
}

void single_calc(const double cali1_raw[264000], const double cali2_raw[264000],
                 const double cali3_raw[264000], const double test_raw[273600],
                 double b_gamma, double ls, double fc, emxArray_real_T *A,
                 emxArray_real_T *ho, double *score)
{
  emxArray_real_T *unusedU0;
  emxArray_real_T *locs;
  int i;
  int i1;
  emxArray_real_T *b_cali1_raw;
  int loop_ub;
  emxArray_real_T *cali1;
  emxArray_real_T *cali2;
  emxArray_real_T *cali3;
  emxArray_real_T *test;
  emxArray_real_T *b_ho;
  if (isInitialized_aware == false) {
    aware_initialize();
  }

  emxInit_real_T(&unusedU0, 1);
  emxInit_real_T(&locs, 1);

  /* SINGLE_CALC2 Summary of this function goes here */
  /*    Detailed explanation goes here */
  d_findpeaks(cali1_raw, unusedU0, locs);
  emxFree_real_T(&unusedU0);
  if ((locs->data[0] - 5280.0) + 1.0 > locs->data[0] + 9120.0) {
    i = 0;
    i1 = 0;
  } else {
    i = static_cast<int>((locs->data[0] - 5280.0) + 1.0) - 1;
    i1 = static_cast<int>(locs->data[0] + 9120.0);
  }

  emxFree_real_T(&locs);
  emxInit_real_T(&b_cali1_raw, 1);
  loop_ub = i1 - i;
  i1 = b_cali1_raw->size[0];
  b_cali1_raw->size[0] = loop_ub;
  emxEnsureCapacity_real_T(b_cali1_raw, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_cali1_raw->data[i1] = cali1_raw[i + i1];
  }

  emxInit_real_T(&cali1, 2);
  align_ave(cali1_raw, b_cali1_raw, cali1);
  i1 = b_cali1_raw->size[0];
  b_cali1_raw->size[0] = loop_ub;
  emxEnsureCapacity_real_T(b_cali1_raw, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_cali1_raw->data[i1] = cali1_raw[i + i1];
  }

  emxInit_real_T(&cali2, 2);
  align_ave(cali2_raw, b_cali1_raw, cali2);
  i1 = b_cali1_raw->size[0];
  b_cali1_raw->size[0] = loop_ub;
  emxEnsureCapacity_real_T(b_cali1_raw, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_cali1_raw->data[i1] = cali1_raw[i + i1];
  }

  emxInit_real_T(&cali3, 2);
  align_ave(cali3_raw, b_cali1_raw, cali3);
  i1 = b_cali1_raw->size[0];
  b_cali1_raw->size[0] = loop_ub;
  emxEnsureCapacity_real_T(b_cali1_raw, i1);
  for (i1 = 0; i1 < loop_ub; i1++) {
    b_cali1_raw->data[i1] = cali1_raw[i + i1];
  }

  emxInit_real_T(&test, 2);
  emxInit_real_T(&b_ho, 1);
  align_dense(test_raw, b_cali1_raw, test);

  /*  [cali1(:,1),~] = WienerNoiseReduction(cali1(:,1),fs,5000); */
  /*  [cali2(:,1),~] = WienerNoiseReduction(cali2(:,1),fs,5000); */
  /*  [cali3(:,1),~] = WienerNoiseReduction(cali3(:,1),fs,5000); */
  /*  for i = 1:size(test,2) */
  /*      [test(:,i),~] = WienerNoiseReduction(test(:,i),fs,5000); */
  /*  end */
  mean(test, b_cali1_raw);
  compute(cali1, cali2, cali3, b_cali1_raw, b_gamma, ls, fc, A, b_ho, score);
  i = ho->size[0];
  ho->size[0] = b_ho->size[0];
  emxEnsureCapacity_real_T(ho, i);
  loop_ub = b_ho->size[0];
  emxFree_real_T(&b_cali1_raw);
  emxFree_real_T(&test);
  emxFree_real_T(&cali3);
  emxFree_real_T(&cali2);
  emxFree_real_T(&cali1);
  for (i = 0; i < loop_ub; i++) {
    ho->data[i] = b_ho->data[i];
  }

  emxFree_real_T(&b_ho);
}

/* End of code generation (aware.cpp) */
