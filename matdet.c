#include "matrix.h"


static mtype signa[2] = {1.0, -1.0};

mtype mat_minor(MATRIX A, int i, int j)
{
    MATRIX S = NULL;
    mtype result;
    S = mat_submat(A, i, j, S);
    result = mat_det(S);
    mat_free(S);
    return result;
}

mtype mat_cofact(MATRIX A, int i, int j)
{
    mtype result;
    result = signa[(i+j)%2]*A[i][j]*mat_minor(A, i, j);
    return result;
}

mtype mat_det(MATRIX a)
{
    MATRIX A, P;
    int i, j, n;
    mtype result;
    n = MatRow(a);
    A = mat_copy(a, NULL);
    P = mat_creat(n, 1, UNDEFINED);
    i = mat_lu(A, P);
    switch (i)
    {
    case -1:
        result = 0.0;
        break;

    default:
        result = 1.0;
        for(j=0; j<n; ++j)
        {
            result *= A[(int)P[j][0]][j];
        }
        result *= signa[i%2];
        break;
    }

    mat_free(A);
    mat_free(P);
    return (result);
}

