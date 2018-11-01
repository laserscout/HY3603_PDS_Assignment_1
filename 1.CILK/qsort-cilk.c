/**********************************************************************
 *
 * qsort-cilk.c -- Parallel CILK implementation of QuickSort
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
#include <cilk/cilk_api.h>
#include <cilk/cilk.h>

void qsort_cilk (int *v, int n);

/* qsortp -- Entry point for parallel  QuickSort */
void qsortp(int *v, int n, int p) {

  char t[4];
  sprintf(t,"%d",(1<<p));
  int err = __cilkrts_set_param("nworkers", t);
  if (err != 0) {
    printf("Failed to set worker count\nError code:%d\n",err);
    exit (1);
  }
  qsort_cilk(v,n);
}

/* Recurring qsort call */
void qsort_cilk (int *v, int n) {
  
  if (n > 1) {
    int p = partition(v, n);
    cilk_spawn qsort_cilk(v,p);
    qsort_cilk(&v[p+1],n-p-1);

nc;
  }
}
