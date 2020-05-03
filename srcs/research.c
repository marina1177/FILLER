#include "filler.h"

void	real_pazzle_size(t_pazzle *pazzle)
{
	int i;
	int j;

	pazzle->left = pazzle->cols;
	pazzle->up = pazzle->rows;
	i = -1;
	while (++i < pazzle->rows)
	{
		j = -1;
		while (++j < pazzle->cols)
		{
			if (pazzle->piece[i][j] == '*')
			{
				if (j < pazzle->left)
					pazzle->left = j;
				if (j > pazzle->right)
					pazzle->right = j;
				if (i < pazzle->up)
					pazzle->up = i;
				if (i > pazzle->down)
					pazzle->down = i;
			}
		}
	}
}

int		valid_place(t_map *map, t_pazzle *pazzle, int x, int y)
{
	int j;
	int i;
	int put;

	if (pazzle->right + 1 + x - pazzle->left > map->cols ||
			pazzle->down + 1 - pazzle->up + y > map->rows)
		return (0);
	put = 0;
	j = -1 + pazzle->up;
	while (++j < pazzle->down + 1)
	{
		i = -1 + pazzle->left;
		while (++i < pazzle->right + 1)
		{
			if (pazzle->piece[j][i] == '*' && (map->map[y + j - pazzle->up]
			[x + i - pazzle->left] == map->ch_opp[0] || map->map[y + j - pazzle->up]
			[x + i - pazzle->left] == map->ch_opp[1]))
				return (0);
			else if (pazzle->piece[j][i] == '*' && (map->map[y + j - pazzle->up]
			[x + i - pazzle->left] == map->ch_player[0] || map->map[y + j - pazzle->up]
			[x + i - pazzle->left] == map->ch_player[1]))
				put++;
		}
	}
	return ((put == 1) ? 1 : 0);
}

int		solve(t_map *map, t_pazzle *pazzle)
{
	int x;
	int y;
	int value;

	value = INT32_MAX;
	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			if (valid_place(map, pazzle, x, y) && map->heat[y][x] <= value)
			{
				map->fin_x = x - pazzle->left;
				map->fin_y = y - pazzle->up;
				value = map->heat[y][x];
			}
		}
	}
	if (value == INT32_MAX)
		return (0);
	return (1);

}

int		research(t_map *map, t_pazzle *pazzle)
{
	pazzle->down = 0;
	pazzle->right = 0;
	real_pazzle_size(pazzle);
	return(solve(map, pazzle));
}
