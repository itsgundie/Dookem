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
	}//проверяем, находится ли стена за правым лучом FOV
	return (-(v1.x * v2.x + v1.y * v2.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
	* sqrt(v2.x * v2.x + v2.y * v2.y)));//если стена находится за левым лучом FOV, возврат будет отрицательным
}


//BugBugBug! need for wall clipping!! If one point of wall is not in FOV, we have a lots of trouble!
void	draw_wall(wall *w, sdl_win *win, data *draw) {
	wall w1;
	wall w2;
	wall w3;
	wall w4;

	w1.left.y = SCREEN_HEIGHT / 2 - (10 / sqrt(pow(w->left.x - draw->m->player->x, 2) + pow(draw->m->player->y - w->left.y, 2)) * ((SCREEN_WIDTH / 2) / TANGENT_45));
	w1.right.y = SCREEN_HEIGHT / 2 + (10 / sqrt(pow(w->left.x - draw->m->player->x, 2) + pow(draw->m->player->y - w->left.y, 2)) * ((SCREEN_WIDTH / 2) / TANGENT_45));
	w1.left.x = (float)(SCREEN_WIDTH) * (find_angle(draw, w->left));
	w1.left.x = w1.left.x < 0 ? 0 : w1.left.x;//если стена находится за левым лучом FOV,
	//то она будет за левой частью экрана - пока присвоим ей 0; если стена находится за
	//правым лучом FOV, функция find_angle вернёт 1 - умножаем 1 на SCREEN_WIDTH и получаем
	//правую границу экрана; конечно, это временное решение
	w1.right.x = w1.left.x;
	w2.left.y = SCREEN_HEIGHT / 2 - (10 / sqrt(pow(w->right.x - draw->m->player->x, 2) + pow(draw->m->player->y - w->right.y, 2)) * ((SCREEN_WIDTH / 2) / TANGENT_45));
	w2.right.y = SCREEN_HEIGHT / 2 + (10 / sqrt(pow(w->right.x - draw->m->player->x, 2) + pow(draw->m->player->y - w->right.y, 2)) * ((SCREEN_WIDTH / 2) / TANGENT_45));
	w2.left.x = (float)(SCREEN_WIDTH) * (find_angle(draw, w->right));
	w2.left.x = w2.left.x < 0 ? 0 : w2.left.x;
	w2.right.x = w2.left.x;
	w3.left = w1.left;
	w3.right = w2.left;
	w4.left = w1.right;
	w4.right = w2.right;
	draw_line(&w1, win->bmap, 0x00FF00FF);
	draw_line(&w2, win->bmap, 0x00FF00FF);
	draw_line(&w3, win->bmap, 0x00FF00FF);
	draw_line(&w4, win->bmap, 0x00FF00FF);
}

void	update_3D_image(sdl_win *win, data *draw) {
	int count = draw->m->w_count;

	wall *w = &draw->m->walls[0];
	clear_all(win);
	while (count > 0) {
		if (possible_vision(w, draw->m->player)) {
			draw_wall(w, win, draw);
		}
		w++;
		count--;
	}
	put_bitmap(win);
}
