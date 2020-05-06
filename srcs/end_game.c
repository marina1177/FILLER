/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:16:19 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/06 16:49:27 by bcharity         ###   ########.fr       */
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
	if (map->map != NULL)
		ft_free2d((void**)(map->map), map->rows);
	if (map->heat != NULL)
		ft_free2d((void**)(map->heat), map->rows);
	if (map->vs.cycle != 0 && map->old_map != NULL)
		ft_free2d((void**)(map->old_map), map->rows);
	if (pazzle->piece != NULL)
		ft_free2d((void**)(pazzle->piece), pazzle->rows);
	map->map = NULL;
	map->old_map = NULL;
	map->heat = NULL;
	pazzle->piece = NULL;
	if (map->vs.end_game == 1)
		ft_putstr("0 0\n");
}

int		handle_error(t_map *map, t_pazzle *pazzle, char *s)
{
	map->vs.end_game = 1;
	ft_dprintf(map->fd, "%s\n", s);
	send_vs(map, pazzle);
	free_map(map, pazzle);
	close(map->fd);
	return (0);
}
