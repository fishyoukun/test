/*
 * zx_fft.h
 *
 *  Created on: 2013-8-5
 *      Author: monkeyzx
 */

#ifndef _ZX_FFT_H
#define _ZX_FFT_H



#define TYPE_FFT_E     float    /* Type is the same with COMPLEX member */     

#ifndef PI
#define PI             (3.14159265f)
#endif

typedef struct T_COMPLEX{
    float real;
    float imag;
}COMPLEX;
typedef int INT;
//#define COMPLEX T_COMPLEX
//typedef  T_COMPLEX COMPLEX ;
/*typedef struct {
    float real;
	float imag;
} COMPLEX;*/

typedef COMPLEX TYPE_FFT;  /* Define COMPLEX in Config.h */
//#define TYPE_FFT COMPLEX

extern int fft(TYPE_FFT *x, int N);
extern int ifft(TYPE_FFT *x, int N);


#endif /* ZX_FFT_H_ */
