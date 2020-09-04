#include "../incs/test.h"

/*
**		нахожу пересечение данной стены и перпендикулярной ей, выпущенной
**		из точки-позиции игрока
*/

/*
**		it's important: because of norme, I placed all coefficients
**		to line_coefficient; angle coefficients is on the left part,
**		line_coefficient.left.x - for wall, line_coefficient.left.y -
**		for perpendicular; line coefficient is in the right part,
**		same logic; p_dot is second dot of perpendicular, directed
**		as perpendicular
*/

static vertex	find_new_dot(t_player *p, wall *w)
{
	vertex	res;
	vertex	p_dot;
	wall	line_coefficient;
	float	angle;
	wall	line;

	line.left = w->left.x <= w->right.x ? w->left : w->right;
	line.right = w->left.x <= w->right.x ? w->right : w->left;
	line_coefficient.left.y = ((-line.right.y + line.left.y)
			/ (-line.right.x + line.left.x + 0.000001));
	line_coefficient.left.x = -1 / line_coefficient.left.y;
	angle = atan(line_coefficient.left.x);
	if (fabs(sin(angle)) <= 0.000001 || fabs(cos(angle)) <= 0.000001)
		angle += 0.0000001;
	p_dot.x = cos(angle) > 0 ? p->x : p->x + cos(angle);
	p_dot.y = cos(angle) > 0 ? p->y : p->y + sin(angle);
	line_coefficient.right.x = (p_dot.y - (line_coefficient.left.x * p_dot.x));
	line_coefficient.right.y =
			(line.left.y - line_coefficient.left.y * line.left.x);
	res.x = ((line_coefficient.right.x - line_coefficient.right.y)
			/ (line_coefficient.left.y - line_coefficient.left.x));
	res.y = (line_coefficient.left.x * res.x + line_coefficient.right.x);
	return (res);
}

/*
**		trying to get point on the wall, that would be one
**		of vertexes of the perpendicular (the second is player's
**		position)
*/

vertex			get_perpendicular_dot(t_player *p, wall *w)
{
	vertex	res;

	if (fabs(w->left.x - w->right.x) <= 0.1)
	{
		res.x = w->left.x;
		res.y = p->y;
	}
	else if (fabs(w->left.y - w->right.y) <= 0.1)
	{
		res.y = w->left.y;
		res.x = p->x;
	}
	else
		res = find_new_dot(p, w);
	if ((w->left.x - res.x) * (w->right.x - res.x) > 0 ||
		(w->left.y - res.y) * (w->right.y - res.y) > 0)
	{
		res.x = -1;
	}
	return (res);
}

/*
**		entry point to the algorithm;
**		at first let's find out is it is possible to
**		draw a perpendicular from player to the wall;
**		if it's not, than the shortest destination is
**		length from the nearest wall's vertex to the player;
**		in the other case it is perpendicular from player to
**		the wall
*/

float			find_destination(wall *w1, t_player *p)
{
	vertex	hint;

	hint = get_perpendicular_dot(p, w1);
	if (hint.x > -0.1)
	{
		return (sqrt(pow(p->x - hint.x, 2) + pow(p->y - hint.y, 2)));
	}
	if (sqrt(pow(p->x - w1->left.x, 2) + pow(p->y - w1->left.y, 2)) <
		sqrt(pow(p->x - w1->right.x, 2) + pow(p->y - w1->right.y, 2)))
	{
		return (sqrt(pow(p->x - w1->left.x, 2) + pow(p->y - w1->left.y, 2)));
	}
	else
	{
		return (sqrt(pow(p->x - w1->right.x, 2) + pow(p->y - w1->right.y, 2)));
	}
}
