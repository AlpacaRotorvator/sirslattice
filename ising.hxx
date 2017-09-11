//ising.hxx simula��o do modelo de Ising
#include <random>
#include <vector>
#include "pmatrix.hxx"
using namespace std;

class ising {
public:
    //matriz peri�dica para o reticulado
    pmatrix<int> lattice;
    //contador de itera��es
    int it;
    //temperatura do sistema
    double temp;

    //vetores para armazenar energia e soma dos spins em cada itera��o
    //eles est�o expostos por pura conveni�ncia; Como eu n�o consegui fazer uma interface limpa entre vectors da STL e arrays do numpy o tempo que demora para criar um array a partir deles � quase proibitivo
    vector<long int> spin;
    vector<long int> energy;

    //fun��es para evoluir o sistema no tempo em um instante e at� um instante passado por argumento, respectivamente
    void step();
    void run_until(int);

    //fun��es para calcular as m�dias intermerdi�rias. A id�ia original era deixar isso para o Python, mas ver coment�rio sobre os vetores de spin e energia
    //o argumento � o n�mero de estados que devem ser considerados como transiente
    double calc_m1(int);
    double calc_m2(int);
    double calc_e1(int);
    double calc_e2(int);

    //imprime o estado do reticulado na tela, porque por que n�o?
    //spins para cima s�o representados por "o", spins para baixo por "x"
    void print_lattice ();

    //Construtor final. Recebe 3 argumentos:
    //dim : lado do reticulado quadrado
    //t   : temperatura em que a simula��o � executada
    //mode: determina a condi��o inicial do problema. Valores poss�veis s�o:
    //      -1: todos os spins para baixo(padr�o)
    //       1: todos os spins para cima
    //       2: spins alternados para baixo e para cima, tabuleiro de xadrez
    //       3: spins determinados aleatoriamente com probabilidade 1/2
    ising(unsigned dim, double t, int mode = -1);// : it(0),  temp(t), l(dim);

private:
    //manter uma vari�vel para o tamanho do reticulado ajuda a manter o c�digo limpo
    int l;
    //um gerador de n�meros aleat�rios, uma distribui��o para o teste na energia e outra para selecionar o s�tio a ser alterado
    static mt19937 prng;
    static uniform_real_distribution<double> dist_test;
    uniform_int_distribution<int> dist_draw;
    
    //fun��o para calcular a varia��o de energia em uma invers�o
    int dE(int, int);

    //fun��es para calcular os valores de spin e energia
    int calc_spin();
    int calc_energy();

    //fun��es de inicializa��o aleat�ria e tipo tabuleiro de xadrez, ver coment�rio sobre o construtor
    void init_random();
    void init_chessboard();
};
