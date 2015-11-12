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
#include <iostream>
#include <cstdlib>
#include <sstream>

void desenhaFlecha (SDL_Surface * superficie, Nodo *orig, Nodo *dest)
{
	double mi;
	double xa, ya, xb, yb;
	double alfa, beta;
	double xc, yc;
	double vx, vy;
	double modac;
	double xe, ye, xf, yf;

	xa = orig->getX();
	ya = orig->getY();
	xb = dest->getX();
	yb = dest->getY();

	alfa = (xb-xa);
	beta = (yb-ya);

	mi = 1 - (RAIO/sqrt(alfa*alfa + beta*beta));
	xc = xa + mi * alfa;
	yc = ya + mi * beta;

	vx = (xc - xa) * cos(TETA) + (yc - ya) * sin(TETA);
	vy = -(xc - xa) * sin(TETA) + (yc - ya) * cos(TETA);

	vx = -vx;
	vy = -vy;

	modac = sqrt( (xc-xa)*(xc-xa) + (yc-ya)*(yc-ya) );

	xe = xc + vx*TAMFLECHA/modac;
	ye = yc + vy*TAMFLECHA/modac;

	vx = (xc - xa) * cos(-TETA) + (yc - ya) * sin(-TETA);
	vy = -(xc - xa) * sin(-TETA) + (yc - ya) * cos(-TETA);

	vx = -vx;
	vy = -vy;

	xf = xc + vx*TAMFLECHA/modac;
	yf = yc + vy*TAMFLECHA/modac;

	filledTrigonRGBA (superficie, METADE_LARG + xe, METADE_ALT + ye, METADE_LARG + xf, METADE_ALT + yf, METADE_LARG + xc, METADE_ALT + yc, 150, 150, 150, 255);

	return;
}

void desenha(SDL_Surface * superficie, Grafo * g,bool flag,bool flagPeso)
{
	SDL_Rect ret;
	int nvertices;
	Nodo *n, *n1;
	TTF_Font* fonte = TTF_OpenFont("airstrip.ttf", 12);

	SDL_Color foregroundColor = { 200, 200, 200 };

	SDL_Surface* textSurface;

	SDL_Rect textLocation;

	ret.w = superficie->w;
	ret.h = superficie->h;
	ret.x = 0;
	ret.y = 0;

	SDL_FillRect (superficie, &ret, SDL_MapRGB(superficie->format, 0, 0, 0));

	nvertices = g->getNumeroVert();

	for (int i=0; i < nvertices; i++){

		n = g->getId(i);

		for (int j=0; j < nvertices; j++){
			if (g->adj(i, j)) {
				n1 = g->getId(j);
				if (flagPeso)
				{
					double x,y;
					stringstream peso;
					x = ((n->getX()+METADE_LARG) + (n1->getX()+METADE_LARG))/2;
					y = ((n->getY()+METADE_ALT) + (n1->getY()+METADE_ALT))/2;

					peso<< g->getPeso(i,j);

					textSurface = TTF_RenderText_Blended(fonte, peso.str().c_str(),foregroundColor);

					textLocation = { x, y, 0, 0 };

					SDL_BlitSurface(textSurface, NULL, superficie, &textLocation);
				}

				lineRGBA (superficie, n->getX() + METADE_LARG, n->getY() + METADE_ALT, n1->getX() + METADE_LARG, n1->getY() + METADE_ALT, 150, 150, 150, 255);
				desenhaFlecha (superficie, n, n1);
			}
		}

		if (flag)
		{
			textSurface = TTF_RenderText_Blended(fonte, n->getNome().c_str(), foregroundColor);
			
			textLocation = { n->getX() + ( METADE_LARG - RAIO ), n->getY() + ( METADE_ALT - RAIO - XFONTE), 0, 0 };

			SDL_BlitSurface(textSurface, NULL, superficie, &textLocation);
		}
			filledEllipseRGBA(superficie, n->getX() + 400, n->getY() + 275, RAIO, RAIO, 150, 150, 150, 255);

	}

	SDL_Flip(superficie);
	TTF_CloseFont(fonte);

	return;
}

int main(int argc, char const *argv[])
{
	string reader,read;
	
	int leitor;
	SDL_Surface * superficie;

	bool rodando = true;
	bool pronto = false;

	cin>> reader >> leitor;


	if (reader.compare("*Vertices") == 0)
	{
		Grafo *g = new Grafo(leitor);

		cin>> read;

		while (read.compare("*Arcs") != 0 && read.compare("*Edges") != 0)
		{
			leitor = atoi(read.c_str());

			cin>> reader;

			g->inserirVertice(leitor,reader);

			cin>> read;
		}

		bool flag; 
		if (read.compare("*Arcs") == 0)
		{
			g->setDirecionado(false);
			flag = false;
		}
		else
		{
			if (read.compare("*Edges") == 0)
			{
				g->setDirecionado(true);
				flag = true;

			}
			else
			{
				cout<< "Entrada Invalida "<<endl;
				return 1;
			}
		}

		cin>> read;
		while(read.compare("@") != 0)
		{
			int Id1, Id2, peso;

			Id1 = atoi(read.c_str());

			cin>> read;

			Id2 = atoi(read.c_str());

			cin>> read;

			peso = atoi(read.c_str());


			if (flag == false)
			{
				g->inserirAresta(Id1,Id2,peso);
			}
			else
			{
				g->inserirAresta(Id1,Id2,peso);
				g->inserirAresta(Id2,Id1,peso);
			}
			cin>> read;
		}

		g->inserirAresta(0,0,INT_MIN);
		SDL_Init (SDL_INIT_EVERYTHING);
		TTF_Init();
		superficie = SDL_SetVideoMode (LARGURA, ALTURA, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
		bool flag2 = false;
		bool flag3 = false;
		while(rodando) {
			SDL_Event evento;
			SDL_PollEvent(&evento);
			if (!pronto) {
				pronto = !g->calcula();
				desenha (superficie, g,flag2,flag3);
			} else {
				SDL_Delay(1);
			}
			if (evento.type == SDL_QUIT) {
				SDL_FreeSurface(superficie);
				SDL_Quit();
				rodando = 0;
			} else {
				if (evento.type == SDL_KEYDOWN)
				{
					if (evento.key.keysym.sym == SDLK_n)
					{
						SDL_Delay(150);
						flag2 = !flag2;
						pronto = false;
					}
					if (evento.key.keysym.sym == SDLK_p)
					{
						SDL_Delay(150);
						flag3 = !flag3;
						pronto = false;
					}
				}
			}
		}
	}
	return 0;
}