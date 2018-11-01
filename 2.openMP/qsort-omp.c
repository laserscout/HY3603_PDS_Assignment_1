/**********************************************************************
 *
 * qsort-omp.c -- Parallel openMP implementation of QuickSort
 *
 * Nikos Pitsianis <nikos.pitsianis@eng.auth.gr>
 * Dimitris Floros <fcdimitr@auth.gr>
 * Frank Blanning <frankgou@ece.auth.gr>
 * AEM: 6698
 * Time-stamp: <2018-10-28>
 *
 **********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "qsort-sequential.h"
#include <omp.h>

void qsort_omp (int *v, int n);

/* qsort -- Entry point for QuickSort */
void qsortp(int *v, int n, int t) {

  omp_set_num_threads(1<<t);
  
#pragma omp parallel
#pragma omp single nowait
    qsort_omp(v,n);
}

void qsort_omp(int *v, int n) {
  
  if (n > 1) {
    int p = partition(v, n);
    qsort_omp(v,p);

    if ( n < 1000 ) {
      qsort_omp(&v[p+1],n-p-1);
    }
    else {
#pragma omp task
      qsort_omp(&v[p+1],n-p-1);
    }
  }
}

