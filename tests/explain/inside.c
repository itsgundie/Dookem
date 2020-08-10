//
// Created by Hugor Chau on 7/30/20.
//

/*
**		simple variant
** 		(works correct if all data is written in int)
*/

/*
**		using structs:
**
** 		struct vertex { int x; int y }
**  	struct wall { vertex left(int x, int y); vertex right(int x, int y); }
**		struct data { map *m; } //only one sector for now
** 		struct map { wall *walls; int w_count; } // all walls in sector as walls[w_count + 1]
*/
int		inside (long x, long y, data *draw)//x, y - current player position
{
	wall *wal;		//iterating in draw->m->walls
	long i, x1, y1, x2, y2;
	unsigned long cnt;
	cnt = 0;
	wal = &draw->m->walls[0];
	i = draw->m->w_count;
	do
	{
		y1 = wal->left.y-y; y2 = wal->right.y-y;
		if ((y1^y2) < 0)
		{
			x1 = wal->left.x-x; x2 = wal->right.x-x;
			if ((x1^x2) >= 0) cnt ^= x1; else cnt ^= (x1*y2-x2*y1)^y2;
		}
		wal++; i--;
	} while (i);
	return(cnt>>31);
}

/*
**		second variant
** 		(as simple as previous, but includes
** 		vector cross product and WORKS WITH FLOATS)
**		needs for extra tests; the whole code need to be cleared
*/

/*
**		using structs:
**
** 		struct vertex { float x; float y }
*/

float cross_product_2d(const vertex *v1, const vertex *v2)
{
	if (v1->y < v2->y)
		return (v1->x * v2->y - v1->y * v2->x);
	return (v2->x * v1->y - v2->y * v1->x);
}

/*
**		using structs:
**
**  	struct wall { vertex left; vertex right; }
*/

int	is_rhs(float x, float y, wall *wal) {
	vertex		v1;
	vertex		v2;

	v1.x = wal->left.x - x;
	v2.x = wal->right.x - x;
	v1.y = wal->left.y - y;
	v2.y = wal->right.y - y;
	return cross_product_2d(&v1, &v2) <= 0 ? 1 : 0;
}

/*
**		using structs:
**
**		struct data { map *m; } //only one sector for now
** 		struct map { wall *walls; int w_count; } // all walls in sector as walls[w_count + 1]
*/

int		inside_vp(float x, float y, data *draw)		//x, y - current player position
{
	wall *wal;
	wal = &draw->m->walls[0];		//iterating in draw->m->walls
	int i = draw->m->w_count;
	int cross_counter = 0;
	do {
		//checking if wall is crossed from left screen side to player's location
		if ((y - wal->left.y) * (y - wal->right.y) < 0) {
			// if player's x position is bigger, than both wall's x's, wall was crossed by x
			if (x > wal->left.x && x > wal->right.x)
				cross_counter += 1;
			// else if one of wall's x's is less than player's x and the second is bigger,
			// we should check is wall on the left or on the right;
			// if it is on the right, than it was crossed
			else if (((x - wal->left.x)) * ((x - wal->right.x)) < 0) {
				cross_counter += is_rhs(x, y, wal);
			}
		}
		wal++; i--;
	} while (i);
	return (cross_counter);
}
