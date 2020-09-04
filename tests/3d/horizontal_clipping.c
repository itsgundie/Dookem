#include "../incs/test.h"

/*
**		function finding point of crossing two vectors -
**		original wall and one of player's FOV
*/

static vertex	find_new_dot(t_player *p, wall *w, float angle)
{
	vertex	res;
	wall	line;
	vertex	p_dot;
	vertex	line_coefficients;
	vertex	p_coefficients;

	line.left = w->left.x <= w->right.x ? w->left : w->right;
	line.right = w->left.x <= w->right.x ? w->right : w->left;
	if (fabs(sin(angle)) <= 0.00001 || fabs(cos(angle)) <= 0.00001)
		angle += 0.00001;
	p_dot.x = cos(angle) > 0 ? p->x : p->x + cos(angle);
	p_dot.y = cos(angle) > 0 ? p->y : p->y + sin(angle);
	p_coefficients.x = tan(angle);
	line_coefficients.x = ((-line.right.y + line.left.y)
			/ (-line.right.x + line.left.x + 0.00001));
	p_coefficients.y = (p_dot.y - (p_coefficients.x * p_dot.x));
	line_coefficients.y = (line.left.y - line_coefficients.x * line.left.x);
	res.x = ((p_coefficients.y - line_coefficients.y)
			/ (line_coefficients.x - p_coefficients.x));
	res.y = (p_coefficients.x * res.x + p_coefficients.y);
	return (res);
}

/*
**		function checks if dot is behind vector
**		from player's pos with some angle
*/

static int		is_overlap(data *draw, vertex w1, float angle)
{
	vertex	v1;
	vertex	check;

	v1.x = (draw->m->player->x - w1.x);
	v1.y = (draw->m->player->y - w1.y);
	check.x = (cos(angle));
	check.y = (sin(angle));
	if ((-(v1.x * check.x + v1.y * check.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
						* sqrt(check.x * check.x + check.y * check.y)) < 0))
		return (TRUE);
	return (FALSE);
}

/*
**		function returns vertex location placed in the FOV and corrects it
**		if it's necessary
*/

vertex			horizontal_clipping(data *draw, vertex original_dot,
												wall *full_wall)
{
	vertex	res;

	res = original_dot;
	if (is_overlap(draw, res, draw->m->player->angle) == TRUE)
	{
		res = (find_new_dot(draw->m->player, full_wall,
				draw->m->player->angle + DEGREES_45 * 2));
	}
	if (is_overlap(draw, res, draw->m->player->angle + DEGREES_45) == TRUE)
	{
		res = (find_new_dot(draw->m->player, full_wall,
				draw->m->player->angle - DEGREES_45));
	}
	if (is_overlap(draw, res, draw->m->player->angle - DEGREES_45) == TRUE)
	{
		res = (find_new_dot(draw->m->player, full_wall,
				draw->m->player->angle + DEGREES_45));
	}
	return (res);
}
