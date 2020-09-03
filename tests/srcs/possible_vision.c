//
// Created by Hugor Chau on 7/31/20.
//

#include "../incs/test.h"

int		possible_vision(wall *w, t_player *p) {
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

static vertex	find_new_dot(t_player *p, wall *w) {
	vertex res;

	vertex v1 = w->left.x <= w->right.x ? w->left : w->right;
	vertex v2 = w->left.x <= w->right.x ? w->right : w->left;

	float a2 = ((-v2.y + v1.y) / (-v2.x + v1.x + 0.000001));
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

static vertex	get_perpendicular_dot(t_player *p, wall *w) {
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

float	find_destination(wall *w1, t_player *p) {
	vertex hint = get_perpendicular_dot(p, w1);
	if (hint.x > 0)
		return sqrt(pow(p->x - hint.x, 2) + pow(p->y - hint.y, 2));
	if (sqrt(pow(p->x - w1->left.x, 2) + pow(p->y - w1->left.y, 2)) <
			sqrt(pow(p->x - w1->right.x, 2) + pow(p->y - w1->right.y, 2))) {
		return sqrt(pow(p->x - w1->left.x, 2) + pow(p->y - w1->left.y, 2));
	} else {
		return sqrt(pow(p->x - w1->right.x, 2) + pow(p->y - w1->right.y, 2));
	}
}

void	sort_by_depth(wall **w, float **depth, int *count) {
	//it's test-variant of whole algorithm, so it is bubble for now, just to check one theory!
	int		i = 0;
	float	x;
	wall	box;
	while (i < *count - 1) {
		//добавить нормальную!!! сОРтировку
		if ((*depth)[i] > (*depth)[i + 1]) {
			x = (*depth)[i];
			(*depth)[i] = (*depth)[i + 1];
			(*depth)[i + 1] = x;
			box = (*w)[i];
			(*w)[i] = (*w)[i + 1];
			(*w)[i + 1] = box;
			i = 0;
			continue;
		}
		i++;
	}
}

void	get_walls_in_front(data *draw, wall **w, int *w_count) {
	int		count = 0;
	float	*depth = malloc(sizeof(float) * (draw->m->w_count));
	wall	*new_list = malloc(sizeof(wall) * (draw->m->w_count));//[draw->m->w_count + 1];
	int i = 0;
	while (i < draw->m->w_count) {
		if (draw->m->walls[i].right.x != -1 && draw->m->walls[i].is_portal == FALSE) {
			if (possible_vision(&draw->m->walls[i], draw->m->player) == 1) {
				if (fabs(find_destination(&draw->m->walls[i], draw->m->player)) < 100) {
					(*w)[count] = draw->m->walls[i];
					new_list[count] = draw->m->walls[i];
					depth[count] = (find_destination(&draw->m->walls[i], draw->m->player));
					printf("%f\n", depth[count]);

					count++;
				}
			}
		}
		i++;
	}
	i = 0;
	//1) sort walls by depth (depth-detector works almost correct!);
	sort_by_depth(&new_list, &depth, &count);
	//2) delete crossing walls;

	*w_count = count;
}
