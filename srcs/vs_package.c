/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_package.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:33:40 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/07 13:47:31 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		vs_pack_cell(int y, int x, t_map *map, int type)
{
	int i;

	if (map->vs.cycle != 0 && ((i = map->map[y][x] & ~(map->old_map[y][x]))))
	{
		if (!type)
			map->vs.my_cells[++map->vs.my_num] = y * map->cols + x + 1;
		else
			map->vs.opp_cells[++map->vs.opp_num] = y * map->cols + x + 1;
	}
	else if (map->vs.cycle == 0)
	{
		if (type == 0)
		{
			map->vs.my_cells[++map->vs.my_num] = y * map->cols + x + 1;
		}
		else if (type == 1)
		{
			map->vs.opp_cells[++map->vs.opp_num] = y * map->cols + x + 1;
		}
	}
	return (1);
}

int		send_vs(t_map *map, t_pazzle *pazzle)
{
	char	*buf;

	if (map->vs.cycle == 0 &&
	(map->vs.fd = open("vis.json", O_CREAT | O_TRUNC | O_WRONLY, 0644)) == -1)
	{
		ft_dprintf(map->fd, "%s\n", "vis.json file error\n");
		return (0);
	}
	if (map->vs.fd > 2)
	{
		put_file(map);
		if (map->vs.end_game == 1)
		{
			write(map->vs.fd, "]", 1);
			close(map->vs.fd);
			return (1);
		}
	}
}
