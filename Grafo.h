/*
	Universidade Federal de Pelotas
	Centro de Desenvolvimento Tecnologico - CDTec
	Bacharelado em Ciência da Computação

	Estruturas de Dados 2 - 2012/2

	Professor Ricardo Matsumura Araújo

	Algoritmo de Visualização de Grafos

	Alunos:
		Lucas Mendonça de Souza Xavier		11105053
		William Dalmorra de Souza		11100360
*/


#ifndef GRAFO_H_
#define GRAFO_H_

#include <vector>
#include <string>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_ttf.h>

#define CE 2000
#define CM 5
#define CP 10
#define CT 1
#define CCIM 100
#define PI 3.14159265
#define TETA PI/6
#define RAIO 5
#define TAMFLECHA 6
#define XFONTE 15
#define ALTURA 550
#define LARGURA 800
#define METADE_ALT 275
#define METADE_LARG 400

using namespace std;

class Nodo
{

	double x,y;
	double x1,y1;
	string nome;

public:
	Nodo();
	Nodo(const Nodo& n);
	~Nodo();

	double getX();
	double getY();
	string getNome();
	void setX(double x);
	void setY(double y);
	void setX1(double x1);
	void setY1(double y1);
	void setNome(string nome);
	void swap();
};

class Grafo
{
	int *matrizAdj;
	vector<Nodo> tabelaRef;
	int numeroVert;
	bool direcionado;

public:

	Grafo(int vertices);

	~Grafo();

	Nodo* getId(int ID);

	int getNumeroVert();

	bool getDirecionado();

	int getPeso(int ID1, int ID2);

	void setDirecionado (bool direcionado);

	void inserirVertice(int ID, string nome);

	void inserirAresta(int ID1, int ID2, int peso);

	void imprimeTable();

	bool calcula();

	bool calculaNodo(int ID);

	void vizinhos(int ID);

	bool adj(int ID1, int ID2);
};

#endif