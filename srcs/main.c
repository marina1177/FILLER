/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:44:25 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/03 13:06:20 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	ft_free2d(void **array, int len)
{
	int i;

	i = -1;
	while (++i < len)
		free(array[i]);
	free(array);
}

void	free_map(t_map *map, t_pazzle *pazzle)
{
	ft_free2d((void**)(map->map), map->rows+1);
	if (pazzle->piece)
		ft_free2d((void**)(pazzle->piece), pazzle->rows);
	ft_free2d((void**)(map->heat), map->rows);
	map->map = NULL;
	ft_putstr("0 0\n");
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
}

int		main(void)
{
	t_map			map;
	t_pazzle		pazzle;

	
	
	ft_bzero(&map, sizeof(t_map));
	ft_bzero(&pazzle, sizeof(t_pazzle));

	int fd = open("logs.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	map.fd = fd;
	ft_dprintf(map.fd, "%s\n", "START!1!:");
	
	init_player(&map);
	int cycle = 0;
	while (TRUE)
	{
		map.fd = fd;
		ft_dprintf(map.fd, "<<<CYCLE #%d>>>\n", cycle++);
		create_map(&map);
		ft_dprintf(map.fd, "%s\n", "create map succsesfully");
		parse_pazzle(&map, &pazzle);
		ft_dprintf(map.fd, "%s\n", "parse pazzle succsesfully");
		heat_map(&map);
		ft_dprintf(map.fd, "%s\n", "create heat_map succsesfully");
		if (research(&map, &pazzle))
			print_coord(&map, &pazzle);
		else
		{
			ft_dprintf(map.fd, "%s\n", "END GAME!");
			free_map(&map, &pazzle);
			return (0);
		}
	}
	close(map.fd);
	return (0);
}
