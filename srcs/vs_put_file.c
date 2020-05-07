/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_put_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:33:22 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/07 16:01:00 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	put_opp_cells(t_vs *vs)
{
	int num;

	vs_putstr_fd(vs->fd, ",\n\t\"opp_cells\": [");
	num = vs->opp_num;
	while (num > -1)
	{
		vs_itoa_fd(vs->fd, vs->opp_cells[num]);
		if (num == 0)
			break ;
		vs_putstr_fd(vs->fd, ",");
		num--;
	}
	vs_putstr_fd(vs->fd, "]");
}

void	put_my_cells(t_vs *vs)
{
	int num;

	vs_putstr_fd(vs->fd, ",\n\t\"my_cells\": [");
	num = vs->my_num;
	while (num > -1)
	{
		vs_itoa_fd(vs->fd, vs->my_cells[num]);
		if (num == 0)
			break ;
		vs_putstr_fd(vs->fd, ",");
		num--;
	}
	vs_putstr_fd(vs->fd, "]");
}

void	put_map_const(t_map *map, t_vs *vs)
{
	const char *s[2];

	s[0] = "\"Oo\"";
	s[1] = "\"Xx\"";
	vs_putstr_fd(vs->fd, "\n\t{\"Consts\": {\n\t\t\"map_rows\": ");
	vs_itoa_fd(vs->fd, map->rows);
	vs_putstr_fd(vs->fd, A_MCOLS);
	vs_itoa_fd(vs->fd, map->cols);
	vs_putstr_fd(vs->fd, A_MY_CH);
	vs_putstr_fd(vs->fd, s[map->num_player - 1]);
	vs_putstr_fd(vs->fd, A_OPP_CH);
	vs_putstr_fd(vs->fd, s[map->num_opp - 1]);
	vs_putstr_fd(vs->fd, "\n\t},");
}

void	put_file(t_map *map)
{
	if (map->vs.cycle == 0)
	{
		vs_putstr_fd(map->vs.fd, "[");
		put_map_const(map, &map->vs);
	}
	else
	{
		vs_putstr_fd(map->vs.fd, ",{");
	}
	vs_putstr_fd(map->vs.fd, A_END_GAME);
	vs_itoa_fd(map->vs.fd, map->vs.cycle);
	vs_putstr_fd(map->vs.fd, A_CYCLE);
	vs_itoa_fd(map->vs.fd, map->vs.cycle);
	if (map->vs.cycle < 0)
	{
		vs_putstr_fd(map->vs.fd, "\n}");
		return ;
	}
	put_my_cells(&map->vs);
	ft_dprintf(map->fd, "opp_cells: num = %d\n", map->vs.opp_num);
	put_opp_cells(&map->vs);
	map->vs.my_num = -1;
	map->vs.opp_num = -1;
	vs_putstr_fd(map->vs.fd, "\n}");
}
