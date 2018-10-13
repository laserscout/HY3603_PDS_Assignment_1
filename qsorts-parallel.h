/**********************************************************************
 *
 * qsorts-parallel.h -- Parallel implementations of QuickSort
 *
 * Frank Blanning <frankgou@ece.auth.gr>
 * Time-stamp: <2018-10-13>
 *
 **********************************************************************/


#ifndef _QSORTS_PARALLEL_H_
#define _QSORTS_PARALLEL_H_

void qsort_cilk(int *v, int n);
void qsort_openmp(int *v, int n);
void qsort_pthreads(int *v, int n);

#endif /* _QSORTS_PARALLEL_H_ */



