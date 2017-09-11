#include "ising.hxx"
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;

mt19937 ising::prng = mt19937(time(NULL));
uniform_real_distribution<double> ising::dist_test = uniform_real_distribution<double> (0,1);

ising::ising (unsigned dim, double t, int mode): lattice(pmatrix<int> (dim, mode)), it(0),  temp(t), l(dim) {  
	dist_draw = uniform_int_distribution<int> (0, l-1);

	switch (mode) {
	case -1:
	    break;
	case  1:
	    break;
	case  2:
	    lattice = pmatrix<int> (dim, 0);
	    init_chessboard();
	    break;
	case 3:
	    lattice = pmatrix<int> (dim, 0);
	    init_random();
	    break;
	default:
	    lattice = pmatrix<int> (dim, -1);
	}

	spin = vector<long int> (1e6+1, 0);
	energy = vector<long int> (1e6+1, 0);
	spin[0] = calc_spin();
	energy[0] = calc_energy();
}

void ising::step () {
    it++;
    
    //sorteia o sítio a ser invertido
    int x = dist_draw(prng);
    int y = dist_draw(prng);

    int diff = dE(x,y);

    //testes para definir se o sítio será mesmo invertido e atualização do spin/energia
    if(diff <= 0) {
	lattice.set(x, y, -1*lattice.mat[x][y]);

	spin[it] = spin[it-1] + 2*lattice.mat[x][y];
	energy[it] = energy[it-1] + diff;
    } else {
	if (dist_test(prng) < exp(-diff/temp)){
	    lattice.set(x, y, -1*lattice.mat[x][y]);

	    spin[it] = spin[it-1] + 2*lattice.mat[x][y];
	    energy[it] = energy[it-1] + diff;
	} else {
	    spin[it] = spin[it-1];
	    energy[it] = energy[it-1];

	}

    } 
}

void ising::run_until (int t_f) {
    while (it < t_f) {
	step();
    }
}

int ising::dE(int x, int y) {
    return 2*lattice.at(x, y)*( lattice.at(x + 1, y) + lattice.at(x - 1, y) + lattice.at(x, y + 1) + lattice.at(x, y - 1));
}

int ising::calc_spin() {
    int s = 0;
    for (int i = 0; i < l; i++) {
	for (int j = 0; j < l; j++) {
	    s += lattice.at(i, j);  
	}
    }
    return s;
}

int ising::calc_energy(){
    int e = 0;
    for (int i = 0; i < l; i++) {
	for (int j = 0; j < l; j++) {
	    e -= lattice.at(i, j) * (lattice.at(i + 1, j) + lattice.at(i, j + 1));  
	}
    }
    return e;    
}

double ising::calc_m1(int trans) {
    double res = 0;
    for (int i = trans; i < it; i++) {
	res += abs(spin[i]);
    }
    return res/double(it - trans);
}

double ising::calc_m2(int trans) {
    double res = 0;
    for (int i = trans; i < it; i++) {
	res += pow(spin[i], 2);
    }
    return res/double(it - trans);
}

double ising::calc_e1(int trans) {
    double res = 0;
    for (int i = trans; i < it; i++) {
	res += double(energy[i]);
    }
    return res/double(it - trans);    
}

double ising::calc_e2(int trans) {
    double res = 0;
    for (int i = trans; i < it; i++) {
	res += pow(energy[i], 2);
    }
    return res/double(it - trans);
}

void ising::print_lattice () {
    cout << endl;
    for (int i = 0; i < l; i++) {
	for (int j = 0; j < l; j++) {
	    cout << (lattice.mat[i][j] == 1? "o ":"x ");  
	}
	cout << endl;
    }
}

void ising::init_random () {
    for (int i = 0; i < l; i++) {
	for (int j = 0; j < l; j++) {
	    double val = dist_test(prng);
	    lattice.mat[i][j] = (val < 0.5)? -1:1;
	}
    }   
}

void ising::init_chessboard () {
    int parity = (l % 2 == 0)? -1:1;
    int val = -1;
    for (int i = 0; i < l; i++) {
	for (int j = 0; j < l; j++) {
	    lattice.mat[i][j] = val;
	    val *= -1;
	}
	val *= parity;
    }   
}
