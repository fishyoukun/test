#include <stdio.h>
#include "myfft.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

int signalgen(TYPE_FFT *p,int length);
int GetLeastPower2(int inumber);
#define datalen 8192
#define DEBUG_PRN
int main (int argc, char *argv[])
{
    int N = datalen;
    int fftN = 0;
    int iloop ;
    TYPE_FFT *p = NULL;
    TYPE_FFT y1 [datalen] ;
    TYPE_FFT y2 [datalen] ;
    TYPE_FFT y3 [datalen] ;

    memset(y1,0,sizeof(y1));
    signalgen(y1,N);
    
    #ifdef DEBUG_PRN
    printf("origin data real imag\n");
    for (iloop = 0;iloop < N;iloop++ )
    {
      
        y2[iloop].real = y1[iloop].real;
        y2[iloop].imag = y1[iloop].imag;
    }
    #endif
    fftN = GetLeastPower2(N);
    p = (TYPE_FFT *)malloc(sizeof(TYPE_FFT) * fftN);
    memset(p,0,sizeof(TYPE_FFT)*fftN);
    for (iloop = 0;iloop < N;iloop++ )
    {
      
        (*p).real = y1[ iloop].real;
        (*p).imag = y1[iloop].imag;
        p = p ++;
        
    }
    printf("N = %d,fftN=%d\n",N,fftN);
    fft(p,N);
    #ifdef DEBUG_PRN
    printf("fft data real imag \n");
    for (iloop = 0;iloop < N;iloop++ )
    {  
        printf("%f\n",y1[iloop].real);
        printf("%f\n",y1[iloop].imag);
    }
    #endif
    ifft(p,fftN);
     #ifdef DEBUG_PRN
    printf("ifft data real imag \n");
    for (iloop = 0;iloop < N;iloop++ )
    {   
          printf("%f\n",y1[iloop].real);
          printf("%f\n",y1[iloop].imag);
    }
    printf("diff of origin data and ifft data: real imag\n");
    for (iloop = 0;iloop < N;iloop++ )
    {
        y3[ iloop].real = y2[iloop].real - y1[iloop].real;
        y3[iloop].imag = y2[iloop].imag - y1[iloop].imag;
        printf("%f %f\n",y3[iloop].real,y3[iloop].imag);
    } 
    #endif
    return(0);
}

int signalgen(TYPE_FFT *p,int length)
{
        int n;/*time slice*/
        int N;/*totol N*/
        N = length;
        float fs = 500.0;/*sample rate*/
        float f1= 100.0;/*freq of signal_1 */
        float f2 = 200.0;/*freq of signal_2*/
        float A1 = 3.0;/*amp of signal_1 */
        float A2= 5.0;/*amp of signal_2 */
        TYPE_FFT *s1;
        s1=(TYPE_FFT *)malloc(length*sizeof(TYPE_FFT));
        if (s1 == NULL)
        {
            printf("malloc s1 error!\n");
            return -1;
        }
        TYPE_FFT *s2;
        if (s2 == NULL)
        {
            printf(" malloc s2 error!\n");
            return -2;
        }
        for (n = 0; n < length; n++) 
        {
            (*(s1+n)) .real=A1*cos(2.0*PI*f1/fs*(float)n) ;
            (*(s1+n) ).imag=0.0;
        }
        for (n = 0; n < length; n++) 
        {
            (*(s2+n)).real =A2*sin(2.0*PI*f2/fs*(float)n) ;
            ( *(s2+n)).imag = 0.0;
        }
        
        
        for (n = 0; n < length; n++) 
        {
            (*(p+n)).real =( *(s1+n)).real  + (*(s2+n)).real;
            (*(p+n)).imag =( *(s1+n)).imag  + (*(s2+n)).imag;
        }
        return 0;

}
/*
 * zx_fft.c
 *
 * Implementation of Fast Fourier Transform(FFT)
 * and reversal Fast Fourier Transform(IFFT)
 * 
 *  Created on: 2013-8-5
 *      Author: monkeyzx
 *
 * TEST OK 2014.01.14
 * == 2014.01.14
 *   Replace @BitReverse(x,x,N,M) by refrence to 
 *   <The Scientist and Engineer's Guide to Digital Signal Processing>
 */





/*
 * FFT Algorithm
 * === Inputs ===
 * x : complex numbers
 * N : nodes of FFT. @N should be power of 2, that is 2^(*)
 * === Output ===
 * the @x contains the result of FFT algorithm, so the original data
 * in @x is destroyed, please store them before using FFT.
 */
int fft(TYPE_FFT *x, int N)
{
	int i,j,l,k,ip;
	static int M = 0;
	static int le,le2;
	static TYPE_FFT_E sR,sI,tR,tI,uR,uI;

	M = (int)(log(N) / log(2));

	/*
	 * bit reversal sorting
	 */
	l = N / 2;
	j = l;
	//BitReverse(x,x,N,M);
    for (i=1; i<=N-2; i++) {
        if (i < j) {
            tR = x[j].real;
			tI = x[j].imag;
            x[j].real = x[i].real;
			x[j].imag = x[i].imag;
            x[i].real = tR;
			x[i].imag = tI;
		}
		k = l;
		while ((k <= j) && (k!=0)) {
            j = j - k;
			k = k / 2;
		}
		j = j + k;
	}

	/*
	 * For Loops
	 */
	for (l=1; l<=M; l++) {   /* loop for ceil{log2(N)} */
		le = (int)pow(2,l);
		le2 = (int)(le / 2);
		uR = 1;
		uI = 0;
		sR = cos(PI / le2);
		sI = -sin(PI / le2);
		for (j=1; j<=le2; j++) {   /* loop for each sub DFT */
			//jm1 = j - 1;
			for (i=j-1; i<=N-1; i+=le) {  /* loop for each butterfly */
				ip = i + le2;
				tR = x[ip].real * uR - x[ip].imag * uI;
				tI = x[ip].real * uI + x[ip].imag * uR;
				x[ip].real = x[i].real - tR;
				x[ip].imag = x[i].imag - tI;
				x[i].real += tR;
				x[i].imag += tI;
			}  /* Next i */
			tR = uR;
			uR = tR * sR - uI * sI;
			uI = tR * sI + uI *sR;
		} /* Next j */
	} /* Next l */

	return 0;
}

/*
 * Inverse FFT Algorithm
 * === Inputs ===
 * x : complex numbers
 * N : nodes of FFT. @N should be power of 2, that is 2^(*)
 * === Output ===
 * the @x contains the result of FFT algorithm, so the original data
 * in @x is destroyed, please store them before using FFT.
 */
int ifft(TYPE_FFT *x, int N)
{
	int k = 0;

	for (k=0; k<=N-1; k++) {
		x[k].imag = -x[k].imag;
	}

	fft(x, N);    /* using FFT */

	for (k=0; k<=N-1; k++) {
		x[k].real = x[k].real / N;
		x[k].imag = -x[k].imag / N;
	}

	return 0;
}
unsigned int is2n(unsigned int un)
{
    return un&(un-1);
}
unsigned int max2n(unsigned int un)
{
    unsigned int mi = is2n(un);
    return mi?max2n(mi):un;
}
int GetLeastPower2(int inumber)
{
   
    int iLeastPower2Number = 0; 
    if (inumber == 0)
    {   
        return iLeastPower2Number;

    }
   
    if ((inumber & (inumber - 1)) == 0)
    {
        iLeastPower2Number = inumber;
    }
    else
    {
        iLeastPower2Number = max2n(inumber)*2;
    }
    return iLeastPower2Number;
}

