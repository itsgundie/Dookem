//
// Created by Hugor Chau on 7/28/20.
//

#ifndef TESTS_ERROR_H
#define TESTS_ERROR_H

#define INIT_SDL_TEXTURE	SDL_CreateTexture(init->render, \
							SDL_PIXELFORMAT_ARGB8888, \
							SDL_TEXTUREACCESS_STREAMING, \
							SCREEN_WIDTH, SCREEN_HEIGHT), \
							NOT_NULL, "SDL-texture init failed."
#define INIT_SDL_RECT		(SDL_Rect *)malloc(sizeof(SDL_Rect)), \
							NOT_NULL, "Crashed malloc at making rect!"
#define INIT_PIXELS			malloc(((SCREEN_HEIGHT) * \
							(SCREEN_WIDTH) * 4) * sizeof(unsigned char)), \
							NOT_NULL, "Crashed malloc at making bitmap!"
#define INIT_SDL_RENDER		SDL_CreateRenderer(window, -1, \
							SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC), \
							NOT_NULL, "SDL-renderer init failed."
#define INIT_SDL_WINDOW		SDL_CreateWindow(name, SCREEN_WIDTH, 200, SCREEN_WIDTH, SCREEN_HEIGHT, \
							SDL_WINDOW_SHOWN), NOT_NULL, "SDL-window init failed."
#define INIT_3D_SDL_WINDOW	SDL_CreateWindow(name, SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT, \
							SDL_WINDOW_SHOWN), NOT_NULL, "SDL-window init failed."
#define INIT_SDL			(void *)(size_t)(SDL_Init( SDL_INIT_EVERYTHING )), \
							NULL, "SDL init failed."
//
//#define CAT(X,Y) X##_##Y
//#define TEMPLATE(X,Y) CAT(X,Y)
///*		single generic pattern		*/
//#ifdef T
//#undef T
#endif
//#define T float
//#ifdef T
//#define CAT(X,Y) X##_##Y
//#define TEMPLATE(X,Y) CAT(X,Y)
//void TEMPLATE(safe_call,T)(char *error, ...);
//#endif
//
//#ifdef T
//#undef T
//#endif
//#define T double
//#ifdef T
//#define CAT(X,Y) X##_##Y
//#define TEMPLATE(X,Y) CAT(X,Y)
//void TEMPLATE(safe_call,T)(char *error, ...);
//#endif
//
//#ifdef T
//#undef T
//#endif
//#define T int
//#ifdef T
//#define CAT(X,Y) X##_##Y
//#define TEMPLATE(X,Y) CAT(X,Y)
//void TEMPLATE(safe_call,T)(char *error, ...);
//#endif
//
//#ifdef T
//#undef T
//#endif
//#define T void
//#ifdef T
//#define CAT(X,Y) X##_##Y
//#define TEMPLATE(X,Y) CAT(X,Y)
//void TEMPLATE(safe_call,T)(char *error, ...);
//#endif
//
//#endif //TESTS_ERROR_H
