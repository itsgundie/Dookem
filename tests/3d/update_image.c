//
// Created by Hugor Chau on 8/4/20.
//
#include "../incs/test.h"

static int		possible_vision(wall *w, t_player *p) {
	float tx1 = w->left.x - p->x;
	float ty1 = w->left.y - p->y;
	float tx2 = w->right.x - p->x;
	float ty2 = w->right.y - p->y;
	float tz1 = tx1 * cos(p->angle) + ty1 * sin(p->angle);
	float tz2 = tx2 * cos(p->angle) + ty2 * sin(p->angle);
	if (tz1 > 0 || tz2 > 0)
		return 1;
	return 0;
}

void	clear_all(sdl_win *win) {
	int	i = 0;

	while (i < (SCREEN_WIDTH) * (SCREEN_HEIGHT) * 4) {
		(*(win->bmap))[i + 1] = 66;
		(*(win->bmap))[i] = 66;
		(*(win->bmap))[i + 2] = 0;
		(*(win->bmap))[i + 3] = 0;
		i += 4;
	}
}

static float cross_product_2d(const vertex v1, const vertex v2)
{
	return (v1.x * v2.y - v1.y * v2.x);
}

float	find_angle(data *draw, wall w1) {
	wall w;
	w.right.x = cos(draw->m->player->angle) * 30 + draw->m->player->x;
	w.right.y = sin(draw->m->player->angle) * 30 + draw->m->player->y;
	float	c = fabs(pow((draw->m->player->x - w.right.x), 2) * pow((draw->m->player->y - w.right.y), 2));
	float	b = pow((draw->m->player->x - w1.left.x), 2) * pow((draw->m->player->y - w1.left.y), 2);
	float	a = pow((w.right.x - w1.left.x), 2) * pow((w.right.y - w1.left.y), 2);
	printf("a = %f\n b = %f\n  c = %f\n", a, b, c);

	return (acos((b * b + c * c - a * a) / (2 * b * c)));
}

void	update_3D_image(sdl_win *win, data *draw) {
	int count = draw->m->w_count;
	wall *w = &draw->m->walls[0];
	wall w1;
	wall w2;
	wall w3;
	w1.left.y = 0;
	w1.left.x = SCREEN_WIDTH / 2;
	w2.left.y = 0;
	w2.left.x = SCREEN_WIDTH / 2;

	clear_all(win);
	while (count > 0) {
		vertex v1; v1.x = draw->m->player->x; v1.y = draw->m->player->y;// w->left.x
		vertex v2; v2.x = w->left.x; v2.y = w->left.y;
		w1.right.x = cross_product_2d(v1, v2);
		w1.right.y = SCREEN_HEIGHT / 2;
		v2.x = w->right.x; v2.y = w->right.y;
		w2.right.x = cross_product_2d(v1, v2);//return ((fabs(p->x - w->left.x)));
		w2.right.y = SCREEN_HEIGHT / 2;
		w3.left.y = 0;
		w3.right.y = SCREEN_HEIGHT - 1;
		if (possible_vision(w, draw->m->player)) {
//			find_angle(draw, *w);
//			w3.left.x = SCREEN_WIDTH / 2 * /* угол от начала в процентном соотношении */
//			((M_PI / 2) */* угол от начала */((M_PI / 4 - /* угол */find_angle(draw, *w)) / 100));// подумать, как перевести в экранный x
//			w3.right.x = w3.left.x;
			printf("your angle: %f\n", find_angle(draw, *w));
//			draw_line(&w3, win->bmap, 0x00FF00FF);
//			1) find angles: arccos((u1v1 + u2v2) / (||u|| * ||v||))
//			2) find how it depends on FOV (90 degrees)
//			float f1 = acos((u1v1 + u2v2) / (||u|| * ||v||))
//			draw_line(&w1, win->bmap, 0x00FFFFFF);
//			draw_line(&w2, win->bmap, 0x00FF00FF);
//			count = 0;
		}
		w++;
		count--;
	}
	put_bitmap(win);
}