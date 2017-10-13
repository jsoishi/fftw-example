/* Start reading here */

#include <fftw3.h>
#include <stdlib.h>
#define NUM_POINTS 10000000


/* Never mind this bit */

#include <stdio.h>
#include <math.h>

#define REAL 0
#define IMAG 1

void acquire_from_somewhere(fftw_complex* signal, int size) {
    /* Generate two sine waves of different frequencies and
     * amplitudes.
     */

    int i;
    for (i = 0; i < size; ++i) {
        double theta = (double)i / (double)size * M_PI;
        signal[i][REAL] = 1.0 * cos(10.0 * theta) +
                          0.5 * cos(25.0 * theta);

        signal[i][IMAG] = 1.0 * sin(10.0 * theta) +
                          0.5 * sin(25.0 * theta);
    }
}

void do_something_with(fftw_complex* result, int size) {
    int i;
    for (i = 0; i < size; ++i) {
        double mag = sqrt(result[i][REAL] * result[i][REAL] +
                          result[i][IMAG] * result[i][IMAG]);

        //printf("%g\n", mag);
    }
}


/* Resume reading here */

int main() {
  int size = NUM_POINTS;
  fftw_complex *signal = malloc(size * sizeof(fftw_complex));
  fftw_complex *result = malloc(size * sizeof(fftw_complex));

  
    
  fftw_plan plan = fftw_plan_dft_1d(size,
                                    signal,
                                    result,
                                    FFTW_FORWARD,
                                    FFTW_ESTIMATE);
  
  acquire_from_somewhere(signal, size);
  fftw_execute(plan);
  do_something_with(result, size);
  
  fftw_destroy_plan(plan);

    return 0;
}
