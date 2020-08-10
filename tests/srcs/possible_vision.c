//
// Created by Hugor Chau on 7/31/20.
//

#include "../incs/test.h"

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

static float cross_product_2d(const vertex v1, const vertex v2)
{
//	if (v1.y < v2.y)
//		return (v1.x * v2.y - v1.y * v2.x);
	return (v1.x * v2.y - v1.y * v2.x);
//	return (v2.x * v1.y - v2.y * v1.x);
}

float	find_destination(wall *w1, t_player *p) {
	//HOW????
	//мб лучший варик? Не всегда корректная выборка стен
	//if you wanna get it, read this carefully:
	//grafika.me/node/980#:~:text=Расстоянием%20от%20точки%20до%20отрезка,до%20одного%20из%20концов%20отрезка
	wall *w = malloc(sizeof(wall));
	w->left = w1->left.x < w1->right.x ? w1->left : w1->right;
	w->right = w1->right.x < w1->left.x ? w1->right : w1->left;
	if (cross_product_2d(w->right, w->left) <= 0 || cross_product_2d(w->left, w->right) <= 0) {//слишком широкое определение, нужно только определение тупого угла здесь
//		if (arccos((u1v1 + u2v2) / (||u|| * ||v||)))
//		if ((cross_product_2d(w1->left, w1->right)) / fabs((w1->left.x - w1->left.y) * (w1->right.x - w->right.y)) < 0)
			return pow((pow((p->x - w->right.x), 2) + pow((p->y - w->right.y), 2)), 0.5);
	}
	if ((int)(w->right.x - w->left.x) == 0)
		return fabs(p->y - w->left.y);
	if ((int)(w->right.y - w->left.y) == 0) {
		return ((fabs(p->x - w->left.x)));
	}
	float a = fabs(w->right.x - w->left.x);
	float b = fabs(w->right.y - w->left.y);
	float y = (((a * 2 / b) * w->left.y + a * (p->x - w->left.x) + b * p->y) / ((a * 2 / b) + b) - p->y);
	float x = ((a / b) * (y - w->left.y) + w->left.x - p->x);
	return (sqrt((x * x) + (y * y)));
}

//void	void_swap(float **x1, float **x2) {
//	float	x;
//	x = *x1;
//	*x1 = *x2;
//	*x2 = x;
//}

void	select_bunch() {

}

void	sort_by_depth(wall **w, float **depth, int *count) {
	//it's test-variant of whole algorithm, so it is bubble for now, just to check one theory!
	int		i = 0;
	float	x;
	wall	box;
	while (i < *count) {
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
	float	*depth = malloc(sizeof(float) * (draw->m->w_count + 2));
	wall	*new_list = malloc(sizeof(wall) * (draw->m->w_count + 2));//[draw->m->w_count + 1];
	int i = 0;
	while (i <= draw->m->w_count) {
		if (draw->m->walls[i].right.x != -1 && draw->m->walls[i].is_portal == FALSE) {
			if (possible_vision(&draw->m->walls[i], draw->m->player) == 1) {
				if (fabs(find_destination(&draw->m->walls[i], draw->m->player)) < 100) {
					(*w)[count] = draw->m->walls[i];
					new_list[count] = draw->m->walls[i];
					depth[count] = fabs(find_destination(&draw->m->walls[i], draw->m->player));
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
