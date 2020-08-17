#include "../incs/test.h"

int main(int ac, char **av) {
	data	draw;
    sdl_win *win = safe_call(malloc(sizeof(sdl_win)), NOT_NULL, "Malloc crashed."
																"SDL-structs container was not allocated.");
	sdl_win *win3D = init_3D();
	if (ac < 2)
    	error("Hey, test one map at a time, please!", 1);
    init_window(win, WIN_NAME);
	draw.m = simple_parse(av[1]);
    //мапа со стенками
	if (draw.m->is_new == TRUE) {
		if (ac != 3)
			error("Hey, enter new filename, please!", 1);
		draw.m->filename = av[2];
	}
	main_loop(win, win3D, &draw);
	if (draw.m->is_new == TRUE)
		add_walls(draw);
    ft_putendl("You're quit.");
    return 0;
}
