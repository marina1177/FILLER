/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:44:25 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/06 16:49:47 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	game(t_map *map, t_pazzle *pazzle)
{
	send_vs(map, pazzle);
	print_coord(map, pazzle);
	if (map->vs.cycle != 0)
		ft_free2d((void**)(map->old_map), map->rows);
	map->old_map = map->map;
	ft_free2d((void**)(map->heat), map->rows);
	map->vs.cycle++;
}

void	print_coord(t_map *map, t_pazzle *pazzle)
{
	int i;

	i = -1;
	ft_putnbr(map->fin_y);
	ft_putchar(' ');
	ft_putnbr(map->fin_x);
	ft_putchar('\n');
	ft_free2d((void**)(pazzle->piece), pazzle->rows);
	pazzle->piece = NULL;
}

void	start_init(t_map *map, t_pazzle *pazzle)
{
	ft_bzero(map, sizeof(t_map));
	ft_bzero(pazzle, sizeof(t_pazzle));
	map->vs.my_num = -1;
	map->vs.opp_num = -1;
	map->vs.fd = -1;
	map->old_map = NULL;
	map->map = NULL;
	map->heat = NULL;
	map->fd = open("logs.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	ft_dprintf(map->fd, "%s\n", "START GAME:");
	map->vs.cycle = 0;
	map->vs.end_game = 0;
	pazzle->piece = NULL;
}

int		main(void)
{
	t_map			map;
	t_pazzle		pazzle;

	start_init(&map, &pazzle);
	if (!init_player(&map))
		return (handle_error(&map, &pazzle, "init player error\n"));
	while (TRUE)
	{
		ft_dprintf(map.fd, "<<<CYCLE #%d>>>\n", map.vs.cycle);
		if (!create_map(&map))
			return (handle_error(&map, &pazzle, "create map error\n"));
		ft_dprintf(map.fd, "%s\n", "create map succesfully");
		if (!parse_pazzle(&map, &pazzle))
			return (handle_error(&map, &pazzle, "parse pazzle error\n"));
		ft_dprintf(map.fd, "%s\n", "parse pazzle succesfully");
		heat_map(&map);
		ft_dprintf(map.fd, "%s\n", "create heat_map succesfully");
		if (research(&map, &pazzle))
		{
			game(&map, &pazzle);
		}
		else
			return (handle_error(&map, &pazzle, "END GAME!\n"));
	}
	return (0);
}
