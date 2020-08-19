#include "../incs/test.h"

void	clear_all(sdl_win *win) {
	int	i = 0;

	while (i < (SCREEN_WIDTH) * (SCREEN_HEIGHT) * 4) {
		(*(win->bmap))[i + 1] = 66;
		(*(win->bmap))[i] = 66;
		(*(win->bmap))[i + 2] = 0;
		(*(win->bmap))[i + 3] = 0;
		i += 4;
	}
}

void	update_3D_image(sdl_win *win, data *draw) {
	int count = draw->m->w_count;

	wall *w = &draw->m->walls[0];
	clear_all(win);
	while (count > 0) {
		if (possible_vision(w, draw->m->player)) {
				draw_wall(w, win, draw);
		}
		w++;
		count--;
	}
	put_bitmap(win);
}
