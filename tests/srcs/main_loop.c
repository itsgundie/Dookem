//
// Created by Hugor Chau on 7/27/20.
//
#include "../incs/test.h"

void	draw_player(sdl_win *win, data *draw) {
	(*(win->bmap))[(int)((int)draw->m->player->x + (int)draw->m->player->y * SCREEN_WIDTH) * 4 - 2 + 4] = 255;
	(*(win->bmap))[(int)((int)draw->m->player->x + (int)draw->m->player->y * SCREEN_WIDTH) * 4 - 2 - 4] = 255;
	(*(win->bmap))[(int)((int)draw->m->player->x + (int)draw->m->player->y * SCREEN_WIDTH) * 4 - 2] = 255;
	(*(win->bmap))[(int)((int)draw->m->player->x + (int)draw->m->player->y * SCREEN_WIDTH) * 4 - 2 + SCREEN_WIDTH * 4] = 255;
	(*(win->bmap))[(int)((int)draw->m->player->x + (int)draw->m->player->y * SCREEN_WIDTH) * 4 - 2 - SCREEN_WIDTH * 4] = 255;
}

void	draw_fov(sdl_win *win, data *draw) {
	wall w;
	w.right.x = draw->m->player->x;
	w.right.y = draw->m->player->y;

//	red vector is the right FOV, blue is left, yellow is player's direction
	w.left.x = draw->m->player->x + 30 * sin(draw->m->player->angle + DEGREES_45);
	w.left.y = draw->m->player->y - 30 * cos(draw->m->player->angle + DEGREES_45);
	draw_line(&w, win->bmap, 0x00FF0000);

	w.left.x = draw->m->player->x - 30 * sin(draw->m->player->angle - DEGREES_45);
	w.left.y = draw->m->player->y + 30 * cos(draw->m->player->angle - DEGREES_45);
	draw_line(&w, win->bmap, 0x000000FF);

	w.left.x = cos(draw->m->player->angle) * 15 + draw->m->player->x;
	w.left.y = sin(draw->m->player->angle) * 15 + draw->m->player->y;
	draw_line(&w, win->bmap, 0xFFFFFF00);
//
//	w.left.x = -sin(draw->m->player->angle) * 30 + draw->m->player->x;
//	w.left.y = cos(draw->m->player->angle) * 30 + draw->m->player->y;
//	draw_line(&w, win->bmap, 0xFF00FF00);
}

void	clear_bitmap(sdl_win *win, data *draw) {
	int i;
	wall *wal;
	wal = malloc(sizeof(wall) * ((draw->m->w_count + 1) * 2));
	int w_count = 0;
	i = 0;
	while (i < (SCREEN_WIDTH) * (SCREEN_HEIGHT) * 4) {
		(*(win->bmap))[i + 1] = 66;
		(*(win->bmap))[i] = draw->m->player->inside == TRUE ? 66 : 0;
		(*(win->bmap))[i + 2] = 0;
		(*(win->bmap))[i + 3] = 0;
		i += 4;
	}
	i = 0;
	while (i <= draw->m->w_count) {
		if (draw->m->walls[i].right.x != -1) {
			if (draw->m->walls[i].is_portal == FALSE)
				draw_line(&draw->m->walls[i], win->bmap, 0x00FFFFFF);
			else
				draw_line(&draw->m->walls[i], win->bmap, 0x00FF00FF);
		}
		i++;
	}
	i = 0;
	//Here! I'm getting all potential visible walls for current sector
	get_walls_in_front(draw, &wal, &w_count);
	while (i < w_count) {
		if (wal[i].right.x != -1) {
			draw_line(&wal[i], win->bmap, 0x00000000);
		}
		i++;
	}

	if (draw->m->is_new != TRUE) {
		draw_player(win, draw);
		draw_fov(win, draw);
	}
}

void	put_bitmap(sdl_win *win) {
	safe_call((void *)(size_t)SDL_UpdateTexture(
			win->texture,
			NULL,
			*win->bmap,
			SCREEN_WIDTH * 4
	), NULL, "Texture update failed");

	safe_call((void *)(size_t)SDL_SetRenderDrawColor( win->render, 0, 0, 0, SDL_ALPHA_OPAQUE ), NULL, "Can't clear render.");
	safe_call((void *)(size_t)SDL_RenderClear( win->render ), NULL, "Can't clear render.");
	safe_call((void *)(size_t)SDL_RenderCopy( win->render, win->texture, NULL, NULL ), NULL, "Can't clear render.");
	SDL_RenderPresent( win->render );
}

void	update_texture(sdl_win *win, data *draw) {//сделать методом?
	clear_bitmap(win, draw);
	put_bitmap(win);
}

void main_loop(sdl_win *win, sdl_win *win3d, data *draw) {
    int quit = 0;
    SDL_Event event;
    int is_pressed = FALSE;

//    int KEYS[322]; если нужно запомнить клаву, крутой пример
    while(!quit) {
        while (SDL_PollEvent(&event)) {
        	//выведение битмапы
			win->update_texture(win, draw);
			win3d->update_texture(win3d, draw);

			mouse_events(event, draw, &is_pressed);
            SDL_PumpEvents(); // обработчик событий.
            if(event.type == SDL_QUIT)
                quit=1;
            if (quit == 1) {
                SDL_DestroyWindow(win->window);
                SDL_Quit();
                exit(0);
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    quit = 1;
				key_event(&event, draw);
            }
        }
    }
	exit(0);
}
