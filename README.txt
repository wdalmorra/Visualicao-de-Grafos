Para compilar é necessário executar o make e executar o arquivo "vg" sem as aspas.
	exemplo:
		make
		./vg

É necessário ter as bibliotecas SDL, SDL_gfx e SDL_ttf.

Comando para instalar as bibliotecas extras:
	apt-get install libsdl1.2-4 libsdl1.2-dev libsdl-gfx1.2-dev libsdl-ttf2.0-0 libsdl-ttf2.0-dev

Não foi testado para grafos desconectados.
Pode levar vários minutos para grafos com centenas de nodos.
É necessária a existência do caracter '@' no final do arquivo.

Foi adicionado duas funções extras onde apertando a tecla 'n' é exibido o nome dos vértices e apertando
a tecla 'p' é exibido o peso das arestas.