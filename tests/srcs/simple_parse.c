//
// Created by Hugor Chau on 7/28/20.
//
#include "../incs/test.h"

wall	*create_new_wall(char *str, wall *w) {

//	w = malloc(sizeof(wall));
	w->left.x = -1;
	while (*str && (*str == 'w' || *str == 'a' || *str == 'l'))
		str++;
	while (*str && *str != '}') {
		if (*str == '(') {
			vertex new;
			new.x = ft_atoi(++str);
			while (*str != ',')
				str++;
			new.y = ft_atoi(++str);
			if (w->left.x == -1)
				w->left = new;
			else
				w->right = new;
		}
		str++;
	}
	return w;
}

void	set_player(char *str, map *m) {
	while (*str != '{' && *str != '(') {
		str++;
	}
	str++;
	m->player->x = (float)ft_atoi(str);
	while (*str != ',') {
		str++;
	}
	str++;
	m->player->y = (float)ft_atoi(str);
}

int		count_walls(char *str) {
	int		count = 0;
	while (*str) {
		if (*str == 'w' || (*str == 'p' && *(str + 1) == 'o'))
			count++;
		str++;
	}
	return count;
}

void	get_string_to_struct(char *str, map *m) {
	int		count = count_walls(str);
	m->w_count = count;
	m->walls = malloc(count * (sizeof(wall)));

	count = 0;
	while (*str) {
		if (*str == 'w') {
			create_new_wall(str, &m->walls[count]);
			m->walls[count].is_portal = FALSE;
			count++;
		}
		if (*str == 'p') {
			if (*(str + 1) == 'o') {
				create_new_wall(str, &m->walls[count]);
				m->walls[count].is_portal = TRUE;
				count++;
			}
			else {
				set_player(str, m);
			}
		}
		str++;
	}

}

void	check_borders(float *check, int max) {
	if (*check < 0)
		*check = 0;
	if (*check >= max)
		*check = (max - 1);
}

map		*simple_parse(char *map_name) {
	char full_str[10000];
	int ret = 0;
	map	*m = malloc(sizeof(map));
	m->player = malloc(sizeof(t_player));
	m->player->x = 400;
	m->player->y = 400;
	m->is_new = FALSE;
	int fd = open(map_name, O_RDONLY);

	if (fd < 0) {
		if (!ft_strequ(map_name, "New map"))
			error("Map error. Not a file.", 2);
		else {
			m->w_count = 0;
			m->walls = malloc(100 * (sizeof(wall)));
			m->is_new = TRUE;
			return (m);
		}
	}
	ret = read(fd, full_str, 10000);
	full_str[ret] = '\0';
	get_string_to_struct(full_str, m);
	for (int i = 0; i < m->w_count; i++) {
		check_borders(&m->walls[i].left.x, SCREEN_WIDTH);
		check_borders(&m->walls[i].right.x, SCREEN_WIDTH);
		check_borders(&m->walls[i].left.y, SCREEN_HEIGHT);
		check_borders(&m->walls[i].right.y, SCREEN_HEIGHT);

		printf("wall %d: {(%f, %f)(%f, %f)}\n", i,
				m->walls[i].left.x, m->walls[i].left.y,
				m->walls[i].right.x, m->walls[i].right.y);
	}
	m->player->angle = 0.1;
	m->player->inside = -1;
	//2) почекать символы
	//3)
	return m;
}
