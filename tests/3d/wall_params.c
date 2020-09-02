//
// Created by Hugor Chau on 8/18/20.
//

#include "../incs/test.h"

float 	wall_h(vertex point, float width, t_player *player) {
	return width / sqrt(pow(point.x - player->x, 2) + pow(player->y - point.y, 2)) * ((SCREEN_HEIGHT / 2) / TANGENT_45);
}

float	vector_leigh(wall *w) {
	return sqrt(pow(w->left.x - w->right.x, 2) + pow(w->left.y - w->right.y, 2));
}

float 	find_textel(float angle, vertex textels, vertex dist, int text_max) {
	float res = ((1.0 - angle) * (textels.x / dist.x)) +
				((angle) * (textels.y / dist.y));
	res = (int)(res /
					  ((1.0 - angle) * (1.0 / dist.x) + (angle * (1.0 / dist.y)))) % text_max;
	return res;
}
