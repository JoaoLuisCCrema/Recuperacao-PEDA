/*
Joao Luis Chiarelotto Crema

Esta Recuperação permite que a média dos trabalhos 1, 2, 3, 4, 5, 6, 7, 8 chegue a, no máximo
7,0.
Para obter estes pontos você precisará criar as estruturas de dados especificadas nos itens a e
b, sem esquecer que uma estrutura de dados é composta de uma representação em memória e, no
mínimo três funções (ou métodos) para a sua manipulação. Sendo assim, todas as estruturas de dados
terão, um método para inclusão, um método para exclusão e um método para busca.
a) Usando, C, C++, Python ou Java, crie uma estrutura de dados chamada minhaNovaFila que
deverá usar como representação em memória uma lista linkada. Para testar esta estrutura
você precisará criar uma fila com 100 registros compostos de uma string com até 100
caracteres e um valor numérico do conjunto dos números reais. Para gerar os strings e os
valores números você deverá usar um gerador de números randômicos baseado no
Mersenne Twister.
Durante a criação dos registros você deverá escolher, aleatóriamente dois destes registros
para testar a função de busca.
Uma vez que a lista tenha sido criada você deve contar o tempo necessário para tirar 20%
dos registros desta fila e o tempo necessário para encontrar a posição na fila onde estão
dois dos registros criados. Neste exercício, o tempo gasto em todas as operações com a
estrutura de dados deverá ser registrado.
A saída esperada será feita por meio de um arquivo onde teremos a fila original impressa
na horizontal com comprimento inferior a 5 registros por linha, seguida da fila depois da
exclusão de 20% dos seus registros, também na horizontal.
As últimas linhas do arquivo de saída serão reservadas para o registro dos tempos médios
utilizados para cada uma das operações da estrutura de dados (criação, inclusão, exclusão,
nova inclusão) como estes tempos serão muito pequenos será necessário tirar as médias
com, no mínimo, 50 repetições.
b) Usando, C, C++, Python ou Java, crie uma estrutura de dados chamada eitaHeap que deverá
usar como representação em memória uma lista linkada. Para testar esta estrutura você
precisará criar um heap (min heap) com 100 registros compostos de uma string com até 100
caracteres e um valor numérico do conjunto dos números reais. Para gerar os strings e os
valores números você deverá usar um gerador de números randômicos baseado no
Mersenne Twister.
Durante a criação dos registros você deverá escolher, aleatoriamente dez destes registros
para testar a função de busca.
Uma vez que a heap tenha sido criada você deve contar o tempo necessário para tirar 16%
dos registros deste heap, o tempo necessário para encontrar a posição na fila onde estão os
registros escolhidos para teste e o tempo necessário para inserir 45 registros novos neste
heap. Sem dúvida os testes para a localização dos dezregistrosselecionados para o resgistro
dos tempos de localização deverão ser feitos com o heap originalmente criado, antes da
exclusão de 16% ou da inclusão de novos registros.
Como a estrutura é muito pequena, todos os tempos deverão ser calculados na forma de
média o que implica na repetição dos processos de criação, inserção, remoção, busca e nova
inserção, no mínimo 50 vezes.
A saída esperada será feita por meio de um arquivo onde teremos o heap estruturado em
formato de árvore usando ASCII, seguido do heap com menos 16% dos registros, também
estruturado no formato de uma árvore usando ASCII, seguido do heap após a inclusão de
novos registros, seguido dos tempos médios de inclusão, exclusão, busca e nova inclusão
identificados cada um em sua própria linha.
*/

#include "minhaNovaFila.hpp"
#include "mt19937.hpp"
#include "randomString.hpp"
#include <bits/stdc++.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
  ofstream outFile;

  outFile.open("resultado.txt");

  if (!outFile) {
    cout << "erro test.txt" << endl;
    abort();
  }

  int aleatorioUm, aleatorioDois;
  minhaNovaFila *fila = new minhaNovaFila();

  // Gerando 2 números aleatórios para buscar futuramente
  aleatorioUm = (rand() % 100);
  aleatorioDois = (rand() % 100);

  while (aleatorioUm == aleatorioDois) {
    aleatorioDois = (rand() % 100);
  }

  // Mersenne Twister para gerar os números
  // OBS: implementei esse algoritmo de forma local
  MT19937 mt(time(NULL));
  int numero;
  string mensagem;
  Registro *r1 = new Registro();
  Registro *r2 = new Registro();

  // Looping para gerar os registros
  for (int i = 0; i < 100; i++) {
    // mt.random utiliza o mt implementado por mim.
    numero = mt.random();

    // random_string é baseado no Mersenne Twister, porém,
    // utiliza o mt existente na linguagem c++
    mensagem = random_string(100);

    // Inclui o novo registro na fila
    fila->incluir(numero, mensagem);

    // Se o registro for o número igual ao escolhido, guardamos o resultado
    if (i == aleatorioUm) {
      r1 = fila->buscar(numero);
    }

    if (i == aleatorioDois) {
      r2 = fila->buscar(numero);
    }
  }
  Registro *aux = new Registro();

  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 4; j++) {
      aux = fila->buscarPorPosicao((j + 1) * (i + 1) - 1);
      outFile << aux->getNumero() << ", " << aux->getMensagem() << " | ";
    }

    outFile << endl;
  }

  outFile << endl;

  cout << "Iniciando busca dos registros" << endl;
  double tempo;

  auto inicio = chrono::high_resolution_clock::now();
  ios_base::sync_with_stdio(false);
  aux = fila->buscar(r1->getNumero());
  auto fim = chrono::high_resolution_clock::now();

  tempo = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
  tempo *= 1e-9;

  outFile << "O programa levou : " << fixed << tempo << setprecision(9);
  outFile << " segundos para encontrar o registro 1 " << endl;

  inicio = chrono::high_resolution_clock::now();
  ios_base::sync_with_stdio(false);
  aux = fila->buscar(r2->getNumero());
  fim = chrono::high_resolution_clock::now();

  tempo = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
  tempo *= 1e-9;

  outFile << "O programa levou : " << fixed << tempo << setprecision(9);
  outFile << " segundos para encontrar o registro 2 " << endl;

  cout << "Iniciando remoção de 20% da lista" << endl;

  inicio = chrono::high_resolution_clock::now();
  ios_base::sync_with_stdio(false);

  for (int i = 0; i < 20; i++) {
    double t;
    auto ini = chrono::high_resolution_clock::now();

    fila->removerPrimeiroDaFila();

    auto f = chrono::high_resolution_clock::now();

    t = chrono::duration_cast<chrono::nanoseconds>(f - ini).count();
    t *= 1e-9;

    outFile << "O programa levou : " << fixed << t << setprecision(9);
    outFile << " segundos para remover o registro número " << i + 1 << endl;
  }

  fim = chrono::high_resolution_clock::now();

  tempo = chrono::duration_cast<chrono::nanoseconds>(fim - inicio).count();
  tempo *= 1e-9;

  outFile << "O programa levou : " << fixed << tempo << setprecision(9);
  outFile << " segundos para remover 20% (20) dos registros" << endl;

  outFile.close();

  return 0;
}