#include "matrix.h"


MATRIX mat_add(MATRIX A, MATRIX B, MATRIX C)
{
    int i, j, m, n, o, p;
    m = MatCol(A);
    n = MatRow(A);
    o = MatCol(B);
    p = MatRow(B);
    if(C==NULL) if((C = mat_creat(MatRow(A), MatCol(A), UNDEFINED))==NULL)
            return mat_error(MAT_MALLOC);
    #pragma omp parallel for private(j)
    for(i=0; i<n; ++i)
        for(j=0; j<m; ++j)
        {
            if(o==m &&p==n) C[i][j] = A[i][j]+B[i][j];
            else if(o==1 && p!=1) C[i][j] = A[i][j]+B[i][0];
            else if(p==1 && o!=1) C[i][j] = A[i][j]+B[0][j];
            else gen_error(GEN_SIZEMISMATCH);
        }
    return (C);
}

MATRIX mat_adds(MATRIX A, mtype s, MATRIX result)
{
    int i, j, m, n;
    m = MatCol(A);
    n = MatRow(A);
    if(result==NULL) if((result = mat_creat( MatRow(A), MatCol(A), UNDEFINED))==NULL)
            return mat_error(MAT_MALLOC);
    #pragma omp parallel for private(j)
    for(i=0; i<n; ++i)
        for(j=0; j<m; ++j)
        {
            result[i][j] = A[i][j]+s;
        }
    return result;
}

INT_VECTOR int_vec_add(INT_VECTOR A, INT_VECTOR B, INT_VECTOR result)
{
    int i, m;
    m = Int_VecLen(A);
    if(result==NULL) if((result = int_vec_creat(m, UNDEFINED))==NULL)
            int_vec_error(INT_VEC_MALLOC);
    if(m!=Int_VecLen(B))gen_error(GEN_SIZEMISMATCH);
    for(i=0; i<m; ++i) result[i] = A[i]+B[i];
    return result;
}

INT_VECTOR int_vec_adds(INT_VECTOR A, int x, INT_VECTOR result)
{
    int i, m;
    m = Int_VecLen(A);
    if(result==NULL) if((result = int_vec_creat(m, UNDEFINED))==NULL)
            int_vec_error(INT_VEC_MALLOC);
    for(i=0; i<m; ++i) result[i] = A[i]+x;
    return result;
}
