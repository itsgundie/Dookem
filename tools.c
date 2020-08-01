
#include "dookem.h"
#include <stdint.h>

uint32_t    min_uint32(uint32_t a, uint32_t b)
{
	return((a < b) ? a : b);
}

int    min_int(int a, int b)
{
	return((a < b) ? a : b);
}

float       min_float(float a, float b)
{
	return((a < b) ? a : b);
}


uint32_t    max_uint32(uint32_t a, uint32_t b)
{
	return((a > b) ? a : b);
}

int		    max_int(int a, int b)
{
	return((a > b) ? a : b);
}

float       max_float(float a, float b)
{
	return((a > b) ? a : b);
}



// int		    abs(int a, int b)
// {
// 	return((a < 0) ? -(a) : a);
// }

float       flo_abs(float a, float b)
{
	return((a < 0) ? -(a) : a);
}

uint32_t	clamp_uint32(uint32_t a, uint32_t minimum, uint32_t maximum)
{
	return(min_uint32(max_uint32(a, minimum), maximum));
}

int			clamp_int(int a, int minimum, int maximum)
{
	return(min_int(max_int(a, minimum), maximum));
}

float		clamp_flo(float a, float minimum, float maximum)
{
	return(min_float(max_float(a, minimum), maximum));
}

int			get_sign(int v)
{
	return(((v) > 0) - ((v) < 0));
}

float		vec2_cross_prod(float x0, float y0, float x1, float y1)
{
	return((x0 * y1) - (x1 * y0));
}

int			overlap_ranges(float a0, float a1, float b0, float b1)
{
	return((min_float(a0, a1) <= max_float(b0, b1)) && (min_float(b0, b1) <= max_float(a0, a1)));
}

t_vec2		vec3_to_vec2(t_vec3 origin)
{
	t_vec2 result;

	result.x = origin.x;
	result.y = origin.y;
	return(result);
}

t_vec3		vec2_to_vec3(t_vec2 origin, float z)
{
	t_vec3 result;

	result.x = origin.x;
	result.y = origin.y;
	result.z = z;
	return(result);
}

int			intersect_2d_boxes(t_vec2 a, t_vec2 b, t_vec2 c, t_vec2 d)
{
	return((overlap_ranges(a.x, b.x, c.x, d.x)) && overlap_ranges(a.y, b.y, c.y, d.y));
}

int			point_from_line(t_vec2 point, t_vec2 line0, t_vec2 line1)
{
	float crossed;

	crossed = vec2_cross_prod((line1.x - line0.x), (line1.y - line0.y), (point.x - line0.x), (point.y - line0.y));
	return(get_sign(crossed));
}

t_vec2		intersect_lines(t_vec2 line_a0, t_vec2 line_a1, t_vec2 line_b0, t_vec2 line_b1)
{
	float cross_a01 = vec2_cross_prod(line_a0.x, line_a0.y, line_a1.x, line_a1.y);
	float cross_b01 = vec2_cross_prod(line_b0.x, line_b0.y, line_b1.x, line_b1.y);
	
	t_vec2 result;

	result.x = (vec2_cross_prod(cross_a01, (line_a0.x - line_a1.x), cross_b01, 
			(line_b0.x - line_b1.x / vec2_cross_prod((line_a0.x - line_a1.x), (line_a0.y - line_a1.y), (line_b0.x - line_b1.x), (line_b0.y - line_b1.y)))));
	result.y = (vec2_cross_prod(cross_a01, (line_a0.y - line_a1.y), cross_b01, 
			(line_b0.y - line_b1.y / vec2_cross_prod((line_a0.x - line_a1.x), (line_a0.y - line_a1.y), (line_b0.x - line_b1.x), (line_b0.y - line_b1.y)))));
	return(result);
}


int		get_indian(int *indian)
{
	unsigned int num;
	char *c;

	num = 1;
	c = (char*)&num;

	if (*c)
		return(1);
	else
		return(0);
}