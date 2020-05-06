/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:17:13 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/06 17:29:23 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			init_player(t_map *map)
{
	char	*line;
	char	ret;

	if ((ret = get_next_line(0, &line)) == -1)
		return (0);
	if (ft_strstr(line, "p1"))
	{
		map->num_player = 1;
		map->ch_player = CH_P1;
		map->num_opp = 2;
		map->ch_opp = CH_P2;
	}
	else
	{
		map->num_player = 2;
		map->ch_player = CH_P2;
		map->num_opp = 1;
		map->ch_opp = CH_P1;
	}
	free(line);
	return (1);
}

static int	init_map(t_map *map)
{
	char	*pnt;
	char	*line;
	char	ret;

	pnt = NULL;
	if ((ret = get_next_line(0, &line) == -1))
		return (0);
	if (ft_strstr(line, "Plateau"))
	{
		pnt = line + 8;
		map->rows = ft_atoi(pnt);
		while (*pnt >= '0' && *pnt <= '9')
			pnt++;
		map->cols = ft_atoi(++pnt);
	}
	free(line);
	return (1);
}

int			create_map(t_map *map)
{
	char	*line;
	int		y;
	int		size;

	y = -1;
	if (!init_map(map))
		return (0);
	if (!(map->map = malloc(sizeof(char*) * map->rows + 1)))
		return (0);
	while (++y < map->rows + 1)
	{
		get_next_line(0, &line);
		ft_dprintf(map->fd, "%s:\n", line);
		if (y > 0 && y < map->rows + 1)
		{
			map->map[y - 1] = ft_strdup(line + 4);
		}
		free(line);
	}
	y = -1;
	map->heat = (int **)malloc(sizeof(int *) * map->rows);
	while (++y < map->rows)
		map->heat[y] = malloc(sizeof(int) * map->cols);
	return (1);
}

static void	conditions(t_map *map, int y, int x)
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

void	heat_map(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			conditions(map, y, x);
		}
	}
	set_first(map);
	set_neighbor(map);
	set_zeros(map);
}
