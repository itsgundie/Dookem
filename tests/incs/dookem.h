#ifndef DOOKEM_H
#define DOOKEM_H

#include "stdint.h"

# include "SDL.h"
# include "SDL_mixer.h"
# include "SDL_image.h"
# include "SDL_ttf.h"


#define PIE 3.14159265358979323846
#define PIE_HALF 1.57079632679489661923
#define PIE_DOUBLE 6.28318530718
#define PIE_AND_HALF 4.71238898038

#define RMASK_BIG 0xFF000000
#define GMASK_BIG 0x00FF0000
#define BMASK_BIG 0x0000FF00
#define AMASK_BIG 0x000000FF
#define AMASK_LITTLE 0xFF000000
#define BMASK_LITTLE 0x00FF0000
#define GMASK_LITTLE 0x0000FF00
#define RMASK_LITTLE 0x000000FF


#define TEXTURE_WIDTH 1024
#define TEXTURE_HEIGHT 1024


#define TRUE 1
#define FALSE 0



#define START_MAP "mapTest.txt"
#define WIN_TITLE "HAIL TO THE KING"
#define WIDTH_WIN 640
#define HEIGHT_WIN 480
#define WIDTH_GAME 640
#define HEIGHT_GAME 640
#define EYE_HEIGHT 6
#define DUCK_HEIGHT 2.5


#define MAX_VISIBLE_SECTORS 16




typedef struct  s_vec2
{
	float       x;
	float          y;
}               t_vec2;

typedef struct  s_vec3
{
	float       x;
	float       y;
	float       z;
}               t_vec3;


typedef struct  s_player
{
	t_vec3		pos;
	t_vec3		velocity;
	float		angle;
	float		angleSin;
	float		angleCos;
	float		yaw;
	int			wsad[4];
	int			ground;
	int			falling;
	int			moving;
	int			ducking;
	unsigned char	current_sector;
}				t_player;

typedef struct	s_ectors
{
	float		floor;
	float		ceil;
	t_vec2		*vertex;
	uint16_t	numOfPoints;
	char		*neighbours;
	int			visible;
}				t_sector;


typedef struct	s_visibility
{
	t_vec2		vis_floor_start[MAX_VISIBLE_SECTORS][WIDTH_GAME];
	t_vec2		vis_floor_end[MAX_VISIBLE_SECTORS][WIDTH_GAME];
	char		vis_floors[MAX_VISIBLE_SECTORS][WIDTH_GAME];
	t_vec2		vis_ceil_start[MAX_VISIBLE_SECTORS][WIDTH_GAME];
	t_vec2		vis_ceil_end[MAX_VISIBLE_SECTORS][WIDTH_GAME];
	char		vis_ceils[MAX_VISIBLE_SECTORS][WIDTH_GAME];
	uint32_t	num_vis_sectors;
}				t_visibility;

typedef struct	s_render
{
	SDL_Window	*win;
	SDL_Renderer *rend;
	SDL_Texture	*color_tex;
	SDL_Surface	*surf;
	SDL_Texture *tex;
	int			indian;
	uint32_t	*color_buffer;
}				t_renderer;

typedef struct	s_dookem
{
	uint32_t	num_of_sectors;
	t_sector	*sectors;
	t_player	player;
	t_visibility	visible_sectors;
	t_renderer	render;
}				t_dookem;

#endif