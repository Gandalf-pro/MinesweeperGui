#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_ttf.h"
SDL_Renderer *renderer;
SDL_Window *window;

#define RED 1
#define WHITE 0



int ROWCOUNT = 10;
int COLCOUNT = 10;
int ROWSIZE;
int COLSIZE;




//how big boxes are
#define SPACES 40
#define MARGIN SPACES



//windows dimensions
int windowwidth = 640;
int windowheight = 480;


#define NAME "Minesweeper"
int BombCount = 12;
#define Bomb -20

typedef enum state {
	unchecked,checked,flagged
}state;


void setcounts()
{
	ROWSIZE = (ROWCOUNT+1) * SPACES;
	COLSIZE = (COLCOUNT+1) * SPACES;
}

typedef struct cellstate {
	int fromx, fromy,tox,toy;
	state state;
	int surround;
}cellstates;

cellstates **table;


void setarrays()
{
	//table = (cellstates*) malloc(ROWCOUNT * COLCOUNT * sizeof(cellstates));
	table = malloc(ROWCOUNT* sizeof(cellstates *));
	for (int i = 0; i < COLCOUNT; i++)
	{
		table[i] = malloc(COLCOUNT * sizeof(cellstates));
	}
}

