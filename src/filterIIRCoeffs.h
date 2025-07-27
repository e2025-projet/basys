// IIRCoeffs : coefficients SOS (b0 b1 b2 a0 a1 a2)
#define IIR_QXY_RES_NBITS 13 // Q2.13
#define N_SOS_SECTIONS 2

int32_t IIRCoeffs[N_SOS_SECTIONS][6] = {
  {3, -3, 3, 8192, -15605, 7456},
  {8192, -14614, 8192, 8192, -15941, 7899},
};

int32_t IIRu_left[N_SOS_SECTIONS] = {0}, IIRv_left[N_SOS_SECTIONS] = {0};

int32_t IIRu_right[N_SOS_SECTIONS] = {0}, IIRv_right[N_SOS_SECTIONS] = {0};