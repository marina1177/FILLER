/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:48:38 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/06 16:49:56 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		init_piece(t_map *map, t_pazzle *pazzle)
{
	char	*pnt;
	char	*line;
	char	ret;

	if ((ret = get_next_line(0, &line) == -1))
		return (0);
	if (ft_strstr(line, "Piece"))
	{
		pnt = line + 6;
		pazzle->rows = ft_atoi(pnt);
		while (*pnt >= '0' && *pnt <= '9')
			pnt++;
		pazzle->cols = ft_atoi(++pnt);
	}
	free(line);
	return (1);
}

int				parse_pazzle(t_map *map, t_pazzle *pazzle)
{
	char	*line;
	int		size;
	int		y;

	y = -1;
	if (!init_piece(map, pazzle))
		return (0);
	if (!(pazzle->piece = malloc(sizeof(char*) * pazzle->rows)))
		return (0);
	while (++y < pazzle->rows)
	{
		if ((size = get_next_line(0, &line)) == -1)
			return (0);
		pazzle->piece[y] = ft_strdup(line);
		free(line);
	}
	return (1);
}
