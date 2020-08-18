//
// Created by Hugor Chau on 8/17/20.
//

#include "../incs/test.h"


float	find_angle(data *draw, vertex w1) {
	vertex v1;
	v1.x = (draw->m->player->x - w1.x);
	v1.y = (draw->m->player->y - w1.y);
	vertex v2;
	v2.x = (cos(draw->m->player->angle + DEGREES_45));
	v2.y = (sin(draw->m->player->angle + DEGREES_45));
	float res = (-(v1.x * v2.x + v1.y * v2.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
												 * sqrt(v2.x * v2.x + v2.y * v2.y))) - 0.2;
	return res / cos(res);
}

vertex	find_new_dot(data *draw, wall *w, float angle) {
	vertex res;

	vertex v1 = w->left.x <= w->right.x ? w->left : w->right;
	vertex v2 = w->left.x <= w->right.x ? w->right : w->left;

	if (fabs(sin(angle)) <= 0.00001 || fabs(cos(angle)) <= 0.00001)
		angle += 0.001;
	float px1 = cos(angle) > 0 ? draw->m->player->x : draw->m->player->x + cos(angle);
	float py1 = cos(angle) > 0 ? draw->m->player->y : draw->m->player->y + sin(angle);

	float a1 = tan(angle);
	float a2 = ((-v2.y + v1.y) / (-v2.x + v1.x));

	float b1 = (py1 - (a1 * px1));
	float b2 = (v1.y - a2 * v1.x);

	res.x = ((b1 - b2) / (a2 - a1));
	res.y = (a1 * res.x + b1);
	if (res.x < v1.x || res.x > v2.x) {
		res.x = -1;
	}
	return res;
}

int	is_overlap(data *draw, vertex w1, float angle) {
	vertex v1;
	vertex check;

	v1.x = (draw->m->player->x - w1.x);
	v1.y = (draw->m->player->y - w1.y);
	check.x = (cos(angle));
	check.y = (sin(angle));
	if ((-(v1.x * check.x + v1.y * check.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
											   * sqrt(check.x * check.x + check.y * check.y)) < 0))
		return TRUE;
	return FALSE;
}

vertex	change_dot(data *draw, vertex w1, wall *full_wall) {
	vertex v1;
	v1.x = (draw->m->player->x - w1.x);
	v1.y = (draw->m->player->y - w1.y);
	vertex res = w1;
	if (is_overlap(draw, w1, draw->m->player->angle) == TRUE)
	{
		res = (find_new_dot(draw, full_wall, draw->m->player->angle + DEGREES_45 * 2));
		v1.x = (draw->m->player->x - res.x); v1.y = draw->m->player->y - res.y;
	}
	if (is_overlap(draw, res, draw->m->player->angle - DEGREES_45) == TRUE)
		res = (find_new_dot(draw, full_wall, draw->m->player->angle + DEGREES_45));
	else if (is_overlap(draw, res, draw->m->player->angle + DEGREES_45) == TRUE)
		res = (find_new_dot(draw, full_wall, draw->m->player->angle - DEGREES_45));
	return (res);
}

void	draw_wall(wall *w_origin, sdl_win *win, data *draw) {
	wall w;
	wall w1;
	wall w2;
	wall w3;
	wall w4;

	w.right = change_dot(draw, w_origin->right, w_origin);
	w.left = change_dot(draw, w_origin->left, w_origin);
	if (w.left.x < 0 || w.right.x < 0)
		return ;

	//1) найти координаты левой точки
	float w_h = wall_h(w.left, 40, draw->m->player);
	w1.left.y = (float)SCREEN_HEIGHT / 2 - w_h;
	w1.right.y = (float)SCREEN_HEIGHT / 2 + w_h;

	w1.left.x = (float)SCREEN_WIDTH * find_angle(draw, w.left);
	w1.right.x = w1.left.x;

	//длина стены: каноническая длина стены от сектора (в данном случае 10) / расстояние до вершины стены / ((кол-во пикселей экрана по х / 2) / тангенс половины угла обзора игрока (45 градусов)
	w_h = wall_h(w.right, 40, draw->m->player);
	w2.left.y = (float)SCREEN_HEIGHT / 2 - w_h;
	w2.right.y = (float)SCREEN_HEIGHT / 2 + w_h;
	w2.left.x = (float)SCREEN_WIDTH * find_angle(draw, w.right);
	w2.right.x = w2.left.x;
	w3.left = w1.left;
	w3.right = w2.left;
	w4.left = w1.right;
	w4.right = w2.right;
	//	if (find_destination(&w, draw->m->player) < 30) {
	wall 	borders;
	float	t_start_x = (fabs(win->wall_img[0]->width / (w_origin->left.x - w_origin->right.x)) * fabs(w_origin->left.x - w.left.x));
	float	end_x = (float)SCREEN_WIDTH * find_angle(draw, w.right);
//	float	step_x =  (float)(win->wall_img[0]->width) / fabs(w_origin->left.x - w_origin->right.x);
	float	step_x =  (float)(win->wall_img[0]->width) / fabs((float)SCREEN_WIDTH * find_angle(draw, w.left) - (float)SCREEN_WIDTH * find_angle(draw, w.right));

	borders.left.x = (float)SCREEN_WIDTH * find_angle(draw, w.left);
	w_h = wall_h(w.left, 40, draw->m->player);
	float step_y =  (((wall_h(w.left, 40, draw->m->player) - wall_h(w.right, 40, draw->m->player)))) / fabs(borders.left.x - end_x + 0.001);
	if (borders.left.x > (float)SCREEN_WIDTH * find_angle(draw, w.right)) {
		end_x = borders.left.x;
		borders.left.x = (float)SCREEN_WIDTH * find_angle(draw, w.right);
		w_h = wall_h(w.right, 40, draw->m->player);
		step_y *= -1;
	}
	borders.right.x = borders.left.x;
	borders.left.y = (float)SCREEN_HEIGHT / 2 - w_h;
	borders.right.y = (float)SCREEN_HEIGHT / 2 + w_h;

//	step_y *= (wall_h(w.left, 40, draw->m->player)
	while (borders.left.x < end_x) {
//			if (borders.left.x > 0 && borders.left.x < SCREEN_WIDTH)
		draw_text(borders, t_start_x, win);
		t_start_x += step_x;
		borders.left.x = (int)borders.left.x + 1;
		borders.right.x = borders.left.x;
		borders.left.y += step_y * 1;
		borders.right.y -= step_y * 1;
//			//1) найти текущий step_y
//			//2) найти новые крайние экранные игрики (брезенхайм в помощь)
////			draw_texture(w_origin);//передать текущие экранные x, y
//		}
	}
	draw_line(&w1, win->bmap, 0x00FF00FF);
	draw_line(&w2, win->bmap, 0x00FF00FF);
	draw_line(&w3, win->bmap, 0x00FF00FF);
	draw_line(&w4, win->bmap, 0x00FF00FF);
}
