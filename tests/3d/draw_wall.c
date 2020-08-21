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
	// 0.2 is magic, don't ask me why
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

	w.right = change_dot(draw, w_origin->right, w_origin);
	w.left = change_dot(draw, w_origin->left, w_origin);
	if (w.left.x < 0 || w.right.x < 0)
		return ;

	float	w_h;
	wall 	borders;
	float	end_x = (float)SCREEN_WIDTH * find_angle(draw, w.right);
	float	t_start_x;

	borders.left.x = (float)SCREEN_WIDTH * find_angle(draw, w.left);

	w_h = wall_h(w.left, 40, draw->m->player);// / cos(DEGREES_45);
	float step_y = (((wall_h(w.left, 40, draw->m->player) /*/ cos(DEGREES_45)*/ - wall_h(w.right, 40, draw->m->player)/* / cos(DEGREES_45)*/))) / fabs(borders.left.x - end_x + 0.001);

	//нужно ли учитывать дальность?
	float rrr = sqrt(pow(w_origin->left.x - w_origin->right.x, 2) + pow(w_origin->left.y - w_origin->right.y, 2));

	float common_start_x = ((float)(win->wall_img[0]->width) / rrr * (sqrt(pow(w_origin->left.x - w.left.x, 2) + pow(w_origin->left.y - w.left.y, 2))));
	t_start_x = common_start_x;
	float t_end_x = ((float)(win->wall_img[0]->width) / rrr * (sqrt(pow(w_origin->left.x - w.right.x, 2) + pow(w_origin->left.y - w.right.y, 2))));
	printf("start = %f, end = %f, angle = %f\n", common_start_x, t_end_x, (fabs(common_start_x - t_end_x) / (float)(win->wall_img[0]->width)));
//	borders.left.x = borders.left.x < 0 ? borders.left.x = 0 : borders.left.x;
//	end_x = end_x < 0 ? end_x = 0 : end_x;
//	end_x < 0 ?
	float step = fabs(t_end_x - common_start_x) / fabs((int)(borders.left.x) - (int)(end_x));
	float count = t_start_x;

	if (borders.left.x > (float)SCREEN_WIDTH * find_angle(draw, w.right)) {
		end_x = borders.left.x;
		borders.left.x = (float)SCREEN_WIDTH * find_angle(draw, w.right);
		w_h = wall_h(w.right, 40, draw->m->player);
		step_y *= -1;
		step *= -1;
		count = t_end_x;
	}
	borders.left.y = (float)SCREEN_HEIGHT / 2 - w_h;
	borders.right.y = (float)SCREEN_HEIGHT / 2 + w_h;

	float end_dist = sqrt(pow(w_origin->right.x - draw->m->player->x, 2) + pow(draw->m->player->y - w_origin->right.y, 2));
	float start_dist = sqrt(pow(w_origin->left.x - draw->m->player->x, 2) + pow(draw->m->player->y - w_origin->left.y, 2));
	float angle;
//	borders.left.x = borders.left.x < 0 ? borders.left.x = 0 : borders.left.x;
//	end_x = end_x < 0 ? 0 : end_x;
	while (borders.left.x < end_x) {
		borders.right.x = borders.left.x;
		if (borders.left.x >= 0 && borders.left.x < SCREEN_WIDTH) {
			angle = (fabs(/*common_start_x - */count) / (float)(win->wall_img[0]->width));

			t_start_x = ((common_start_x * ((1.0 - angle) / start_dist)) +
						 (t_end_x * ((angle) / end_dist)))/ //;// /
						((1.0 - angle) * (1 / start_dist) + (angle) * (1 / end_dist));
			draw_text(borders, t_start_x, win);
		}
		count += step;
		borders.left.x = (int)borders.left.x + 1;
		borders.left.y += step_y * 1;
		borders.right.y -= step_y * 1;
	}
	wall_delineation(w_origin, win, draw);
}
