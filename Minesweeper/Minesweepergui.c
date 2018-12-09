#include "sweeper.h"
#include "windowsweeper.h"


int printmainmenu(SDL_Surface* screen)
{
	SDL_Event event;
	TTF_Font* font;
	font = TTF_OpenFont("Angelow.ttf", 30);
	int x, y;
	const char* labels[2] = { "Start Game","Exit" };
	SDL_Surface* menus[2];
	bool selected[2] = { 0,0 };
	SDL_Color color[2] = { { 255,255,255 }, { 255,0,0 } };
	menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
	menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
	SDL_Rect pos[2];
	pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
	pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
	pos[1].y = screen->clip_rect.h / 2 + menus[0]->clip_rect.h;
	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

	bool menurun = true;
	while (menurun) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type)
			{
			case SDL_QUIT:
				SDL_FreeSurface(menus[0]);
				SDL_FreeSurface(menus[1]);
				return 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;

				for (int i = 0; i < 2; i += 1){
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
						if (!selected[i]){
							selected[i] = 1;
							SDL_FreeSurface(menus[i]);
							menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
						}
					}
					else {
						if (selected[i])
						{
							selected[i] = 0;
							SDL_FreeSurface(menus[i]);
							menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
						}
					}

				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < 2; i += 1) {
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h){
						SDL_FreeSurface(menus[0]);
						SDL_FreeSurface(menus[1]);
						return i;
					}
				}
				break;
			default:
				break;
			}


		}
		SDL_BlitSurface(menus[0], NULL, screen, &pos[0]);
		SDL_BlitSurface(menus[1], NULL, screen, &pos[1]);
		

	}


	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);

}


int main(int agrc, char *agrv[])
{
	while (1) {
		printf("Enter how many bomb you want between 8 and 25:");
		scanf_s("%d,\n", &BombCount);
		if (BombCount < 8 || BombCount>25)
			printf("Error invalid bomb count enter again\n");
		else
			break;
	}


	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Couldn't init sdl error code:%s\n", SDL_GetError());
		return -1;
	}
	if (TTF_Init() < 0) {
		printf("Couldn't init ttf Error Code:%s\n", TTF_GetError());
		return -1;
	}
	SDL_Window *window;
	//count
	setcounts();
	//settig the window
	setwindow(&window);
	//setting the arrays
	setarrays();


	/*
	SDL_Surface *screen;
	screen = SDL_GetWindowSurface(window);
	if (printmainmenu(screen) == 1) {
		exit(1);
	}
	*/



	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_bool running = SDL_TRUE;
	initgame();
	int x, y,flagcount=0,reelflagcount=0;
	SDL_Event event;
	while (running)
	{
		printoutlines();
		//printf("%d\n", table[0][0].state);


		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT)
				running = SDL_FALSE;
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				printf("\nLeft Mouse pos x:%d  Mouse pos y:%d", event.motion.x, event.motion.y);
				if (getindexofcoord(event.motion.x, event.motion.y, &x, &y)) {
					printf("x:%d   y:%d\n", x, y);
					if(table[y][x].state != flagged)
						table[y][x].state = checked;
					
					
					if (table[y][x].surround == 0) {
						table[y][x].state = checked;
						checksaround0(x,y);
					}

					if (table[y][x].surround == Bomb&&table[y][x].state != flagged) {
						printf(".....You Lost....\a\n");
						printeverybomb();
						SDL_Delay(2000);
						exit(1);
					}
						
					renderboxes();
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
				printf("\nRight Mouse pos x:%d  Mouse pos y:%d", event.motion.x, event.motion.y);
				if (getindexofcoord(event.motion.x, event.motion.y, &x, &y)) {
					printf("x:%d   y:%d\n", x, y);
					if (table[y][x].state == unchecked) {
						table[y][x].state = flagged;
						flagcount++;
						if (table[y][x].surround==Bomb)
							reelflagcount++;
						if (flagcount == BombCount&&flagcount==reelflagcount) {
							printf("...You Won...\n");
							SDL_Delay(3000);
							exit(1);
						}
					}
					else if (table[y][x].state == flagged) {
						table[y][x].state = unchecked;
						flagcount--;
						if (table[y][x].surround == Bomb)
							reelflagcount--;
					}
					renderboxes();
				}
			}
		}
	}



		
	


	SDL_Delay(1000);



	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	return 0;
}


