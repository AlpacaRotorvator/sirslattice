#include "pmatrix.hxx"
#include <cmath>
#include <iostream>
using namespace std;

template <class T>
T pmatrix<T>::at(int i, int j) {
    int res_i = i;
    int res_j = j;

    int size_i = mat.size();
    int size_j = mat[0].size();

    if (i < 0) {
	res_i = size_i + (i % size_i);
    } else if (i >= size_i) {
	res_i = i % size_i;
    }
    if (j < 0) {
	res_j = size_j + (j % size_j);
    } else if (j >= size_j) {
	res_j = j % size_j;
    }
    
    return mat[res_i][res_j];
}

template <class T>
void pmatrix<T>::set(int i, int j, T val) {
    int res_i = i;
    int res_j = j;

    int size_i = mat.size();
    int size_j = mat[0].size();

    if (i < 0) {
	res_i = size_i + (i % size_i);
    } else if (i >= size_i) {
	res_i = i % j;
    }
    if (j < 0) {
	res_j = size_j + (j % size_j);
    } else if (j >= size_j) {
	res_j = j % size_j;
    }


    mat[res_i][res_j] = val;
}

