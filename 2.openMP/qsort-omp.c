/**********************************************************************
 *
 * qsort-omp.c -- Parallel openMP implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Frank Blanning <frankgou@ece.auth.gr>
 * Time-stamp: <2018-10-26>
 *
 **********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int cpus;
int count;

/* swap -- swap elements k and l of vector v */
void swap_omp(int *v, int k, int l) {
  int temp = v[k];
  v[k] = v[l];
  v[l] = temp;
}


/* partition -- in-place update of elements */
int partition_omp(int *v, int n) {
  int pivot = v[n-1];
  int i = 0;

  for (int j = 0; j < n - 1; j++) {
    if (v[j] < pivot) {
      swap_omp(v,i++,j);
    }
  }
  swap_omp(v, i, n - 1);
  
  return (i);
}

void qsort_omp_p(int *v, int n) {
  
  if (n > 1000) {
      if ( n < 1 ) {
	int p = partition_omp(v, n);
	qsort_omp_p(v,p);
	qsort_omp_p(&v[p+1],n-p-1);
      }
      else {
	int p = partition_omp(v, n);
	qsort_omp_p(v,p);
#pragma omp task
	qsort_omp_p(&v[p+1],n-p-1);
      }
  }
}

/* qsort -- Entry point for QuickSort */
void qsort_omp(int *v, int n, int t) {

  omp_set_num_threads(t);
  count = 1;
#pragma omp parallel
  {
#pragma omp single nowait
  qsort_omp_p(v,n);
}
}
