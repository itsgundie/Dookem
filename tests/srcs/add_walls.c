//
// Created by Hugor Chau on 7/29/20.
//
#include "../incs/test.h"

void	add_walls(data	draw) {
	int fd = open(draw.m->filename, O_RDWR);
//		if (fd < 0) {
//			error("Map error. Can't write in file", 2);
//		}
	for (int i = 0; i < draw.m->w_count; i++) {
		write(fd, "wall{(", ft_strlen("wall{("));
		write(fd, ft_itoa(draw.m->walls[i].left.x),
			  ft_strlen(ft_itoa(draw.m->walls[i].left.x)));
		write(fd, ",", 1);
		write(fd, ft_itoa(draw.m->walls[i].left.y),
			  ft_strlen(ft_itoa(draw.m->walls[i].left.y)));
		write(fd, ")(", 2);
		write(fd, ft_itoa(draw.m->walls[i].right.x),
			  ft_strlen(ft_itoa(draw.m->walls[i].right.x)));
		write(fd, ",", 1);
		write(fd, ft_itoa(draw.m->walls[i].right.y),
			  ft_strlen(ft_itoa(draw.m->walls[i].right.y)));
		write(fd, ")}\n", 3);
	}
	close(fd);
}