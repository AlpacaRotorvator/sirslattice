//sirs: simulação do modelo SIRS
#ifndef SIRS_H
#define SIRS_H

#include <random>
#include <vector>
#include "pmatrix.hxx"
using namespace std;

class sirs {
public:

    //funções para evoluir o sistema no tempo em um instante e até um instante passado por argumento, respectivamente
    int step();
    void run_until(int);

    //getters para algumas variáveis:
    int get_S() {return num_S;}
    int get_I() {return num_I;}
    int get_R() {return num_R;}
    int get_it() {return it;}

    //imprime o estado do reticulado na tela, porque por que não?
    void print_lattice ();

    //Construtor, recebe 3 argumentos:
    //dim : lado do reticulado quadrado
    //a   : taxa de transição R -> S
    //b   : taxa de transição S -> I
    //c   : taxa de transição I -> R
    //frac: porporção da população inicial de indivíduos infectados
    sirs(unsigned dim, double a, double b, double c, double frac);

private:
    //manter uma variável para o tamanho do reticulado ajuda a manter o código limpo
    int l;
    
    //um gerador de números aleatórios, uma distribuição para os testes de transição e outra para selecionar o sítio a ser alterado
    static mt19937 prng;
    static uniform_real_distribution<double> dist_test;
    uniform_int_distribution<int> dist_draw;

    //matriz periódica para o reticulado
    pmatrix<int> lattice;
    //contador de iterações
    int it;
    
    //Contagem de indivíduos
    int num_S = 0;
    int num_I = 0;
    int num_R = 0;

    //Probabilidades de transição
    double a;
    double b;
    double c;
    
    //função de inicialização do reticulado
    void init_random(float);
};

#endif
