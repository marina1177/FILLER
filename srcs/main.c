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

void	free_map(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->rows)
	{
		free(map->map[i]);
		map->map[i] = NULL;
	}
	while (--i > -1)
	{
		free(map->heat[i]);
	}
	free(map->map);
	free(map->heat);
	map->map = NULL;
	ft_putstr("0 0\n");
}

void	print_coord(t_map *map, t_pazzle *pazzle)
{
	int i;

	i = -1;
	ft_printf("%d %d\n",map->fin_y,map->fin_x);
	while (++i < pazzle->rows)
		ft_strdel(&pazzle->piece[i]);
	free(pazzle->piece);
	pazzle->piece = NULL;
}

int		main(void)
{
	t_map		map;
	t_pazzle		pazzle;

	ft_bzero(&map, sizeof(t_map));
	ft_bzero(&pazzle, sizeof(t_pazzle));
	if (!create_map(&map))
	{
		ft_dprintf(2, "%sError: Invalid input%s\n", RED, EOC);
		return (0) ;
	}
	while (TRUE)
	{
		parse_pazzle(&map, &pazzle);
		heat_map(&map);
		if (research(&map, &pazzle))
			print_coord(&map, &pazzle);
		else
		{
			free_map(&map);
			break ;
		}
	}
	return (0);
}
