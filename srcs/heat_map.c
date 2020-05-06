/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 21:09:52 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/06 17:29:18 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		set_zeros(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			if (map->heat[y][x] == 0)
				map->heat[y][x] = map->rows + map->cols;
		}
	}
}

void		set_neighbor(t_map *map)
{
	int	y;
	int	x;
	int i;

	i = 0;
	while (++i < map->cols + map->rows)
	{
		y = -1;
		while (++y < map->rows)
		{
			x = -1;
			while (++x < map->cols)
				if (map->heat[y][x] == 0)
				{
					if (x < map->cols - 1 && map->heat[y][x + 1] == i)
						map->heat[y][x] = i + 1;
					else if (y < map->rows - 1 && map->heat[y + 1][x] == i)
						map->heat[y][x] = i + 1;
					else if (x > 0 && map->heat[y][x - 1] == i)
						map->heat[y][x] = i + 1;
					else if (y > 0 && map->heat[y - 1][x] == i)
						map->heat[y][x] = i + 1;
				}
		}
	}
}

void		set_first(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			if (map->heat[y][x] == -2)
				;
			else if (x < map->cols - 1 && map->heat[y][x + 1] == -2)
				map->heat[y][x] = 1;
			else if (y < map->rows - 1 && map->heat[y + 1][x] == -2)
				map->heat[y][x] = 1;
			else if (x > 0 && map->heat[y][x - 1] == -2)
				map->heat[y][x] = 1;
			else if (y > 0 && map->heat[y - 1][x] == -2)
				map->heat[y][x] = 1;
		}
	}
}

static void	set_begin(int y, int x, t_map *map)
{
	if (map->map[y][x] == map->ch_player[0] ||
				map->map[y][x] == map->ch_player[1])
	{
		vs_pack_cell(y, x, map, 0);
		map->heat[y][x] = -1;
	}
	else if (map->map[y][x] == map->ch_opp[0] ||
			map->map[y][x] == map->ch_opp[1])
	{
		vs_pack_cell(y, x, map, 1);
		map->heat[y][x] = -2;
	}
	else
		map->heat[y][x] = 0;
}
