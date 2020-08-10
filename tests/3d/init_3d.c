//
// Created by Hugor Chau on 8/4/20.
//

#include "../incs/test.h"

sdl_win		*init_3D() {
	sdl_win *win = safe_call(malloc(sizeof(sdl_win)), NOT_NULL, "Malloc crashed."
																"SDL-structs container was not allocated.");
	init_window(win, WIN_3D);
	win->update_texture = &update_3D_image;
	return (win);
}