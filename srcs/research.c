/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   research.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:35:16 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/06 17:09:40 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	real_pazzle_size(t_map *map, t_pazzle *pazzle)
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
	int	var[3];

	if (pazzle->right + 1 + x - pazzle->left > map->cols ||
			pazzle->down + 1 - pazzle->up + y > map->rows)
		return (0);
	var[2] = 0;
	var[1] = -1 + pazzle->up;
	while (++var[1] < pazzle->down + 1)
	{
		var[0] = -1 + pazzle->left;
		while (++var[0] < pazzle->right + 1)
		{
			if (pazzle->piece[var[1]][var[0]] == '*' &&
			(map->map[y + var[1] - pazzle->up][x + var[0] - pazzle->left]
			== map->ch_opp[0] || map->map[y + var[1] - pazzle->up]
			[x + var[0] - pazzle->left] == map->ch_opp[1]))
				return (0);
			else if (pazzle->piece[var[1]][var[0]] == '*' &&
			(map->map[y + var[1] - pazzle->up][x + var[0] - pazzle->left]
			== map->ch_player[0] || map->map[y + var[1] - pazzle->up]
			[x + var[0] - pazzle->left] == map->ch_player[1]))
				var[2]++;
		}
	}
	return ((var[2] == 1) ? 1 : 0);
}

int		solve(t_map *map, t_pazzle *pazzle)
{
	int	v[3];

	v[2] = INT32_MAX;
	v[1] = -1;
	while (++v[1] < map->rows)
	{
		v[0] = -1;
		while (++v[0] < map->cols)
		{
			if (valid_place(map, pazzle, v[0], v[1]) &&
			map->heat[v[1]][v[0]] <= v[2])
			{
				map->fin_x = v[0] - pazzle->left;
				map->fin_y = v[1] - pazzle->up;
				v[2] = map->heat[v[1]][v[0]];
			}
		}
	}
	if (v[2] == INT32_MAX)
	{
		ft_dprintf(map->fd, "		no\n");
		return (0);
	}
	ft_dprintf(map->fd, "		yes\n");
	return (1);
}

int		research(t_map *map, t_pazzle *pazzle)
{
	pazzle->down = 0;
	pazzle->right = 0;
	real_pazzle_size(map, pazzle);
	return (solve(map, pazzle));
}
