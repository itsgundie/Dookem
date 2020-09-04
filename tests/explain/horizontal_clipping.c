#include "../incs/test.h"

/*
**		function finding point of crossing two vectors -
**		original wall and one of player's FOV
*/

static vertex	find_new_dot(data *draw, wall *w, float angle) {
	vertex res;

	vertex v1 = w->left.x <= w->right.x ? w->left : w->right;
	vertex v2 = w->left.x <= w->right.x ? w->right : w->left;

	if (fabs(sin(angle)) <= 0.000001 || fabs(cos(angle)) <= 0.000001)
		angle += 0.0000001;
	float px1 = cos(angle) > 0 ? draw->m->player->x : draw->m->player->x + cos(angle);
	float py1 = cos(angle) > 0 ? draw->m->player->y : draw->m->player->y + sin(angle);

	float a1 = tan(angle);
	float a2;
	a2 = ((-v2.y + v1.y) / (-v2.x + v1.x + 0.000001));

	float b1 = (py1 - (a1 * px1));
	float b2 = (v1.y - a2 * v1.x);

	res.x = ((b1 - b2) / (a2 - a1));
	res.y = (a1 * res.x + b1);
//	Don't need this check anymore because of wall-clipping
//	if (res.x < v1.x || res.x > v2.x) {
//		res.x = -1;
//	}
	return res;
}

/*
**		function checks if dot is behind vector
**		from player's pos with some angle
*/

static int	is_overlap(data *draw, vertex w1, float angle) {
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

/*
**		function returns vertex location placed in the FOV and corrects it
**		if it's necessary
*/

vertex	horizontal_clipping(data *draw, vertex original_dot, wall *full_wall) {
/*
**	if everything is fine, function will return original vertex
*/
	vertex res = original_dot;

/*
**	clip wall, if one of it's vertexes is partly behind FOV-vectors
*/
	if (is_overlap(draw, original_dot, draw->m->player->angle) == TRUE)
	{
		res = (find_new_dot(draw, full_wall, draw->m->player->angle + DEGREES_45 * 2));
	}
	if (is_overlap(draw, res, draw->m->player->angle + DEGREES_45) == TRUE)
	{
		res = (find_new_dot(draw, full_wall, draw->m->player->angle - DEGREES_45));
	}
	if (is_overlap(draw, res, draw->m->player->angle - DEGREES_45) == TRUE)
	{
		res = (find_new_dot(draw, full_wall, draw->m->player->angle + DEGREES_45));
	}
	return (res);
}
