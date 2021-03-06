#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int clacrm_(integer *m, integer *n, complex *a, integer *lda,
	 real *b, integer *ldb, complex *c__, integer *ldc, real *rwork)
{
/*  -- LAPACK auxiliary routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    CLACRM performs a very simple matrix-matrix multiplication:   
             C := A * B,   
    where A is M by N and complex; B is N by N and real;   
    C is M by N and complex.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A and of the matrix C.   
            M >= 0.   

    N       (input) INTEGER   
            The number of columns and rows of the matrix B and   
            the number of columns of the matrix C.   
            N >= 0.   

    A       (input) COMPLEX array, dimension (LDA, N)   
            A contains the M by N matrix A.   

    LDA     (input) INTEGER   
            The leading dimension of the array A. LDA >=max(1,M).   

    B       (input) REAL array, dimension (LDB, N)   
            B contains the N by N matrix B.   

    LDB     (input) INTEGER   
            The leading dimension of the array B. LDB >=max(1,N).   

    C       (input) COMPLEX array, dimension (LDC, N)   
            C contains the M by N matrix C.   

    LDC     (input) INTEGER   
            The leading dimension of the array C. LDC >=max(1,N).   

    RWORK   (workspace) REAL array, dimension (2*M*N)   

    =====================================================================   


       Quick return if possible.   

       Parameter adjustments */
    /* Table of constant values */
    static real c_b6 = 1.f;
    static real c_b7 = 0.f;
    
    /* System generated locals */
    integer b_dim1, b_offset, a_dim1, a_offset, c_dim1, c_offset, i__1, i__2, 
	    i__3, i__4, i__5;
    real r__1;
    complex q__1;
    /* Builtin functions */
    double r_imag(complex *);
    /* Local variables */
    static integer i__, j, l;
    extern /* Subroutine */ int sgemm_(char *, char *, integer *, integer *, 
	    integer *, real *, real *, integer *, real *, integer *, real *, 
	    real *, integer *);
#define a_subscr(a_1,a_2) (a_2)*a_dim1 + a_1
#define a_ref(a_1,a_2) a[a_subscr(a_1,a_2)]
#define c___subscr(a_1,a_2) (a_2)*c_dim1 + a_1
#define c___ref(a_1,a_2) c__[c___subscr(a_1,a_2)]


    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1 * 1;
    c__ -= c_offset;
    --rwork;

    /* Function Body */
    if (*m == 0 || *n == 0) {
	return 0;
    }

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = a_subscr(i__, j);
	    rwork[(j - 1) * *m + i__] = a[i__3].r;
/* L10: */
	}
/* L20: */
    }

    l = *m * *n + 1;
    sgemm_("N", "N", m, n, n, &c_b6, &rwork[1], m, &b[b_offset], ldb, &c_b7, &
	    rwork[l], m);
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = c___subscr(i__, j);
	    i__4 = l + (j - 1) * *m + i__ - 1;
	    c__[i__3].r = rwork[i__4], c__[i__3].i = 0.f;
/* L30: */
	}
/* L40: */
    }

    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    rwork[(j - 1) * *m + i__] = r_imag(&a_ref(i__, j));
/* L50: */
	}
/* L60: */
    }
    sgemm_("N", "N", m, n, n, &c_b6, &rwork[1], m, &b[b_offset], ldb, &c_b7, &
	    rwork[l], m);
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = c___subscr(i__, j);
	    i__4 = c___subscr(i__, j);
	    r__1 = c__[i__4].r;
	    i__5 = l + (j - 1) * *m + i__ - 1;
	    q__1.r = r__1, q__1.i = rwork[i__5];
	    c__[i__3].r = q__1.r, c__[i__3].i = q__1.i;
/* L70: */
	}
/* L80: */
    }

    return 0;

/*     End of CLACRM */

} /* clacrm_ */

#undef c___ref
#undef c___subscr
#undef a_ref
#undef a_subscr


