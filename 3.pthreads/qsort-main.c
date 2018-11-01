/**********************************************************************
 *
 * qsort-main.c -- Test wrapper for parallel QuickSort implementations
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Frank Blanning <frankgou@ece.auth.gr>
 * AEM: 6698
 * Time-stamp: <2018-10-28>
 *
 **********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#include "qsort-pth.h"

#define SEED 6698

/* local function declarations */
int  test( int *a, int n);
void init( int *a, int n);
void print(int *a, int n);

/* --- Entry POINT --- */
int main(int argc, char **argv) {

  /* parse input */
  if (argc != 3) {
    printf("Usage: %s q p\nwhere n=2^q is problem size\nand t=2^p the number of threads", 
	   argv[0]);
    exit(1);
  }

  int p = atoi(argv[2]);
  if (p>8 || p<1) {
    printf("The p parameter needs to be between 1 and 8\nt=2^p the number of threads");
    exit(1);
  }

  /* variables to hold execution time */
  struct timeval startwtime, endwtime;
  double seq_time;
 
  /* initiate vector of random integerts */
  int n  = 1<<atoi(argv[1]);
  int *a = (int *) malloc(n * sizeof(int));

  /* initialize vector */
  init(a, n);

  /* print vector */
  /* print(a, n); */
  
  /* sort elements in original order */
  gettimeofday (&startwtime, NULL);
  qsortp(a, n, p);
  gettimeofday (&endwtime, NULL);

  /* print sorted vector */
  print(a+n-10, 10);
  
  /* get time in seconds */
  seq_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6
                      + endwtime.tv_sec - startwtime.tv_sec);

  /* validate result */
  int pass = test(a, n);
  assert( pass != 0 );
  
  
  /* print execution time */
  printf("%f", seq_time);

  /* exit */
  return 0;
  
}

/** -------------- SUB-PROCEDURES  ----------------- **/ 

/** procedure test() : verify sort results **/
int test(int *a, int n) {

  int pass = 1;
  for (int i = 1; i < n; i++) {
    if (a[i-1]>a[i]) {
      printf("Failure at item %d\n", i);
      pass = 0;
      break;
    }
  }
  return pass;
  
}

/** procedure init() : initialize array "a" with data **/
void init(int *a, int n) {
  srand(SEED);
  int i;
  for (i = 0; i < n; i++) {
    a[i] = rand() % n; // (N - i);
  }
}

/** procedure  print() : print array elements **/
void print(int *a, int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}
