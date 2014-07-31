#include <string.h>
#include <math.h>
#include "benchmark.h"
#include<stdio.h>
#include<stdlib.h>
#include <omp.h>
#include<nmmintrin.h>
#include <stdarg.h>
#include <malloc.h>
#define blocksize 61

#define show(varname) fprintf(stderr, "%s = %d\n", #varname, varname); fflush(stdout)   //a debug macro : show(x); would print===> x = value_)of_x

#define sentinel()  do { fprintf(stdout, "filename = %s  : line_number =  %d  : function =  %s()\n: " , __FILE__, \
				 __LINE__, __func__);  fflush(stdout); } while (0)     //a debug macro : sentinel(); would print ===> filename:linenum:fun

void my_perror(const char *fmt, ...){ //a error function: my_perror("error :%d",1); would print ====> error: 1, and exit the program.
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);
    exit(EXIT_FAILURE);
}
void transpose( int n , float *dst, float *src,int num_threads ) { /* transpose the n x n matrix src into dst, num_threads unexplained */
#pragma omp  parallel
    {
	for (int i = omp_get_thread_num(); i <= n/blocksize; i+=num_threads)
	    for (int j = 0; j <= n/blocksize ; j++){
		for(int in_i = i*blocksize; in_i < (i + 1)*blocksize; in_i++)
		    for(int in_j = j*blocksize; in_j < (j + 1)*blocksize; in_j++){
			if ((in_i+in_j*n)>= n*n || (in_j + in_i*n)>=n*n){
			    break;
			}else{
			    dst[in_j + in_i*n] = src[in_i + in_j*n];
			}
		    }
	    }
    }
}
void padding_mat(int old_size,int new_size,float*new,float* old){ /* padding the 'old' matrix with old_size into 'new' matrix with new_size */
    float* jnew,*jold;
#pragma omp  parallel  for  private(jnew,jold)
	for (int  j = 0; j< old_size ; j++)	
	    {
		jnew = new+j*new_size;
		jold = old+j*old_size;
		for (int i = 0; i< old_size ; i++)
		    jnew[i] = jold[i];
	    }
}
void assign(int old_size,int new_size,float* r,float* padding){ /* transfer the result contained in vector array 'padding' into vector array 'r' */
    float* pi,*ri;
#pragma omp  parallel for private(pi,ri)
	for (int  i = 0; i< old_size ; i++)	
	    {
		ri = r + i*old_size;
		pi = padding + i*new_size;
		for(int j = 0 ; j < old_size ; j++)
		    ri[j] = pi[j];
	    }
}

void determine_threads_num(int *num_threads,size_t n) /* given the size of the matrix n, determine the num_threads which used in OpenMp */
{						  
    if (n <= 128)
	{
	    *num_threads = 8;
	}
    else if (n <= 256)
	{
	    *num_threads = 16;
	}
    else 
	{
	    *num_threads = 16;
	}
}


void	my_memset(float* addr,int size){
/* #pragma omp parallel for     */
    __m128 tmp = _mm_setzero_ps();
    addr-=4;
    for (int i = 0;i<size;i+=8)
	{	
	    _mm_store_ps(addr+=4,tmp);
	    _mm_store_ps(addr+=4,tmp);
	}
}
#define PADDING 8
#define BLOCK 64
#define MEM_CHUNK(x) memalign(BLOCK,x*x*sizeof(float))
#define ALIGN(x) __attribute__ ((aligned (x)))
void eig	(float *v, float *A, float *u, size_t n, unsigned iters) {
	/* determine the threads num in openmp */
    int num_threads;
    determine_threads_num(&num_threads,n);
    /* num_threads = 1; */
    omp_set_num_threads(num_threads);  
	/* determine the padding size */
    int remain = n%PADDING;
    int n_m = (n + remain)%PADDING == 0 ? n + remain : n - remain + PADDING ; 
	/* padding */
    float *v_m,*u_m,*A_p,*A_tp;
    if (n_m == n) 		/* no need for padding */
	{
	    v_m = v;
	    u_m = u;
	    A_p = A;
	}
    else 			
	{
	    v_m = MEM_CHUNK(n_m);
	    u_m = MEM_CHUNK(n_m);
	    my_memset(u_m,n_m * n_m);
	    A_p = MEM_CHUNK(n_m);
	    my_memset(A_p,n_m * n_m);
	    padding_mat(n,n_m,u_m,u); 
	    padding_mat(n,n_m,A_p,A);
	}
    
	/* A_tp is the transpose of the padding matrix */
    A_tp = MEM_CHUNK(n_m);
    transpose(n_m,A_tp,A_p,num_threads);
	/* some local variable */
    int rb1,rb2,rb3;
    float norm,tmp_flt;

    __m128 tmp;
    float tmp_p[4] ALIGN(16);
    __m128 tmp2;
    float *v_m_temp,*u_m_temp,*A_tp_temp;
    
    for (size_t k = 0; k < iters; k += 1) {
	my_memset(v_m,n_m*n_m);
#pragma omp parallel for  private(rb1  ,  rb2  ,tmp  , rb3  ,   norm  ,  tmp_p , tmp2 , u_m_temp,v_m_temp,tmp_flt,A_tp_temp) /* use openmp in the main loop */
	for (size_t l = 0; l < n; l ++) {
		rb2 = n_m*l;
		norm = 0.0;
		for (size_t i = 0; i < n_m; i += 1) {
		    A_tp_temp = A_tp + i*n_m - 4;		    
		    tmp  = _mm_setzero_ps();
		    u_m_temp = u_m+rb2 - 4;
		    for (size_t j = 0; j < n_m; j += PADDING) {
			tmp =  _mm_add_ps (tmp,_mm_mul_ps (_mm_load_ps(u_m_temp+=4),_mm_load_ps(A_tp_temp+=4))); /* !!!!!!the Key Change!!!!!!!!! */
			tmp =  _mm_add_ps (tmp,_mm_mul_ps (_mm_load_ps(u_m_temp+=4),_mm_load_ps(A_tp_temp+=4))); 
		    }
		    _mm_store_ps(tmp_p, tmp);
		    tmp_flt = (tmp_p[0]+tmp_p[1]+tmp_p[2]+tmp_p[3]);
		    v_m[i+rb2] = tmp_flt;
		    norm += tmp_flt*tmp_flt;
		}
		norm = sqrt(norm);
		v_m_temp = v_m+rb2 - 4;
		u_m_temp = u_m+rb2 - 4;
		tmp2 = _mm_set_ps (norm,norm,norm,norm);
		for (size_t i = 0; i < n_m; i += PADDING) {
		    _mm_store_ps(u_m_temp+=4,_mm_div_ps ( _mm_load_ps(v_m_temp+=4) ,tmp2));
		    _mm_store_ps(u_m_temp+=4,_mm_div_ps ( _mm_load_ps(v_m_temp+=4) ,tmp2));
		}
	    }	
	
    }
    free(A_tp);
    if (n != n_m)
	{
	    free(A_p);
	    assign(n,n_m,v,v_m);
	    free(v_m);
	    free(u_m);
	}
}


    

