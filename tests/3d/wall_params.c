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

float	find_full_angle(data *draw, vertex w1, float angle) {
	vertex v1;
	float res;
	v1.x = (draw->m->player->x - w1.x);
	v1.y = (draw->m->player->y - w1.y);
	vertex v2;
	v2.x = (cos(draw->m->player->angle + angle));
	v2.y = (sin(draw->m->player->angle + angle));
	res = -(((v1.x * v2.x + v1.y * v2.y) / (sqrt(v1.x * v1.x + v1.y * v1.y)
											* sqrt(v2.x * v2.x + v2.y * v2.y))));

	res = res >= 1 ? acos(1) : res <= -1 ? acos(-1) : acos(res);
	res = (180 / M_PI * res) / 90.0;
	return res;
}

float	find_step(vertex check, data *draw, int hit_side) {
	float hit_angle;

	hit_angle = 0.0;//if side is MIDDLE - there was not hit with FOV-lines
	if (hit_side == MIDDLE)
		return hit_angle;
	if (is_overlap(draw, check, draw->m->player->angle + DEGREES_45) == TRUE &&
			(is_overlap(draw, check, draw->m->player->angle - DEGREES_45) == TRUE)) {
		if (is_overlap(draw, check, draw->m->player->angle + DEGREES_45 * 2) == TRUE) {
			hit_angle = find_full_angle(draw, check, -DEGREES_45);
//			printf("HERE %f\n", hit_angle);
		}
		else {
			hit_angle = find_full_angle(draw, check, DEGREES_45);
//			printf("OVER HERE %f\n", hit_angle);
		}
//		return hit_angle;
//		hit_angle += 1.0;
	}
	else {
		if (hit_side == LEFT) {
			//ищу угол по левый луч FOV
			hit_angle = find_full_angle(draw, check, -DEGREES_45);
		}
		if (hit_side == RIGHT) {
			hit_angle = find_full_angle(draw, check, DEGREES_45);
		}
	}
	hit_angle = hit_side == LEFT ? hit_angle * -1 : hit_angle;
//	printf("%f\n", hit_angle);
	return hit_angle;
}

float 	find_textel(float angle, vertex textels, vertex dist, int text_max) {
	float res = ((1.0 - angle) * (textels.x / dist.x)) +
				((angle) * (textels.y / dist.y));
	res = (int)(res /
					  ((1.0 - angle) * (1.0 / dist.x) + (angle * (1.0 / dist.y)))) % text_max;
	return res;
}



//vertex hit;
//hit.x = floor(cos(start_dist));
//hit.y = floor(sin(start_dist));
//hit.x = cos(start_dist) - hit.x;
//hit.y = sin(start_dist) - hit.y;
//common_start_x = hit.x * win->wall_img[0]->width;
//////крайние пиксели текстуры????
//hit.x = floor(cos(end_dist));
//hit.y = floor(sin(end_dist));
//hit.x = cos(end_dist) - hit.x;
//hit.y = sin(end_dist) - hit.y;
//end_dist = hit.x * win->wall_img[0]->width;