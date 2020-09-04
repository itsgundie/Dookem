//
// Created by Hugor Chau on 9/3/20.
//

#include "../incs/test.h"

/*
**		нахожу пересечение данной стены и перпендикулярной ей, выпущенной
**		из точки-позиции игрока
*/

static vertex	find_new_dot(t_player *p, wall *w) {
	vertex res;

	vertex v1 = w->left.x <= w->right.x ? w->left : w->right;
	vertex v2 = w->left.x <= w->right.x ? w->right : w->left;

	float a2 = ((-v2.y + v1.y) / (-v2.x + v1.x + 0.000001));
	/*
	**		я хз, как это по-áнглицки; произведение угловых
	**		коэффициентов перпендикулярных прямых (т.е. a1 * a2)
	**		равно -1, отсюда всё и высчитывается
	*/
	float a1 = -1 / a2;
	float angle = atan(a1);

	if (fabs(sin(angle)) <= 0.000001 || fabs(cos(angle)) <= 0.000001)
		angle += 0.0000001;
	float px1 = cos(angle) > 0 ? p->x : p->x + cos(angle);
	float py1 = cos(angle) > 0 ? p->y : p->y + sin(angle);

	float b1 = (py1 - (a1 * px1));
	float b2 = (v1.y - a2 * v1.x);

	res.x = ((b1 - b2) / (a2 - a1));
	res.y = (a1 * res.x + b1);
	return res;
}

/*
**		trying to get point on the wall, that would be one
**		of vertexes of the perpendicular (the second is player's
**		position)
*/

vertex	get_perpendicular_dot(t_player *p, wall *w) {
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
		(w->left.y - res.y) * (w->right.y - res.y) > 0) {
		res.x = -1;
	}
	return res;
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

float	find_destination(wall *w1, t_player *p) {
	/*
	**		trying to find the perpendicular
	*/
	vertex hint = get_perpendicular_dot(p, w1);
	/*
	**		if perpendicular does not exists, hint.x will be around -1.0
	*/
	if (hint.x > -0.1)
		return sqrt(pow(p->x - hint.x, 2) + pow(p->y - hint.y, 2));
	if (sqrt(pow(p->x - w1->left.x, 2) + pow(p->y - w1->left.y, 2)) <
		sqrt(pow(p->x - w1->right.x, 2) + pow(p->y - w1->right.y, 2))) {
		return sqrt(pow(p->x - w1->left.x, 2) + pow(p->y - w1->left.y, 2));
	} else {
		return sqrt(pow(p->x - w1->right.x, 2) + pow(p->y - w1->right.y, 2));
	}
}