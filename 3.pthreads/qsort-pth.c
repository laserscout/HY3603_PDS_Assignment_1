/**********************************************************************
 *
 * qsort-pth.c -- Parallel pthreads implementation of QuickSort
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
#include <pthread.h>
#include <assert.h>
#include "qsort-sequential.h"

struct vnn {
  int *v;
  int n;
  int l;
  int hop;
};

pthread_t *tha;
struct vnn *args_pass;
int t_levels;

void * qsort_pth(void *arg);

/* qsort -- Entry point for QuickSort */
void qsortp(int *v, int n, int p) {

  t_levels = p;

  tha = (pthread_t *) malloc (sizeof(pthread_t) * ((1<<p)-1));
  if (tha == 0) {
    printf ("Could not allocate memory for the pthreads");
    exit(1);
  }

  args_pass = (struct vnn *) malloc (sizeof(struct vnn) * (1<<p));
  if (args_pass == 0) {
    printf ("Could not allocate memory for the arg structure");
    exit(1);
  }

  /* struct vnn args_pass; */

  (args_pass+p)->v = v;
  (args_pass+p)->n = n;
  (args_pass+p)->l = 1;
  (args_pass+p)->hop = (1<<(p-1))-1; // ( 2^(p) / 2 ) -1 | the median

  qsort_pth( (void *)(args_pass+p) );

  free (tha);
  free (args_pass);
}

void * qsort_pth(void *arg) {
  int *v = ((struct vnn *) arg)->v;
  int n  = ((struct vnn *) arg)->n;
  int l  = ((struct vnn *) arg)->l;
  int hop  = ((struct vnn *) arg)->hop;

  if (n > 1) {
    if (l > t_levels || n < 1000) {
      qsort_seq(v,n);
    }
    else {
      
      int p = partition(v,n);

      /* struct vnn arg_pass; */

      (args_pass+hop)->v = &v[p+1];
      (args_pass+hop)->n = n-p-1;
      (args_pass+hop)->l = l+1;
      (args_pass+hop)->hop = hop + (1<<(t_levels-l-1)); // right half median

      pthread_t * thr = (tha + hop);
      assert (pthread_create (thr, NULL, qsort_pth, (void *)(args_pass+hop)) == 0);

      ((struct vnn *) arg)->n = p;
      ((struct vnn *) arg)->l = l+1;
      ((struct vnn *) arg)->hop = hop - (1<<(t_levels-l-1)); // left half median
      qsort_pth(arg);

      void *value;
      assert(pthread_join(*thr, &value) == 0);
    }
  }
}
