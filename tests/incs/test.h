//
// Created by Hugor Chau on 7/24/20.
//

#ifndef TESTS_TEST_H
#define TESTS_TEST_H

/*
**		includes
**/
# include "SDL.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "error.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <math.h>

#define ERROR			"\033[38;2;200;0;30m"
#define EOC				"\033[38;2;0m"
#define SCREEN_WIDTH	600
#define SCREEN_HEIGHT	500
#define TRUE			1
#define FALSE			0
#define NOT_NULL		(void *)(size_t)1
#define WIN_NAME		"1 test: where is player placed on non-convex sector?"
#define WIN_3D			"3d test: how to render?"
#define LEFT			0
#define RIGHT			1
#define MIDDLE			2
#define BACK			3
#define DEGREES_45		0.785398
#define TANGENT_45		1.61977519054
#define TANGENT_90		-1.99520041221

struct		s_data;

typedef struct s_textures{
	unsigned char	*pixels;
	int				width;
	int 			height;
}				t_textures;

typedef struct		s_sdl_win {

	SDL_Window		*window;
	SDL_Renderer	*render;

	SDL_Texture		*texture;
	SDL_Rect		*rect;
	unsigned char	**bmap;

	t_textures		*wall_img[3];
//	SDL_Surface		*surface;
	void			(*update_texture)(struct s_sdl_win *win, struct s_data *draw);
}					sdl_win;

typedef struct		s_vertex {
	float				x;
	float				y;
}					vertex;

typedef struct		s_wall {
	vertex			left;
	vertex			right;
	int				height;
	int				is_portal;
	int 			texture_num;
}					wall;

typedef struct		s_player {
	float			x;
	float			y;
	float			angle;//direction
	wall			*seeing_walls;//?
	int				inside;
}					t_player;

typedef struct		s_map {
	wall			*walls;
	int				w_count;
	int				is_new;
	const char		*filename;
	t_player		*player;
}					map;

typedef struct		s_data {
	map				*m;
}					data;

typedef struct		s_test {
	void			(*f)(struct s_test);
}					test;

typedef struct		s_vertex_x
{
	float			start;
	float			end;
}					vertex_x;

typedef struct s_borders {

}				t_borders;
/*
**		init
*/
void	init_window(sdl_win *init, char *name);
/*
**		2D
*/
void	main_loop(sdl_win *win, sdl_win *win3d, data *draw);
int 	inside (long x, long y, data *draw);
int 	inside_vp(float x, float y, data *draw);
void	draw_line(wall *w, unsigned char **pix_array, int color);

/*
**		potential visible walls
*/
void	get_walls_in_front(data *draw, wall **w, int *w_count);
void	update_texture(sdl_win *win, data *draw);
float	find_destination(wall *w1, t_player *p);
vertex	get_perpendicular_dot(t_player *p, wall *w);

/*
**		3D
*/
void	update_3D_image(sdl_win *win, data *draw);
void	draw_wall(wall *w_origin, sdl_win *win, data *draw);
void	draw_texture(wall *w_origin, sdl_win *win, data *draw);
float 	wall_h(vertex point, float width, t_player *player);
void	draw_text(wall borders, float text_x, sdl_win *win, int text_num);
void	draw_line(wall *w, unsigned char **pix_array, int color);
void	update_texture(sdl_win *win, data *draw);

/*
**		texture mapping
*/
float 	find_textel(float angle, vertex textels, vertex dist, int text_max);

/*
**		checking 3D-boundaries
*/
void	wall_delineation(wall *w_origin, sdl_win *win, data *draw);

/*
**		wall clipping
*/
vertex	horizontal_clipping(data *draw, vertex original_dot, wall *full_wall);
float	find_angle(data *draw, vertex w1);

/*
**		wall sort
*/
float	find_destination(wall *w1, t_player *p);
int		possible_vision(wall *w, t_player *p);
/*
**		tools
*/
void	error(char *error, int ex);
void	*safe_call(void *res, void *expression, char *error_message);
void	put_bitmap(sdl_win *win);

/*
**		parsing
*/
map		*simple_parse(char *map);
void	add_walls(data	draw);

/*
**		SDL events
*/
void	mouse_events(SDL_Event event, data *draw, int *is_pressed);
void	key_event(SDL_Event *event, data *draw);

#include "3d.h"

#endif //TESTS_TEST_H
