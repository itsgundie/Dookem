//
// Created by Hugor Chau on 7/27/20.
//
#include "../incs/test.h"
void init_rect(sdl_win *init) {
    SDL_Rect *background_RECT;//img-size
	background_RECT = safe_call(INIT_SDL_RECT);
    background_RECT->x = 0;
    background_RECT->y = 0;
    background_RECT->w = SCREEN_WIDTH;
    background_RECT->h = SCREEN_HEIGHT;
	init->rect = background_RECT;
}

//void init_surface(sdl_win *init) {
//	SDL_Surface		*surface;
//	surface = (SDL_Surface *)malloc(sizeof(SDL_Surface));
//}

void init_texture(sdl_win *init) {
	init->texture = safe_call(INIT_SDL_TEXTURE);
	unsigned char **pixels;
	pixels = (unsigned char **)safe_call(malloc(sizeof(unsigned char *)), NOT_NULL, "malloc crashed, watch out!");
	*pixels = safe_call(INIT_PIXELS);
	init->bmap = pixels;
//	init->bitmap = *pixels;


//	if (SDL_UpdateTexture(
//			init->texture,
//			NULL,
//			pixels,
//			SCREEN_WIDTH * 4
//	) != 0)
//		return;
	safe_call((void *)(size_t)SDL_SetRenderDrawColor( init->render, 0, 0, 0, SDL_ALPHA_OPAQUE ), NULL, "Can't clear render.");
	safe_call((void *)(size_t)SDL_RenderClear( init->render ), NULL, "Can't clear render.");
	safe_call((void *)(size_t)SDL_RenderCopy( init->render, init->texture, NULL, NULL ), NULL, "Can't clear render.");
	SDL_RenderPresent( init->render );
}

void init_window(sdl_win *init, char *name) {
	safe_call(INIT_SDL);
	SDL_Window* window = safe_call(INIT_SDL_WINDOW);

	init->render = safe_call(INIT_SDL_RENDER);
	init_rect(init);
//    init_surface(init);
	init_texture(init);
	init->update_texture = &update_texture;
}
