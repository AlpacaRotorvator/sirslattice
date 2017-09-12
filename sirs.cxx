#include "sirs.hxx"
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;

mt19937 sirs::prng = mt19937(time(NULL));
uniform_real_distribution<double> sirs::dist_test = uniform_real_distribution<double> (0,1);

sirs::sirs (unsigned dim, double t, int mode): lattice(pmatrix<int> (dim, 1)), it(0), l(dim) {  
	dist_draw = uniform_int_distribution<int> (0, l-1);

	init_random(frac);
}

void sirs::step () {
    it++;
    
    //sorteia o sítio a ser invertido
    int x = dist_draw(prng);
    int y = dist_draw(prng);

    double rand_test = dist_test();

    switch(lattice.mat[x][y]) {
    case -1:
	if (rand_test < c){
		mat[x][y] = 0;
		num_R++;
		num_I--;
	}
	
	break;
	    
    case 1:
    {
	int ngbCount = 0;
	if (lattice.mat.at(x + 1, y) == 0){ ngbCount++;}  
	if (lattice.mat.at(x - 1, y) == 0){ ngbCount++;}  
	if (lattice.mat.at(x, y + 1) == 0){ ngbCount++;}
	if (lattice.mat.at(x, y - 1) == 0){ ngbCount++;}

	if (rand_test < ngbCount * b / 4) {
	    mat[x][y] = -1;
	    num_I++;
	    num_S--;
	}
	
	break;
    }
    
    case 0:
	if (rand_test < a) {
	    mat[x][y]  = 1;
	    num_S++;
	    num_R--;
	}

	break;
    } 
}

void sirs::run_until (int t_f) {
    while (it < t_f) {
	step();
    }
}

void sirs::print_lattice () {
    cout << endl;
    for (int i = 0; i < l; i++) {
	for (int j = 0; j < l; j++) {
	    cout << (lattice.mat[i][j] == 1? "S ":lattice.mat[i][j] == -1? "I ":"R ");  
	}
	cout << endl;
    }
}

void sirs::init_random (float frac) {
    for (int i = 0; i < l; i++) {
	for (int j = 0; j < l; j++) {
	    double val = dist_test(prng);
	    if (val < frac) {
		lattice.mat[i][j] = -1;
		num_I++;
	    }
	    else {
		lattice.mat[i][j] = 1;
		num_S++;
	    }
	}
    }   
}
