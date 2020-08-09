
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



void	parse_map(t_dookem *doomer)
{
	FILE *fp = fopen(MAP_FILE, "rt");

	if(!fp)
	{
		perror(MAP_FILE);
		exit(1);
	}

	char buf[256] = {0};
	char word[256] = {0};
	char *ptr = NULL;

	t_vec2 *vert = NULL;
	t_vec2 v = (t_vec2){0};

	int32_t n = 0;
	int32_t verticesNum = 0;

	int32_t NumOfVec = 0;
	int32_t NumOfSec = 0;
	int32_t NumOfPlayers = 0;


	while(fgets(buf, sizeof(buf), fp))
	{
		ptr = buf;
		if(sscanf(ptr, "%32s%n", word, &n) == 1)
		{
			if(word[0] == 'v')
			{
				while(sscanf(ptr += n, "%f%n", &v.y, &n))
				{
					while(sscanf(ptr += n, "%f%n", &v.x, &n) == 1)
					{
						NumOfVec++;
					}
				}
			}
			else if(word[0] == 's')
				{
				NumOfSec++;
				}
			else if(word[0] == 'p')
			{
				NumOfPlayers++;
			}
		}
	}

	fclose(fp);

	bzero(buf, sizeof(buf));
	bzero(word, sizeof(word));
	ptr = NULL;
	v = (t_vec2){0};
	n = 0;

	if(NumOfSec == 0 || NumOfVec == 0 || NumOfPlayers != 1)
	{
		perror("Not enough data on map\n");
		exit(1);
	}	

	if(NumOfVec)
	{
		vert = (t_vec2*)malloc(sizeof(t_vec2) * NumOfVec);
		if(vert == NULL)
		{
			perror("Vertices malloc failed\n");
			exit(1);
		}
	}

	if(NumOfSec)
	{
		doomer->sectors = (t_sector*)malloc(sizeof(t_sector) * NumOfSec);
		if(doomer->sectors == NULL)
		{
			perror("Vertices malloc failed\n");
			exit(1);
		}		
	}

	NumOfVec = 0;
	NumOfSec = 0;
	NumOfPlayers = 0;
	
	fp = fopen(MAP_FILE, "rt");

	if(!fp)
	{
		perror(MAP_FILE);
		exit(1);
	}

	while(fgets(buf, sizeof(buf), fp))
	{
		ptr = buf;
		if(sscanf(ptr, "%32s%n", word, &n) == 1)
		{
			if(word[0] == 'v')
			{
				sscanf(ptr += n, "%f%n", &v.y, &n);
				while(sscanf(ptr += n, "%f%n", &v.x, &n) == 1)
				{
					NumOfVec++;
					vert[NumOfVec - 1] = v;
				}
			}				
			//parse_vector();
			else if(word[0] == 's')
			{
				int32_t num[256] = {0};
				t_sector *this_sect = NULL;
				int32_t m = 0;


				NumOfSec++;
				this_sect = &doomer->sectors[NumOfSec - 1];

				sscanf(ptr += n, "%f%f%n", &this_sect->floor, &this_sect->ceil, &n);

				while(word[0] != '#' && (sscanf(ptr += n, "%32s%n", word, &n) == 1))
				{
					m++;
					num[m -1] = (word[0] == 'x' ? -1 : atoi(word));
				}
				this_sect->numOfPoints = m /= 2;
				this_sect->neighbours = malloc(sizeof(*this_sect->neighbours) * m);
				this_sect->vertex = (t_vec2*)malloc(sizeof(*this_sect->vertex) * (m + 1));

				if(this_sect->neighbours == NULL || this_sect->vertex == NULL)
				{
					perror("Malloc of this sektor's neighbours or vertices FAILED\n");
					exit(1);
				}

				n = 0;
				while(n < m)
				{
					this_sect->neighbours[n] = num[m + n];
					n++;
				}

				n = 0;
				while(n < m)
				{
					this_sect->vertex[n + 1] = vert[num[n]];
					n++;
				}

				this_sect->vertex[0] = this_sect->vertex[m];
			}	
			//parse_sector();
			else if(word[0] == 'p')
			{
				float angle;
				sscanf(ptr += n, "%f %f %f %d", &v.x, &v.y, &angle, &n);
				doomer->player = (t_player) { {v.x, v.y, 0}, {0, 0, 0}, angle, 0, 0, 0, n};
				doomer->player.pos.z = doomer->sectors[doomer->player.current_sector].floor + EYE_HEIGHT;
			}	
			//parse_player();
		}
	}
	fclose(fp);
	free(vert);
	vert = NULL;
	return ;
}


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
					t_vec2 *tmp_vec = vert;
					vert = realloc(vert, ++num_of_vert * sizeof(t_vec2));
					if (vert == NULL)
					{
						printf("realloc of 'V' is failed\n");
						free(tmp_vec);
						exit(1);
					}
					vert[num_of_vert - 1] = v;
					printf("Case 'V', x - %f and y - %f\n", v.x, v.y);
				}
				break;
			case 's':;
				t_sector *tmp_sec = doomer->sectors;
				doomer->sectors = realloc(doomer->sectors, ++doomer->num_of_sectors * sizeof(t_sector));
				if (doomer->sectors == NULL)
				{
					printf("realloc of 'S' is failed\n");
					free(tmp_sec);
					exit(1);
				}				
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
	t_dookem *doomer = (t_dookem*)malloc(sizeof(t_dookem));

	bzero(doomer, sizeof(t_dookem));

	// t_dookem doomer = {0};

	// loading(&doomer);
	parse_map(doomer);

	if(!(init(doomer)))
	{
		printf("Render init failed {;_;} \n");
		exit(1);
	}

	while(1)
	{
		render(doomer);
		update(doomer);
		controls();
	}
	return(0);
}