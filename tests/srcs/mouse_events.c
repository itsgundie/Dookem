//
// Created by Hugor Chau on 7/29/20.
//
#include "../incs/test.h"

void	mouse_events(SDL_Event event, data *draw, int *is_pressed) {
	if (draw->m->is_new == FALSE)
		return;
	if (event.type == SDL_MOUSEMOTION && *is_pressed == TRUE) {
		draw->m->walls[draw->m->w_count].right.x = event.button.x;
		draw->m->walls[draw->m->w_count].right.y = event.button.y;
	}
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		if (draw->m->is_new == FALSE || *is_pressed == TRUE)
			return;
		if (draw->m->w_count > 0) {
			draw->m->walls[draw->m->w_count].left.x = draw->m->walls[draw->m->w_count - 1].right.x;
			draw->m->walls[draw->m->w_count].left.y = draw->m->walls[draw->m->w_count - 1].right.y;
			draw->m->walls[draw->m->w_count].right.x = -1;
		} else {
			draw->m->walls[draw->m->w_count].left.x = event.button.x;
			draw->m->walls[draw->m->w_count].left.y = event.button.y;
			draw->m->walls[draw->m->w_count].right.x = -1;
		}
		*is_pressed = TRUE;
		SDL_Log("OOOOOOOOOOOOOO");
	}
	if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
		draw->m->walls[draw->m->w_count].right.x = event.button.x;
		draw->m->walls[draw->m->w_count].right.y = event.button.y;
		draw->m->w_count++;
		*is_pressed = FALSE;
		if (draw->m->is_new == FALSE)
			return;
		SDL_Log("NOOOOOOOOOOOOO!");
	}
}