#include "blaswrap.h"
#include "f2c.h"

/* Subroutine */ int cgbrfs_(char *trans, integer *n, integer *kl, integer *
	ku, integer *nrhs, complex *ab, integer *ldab, complex *afb, integer *
	ldafb, integer *ipiv, complex *b, integer *ldb, complex *x, integer *
	ldx, real *ferr, real *berr, complex *work, real *rwork, integer *
	info)
{
/*  -- LAPACK routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    CGBRFS improves the computed solution to a system of linear   
    equations when the coefficient matrix is banded, and provides   
    error bounds and backward error estimates for the solution.   

    Arguments   
    =========   

    TRANS   (input) CHARACTER*1   
            Specifies the form of the system of equations:   
            = 'N':  A * X = B     (No transpose)   
            = 'T':  A**T * X = B  (Transpose)   
            = 'C':  A**H * X = B  (Conjugate transpose)   

    N       (input) INTEGER   
            The order of the matrix A.  N >= 0.   

    KL      (input) INTEGER   
            The number of subdiagonals within the band of A.  KL >= 0.   

    KU      (input) INTEGER   
            The number of superdiagonals within the band of A.  KU >= 0.   

    NRHS    (input) INTEGER   
            The number of right hand sides, i.e., the number of columns   
            of the matrices B and X.  NRHS >= 0.   

    AB      (input) COMPLEX array, dimension (LDAB,N)   
            The original band matrix A, stored in rows 1 to KL+KU+1.   
            The j-th column of A is stored in the j-th column of the   
            array AB as follows:   
            AB(ku+1+i-j,j) = A(i,j) for max(1,j-ku)<=i<=min(n,j+kl).   

    LDAB    (input) INTEGER   
            The leading dimension of the array AB.  LDAB >= KL+KU+1.   

    AFB     (input) COMPLEX array, dimension (LDAFB,N)   
            Details of the LU factorization of the band matrix A, as   
            computed by CGBTRF.  U is stored as an upper triangular band   
            matrix with KL+KU superdiagonals in rows 1 to KL+KU+1, and   
            the multipliers used during the factorization are stored in   
            rows KL+KU+2 to 2*KL+KU+1.   

    LDAFB   (input) INTEGER   
            The leading dimension of the array AFB.  LDAFB >= 2*KL*KU+1.   

    IPIV    (input) INTEGER array, dimension (N)   
            The pivot indices from CGBTRF; for 1<=i<=N, row i of the   
            matrix was interchanged with row IPIV(i).   

    B       (input) COMPLEX array, dimension (LDB,NRHS)   
            The right hand side matrix B.   

    LDB     (input) INTEGER   
            The leading dimension of the array B.  LDB >= max(1,N).   

    X       (input/output) COMPLEX array, dimension (LDX,NRHS)   
            On entry, the solution matrix X, as computed by CGBTRS.   
            On exit, the improved solution matrix X.   

    LDX     (input) INTEGER   
            The leading dimension of the array X.  LDX >= max(1,N).   

    FERR    (output) REAL array, dimension (NRHS)   
            The estimated forward error bound for each solution vector   
            X(j) (the j-th column of the solution matrix X).   
            If XTRUE is the true solution corresponding to X(j), FERR(j)   
            is an estimated upper bound for the magnitude of the largest   
            element in (X(j) - XTRUE) divided by the magnitude of the   
            largest element in X(j).  The estimate is as reliable as   
            the estimate for RCOND, and is almost always a slight   
            overestimate of the true error.   

    BERR    (output) REAL array, dimension (NRHS)   
            The componentwise relative backward error of each solution   
            vector X(j) (i.e., the smallest relative change in   
            any element of A or B that makes X(j) an exact solution).   

    WORK    (workspace) COMPLEX array, dimension (2*N)   

    RWORK   (workspace) REAL array, dimension (N)   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   

    Internal Parameters   
    ===================   

    ITMAX is the maximum number of steps of iterative refinement.   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    /* Table of constant values */
    static complex c_b1 = {1.f,0.f};
    static integer c__1 = 1;
    
    /* System generated locals */
    integer ab_dim1, ab_offset, afb_dim1, afb_offset, b_dim1, b_offset, 
	    x_dim1, x_offset, i__1, i__2, i__3, i__4, i__5, i__6, i__7;
    real r__1, r__2, r__3, r__4;
    complex q__1;
    /* Builtin functions */
    double r_imag(complex *);
    /* Local variables */
    static integer kase;
    static real safe1, safe2;
    static integer i__, j, k;
    static real s;
    extern /* Subroutine */ int cgbmv_(char *, integer *, integer *, integer *
	    , integer *, complex *, complex *, integer *, complex *, integer *
	    , complex *, complex *, integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int ccopy_(integer *, complex *, integer *, 
	    complex *, integer *), caxpy_(integer *, complex *, complex *, 
	    integer *, complex *, integer *);
    static integer count, kk;
    extern /* Subroutine */ int clacon_(integer *, complex *, complex *, real 
	    *, integer *);
    static real xk;
    extern doublereal slamch_(char *);
    static integer nz;
    static real safmin;
    extern /* Subroutine */ int xerbla_(char *, integer *), cgbtrs_(
	    char *, integer *, integer *, integer *, integer *, complex *, 
	    integer *, integer *, complex *, integer *, integer *);
    static logical notran;
    static char transn[1], transt[1];
    static real lstres, eps;
#define b_subscr(a_1,a_2) (a_2)*b_dim1 + a_1
#define b_ref(a_1,a_2) b[b_subscr(a_1,a_2)]
#define x_subscr(a_1,a_2) (a_2)*x_dim1 + a_1
#define x_ref(a_1,a_2) x[x_subscr(a_1,a_2)]
#define ab_subscr(a_1,a_2) (a_2)*ab_dim1 + a_1
#define ab_ref(a_1,a_2) ab[ab_subscr(a_1,a_2)]


    ab_dim1 = *ldab;
    ab_offset = 1 + ab_dim1 * 1;
    ab -= ab_offset;
    afb_dim1 = *ldafb;
    afb_offset = 1 + afb_dim1 * 1;
    afb -= afb_offset;
    --ipiv;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;
    x_dim1 = *ldx;
    x_offset = 1 + x_dim1 * 1;
    x -= x_offset;
    --ferr;
    --berr;
    --work;
    --rwork;

    /* Function Body */
    *info = 0;
    notran = lsame_(trans, "N");
    if (! notran && ! lsame_(trans, "T") && ! lsame_(
	    trans, "C")) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*kl < 0) {
	*info = -3;
    } else if (*ku < 0) {
	*info = -4;
    } else if (*nrhs < 0) {
	*info = -5;
    } else if (*ldab < *kl + *ku + 1) {
	*info = -7;
    } else if (*ldafb < (*kl << 1) + *ku + 1) {
	*info = -9;
    } else if (*ldb < max(1,*n)) {
	*info = -12;
    } else if (*ldx < max(1,*n)) {
	*info = -14;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("CGBRFS", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *nrhs == 0) {
	i__1 = *nrhs;
	for (j = 1; j <= i__1; ++j) {
	    ferr[j] = 0.f;
	    berr[j] = 0.f;
/* L10: */
	}
	return 0;
    }

    if (notran) {
	*(unsigned char *)transn = 'N';
	*(unsigned char *)transt = 'C';
    } else {
	*(unsigned char *)transn = 'C';
	*(unsigned char *)transt = 'N';
    }

/*     NZ = maximum number of nonzero elements in each row of A, plus 1   

   Computing MIN */
    i__1 = *kl + *ku + 2, i__2 = *n + 1;
    nz = min(i__1,i__2);
    eps = slamch_("Epsilon");
    safmin = slamch_("Safe minimum");
    safe1 = nz * safmin;
    safe2 = safe1 / eps;

/*     Do for each right hand side */

    i__1 = *nrhs;
    for (j = 1; j <= i__1; ++j) {

	count = 1;
	lstres = 3.f;
L20:

/*        Loop until stopping criterion is satisfied.   

          Compute residual R = B - op(A) * X,   
          where op(A) = A, A**T, or A**H, depending on TRANS. */

	ccopy_(n, &b_ref(1, j), &c__1, &work[1], &c__1);
	q__1.r = -1.f, q__1.i = 0.f;
	cgbmv_(trans, n, n, kl, ku, &q__1, &ab[ab_offset], ldab, &x_ref(1, j),
		 &c__1, &c_b1, &work[1], &c__1);

/*        Compute componentwise relative backward error from formula   

          max(i) ( abs(R(i)) / ( abs(op(A))*abs(X) + abs(B) )(i) )   

          where abs(Z) is the componentwise absolute value of the matrix   
          or vector Z.  If the i-th component of the denominator is less   
          than SAFE2, then SAFE1 is added to the i-th components of the   
          numerator and denominator before dividing. */

	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = b_subscr(i__, j);
	    rwork[i__] = (r__1 = b[i__3].r, dabs(r__1)) + (r__2 = r_imag(&
		    b_ref(i__, j)), dabs(r__2));
/* L30: */
	}

/*        Compute abs(op(A))*abs(X) + abs(B). */

	if (notran) {
	    i__2 = *n;
	    for (k = 1; k <= i__2; ++k) {
		kk = *ku + 1 - k;
		i__3 = x_subscr(k, j);
		xk = (r__1 = x[i__3].r, dabs(r__1)) + (r__2 = r_imag(&x_ref(k,
			 j)), dabs(r__2));
/* Computing MAX */
		i__3 = 1, i__4 = k - *ku;
/* Computing MIN */
		i__6 = *n, i__7 = k + *kl;
		i__5 = min(i__6,i__7);
		for (i__ = max(i__3,i__4); i__ <= i__5; ++i__) {
		    i__3 = ab_subscr(kk + i__, k);
		    rwork[i__] += ((r__1 = ab[i__3].r, dabs(r__1)) + (r__2 = 
			    r_imag(&ab_ref(kk + i__, k)), dabs(r__2))) * xk;
/* L40: */
		}
/* L50: */
	    }
	} else {
	    i__2 = *n;
	    for (k = 1; k <= i__2; ++k) {
		s = 0.f;
		kk = *ku + 1 - k;
/* Computing MAX */
		i__5 = 1, i__3 = k - *ku;
/* Computing MIN */
		i__6 = *n, i__7 = k + *kl;
		i__4 = min(i__6,i__7);
		for (i__ = max(i__5,i__3); i__ <= i__4; ++i__) {
		    i__5 = ab_subscr(kk + i__, k);
		    i__3 = x_subscr(i__, j);
		    s += ((r__1 = ab[i__5].r, dabs(r__1)) + (r__2 = r_imag(&
			    ab_ref(kk + i__, k)), dabs(r__2))) * ((r__3 = x[
			    i__3].r, dabs(r__3)) + (r__4 = r_imag(&x_ref(i__, 
			    j)), dabs(r__4)));
/* L60: */
		}
		rwork[k] += s;
/* L70: */
	    }
	}
	s = 0.f;
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    if (rwork[i__] > safe2) {
/* Computing MAX */
		i__4 = i__;
		r__3 = s, r__4 = ((r__1 = work[i__4].r, dabs(r__1)) + (r__2 = 
			r_imag(&work[i__]), dabs(r__2))) / rwork[i__];
		s = dmax(r__3,r__4);
	    } else {
/* Computing MAX */
		i__4 = i__;
		r__3 = s, r__4 = ((r__1 = work[i__4].r, dabs(r__1)) + (r__2 = 
			r_imag(&work[i__]), dabs(r__2)) + safe1) / (rwork[i__]
			 + safe1);
		s = dmax(r__3,r__4);
	    }
/* L80: */
	}
	berr[j] = s;

/*        Test stopping criterion. Continue iterating if   
             1) The residual BERR(J) is larger than machine epsilon, and   
             2) BERR(J) decreased by at least a factor of 2 during the   
                last iteration, and   
             3) At most ITMAX iterations tried. */

	if (berr[j] > eps && berr[j] * 2.f <= lstres && count <= 5) {

/*           Update solution and try again. */

	    cgbtrs_(trans, n, kl, ku, &c__1, &afb[afb_offset], ldafb, &ipiv[1]
		    , &work[1], n, info);
	    caxpy_(n, &c_b1, &work[1], &c__1, &x_ref(1, j), &c__1);
	    lstres = berr[j];
	    ++count;
	    goto L20;
	}

/*        Bound error from formula   

          norm(X - XTRUE) / norm(X) .le. FERR =   
          norm( abs(inv(op(A)))*   
             ( abs(R) + NZ*EPS*( abs(op(A))*abs(X)+abs(B) ))) / norm(X)   

          where   
            norm(Z) is the magnitude of the largest component of Z   
            inv(op(A)) is the inverse of op(A)   
            abs(Z) is the componentwise absolute value of the matrix or   
               vector Z   
            NZ is the maximum number of nonzeros in any row of A, plus 1   
            EPS is machine epsilon   

          The i-th component of abs(R)+NZ*EPS*(abs(op(A))*abs(X)+abs(B))   
          is incremented by SAFE1 if the i-th component of   
          abs(op(A))*abs(X) + abs(B) is less than SAFE2.   

          Use CLACON to estimate the infinity-norm of the matrix   
             inv(op(A)) * diag(W),   
          where W = abs(R) + NZ*EPS*( abs(op(A))*abs(X)+abs(B) ))) */

	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    if (rwork[i__] > safe2) {
		i__4 = i__;
		rwork[i__] = (r__1 = work[i__4].r, dabs(r__1)) + (r__2 = 
			r_imag(&work[i__]), dabs(r__2)) + nz * eps * rwork[
			i__];
	    } else {
		i__4 = i__;
		rwork[i__] = (r__1 = work[i__4].r, dabs(r__1)) + (r__2 = 
			r_imag(&work[i__]), dabs(r__2)) + nz * eps * rwork[
			i__] + safe1;
	    }
/* L90: */
	}

	kase = 0;
L100:
	clacon_(n, &work[*n + 1], &work[1], &ferr[j], &kase);
	if (kase != 0) {
	    if (kase == 1) {

/*              Multiply by diag(W)*inv(op(A)**H). */

		cgbtrs_(transt, n, kl, ku, &c__1, &afb[afb_offset], ldafb, &
			ipiv[1], &work[1], n, info);
		i__2 = *n;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    i__4 = i__;
		    i__5 = i__;
		    i__3 = i__;
		    q__1.r = rwork[i__5] * work[i__3].r, q__1.i = rwork[i__5] 
			    * work[i__3].i;
		    work[i__4].r = q__1.r, work[i__4].i = q__1.i;
/* L110: */
		}
	    } else {

/*              Multiply by inv(op(A))*diag(W). */

		i__2 = *n;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    i__4 = i__;
		    i__5 = i__;
		    i__3 = i__;
		    q__1.r = rwork[i__5] * work[i__3].r, q__1.i = rwork[i__5] 
			    * work[i__3].i;
		    work[i__4].r = q__1.r, work[i__4].i = q__1.i;
/* L120: */
		}
		cgbtrs_(transn, n, kl, ku, &c__1, &afb[afb_offset], ldafb, &
			ipiv[1], &work[1], n, info);
	    }
	    goto L100;
	}

/*        Normalize error. */

	lstres = 0.f;
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
/* Computing MAX */
	    i__4 = x_subscr(i__, j);
	    r__3 = lstres, r__4 = (r__1 = x[i__4].r, dabs(r__1)) + (r__2 = 
		    r_imag(&x_ref(i__, j)), dabs(r__2));
	    lstres = dmax(r__3,r__4);
/* L130: */
	}
	if (lstres != 0.f) {
	    ferr[j] /= lstres;
	}

/* L140: */
    }

    return 0;

/*     End of CGBRFS */

} /* cgbrfs_ */

#undef ab_ref
#undef ab_subscr
#undef x_ref
#undef x_subscr
#undef b_ref
#undef b_subscr


