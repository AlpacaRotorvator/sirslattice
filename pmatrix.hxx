//pmatrix: matriz com condições periódicas de contorno
#ifndef PMATRIX_H
#define PMATRIX_H

#include <vector>
using namespace std;

template <class T>
class pmatrix {
public:
    vector< vector<T> > mat;

    pmatrix (unsigned h, unsigned w, T init) {
	                    mat = vector< vector<T> > (h);
			    for (unsigned i = 0; i < h; i++) {
				mat[i] = vector <T> (w, init);
			    }
    }
    pmatrix(unsigned l, T init): pmatrix(l, l, init) {};

    T at (int, int);
    void set (int, int, T);
};

template class pmatrix<int>;

#endif
