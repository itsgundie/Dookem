//
// Created by Hugor Chau on 8/18/20.
//

#include "../incs/test.h"

void	draw_texture(wall *w_origin, sdl_win *win, data *draw) {
	wall	w;
	float	start_x;
	int		start_y;
	int 	canonical_width;
	int 	canonical_height;
	float	step_x;
	int 	w_x;
//1) получить координаты крайних точек стен
	w.right = change_dot(draw, w_origin->right, w_origin);
	w.left = change_dot(draw, w_origin->left, w_origin);
	canonical_width = fabs(w_origin->left.x - w_origin->right.x);//canonical width
	w_x = canonical_width / 10;//1 стена
	step_x = (float)w_x / (float)win->wall_img[0]->width;
	start_x = (w_origin->left.x - canonical_width % 10) * step_x;
	int i = 0;
	while (i < SCREEN_WIDTH) {
		start_x = (start_x >= win->wall_img[0]->width) ? 0.0 : start_x + step_x;
		i++;
	}
}

void	draw_text(wall borders, float text_x, sdl_win *win) {//есть x, y точек,
	float step = (float)win->wall_img[0]->height / (fabs((borders.right.y) - (borders.left.y)));
//	if ((int)(fabs((borders.right.y) - /*fabs*/(borders.left.y))) == 0)
//		step = 0;
	float y = borders.left.y;
	float y1 = 0.0;
//	printf("my bx2 = %f\n", borders.left.y);

//	while (y < 0.0) {
		if (y < 0.0) {
			y1 = -y * step;
			y = 0.0;
//			y1 += step;
		}
//	}
	if (y > SCREEN_HEIGHT) {
		return;
	}
//	printf("my bx2 = %f\n", y);

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
			((int *)(win->wall_img[0]->pixels))[(int)((int)y1 * win->wall_img[0]->width + text_x)];
		}
		y += 1;
		y1 += step;
	}
}