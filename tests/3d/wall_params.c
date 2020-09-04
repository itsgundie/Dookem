//
// Created by Hugor Chau on 8/18/20.
//

#include "../incs/test.h"

float 	wall_h(vertex point, float width, t_player *player) {
	return width / sqrt(pow(point.x - player->x, 2) + pow(player->y - point.y, 2)) * ((SCREEN_HEIGHT / 2) / TANGENT_45);
}

//float 	find_textel(float angle, vertex textels, vertex dist, int text_max) {
//	float t_start_x = ((1.0 - angle) * (textels.x / dist.x)) +
//				((angle) * (textels.y / dist.y));
//	t_start_x = (int)(t_start_x /
//					  ((1.0 - angle) * (1.0 / dist.x) + (angle * (1.0 / dist.y)))) % text_max;
//	return t_start_x;
//}
