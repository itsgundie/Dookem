//
// Created by Hugor Chau on 7/27/20.
//
#include "../incs/test.h"

void	draw_player(sdl_win *win, data *draw) {
	wall w;
	w.left.x = draw->m->player->x;
	w.left.y = draw->m->player->y;
	w.right.x = cos(draw->m->player->angle) * 15 + draw->m->player->x;
	w.right.y = sin(draw->m->player->angle) * 15 + draw->m->player->y;
	draw_line(&w, win->bmap, 0xFFFFFF00);
	(*(win->bmap))[(int)((int)draw->m->player->x + (int)draw->m->player->y * SCREEN_WIDTH) * 4 - 2 + 4] = 255;
	(*(win->bmap))[(int)((int)draw->m->player->x + (int)draw->m->player->y * SCREEN_WIDTH) * 4 - 2 - 4] = 255;
	(*(win->bmap))[(int)((int)draw->m->player->x + (int)draw->m->player->y * SCREEN_WIDTH) * 4 - 2] = 255;
	(*(win->bmap))[(int)((int)draw->m->player->x + (int)draw->m->player->y * SCREEN_WIDTH) * 4 - 2 + SCREEN_WIDTH * 4] = 255;
	(*(win->bmap))[(int)((int)draw->m->player->x + (int)draw->m->player->y * SCREEN_WIDTH) * 4 - 2 - SCREEN_WIDTH * 4] = 255;
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
	////////Here! I'm getting all potential visible walls for current sector
	get_walls_in_front(draw, &wal, &w_count);
	while (i < w_count) {
		if (wal[i].right.x != -1) {
			draw_line(&wal[i], win->bmap, 0x00000000);

//			wall check;
//			printf("Old wall: %f, %f\n", wal[i].left.x, wal[i].left.y);
//			check.left = find_new_dot(draw, &wal[i], (draw->m->player->angle - DEGREES_45));//sin(draw->m->player->angle - DEGREES_45) / cos(draw->m->player->angle - DEGREES_45));//:)
//			if (check.left.x == -1)
//				check.left = wal[i].left;
//			vertex v1;
//			v1.x = (draw->m->player->x - wal[i].right.x);
//			v1.y = (draw->m->player->y - wal[i].right.y);
//			vertex check4;
//			check4.x = (cos(draw->m->player->angle + DEGREES_45 * 2));
//			check4.y = (sin(draw->m->player->angle + DEGREES_45 * 2));
////			if (-(v1.x * check4.x + v1.y * check4.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
////														* sqrt(check4.x * check4.x + check4.y * check4.y)) > 0) {
////				printf("Is it on the right?\n");
////			}
//			printf("new wall: %f, %f\n", check.left.x, check.left.y);
//			check.right.x =  draw->m->player->x;
//			check.right.y =  draw->m->player->y;
//			draw_line(&check, win->bmap, 0x00FFFFFF);
		}
		i++;
	}



	wall w6;
	w6.left.x = draw->m->player->x + 30 * sin(draw->m->player->angle);
	w6.left.y = draw->m->player->y - 30 * cos(draw->m->player->angle);

	w6.right.x = draw->m->player->x;
	w6.right.y = draw->m->player->y;
//	draw_line(&w6, win->bmap, 0x00FFFF00);
//red vectors are FOV
	w6.left.x = draw->m->player->x + 30 * sin(draw->m->player->angle + DEGREES_45);
	w6.left.y = draw->m->player->y - 30 * cos(draw->m->player->angle + DEGREES_45);
	draw_line(&w6, win->bmap, 0x00FF0000);
	w6.left.x = draw->m->player->x - 30 * sin(draw->m->player->angle - DEGREES_45);
	w6.left.y = draw->m->player->y + 30 * cos(draw->m->player->angle - DEGREES_45);
	draw_line(&w6, win->bmap, 0x000000FF);

	if (draw->m->is_new != TRUE) {
		draw_player(win, draw);
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
