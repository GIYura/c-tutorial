#ifndef FUNC_H
#define FUNC_H

/*
@brief: Fill the  matrix
@in: matrix - pointer to the first matrix element
@in: rows - number of rows in matrix
@in: columnss - number of columns in matrix
@out: none
*/
void MatrixInit(int* matrix, int rows, int columns);

/*
@brief: Print all elements in matrix
@in: matrix - pointer to the first matrix element
@in: rows - number of rows in matrix
@in: columnss - number of columns in matrix
@out: none
*/
void MatrixPrint2D(int* matrix, int rows, int columns);

/*
@brief: Print all elements in matrix
@in: matrix - pointer to the first matrix element
@in: rows - number of rows in matrix
@in: columnss - number of columns in matrix
@out: none
*/
void MatrixPrint1D(int* matrix, int rows, int columns);

/*
NOTE: iterate over rows to cols

@brief: Calculate sum of all elements in matrix
@in: matrix - pointer to the first matrix element
@in: rows - number of rows in matrix
@in: columnss - number of columns in matrix
@out: int - sum of all matrix elements
*/
int MatrixFriendlySum(int* matrix, int rows, int columns);

/*
NOTE: iterate over cols to rows

@brief: Calculate sum of all elements in matrix
@in: matrix - pointer to the first matrix element
@in: rows - number of rows in matrix
@in: columnss - number of columns in matrix
@out: int - sum of all matrix elements
*/
int MatrixNoneFriendlySum(int* matrix, int rows, int columns);

#endif /* FUNC_H */
