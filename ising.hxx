//ising.hxx simulação do modelo de Ising
#include <random>
#include <vector>
#include "pmatrix.hxx"
using namespace std;

class ising {
public:
    //matriz periódica para o reticulado
    pmatrix<int> lattice;
    //contador de iterações
    int it;
    //temperatura do sistema
    double temp;

    //vetores para armazenar energia e soma dos spins em cada iteração
    //eles estão expostos por pura conveniência; Como eu não consegui fazer uma interface limpa entre vectors da STL e arrays do numpy o tempo que demora para criar um array a partir deles é quase proibitivo
    vector<long int> spin;
    vector<long int> energy;

    //funções para evoluir o sistema no tempo em um instante e até um instante passado por argumento, respectivamente
    void step();
    void run_until(int);

    //funções para calcular as médias intermerdiárias. A idéia original era deixar isso para o Python, mas ver comentário sobre os vetores de spin e energia
    //o argumento é o número de estados que devem ser considerados como transiente
    double calc_m1(int);
    double calc_m2(int);
    double calc_e1(int);
    double calc_e2(int);

    //imprime o estado do reticulado na tela, porque por que não?
    //spins para cima são representados por "o", spins para baixo por "x"
    void print_lattice ();

    //Construtor final. Recebe 3 argumentos:
    //dim : lado do reticulado quadrado
    //t   : temperatura em que a simulação é executada
    //mode: determina a condição inicial do problema. Valores possíveis são:
    //      -1: todos os spins para baixo(padrão)
    //       1: todos os spins para cima
    //       2: spins alternados para baixo e para cima, tabuleiro de xadrez
    //       3: spins determinados aleatoriamente com probabilidade 1/2
    ising(unsigned dim, double t, int mode = -1);// : it(0),  temp(t), l(dim);

private:
    //manter uma variável para o tamanho do reticulado ajuda a manter o código limpo
    int l;
    //um gerador de números aleatórios, uma distribuição para o teste na energia e outra para selecionar o sítio a ser alterado
    static mt19937 prng;
    static uniform_real_distribution<double> dist_test;
    uniform_int_distribution<int> dist_draw;
    
    //função para calcular a variação de energia em uma inversão
    int dE(int, int);

    //funções para calcular os valores de spin e energia
    int calc_spin();
    int calc_energy();

    //funções de inicialização aleatória e tipo tabuleiro de xadrez, ver comentário sobre o construtor
    void init_random();
    void init_chessboard();
};
