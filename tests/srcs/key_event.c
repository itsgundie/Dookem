//
// Created by Hugor Chau on 7/29/20.
//

#include "../incs/test.h"

void	key_event(SDL_Event *event, data *draw) {
//	SDL_Log("User just pressed down a key!");
	if (event->key.keysym.sym == SDLK_ESCAPE)
		;
	if (event->key.keysym.sym == SDLK_RIGHT)
		draw->m->player->angle += 0.01;
	if (event->key.keysym.sym == SDLK_LEFT)
		draw->m->player->angle -= 0.01;
	if (event->key.keysym.sym == SDLK_w) {
		draw->m->player->x += cos(draw->m->player->angle) * 2;
		draw->m->player->y += sin(draw->m->player->angle) * 2;
	}
	if (event->key.keysym.sym == SDLK_s) {
		draw->m->player->x -= cos(draw->m->player->angle) * 2;
		draw->m->player->y -= sin(draw->m->player->angle) * 2;
	}
	if (inside_vp(draw->m->player->x, draw->m->player->y, draw) % 2)
		draw->m->player->inside = TRUE;
	else
		draw->m->player->inside = FALSE;
//
//	if (abs(inside_vp(draw->m->player->x, draw->m->player->y, draw) % 2) == abs(inside(draw->m->player->x, draw->m->player->y, draw) % 2)) {
//		ft_putendl("EQUALS!!!!!!!!!");
//	} else {
//		ft_putendl("NOT EQUALS!!!!!");
//	}
}
