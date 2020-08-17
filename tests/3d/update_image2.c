#include "../incs/test.h"

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
	vertex v1;
	float res;
	v1.x = (draw->m->player->x - w1.x);
	v1.y = (draw->m->player->y - w1.y);
	vertex v2;
	v2.x = (cos(draw->m->player->angle + DEGREES_45 * 2));
	v2.y = (sin(draw->m->player->angle + DEGREES_45 * 2));
	res = (-(v1.x * v2.x + v1.y * v2.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
											* sqrt(v2.x * v2.x + v2.y * v2.y)));
	return ((res / cos(res)) + 1.0) / 2;
}

vertex	find_new_dot(data *draw, wall *w, float angle) {

	vertex res;
	//1) с какой стороны вектора ищем пересечение? Справа или слева?
	vertex v1 = w->left.x <= w->right.x ? w->left : w->right;
	vertex v2 = w->left.x <= w->right.x ? w->right : w->left;
	if (fabs(sin(angle)) <= 0.00001)
		angle += 0.001;
	if (fabs(cos(angle)) <= 0.00001)
		angle += 0.001;
	float px1 = cos(angle) > 0 ? draw->m->player->x : draw->m->player->x + cos(angle);
	float py1 = cos(angle) > 0 ? draw->m->player->y : draw->m->player->y + sin(angle);
	float px2 = cos(angle) < 0 ? draw->m->player->x : draw->m->player->x + cos(angle);
	float py2 = cos(angle) < 0 ? draw->m->player->y : draw->m->player->y + sin(angle);
	if (px2 < px1) {
		printf("error!\n");
	}
	float a1 = ((-py2 + py1) / (-px2 + px1));
	float a2 = ((-v2.y + v1.y) / (-v2.x + v1.x));

	float b1 = (py1 - (a1 * px1));//коэффициент смещения
	float b2 = (v1.y - a2 * v1.x);

	res.x = ((b1 - b2) / (a2 - a1));
	res.y = (a1 * res.x + b1);
	if (res.x < v1.x || res.x > v2.x) {
		res.x = -1;
	}
	return res;
}

vertex	change_dot(data *draw, vertex w1, vertex w2, wall *full_wall) {
	vertex v1;
	v1.x = (draw->m->player->x - w1.x);
	v1.y = (draw->m->player->y - w1.y);
	vertex check4;
	vertex res = w1;
	check4.x = (cos(draw->m->player->angle));
	check4.y = (sin(draw->m->player->angle));
	if ((-(v1.x * check4.x + v1.y * check4.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
											  * sqrt(check4.x * check4.x + check4.y * check4.y)) < 0))
	{
		res = (find_new_dot(draw, full_wall, draw->m->player->angle + DEGREES_45 * 2));
		v1.x = (draw->m->player->x - res.x); v1.y = draw->m->player->y - res.y;
	}// проверить перекрываемость краями FOV
		vertex v2;
		v2.x = (cos(draw->m->player->angle + DEGREES_45));
		v2.y = (sin(draw->m->player->angle + DEGREES_45));
		vertex check;
		check.x = (cos(draw->m->player->angle - DEGREES_45));
		check.y = (sin(draw->m->player->angle - DEGREES_45));
		if ((-(v1.x * check.x + v1.y * check.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
													  * sqrt(check.x * check.x + check.y * check.y)) < 0))
		{
			//точка слева от направления взгляда игрока
			res = (find_new_dot(draw, full_wall, draw->m->player->angle + DEGREES_45));
		} else if (((-(v1.x * v2.x + v1.y * v2.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
										  * sqrt(v2.x * v2.x + v2.y * v2.y))) < 0)) {
			res = (find_new_dot(draw, full_wall, draw->m->player->angle - DEGREES_45));
		}
	return (res);
}

//BugBugBug! need for wall clipping!! If one point of wall is not in FOV, we have a lots of trouble!
void	draw_wall(wall *w_origin, sdl_win *win, data *draw) {
	wall *w = malloc(sizeof(wall));
	wall w1;
	wall w2;
	wall w3;
	wall w4;

	w->right = w_origin->right;
	w->left = w_origin->left;
	w->right = change_dot(draw, w_origin->right, w_origin->left, w_origin);
	w->left = change_dot(draw, w_origin->left, w_origin->right, w_origin);

	if (w->left.x < 0 || w->right.x < 0)
		return ;
	float w_h = 20 / sqrt(pow(w->left.x - draw->m->player->x, 2) + pow(draw->m->player->y - w->left.y, 2)) * ((SCREEN_WIDTH / 2) / TANGENT_45);
	w1.left.y = SCREEN_HEIGHT / 2 - w_h;
	w1.right.y = SCREEN_HEIGHT / 2 + w_h;

	w1.left.x = SCREEN_WIDTH * find_angle(draw, w->left);
	w1.left.x = w1.left.x < 0 ? 0 : w1.left.x;//если стена находится за левым лучом FOV,
	//то она будет за левой частью экрана - пока присвоим ей 0; если стена находится за
	//правым лучом FOV, функция find_angle вернёт 1 - умножаем 1 на SCREEN_WIDTH и получаем
	//правую границу экрана; конечно, это временное решение
	w1.right.x = w1.left.x;

	//длина стены: каноническая длина стены от сектора (в данном случае 10) / расстояние до вершины стены / ((кол-во пикселей экрана по х / 2) / тангенс половины угла обзора игрока (45 градусов)
	w_h = 20 / sqrt(pow(w->right.x - draw->m->player->x, 2) + pow(draw->m->player->y - w->right.y, 2)) * ((SCREEN_WIDTH / 2) / TANGENT_45);
	w2.left.y = SCREEN_HEIGHT / 2 - w_h;
	w2.right.y = SCREEN_HEIGHT / 2 + w_h;

	w2.left.x = SCREEN_WIDTH * find_angle(draw, w->right);// / cos(find_angle(draw, w->right));
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