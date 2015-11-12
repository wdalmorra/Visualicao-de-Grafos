
##	Universidade Federal de Pelotas
##	Centro de Desenvolvimento Tecnologico - CDTec
##	Bacharelado em Ciência da Computação
##
##	Estruturas de Dados 2 - 2012/2
##
##	Professor Ricardo Matsumura Araújo
##
##	Algoritmo de Visualização de Grafos
##
##	Alunos:
##		Lucas Mendonça de Souza Xavier		11105053
##		William Dalmorra de Souza		11100360

vg: GrafoMain.o Grafo.o
	g++ -o vg GrafoMain.o Grafo.o -lSDL -lSDL_gfx -lSDL_ttf

GrafoMain.o: GrafoMain.cpp Grafo.h
	g++ -c GrafoMain.cpp

Grafo.o: Grafo.cpp Grafo.h
	g++ -c Grafo.cpp

clean:
	rm *.o vg
