//
// Created by Hugor Chau on 8/18/20.
//

#include "../incs/test.h"

float 	wall_h(vertex point, float width, t_player *player) {
	return width / sqrt(pow(point.x - player->x, 2) + pow(player->y - point.y, 2)) * ((SCREEN_WIDTH / 2) / TANGENT_45);
}

float	vector_leigh(wall *w) {
	return sqrt(pow(w->left.x - w->right.x, 2) + pow(w->left.y - w->right.y, 2));
}

float 	next_y(wall *w, int is_new_wall) {
	int		x0 = w->left.x;
	int		x1 = w->right.x;
	int		y0 = w->left.y;
	int		y1 = w->right.y;
	static int error = 0;
	vertex  res = w->right;

	if (is_new_wall == TRUE) {
		error = 0;
		return 0.0;
	}
	int deltax = abs(x1 - x0);
	int deltay = abs(y1 - y0);
	int deltaerr = (deltay + 1);
	int y = y0;
	int x = x0;
	int diry = y1 - y0;
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	int dirx = x0 < x1 ? 1 : -1;
	if (abs(x1 - x0) > abs(y1 - y0)) {
		while (x != x1) {
			error = error + deltaerr;
			if (error >= (deltax + 1)) {
				y = y + diry;
				error = error - (deltax + 1);
			}
			if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT) {
				return y;
			}
			x += dirx;
		}
	}
	else {
		int diry = y0 < y1 ? 1 : -1;
		int dirx = x1 - x0;
		if (dirx > 0)
			dirx = 1;
		if (dirx < 0)
			dirx = -1;
		int deltaerr = (deltax + 1);
		while (y != y1) {
			error = error + deltaerr;
			if (error >= (deltay + 1))
			{
				x = x + dirx;
				error = error - (deltay + 1);
			}
			else if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
			{
				return y;
			}
			y += diry;
		}
	}
	return 0.0;
}