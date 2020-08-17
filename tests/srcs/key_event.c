//
// Created by Hugor Chau on 7/29/20.
//

#include "../incs/test.h"

void	key_event(SDL_Event *event, data *draw) {
//	SDL_Log("User just pressed down a key!");
	vertex new_move;
	new_move.x = draw->m->player->x;
	new_move.y = draw->m->player->y;
	if (draw->m->player->inside == -1) {
		if (inside_vp(draw->m->player->x, draw->m->player->y, draw) % 2)
			draw->m->player->inside = TRUE;
		else
			draw->m->player->inside = FALSE;
	}
	if (event->key.keysym.sym == SDLK_ESCAPE)
		;
	if (event->key.keysym.sym == SDLK_RIGHT)
		draw->m->player->angle += 0.1;
	if (event->key.keysym.sym == SDLK_LEFT)
		draw->m->player->angle -= 0.1;
	if (event->key.keysym.sym == SDLK_w) {
		new_move.x = draw->m->player->x + cos(draw->m->player->angle) * 2;
		new_move.y = draw->m->player->y + sin(draw->m->player->angle) * 2;
	}
	if (event->key.keysym.sym == SDLK_s) {
		new_move.x = draw->m->player->x - cos(draw->m->player->angle) * 2;
		new_move.y = draw->m->player->y - sin(draw->m->player->angle) * 2;
	}
	if (inside_vp(new_move.x, draw->m->player->y, draw) % 2 == draw->m->player->inside) {
		draw->m->player->x = new_move.x;
//		draw->m->player->y = new_move.y;
		}
	if (inside_vp(draw->m->player->x, new_move.y, draw) % 2 == draw->m->player->inside) {
		draw->m->player->y = new_move.y;
//		draw->m->player->y = new_move.y;
	}
//	else
//		draw->m->player->inside = FALSE;
//
//	if (abs(inside_vp(draw->m->player->x, draw->m->player->y, draw) % 2) == abs(inside(draw->m->player->x, draw->m->player->y, draw) % 2)) {
//		ft_putendl("EQUALS!!!!!!!!!");
//	} else {
//		ft_putendl("NOT EQUALS!!!!!");
//	}
}
