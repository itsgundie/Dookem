
#include "../incs/test.h"

/*
**		formula for finding textel
*/

float 	find_textel(float angle, vertex textels, vertex dist, int text_max) {
	float t_start_x = ((1.0 - angle) * (textels.x / dist.x)) +
					  ((angle) * (textels.y / dist.y));
	t_start_x = (int)(t_start_x /
					  ((1.0 - angle) * (1.0 / dist.x) + (angle * (1.0 / dist.y)))) % text_max;
	return t_start_x;
}

/*
**		wall's x on the screen is calculated by
**		angle from the left vector of FOV
*/

float	find_angle(data *draw, vertex w1)
{
	vertex	v1;
	float	res;
	vertex	v2;

	v1.x = (draw->m->player->x - w1.x);
	v1.y = (draw->m->player->y - w1.y);
	v2.x = (cos(draw->m->player->angle - DEGREES_45));
	v2.y = (sin(draw->m->player->angle - DEGREES_45));
	res = -(((v1.x * v2.x + v1.y * v2.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
							* sqrt(v2.x * v2.x + v2.y * v2.y))));
	res = res >= 1 ? acos(1) : acos(res);
	res = (180 / M_PI * res) / 90.0;
	return (res);
}

/*
**		finding extreme wall points for affine-correction formula
*/

void	wall_extremes(data *draw, wall w, wall *borders, float *end_x)
{
	float	left;
	float	right;
	float	left_h;
	float	right_h;

	left = (float)SCREEN_WIDTH * find_angle(draw, w.left);
	right = (float)SCREEN_WIDTH * find_angle(draw, w.right);
	right_h = wall_h(w.right, 40, draw->m->player);
	left_h = wall_h(w.left, 40, draw->m->player);
	*end_x = right;
	borders->left.x = left;
	borders->left.y = (float)SCREEN_HEIGHT / 2 - left_h;
	borders->right.y = (float)SCREEN_HEIGHT / 2 + left_h;
	if (borders->left.x > *end_x)
	{
		*end_x = left;
		borders->left.x = right;
		borders->left.y = (float)SCREEN_HEIGHT / 2 - right_h;
		borders->right.y = (float)SCREEN_HEIGHT / 2 + right_h;
	}
}

/*
**		finding extreme texture points for affine-correction formula
*/

void	text_extremes(wall w, wall *w_origin, sdl_win *win, wall *text_extremes)
{
	float original_wall_length;

	original_wall_length = sqrt(pow(w_origin->left.x - w_origin->right.x, 2) +
		pow(w_origin->left.y - w_origin->right.y, 2));
	text_extremes->left.x = (float)win->wall_img[0]->width
			/ original_wall_length *
			(sqrt(pow(w_origin->left.x - w.left.x, 2)
			+ pow(w_origin->left.y - w.left.y, 2)));
	text_extremes->left.y = (float)win->wall_img[0]->width
			/ original_wall_length *
		(sqrt(pow(w_origin->left.x - w.right.x, 2)
		+ pow(w_origin->left.y - w.right.y, 2)));
}

void	text_destination(data *draw, wall w, wall *text_extremes)
{
	text_extremes->right.x = sqrt(pow(w.left.x - draw->m->player->x, 2)
			+ pow(draw->m->player->y - w.left.y, 2));
	text_extremes->right.y = sqrt(pow(w.right.x - draw->m->player->x, 2)
			+ pow(draw->m->player->y - w.right.y, 2));
}

void	inverse_steps(vertex *step, float *angle)
{
	step->y *= -1;
	*angle = 1;
	step->x *= -1;
}

void	texturing_algorithm(wall w, sdl_win *win, data *draw,
						wall *text_extremes)
{
	wall		borders;
	float		end_x;
	vertex		step;
	float		angle;
	float		t_start_x;

	wall_extremes(draw, w, &borders, &end_x);
	step.y = (wall_h(w.left, 40, draw->m->player)
			- wall_h(w.right, 40, draw->m->player)) / (end_x - borders.left.x);
	angle = 0;
	step.x = (1.0) / (end_x - borders.left.x);
	if (find_angle(draw, w.left) > find_angle(draw, w.right))
		inverse_steps(&step, &angle);
	while (borders.left.x < end_x)
	{
		borders.right.x = (int)borders.left.x;
		t_start_x = find_textel(angle, text_extremes->left,
				text_extremes->right, win->wall_img[0]->width);
		draw_text(borders, t_start_x, win, 0);
		borders.left.x = (int)borders.left.x + 1;
		borders.left.y += step.y;
		angle += step.x;
		borders.right.y -= step.y;
	}
}

void	draw_wall(wall *w_origin, sdl_win *win, data *draw)
{
	wall		w;
	wall		text_extreme;

	w.right = horizontal_clipping(draw, w_origin->right, w_origin);
	w.left = horizontal_clipping(draw, w_origin->left, w_origin);
	if (w.left.x < 0 || w.right.x < 0)
		return ;
	text_extremes(w, w_origin, win, &text_extreme);
	text_destination(draw, w, &text_extreme);
	texturing_algorithm(w, win, draw, &text_extreme);
}
