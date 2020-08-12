//
// Created by Hugor Chau on 7/28/20.
//

#include "../incs/test.h"

void	draw_line(wall *w, unsigned char **pix_array, int color) {
	int		x0 = w->left.x;// = w->left.x;
	int		x1 = w->right.x;// < 0 ? 0 : w->right.x > SCREEN_WIDTH ? SCREEN_WIDTH - 1 : w->right.x;
	int		y0 = w->left.y;// < 0 ? 0 : w->left.y > SCREEN_HEIGHT ? SCREEN_HEIGHT - 1 : w->left.y;
	int		y1 = w->right.y;// < 0 ? 0 : w->right.y > SCREEN_HEIGHT ? SCREEN_HEIGHT - 1 : w->right.y;

	int deltax = abs(x1 - x0);
	int deltay = abs(y1 - y0);
	int error = 0;
	int deltaerr = (deltay + 1);
	int y = y0;
	int x = x0;
	int diry = y1 - y0;// > 0 ? 1 : y1 - y0 < 0 ? -1 : 0;
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	int dirx = x0 < x1 ? 1 : -1;
	if (abs(x1 - x0) > abs(y1 - y0)) {
		while (x != x1) {
//			if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
//				break;
			if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
			((int *)(*pix_array))[((x) + y * SCREEN_WIDTH) - 0] = color;
			error = error + deltaerr;
			if (error >= (deltax + 1)) {
				y = y + diry;
				error = error - (deltax + 1);
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
			if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
				break;
			((int *)(*pix_array))[((x) + y * SCREEN_WIDTH) - 0] = color;
			error = error + deltaerr;
			if (error >= (deltay + 1)) {
				x = x + dirx;
				error = error - (deltay + 1);
			}
			y += diry;
		}
	}
}