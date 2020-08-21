//
// Created by Hugor Chau on 8/20/20.
//
#include "../incs/test.h"

void	wall_delineation(wall *w_origin, sdl_win *win, data *draw) {
	wall w;
	wall w1;
	wall w2;
	wall w3;
	wall w4;

	w.right = change_dot(draw, w_origin->right, w_origin);
	w.left = change_dot(draw, w_origin->left, w_origin);
	if (w.left.x < 0 || w.right.x < 0)
		return;

	//1) найти координаты левой точки
	float w_h = wall_h(w.left, 40, draw->m->player);
	w1.left.y = (float) SCREEN_HEIGHT / 2 - w_h;
	w1.right.y = (float) SCREEN_HEIGHT / 2 + w_h;

	w1.left.x = (float) SCREEN_WIDTH * find_angle(draw, w.left);
	w1.right.x = w1.left.x;

	w_h = wall_h(w.right, 40, draw->m->player);
	w2.left.y = ((float)SCREEN_HEIGHT / 2 - w_h);
	w2.right.y = ((float)SCREEN_HEIGHT / 2 + w_h);
	w2.left.x = (float)SCREEN_WIDTH * find_angle(draw, w.right);
	w2.right.x = w2.left.x;
	w3.left = w1.left;
	w3.right = w2.left;
	w4.left = w1.right;
	w4.right = w2.right;
	w_h = wall_h(w.left, 40, draw->m->player);// / cos(DEGREES_45);
	draw_line(&w1, win->bmap, 0x00FF00FF);
	draw_line(&w2, win->bmap, 0x00FF00FF);
	draw_line(&w3, win->bmap, 0x00FF00FF);
	draw_line(&w4, win->bmap, 0x00FF00FF);
}