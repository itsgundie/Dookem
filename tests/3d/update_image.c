#include "../incs/test.h"

//Wall x in screen-view!!!

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

float	find_angle(data *draw, vertex w1) {
	//1) v1 (от левой точки стены к точке игрока)
	vertex v1;
	v1.x = (draw->m->player->x - w1.x);
	v1.y = (draw->m->player->y - w1.y);
	//1) раньше было v1 (от направления взгляда игрока к левой точке стены)
	//теперь от угла FOV (90 degrees)
	vertex v2;
	v2.x = (cos(draw->m->player->angle + DEGREES_45));
	v2.y = (sin(draw->m->player->angle + DEGREES_45));
	vertex check;
	check.x = (cos(draw->m->player->angle - DEGREES_45));
	check.y = (sin(draw->m->player->angle - DEGREES_45));
	//trying to don't include points that aren't in FOV (90 degrees)
	if (-(v1.x * check.x + v1.y * check.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
														 * sqrt(check.x * check.x + check.y * check.y)) < 0) {
		return (1);
	}
	return (-(v1.x * v2.x + v1.y * v2.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
	* sqrt(v2.x * v2.x + v2.y * v2.y)));
}

void	update_3D_image(sdl_win *win, data *draw) {
	int count = draw->m->w_count;
	wall *w = &draw->m->walls[0];
	wall w3;

	w3.left.y = 0;
	w3.right.y = SCREEN_HEIGHT - 1;

	clear_all(win);
	while (count > 0) {
		if (possible_vision(w, draw->m->player)) {

			w3.left.x = (float)(SCREEN_WIDTH) * (find_angle(draw, w->left));
			w3.right.x = w3.left.x;
			draw_line(&w3, win->bmap, 0x00FF00FF);
			w3.left.x = (float)(SCREEN_WIDTH) * (find_angle(draw, w->right));
			w3.right.x = w3.left.x;
			draw_line(&w3, win->bmap, 0x00FF00FF);
		}
		w++;
		count--;
	}
	put_bitmap(win);
}
