#include <time.h>
void setwindow(SDL_Window **window)
{
	*window = SDL_CreateWindow(
		NAME,					           // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		windowwidth,                       // width, in pixels
		windowheight,                      // height, in pixels
		SDL_WINDOW_OPENGL                  // flags
	);
	if (*window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		exit(-1);
	}
}


void setstate(){
	for (int i = 0; i < ROWCOUNT; i++)
		for (int j = 0; j < COLCOUNT; j++)
		table[i][j].state = unchecked;
	}

void printoutlines()
{
	SDL_SetRenderDrawColor(renderer, 71, 188, 112, SDL_ALPHA_OPAQUE);
	for (int i = SPACES; i <= ROWSIZE; i += SPACES)
	{
		SDL_RenderDrawLine(renderer, SPACES, i, COLSIZE, i);
		//SDL_RenderDrawLine(renderer, SPACES, i+1, COLSIZE, i+1);
	}
	for (int i = SPACES; i <= COLSIZE; i += SPACES)
	{
		SDL_RenderDrawLine(renderer, i, SPACES, i, ROWSIZE);
		//SDL_RenderDrawLine(renderer, i+1, SPACES, i+1, ROWSIZE);
	}
	SDL_RenderPresent(renderer);
}


void setbombs()
{
	int count = 0;
	start:
	for (int i = 0; i < ROWCOUNT; i++){
		for (int j = 0; j < COLCOUNT; j++) {
			if (count < BombCount&&rand() % 10 == 0) {
				table[i][j].surround = Bomb;
				count++;
			}
			if (count == BombCount)
				break;
		}
	}
	if (count < BombCount)
		goto start;
}

void checksaround0(int indexx,int indexy)
{
	state tmp;
	//upleft
	if (indexy - 1 >= 0 && indexx - 1 >= 0) {
		tmp = table[indexy - 1][indexx - 1].state;
		table[indexy - 1][indexx - 1].state = checked;
		if (table[indexy - 1][indexx - 1].surround == 0&& tmp == unchecked)
			checksaround0(indexx - 1,indexy - 1);
		
	}
	//up
	if (indexy - 1 >= 0) {
		tmp = table[indexy - 1][indexx].state;
		table[indexy - 1][indexx].state = checked;
		if (table[indexy - 1][indexx].surround == 0&& tmp == unchecked)
			checksaround0(indexx, indexy - 1);
		
	}
	//upright
	if (indexy - 1 >= 0 && indexx + 1 < COLCOUNT) {
		tmp = table[indexy - 1][indexx + 1].state;
		table[indexy - 1][indexx + 1].state = checked;
		if (table[indexy - 1][indexx + 1].surround == 0&& tmp == unchecked)
			checksaround0(indexx + 1, indexy - 1);
		
	}
	//left
	if (indexx - 1 >= 0) {
		tmp = table[indexy][indexx - 1].state;
		table[indexy][indexx - 1].state = checked;
		if (table[indexy][indexx - 1].surround == 0&& tmp ==unchecked)
			checksaround0(indexx - 1, indexy);
		
	}
	//right
	if (indexx + 1 < COLCOUNT) {
		tmp = table[indexy][indexx + 1].state;
		table[indexy][indexx + 1].state = checked;
		if (table[indexy][indexx + 1].surround == 0&& tmp == unchecked)
			checksaround0(indexx + 1, indexy);
		
	}
	//downleft
	if (indexx - 1 >= 0 && indexy + 1 < ROWCOUNT) {
		tmp = table[indexy + 1][indexx - 1].state;
		table[indexy + 1][indexx - 1].state = checked;
		if (table[indexy + 1][indexx - 1].surround == 0&& tmp == unchecked)
			checksaround0(indexx - 1, indexy + 1);
		
	}
	//down
	if (indexy + 1 < ROWCOUNT) {
		tmp = table[indexy + 1][indexx].state;
		table[indexy + 1][indexx].state = checked;
		if (table[indexy + 1][indexx].surround == 0&& tmp == unchecked)
			checksaround0(indexx, indexy + 1);
		
	}
	//downright
	if (indexy + 1 < ROWCOUNT && indexx + 1 < COLCOUNT) {
		tmp = table[indexy + 1][indexx + 1].state;
		table[indexy + 1][indexx + 1].state = checked;
		if (table[indexy + 1][indexx + 1].surround == 0&& tmp == unchecked)
			checksaround0(indexx + 1, indexy + 1);
		
	}
}


void check3(int indexy,int indexx)
{
	int count = 0;
			//upleft
			if(indexy - 1 >= 0 && indexx - 1 >= 0)
			if (table[indexy - 1][indexx - 1].surround == Bomb)
				count++;
			//up
			if(indexy - 1 >= 0)
			if (table[indexy - 1][indexx].surround == Bomb)
				count++;
			//upright
			if(indexy - 1 >= 0 && indexx + 1 < COLCOUNT)
			if (table[indexy - 1][indexx + 1].surround == Bomb)
				count++;
			//left
			if(indexx - 1 >= 0)
			if (table[indexy][indexx - 1].surround == Bomb)
				count++;
			//right
			if(indexx + 1 < COLCOUNT)
			if (table[indexy][indexx + 1].surround == Bomb)
				count++;
			//downleft
			if(indexx - 1 >= 0 && indexy + 1 < ROWCOUNT)
			if (table[indexy + 1][indexx - 1].surround == Bomb)
				count++;
			//down
			if(indexy + 1 < ROWCOUNT)
			if (table[indexy + 1][indexx].surround == Bomb)
				count++;
			//downright
			if(indexy + 1 < ROWCOUNT && indexx + 1 < COLCOUNT)
			if (table[indexy + 1][indexx + 1].surround == Bomb)
				count++;
			table[indexy][indexx].surround = count;


}

void printit()
{
	for (int i = 0; i < ROWCOUNT; i++) {
		for (int j = 0; j < COLCOUNT; j++) {
			printf("%d ", table[i][j].surround);
		}
		printf("\n");
	}
}


void checksuround()
{
	for (int i = 0; i < ROWCOUNT; i++){
		for (int j = 0; j < COLCOUNT; j++) {
			if (table[i][j].surround == Bomb)
				continue;
			else
				check3(i, j);
		}
	}
}


void setsurround0()
{
	for (int i = 0; i < ROWCOUNT; i++)
		for (int j = 0; j < COLCOUNT; j++) {

			table[i][j].surround = 0;
		}

}

void setpos()
{
	int copyx = MARGIN;
	int copyy = MARGIN;
	for (int i = 0; i < ROWCOUNT; i++) {
		copyx = MARGIN;
		for (int j = 0; j < COLCOUNT; j++) {
			table[i][j].fromx = copyx + 1;
			table[i][j].fromy = copyy + 1;
			table[i][j].tox = copyx + SPACES - 1;
			table[i][j].toy = copyy + SPACES - 1;
			copyx += SPACES;

		}
		copyy += SPACES;
	}
}

void render1(int x,int y)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x, y + 10, x, y - 10);
	SDL_RenderDrawLine(renderer, x, y - 10, x - 4, y - 3);
	SDL_RenderDrawLine(renderer, x + 5, y + 10, x - 5, y +10);
	SDL_RenderPresent(renderer);
}

void render2(int x, int y)
{
	SDL_SetRenderDrawColor(renderer, 139, 54, 150, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x - 5, y - 10, x + 5, y - 10);
	SDL_RenderDrawLine(renderer, x + 5, y - 10, x + 5, y     );
	SDL_RenderDrawLine(renderer, x + 5, y     , x - 5, y     );
	SDL_RenderDrawLine(renderer, x - 5, y     , x - 5, y + 10);
	SDL_RenderDrawLine(renderer, x - 5, y + 10, x + 5, y + 10);
	SDL_RenderPresent(renderer);
}

void render3(int x, int y)
{
	SDL_SetRenderDrawColor(renderer, 201, 25, 16, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x + 5, y - 10, x + 5, y + 10);
	SDL_RenderDrawLine(renderer, x + 5, y + 10, x - 5, y + 10);
	SDL_RenderDrawLine(renderer, x + 5, y     , x - 5, y    );
	SDL_RenderDrawLine(renderer, x + 5, y - 10, x - 5, y - 10);
	SDL_RenderPresent(renderer);
}

void rendernums(int x, int y, int n)
{
	switch (n)
	{
	case 1:
		render1(x,y);
		break;
	case 2:
		render2(x, y);
		break;
	case 3:
		render3(x, y);
		break;
	case 0:
		break;
	default:
		printf("ERROR NUMS\n");
		break;
	}
}


void drawflagbox(int x,int y)
{
	int bam=1, bum=10;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x,y+10,x,y-10);
	SDL_RenderDrawLine(renderer, x-5, y + 11, x+5, y + 11);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	for (; bam < 10 && bum >= 5; bam++, bum--) {
		SDL_RenderDrawLine(renderer, x - bam, y - bum, x - bam, y -(bam-1));
	}
	SDL_RenderPresent(renderer);
}


void renderboxes()
{
	
	SDL_Rect rect;
	for (int i = 0; i < ROWCOUNT; i++) {
		for (int j = 0; j < COLCOUNT; j++) {
			if (table[i][j].state==unchecked){
				SDL_SetRenderDrawColor(renderer, 158, 155, 151, SDL_ALPHA_OPAQUE);
				rect.x = table[i][j].fromx;
				rect.y = table[i][j].fromy;
				rect.h = table[i][j].toy - table[i][j].fromy;
				rect.w = table[i][j].tox - table[i][j].fromx;
				SDL_RenderDrawRect(renderer, &rect);
				SDL_RenderFillRect(renderer, &rect);
			}
			else if (table[i][j].state == checked&& table[i][j].surround==Bomb){
				printf("You Lost\n");
			}
			else if (table[i][j].state == checked) {
				SDL_SetRenderDrawColor(renderer, 216, 214, 210, SDL_ALPHA_OPAQUE);
				rect.x = table[i][j].fromx;
				rect.y = table[i][j].fromy;
				rect.h = table[i][j].toy - table[i][j].fromy;
				rect.w = table[i][j].tox - table[i][j].fromx;
				SDL_RenderDrawRect(renderer, &rect);
				SDL_RenderFillRect(renderer, &rect);
				SDL_RenderPresent(renderer);
				rendernums((table[i][j].fromx) + (SPACES / 2), (table[i][j].fromy) + (SPACES / 2),table[i][j].surround);
			}
			else if (table[i][j].state == flagged) {
				drawflagbox((table[i][j].fromx)+(SPACES/2), (table[i][j].fromy)+(SPACES/2));
			}
		}
	}
	SDL_RenderPresent(renderer);
}


void checkfor3()
{
	int bam;
	while (1) {
		bam = 0;
		for (int i = 0; i < ROWCOUNT; i++)
			for (int j = 0; j < COLCOUNT; j++) {
				if (table[i][j].surround > 3)
				{
					setsurround0();
					setbombs();
					checksuround();
					bam = 1;
				}
			}
		if (bam == 0)
			break;
	}
}

bool getindexofcoord(int x,int y,int *reelx,int *reely)
{
	for (int i = 0; i < ROWCOUNT; i++)
		for (int j = 0; j < COLCOUNT; j++) {
			if (table[i][j].fromx<=x&& table[i][j].tox>=x&& table[i][j].fromy<=y&& table[i][j].toy>=y){
				*reelx = j;
				*reely = i;
				return true;
			}
		}
	return false;
}

void printbomb(int x, int y)
{
	SDL_Rect rect;
	SDL_SetRenderDrawColor(renderer, 216, 214, 210, SDL_ALPHA_OPAQUE);
	rect.x = x - SPACES / 2 + 1;
	rect.y = y - SPACES / 2 + 1;
	rect.h = SPACES - 3;
	rect.w = SPACES - 3;
	SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderPresent(renderer);
	//actual bomb
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x, y - 5, x, y + 5);
	SDL_RenderDrawLine(renderer, x + 5, y, x - 5, y);
	SDL_RenderDrawLine(renderer, x + 4, y - 4, x - 4, y + 4);
	SDL_RenderDrawLine(renderer, x - 4, y - 4, x + 4, y + 4);
	SDL_RenderPresent(renderer);
}

void printeverybomb()
{
	int x, y;
	for (int i = 0; i < ROWCOUNT; i++)
		for (int j = 0; j < COLCOUNT; j++) {
			if (table[i][j].surround == Bomb){
				printbomb(table[i][j].fromx+SPACES/2, table[i][j].fromy+SPACES/2);
			}

		}
}





void initgame()
{
	srand(time(NULL));
	setstate();
	setsurround0();
	setbombs();
	checksuround();
	checkfor3();
	setpos();
	renderboxes();
	printit();
}


