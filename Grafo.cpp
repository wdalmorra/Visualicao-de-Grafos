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

#include "Grafo.h"

Grafo::Grafo(int vertices){

	int i,j;

	tabelaRef.resize(vertices);

	// Cria o ponteiro da matriz com n vertices
	matrizAdj = (int*) malloc((vertices*vertices)*sizeof(int));

	// Inicia a matriz com valor "nulo"
	for (i = 0; i < vertices; ++i) {
		for (j = 0; j < vertices; ++j) {
			matrizAdj[i*vertices + j] = INT_MIN;
		}
	}

	numeroVert = vertices;
}

Grafo::~Grafo(){
	free(matrizAdj);
}

Nodo* Grafo::getId(int ID){
	return &tabelaRef[ID];
}

int Grafo::getPeso(int ID1, int ID2){
	return matrizAdj[ID1*numeroVert+ID2];
}

int Grafo::getNumeroVert(){
	return numeroVert;
}

bool Grafo::getDirecionado(){
	return direcionado;
}

void Grafo::setDirecionado (bool direcionado){
	this->direcionado = direcionado;
}

void Grafo::inserirVertice(int ID, string nome){
	tabelaRef[ID].setNome(nome);
	tabelaRef[ID].setX(300*cos(ID+(2*PI/numeroVert)));
	tabelaRef[ID].setY(300*sin(ID+(2*PI/numeroVert)));
}

void Grafo::inserirAresta(int ID1, int ID2, int peso){
	matrizAdj[ID1*numeroVert+ID2] = peso;
}

void Grafo::vizinhos(int ID){

}

bool Grafo::adj(int ID1, int ID2){
	return matrizAdj[ID1*numeroVert+ID2] != INT_MIN;
}


void Grafo::imprimeTable()
{
	int i,j;
	for (i = 0; i < numeroVert; ++i) {
		cout << "NOME: " << tabelaRef[i].getNome() << " ";
		cout << "X: " << tabelaRef[i].getX() << " ";
		cout << "Y: " << tabelaRef[i].getY() << " ";	
	}

	for (i = 0; i < numeroVert; ++i) {
		for (j = 0; j < numeroVert; ++j) {
			if (matrizAdj[ i*numeroVert + j] == INT_MIN)
			{
				cout<< "-  ";
			}
			else
			{
				cout<<matrizAdj[ i*numeroVert + j]<< "  ";
			}
		}
		cout<< endl;
	}
}

bool Grafo::calcula()
{
	bool flag = false;

	for (int i = 0; i < numeroVert; ++i) {
		if (calculaNodo(i)) {
			flag = true;
		}
	}
	for (int i = 0; i < numeroVert; ++i) {
		tabelaRef[i].swap();
	}

	return flag;
}

bool Grafo::calculaNodo(int ID)
{
	double fx = 0,fy = 0;
	double x0,y0;

	x0 = tabelaRef[ID].getX();
	y0 = tabelaRef[ID].getY();

	for (int i = 0; i < numeroVert; ++i) {
		if (i != ID)
		{
			double d;

			double x1,y1;

			x1 = tabelaRef[i].getX();
			y1 = tabelaRef[i].getY();

			double x,y;

			x = (x1 - x0)*(x1 - x0);
			y = (y1 - y0)*(y1 - y0);

			d = sqrt(x + y);

			fx -= (CE/ (d*d)) * ((x1 - x0)/d);

			fy -= (CE/ (d*d)) * ((y1 - y0)/d);
		}
	}

	for (int i = 0; i < numeroVert; ++i) {
		if((matrizAdj[ID*numeroVert+i] != INT_MIN || matrizAdj[i*numeroVert+ID] != INT_MIN) && i != ID)
		{
			double x1, y1, xp, yp;

			x1 = tabelaRef[i].getX();
			y1 = tabelaRef[i].getY();

			double d10q = (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0);

			xp = CCIM * (x1 - x0) / sqrt ( d10q );
			yp = CCIM * (y1 - y0) / sqrt ( d10q );

			double dp0q = (xp-x0)*(xp-x0) + (yp-y0)*(yp-y0);

			fx += CM * log (sqrt(d10q) / CCIM) * (x1-x0) / sqrt(d10q);
			fy += CM * log (sqrt(d10q) / CCIM) * (y1-y0) / sqrt(d10q);
		}
	}


	double vx = fx/CP;
	double vy = fy/CP;

	tabelaRef[ID].setX1(x0+vx*CT);
	tabelaRef[ID].setY1(y0+vy*CT);

	if (vx < 0.01 && vy < 0.01 && vx > -0.01 && vy > -0.01) {
		return false;
	} else {
		return true;
	}
}

Nodo::Nodo()
{
	this->x = 0;
	this->y = 0;
	this->nome = "";
}

Nodo::Nodo(const Nodo& n)
{
	this->x = n.x;
	this->y = n.y;
	this->nome = "";
}
Nodo::~Nodo(){
}

double Nodo::getX(){
	return x;
}
double Nodo::getY(){
	return y;
}

string Nodo::getNome(){
	return nome;
}
void Nodo::setX(double x){
	this->x = x;
}

void Nodo::setY(double y){
	this->y = y;
}
void Nodo::setX1(double x1){
	this->x1 = x1;
}

void Nodo::setY1(double y1){
	this->y1 = y1;
}

void Nodo::swap(){
	this->x = this->x1;
	this->y = this->y1;
}

void Nodo::setNome(string nome){
	this->nome = nome;
}