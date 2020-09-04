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
	wall	*new_list = malloc(sizeof(wall) * (draw->m->w_count));
	int i = 0;
	while (i < draw->m->w_count) {
		if (draw->m->walls[i].right.x != -1 && draw->m->walls[i].is_portal == FALSE) {
			if (possible_vision(&draw->m->walls[i], draw->m->player) == 1) {
				if (fabs(find_destination(&draw->m->walls[i], draw->m->player)) < 100) {
					(*w)[count] = draw->m->walls[i];
					new_list[count] = draw->m->walls[i];
					depth[count] = (find_destination(&draw->m->walls[i], draw->m->player));
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
