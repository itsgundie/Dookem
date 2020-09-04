
#include "../incs/test.h"

/*
**		wall's x on the screen is calculated by angle from the left vector of FOV
*/

float	find_angle(data *draw, vertex w1) {
	vertex v1;
	float res;
	v1.x = (draw->m->player->x - w1.x);
	v1.y = (draw->m->player->y - w1.y);
	vertex v2;
	v2.x = (cos(draw->m->player->angle - DEGREES_45));
	v2.y = (sin(draw->m->player->angle - DEGREES_45));
	res = -(((v1.x * v2.x + v1.y * v2.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
											* sqrt(v2.x * v2.x + v2.y * v2.y))));

	res = res >= 1 ? acos(1) : res <= -1 ? acos(-1) : acos(res);
	res = (180 / M_PI * res) / 90.0;
	return res;
}

/*
**		finding extreme wall points for affine-correction formula
*/

void	wall_extremes(data *draw, wall w, wall *borders, float *end_x)
{
	float	left = (float)SCREEN_WIDTH * find_angle(draw, w.left);
	float	right = (float)SCREEN_WIDTH * find_angle(draw, w.right);
	float	left_h = wall_h(w.left, 40, draw->m->player);
	float	right_h = wall_h(w.right, 40, draw->m->player);
	*end_x = right;
	borders->left.x = left;
	borders->left.y = (float)SCREEN_HEIGHT / 2 - left_h;
	borders->right.y = (float)SCREEN_HEIGHT / 2 + left_h;

	if (borders->left.x > *end_x) {
		*end_x = left;
		borders->left.x = right;
		borders->left.y = (float)SCREEN_HEIGHT / 2 - right_h;
		borders->right.y = (float)SCREEN_HEIGHT / 2 + right_h;
	}
}

/*
**		finding extreme texture points for affine-correction formula
*/

void	text_extremes(data *draw, wall w, wall *w_origin,sdl_win *win,  vertex_x *dist, vertex_x *text_x)
{
	float rrr = sqrt(pow(w_origin->left.x - w_origin->right.x, 2) + pow(w_origin->left.y - w_origin->right.y, 2));

	text_x->start = (float)win->wall_img[0]->width / rrr * (sqrt(pow(w_origin->left.x - w.left.x, 2) + pow(w_origin->left.y - w.left.y, 2)));
	text_x->end = (float)win->wall_img[0]->width / rrr * (sqrt(pow(w_origin->left.x - w.right.x, 2) + pow(w_origin->left.y - w.right.y, 2)));
	dist->start = sqrt(pow(w.left.x - draw->m->player->x, 2) + pow(draw->m->player->y - w.left.y, 2));
	dist->end = sqrt(pow(w.right.x - draw->m->player->x, 2) + pow(draw->m->player->y - w.right.y, 2));
}

void	draw_wall(wall *w_origin, sdl_win *win, data *draw) {
	wall		w;
	wall 		borders;
	vertex_x	dist;
	vertex_x	text_x;
	float		end_x;
	float		step_y;
	float		t_start_x;
	float		angle;
	float		angle_step;

	//preparations
	w.right = horizontal_clipping(draw, w_origin->right, w_origin);
	w.left = horizontal_clipping(draw, w_origin->left, w_origin);
	if (w.left.x < 0 || w.right.x < 0)
		return ;
	wall_extremes(draw, w, &borders, &end_x);
	text_extremes(draw, w, w_origin, win, &dist, &text_x);

	step_y = (wall_h(w.left, 40, draw->m->player) - wall_h(w.right, 40, draw->m->player)) / fabs(borders.left.x - end_x);
	angle = 0;
	angle_step = fabs(1.0) / fabs(borders.left.x - end_x);
	if (find_angle(draw, w.left) > find_angle(draw, w.right)) {
		step_y *= -1;
		angle = 1;
		angle_step *= -1;
	}

	//texture mapping algorithm
	while (borders.left.x < end_x)
	{
		borders.right.x = (int)borders.left.x;
		t_start_x = ((1.0 - angle) * (text_x.start / dist.start)) +
						 ((angle) * (text_x.end / dist.end));
		t_start_x = (int)(t_start_x /
						((1.0 - angle) * (1.0 / dist.start) + (angle * (1.0 / dist.end)))) % win->wall_img[0]->width;
		draw_text(borders, t_start_x, win, 0);
		borders.left.x = (int)borders.left.x + 1;
		borders.left.y += step_y;
		angle += angle_step;
		borders.right.y -= step_y;
	}
	//это проверка - обводит стенки розовым, чтобы проверить исходные размеры стен
	wall_delineation(w_origin, win, draw);
}
