
#include "dookem.h"

#define MAP_FILE "mapTest.txt"

#define min(a,b)			 (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)			 (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)	  min(max(a,mi),ma)		 // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)	((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((t_vec2) { \
	vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
	vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })

#define Yaw(y,z) (y + z*doomer->senior_tomato.yaw)



void    loading(t_dookem *doomer)
{
	FILE *fp = fopen(MAP_FILE, "rt");

	if (!fp)
	{
		perror(MAP_FILE);
		exit(1);
	}
	
	char buf[256];
	char word[256];
	char *ptr;
	t_vec2 *vert;
	t_vec2 v;

	int32_t n = 0;
	int32_t m = 0;
	int32_t num_of_vert = 0;

	while(fgets(buf, sizeof(buf), fp))
		switch(sscanf(ptr = buf, "%32s%n", word, &n) == 1 ? word[0] : '\0')
		{
			case 'v':
				for(sscanf(ptr += n, "%f%n", &v.y, &n); sscanf(ptr += n, "%f%n", &v.x, &n) == 1; )
				{
					vert = realloc(vert, ++num_of_vert * sizeof(*vert));
					vert[num_of_vert - 1] = v;
					printf("Case 'V', x - %f and y - %f\n", v.x, v.y);
				}
				break;
			case 's':
				doomer->sectors = realloc(doomer->sectors, ++doomer->num_of_sectors * sizeof(t_sector));
				t_sector *sic = &(doomer->sectors[doomer->num_of_sectors - 1]);
				int32_t *num = NULL;
				sscanf(ptr += n, "%f%f%n", &sic->floor, &sic->ceil, &n);
				for(m = 0; sscanf(ptr += n, "%32s%n", word, &n) == 1 && word[0] != '#'; )
				{
					num = realloc(num, ++m * sizeof(*num));
					num[m - 1] = word[0] == 'x' ? -1 : atoi(word);
				}
				sic->numOfPoints = m /= 2;
				sic->neighbours = malloc((m + 1) * sizeof(*sic->neighbours));
				sic->vertex = malloc((m + 1) * sizeof(*sic->vertex));
				for( n = 0; n < m; ++n)
				{
					sic->neighbours[n] = num[m + n];
				}
				for( n = 0; n < m; ++n)
				{
					sic->vertex[n + 1] = vert[num[n]];
				}
				sic->vertex[0] = sic->vertex[m];
				//free(num);
				printf( "Case 's', x - %f and y - %f\n",sic->vertex[0].x, sic->vertex[0].y);
				num = NULL;
				break;
			case 'p':;
				float angle;
				sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle, &n);
				doomer->player.pos.x = v.x;
				doomer->player.pos.y = v.y;
				doomer->player.angle = angle;
				doomer->player.current_sector = n;
				doomer->player.pos.z = doomer->sectors[n].floor + EYE_HEIGHT;
				doomer->player.angleCos = 0;
				doomer->player.angleSin = 0;
				doomer->player.velocity = (t_vec3) {0,0,0};
				doomer->player.yaw = 0;
				printf( "Case 'p', x - %f and y - %f\n",doomer->player.pos.x, doomer->player.pos.y);
		}
	fclose(fp);
	free(vert);
	vert = NULL;
	exit(1);
}

int		init(t_dookem *doomer)
{
	return(0);
}

void    render(t_dookem *doomer)
{
	return ;
}


void    controls(void)
{
	return ;
}

void    update(t_dookem *doomer)
{
	return ;
}

int main(void)
{
	t_dookem doomer = {0};

	loading(&doomer);

	if(!(init(&doomer)))
	{
		printf("Render init failed {;_;} \n");
		exit(1);
	}

	while(1)
	{
		render(&doomer);
		update(&doomer);
		controls();
	}
	return(0);
}