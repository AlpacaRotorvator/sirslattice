#include "sirs.hxx"
#include <fstream>
#include <iostream>

void print_status ();

int main() {
    sirs sim(25, 0.05, 0.8, 0.2, 0.01);

    std::cout << "Estado Inicial:\n";
    std::cout << "\tIteracao: " << sim.get_it() << "\n";
    std::cout << "\tS: " << sim.get_S() << "\n";
    std::cout << "\tI: " << sim.get_I() << "\n";
    std::cout << "\tR: " << sim.get_R() << "\n";
    sim.print_lattice();

    int num_its = 2.5e5;
    
    std::vector<int> it(num_its, 0);
    std::vector<int> S(num_its, 0);
    std::vector<int> I(num_its, 0);
    std::vector<int> R(num_its, 0);

    for(int i = 0; i < num_its; i++) {
	it[i] = sim.get_it();
	S[i] = sim.get_S();
	I[i] = sim.get_I();
	R[i] = sim.get_R();
	
	int res = sim.step();

	if(!res) {
	    it.resize(i);
	    S.resize(i);
	    I.resize(i);
	    R.resize(i);
	    break;
	}
    }

    std::cout << "Estado Final:\n";
    std::cout << "\tIteracao: " << sim.get_it() << "\n";
    std::cout << "\tS: " << sim.get_S() << "\n";
    std::cout << "\tI: " << sim.get_I() << "\n";
    std::cout << "\tR: " << sim.get_R() << "\n";
    sim.print_lattice();

    ofstream outFile("output.csv");
    for(int i = 0; i < S.size(); i++) {
	outFile << it[i] << " " << S[i] << " " << I[i] << " " << R[i] << "\n";
    }

    return 0;
}
