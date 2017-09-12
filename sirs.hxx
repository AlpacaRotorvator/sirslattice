//sirs: simulação do modelo SIRS
#ifndef SIRS_H
#define SIRS_H

#include <random>
#include <vector>
#include "pmatrix.hxx"
using namespace std;

class sirs {
public:
    //matriz periódica para o reticulado
    pmatrix<int> lattice;
    //contador de iterações
    int it;


    //funções para evoluir o sistema no tempo em um instante e até um instante passado por argumento, respectivamente
    void step();
    void run_until(int);

    //imprime o estado do reticulado na tela, porque por que não?
    //spins para cima são representados por "o", spins para baixo por "x"
    void print_lattice ();

    //Construtor final. Recebe 3 argumentos:
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
