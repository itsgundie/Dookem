#include "../incs/test.h"

//add perspective correction by height to make textures with incline (наклон)

void	draw_text(wall borders, float text_x, sdl_win *win, int text_num) {
	float step = (float)win->wall_img[0]->height / (fabs((borders.right.y) - (borders.left.y)));
	float y = borders.left.y;
	float y1 = 0.0;

		if (y < 0.0) {
			y1 = -y * step;
			y = 0.0;
		}
	if (y > SCREEN_HEIGHT) {
		return;
	}

	if (text_x < 0 || text_x > win->wall_img[0]->width)
		return;
	if (borders.left.x < 0 || borders.left.x > SCREEN_WIDTH)
		return;
	while (y < borders.right.y) {
		if (y1 >= win->wall_img[0]->height || y1 < 0)
			return;
		if (y >= SCREEN_HEIGHT)
			return;
		if (borders.left.x >= 0 && y >= 0 &&
		borders.left.x < SCREEN_WIDTH && y < SCREEN_HEIGHT) {
			((int *)(*(win->bmap)))[(int)((int)borders.left.x + (int)y * SCREEN_WIDTH)] =
			((int *)(win->wall_img[text_num]->pixels))[(int)((int)y1 * win->wall_img[text_num]->width + text_x)];
		}
		y += 1;
		y1 += step;
	}
}
