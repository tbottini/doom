#include "SDL2/SDL.h"
#include "wolf3d.h"
//#include "SDL_image.h"


uint32_t	color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int			error_iret(char *msg, int ret)
{
	ft_putendl(msg);
	return (ret);
}

int		main(void)
{
	SDL_Window *window = NULL;
	SDL_Window *window2 = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture	*texture;
	//SDL_Color bleu = {0, 255, 255, 255};

	ft_putendl("hello");
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		error_iret("error init sdl", 0);
	window = SDL_CreateWindow("WOLF3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 1200, SDL_WINDOW_SHOWN);
	if (!window)
		error_iret("error create window 1", 0);
	window2 = SDL_CreateWindow("TEST de deuxieme fenetre", 0, 0, 400, 1200, SDL_WINDOW_RESIZABLE);
		error_iret("error create window 2", 0);
	if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		ft_putendl("error to create renderer accelerate");
	else if (!renderer && !(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC)))
		error_iret("error create renderer", 0);
	//le render gere le visuel
	//renderer sofware : rendu logiciel CPU / Memoire vive
	//renderer accelerated : memoire video et gpu
	//renderer presentvsync : syncro rafraichissement video
	//SDL_SetRenderDrawColor(renderer,255,200,255,255);
    //DL_RenderClear(renderer);
    //DL_RenderPresent(renderer);
	if (0 != SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255))
		error_iret("RenderDrawColor Window1", 0);
	//on change toute la couleur
	if (SDL_RenderClear(renderer) < 0)
		error_iret("RenderClear Window1", 0);

	/* ----SDL_Create Texture---- */
	//format SDL_PIXELFORMAT_RGBA8888 4 * 255
	//access changement rare unlockable, changement frequent et lockable, utiliser en rendu...
	//SDL_TEXTUREACCESS_{STATIC, STREAMING, TARGET}
	//w et h size
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
	 SDL_TEXTUREACCESS_TARGET, 450, 1200);
	if (!texture)
		return (0);


	/*
	*	on cible la texture sur le rendu
	*	pour pouvoir le modifier
	*	on remet le render en cible de rendu
	*/
	//on modifie la texture que l'on affichera
	SDL_Rect rect = {10, 50, 100, 1000};
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	//on choisie un rectangle de modification dans la texture, on choisie une couleur pour la modification
	//de cette texture
	//on pointe le render sur la texture puis sdl render fill rect va remplir avec la rendu la texture
	//donc va remplir avec la couleur verte la texture
	//puis on va supprimer la liaison sdl et texture
	if (SDL_SetRenderTarget(renderer, texture) < 0)
		return (0);
	SDL_RenderFillRect(renderer, &rect);
	//affichage texture violette
	if (SDL_SetRenderTarget(renderer, NULL) < 0)
		return (0);

	SDL_Texture *actualTexture;
	//recupere la texture
	actualTexture = SDL_GetRenderTarget(renderer);
	if (actualTexture == NULL)
		ft_putendl("pas de texture de rendu, direct sur le rendu");
	else
		ft_putendl("texture de rendu presente");


	/*	sur quelle rendu on agit
	*	on copy quelle texture
	*	srcrect rectangle quelle partie prendre si NULL on prend tous
	*	dstrect ou la mettre, si NULL on remplit tous
	*/
	if (SDL_RenderCopy(renderer, texture, NULL, &rect) < 0)
		error_iret("error cpy", 0);

	SDL_RenderPresent(renderer);
	/*
	le rendu sera un fond rouge pour avec le render
	avec un carre noire pour la couleur standard
	*/

	//Texture gpu
	//Surface cpu
	//sdlsurface (flag, w, h, depth (bit/pixel), 4xfiltres rgba)
	SDL_Surface *surface;
	SDL_Rect rect2 = {100, 100, 200, 200};

	surface = SDL_CreateRGBSurface(0, 600, 600, 32, 0, 0 ,0, 0);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 255, 0));
	//SDL_MapRGB pour mettre sur le meme format de pixel

	//permet de coller sur une surface sur une autre surface2 si on a une autre surface
	//SDL_BlitSurface(surface, NULL, , &rect2);

	//creer une texture depuis une surface
	SDL_Texture *textureFromSurface;
	textureFromSurface = SDL_CreateTextureFromSurface(renderer, surface);
	if (!textureFromSurface)
		error_iret("bad translation to texure", 0);


	//! SetRenderDrawColor parametre la couleur pour dessiner
	//! SDL_RenderClear remplace l'ecran par la couleur choisie
	//! Show the new content




	SDL_SetRenderTarget(renderer, textureFromSurface);
	SDL_RenderFillRect(renderer, &rect2);
	SDL_SetRenderTarget(renderer, NULL);

	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_RenderPresent(renderer);


	//renvoie un uint32 d'une valeur rgba dans un format de couleur precis
	SDL_MapRGBA(SDL_PIXELFORMAT_RGBA8888, 255, 255, 255, 255);

	//obtenir un tableau de texture seule
	SDL_LockTexture(texture, NULL, **tableau de pixel, pitch longueur d une ligne);

	SDL_Delay(4000);


	//supression des elements
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyWindow(window2);
	SDL_Quit();
	return (0);
}
