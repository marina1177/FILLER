#include "filler.h"

static void	init_map(t_map *map)
{
	char	*pnt;
	char	*line;
	char	ret;

	pnt = NULL;

	if ((ret = get_next_line(0, &line) == -1))
		return ;
	if (ft_strstr(line, "Piece"))
	{
		pnt = line + 8;
		map->rows = ft_atoi(pnt);
		while (*pnt >= '0' && *pnt <= '9')
			pnt++;
		map->cols = ft_atoi(++pnt);
	}
	free(line);
}

static void		init_piece(t_map *map, t_pazzle *pazzle)
{
	char	*pnt;
	char	*line;
	char	ret;

	if ((ret = get_next_line(0, &line) == -1))
		return ;
	if (ft_strstr(line, "Piece"))
	{
		pnt = line + 6;
		pazzle->rows = ft_atoi(pnt);
		while (*pnt >= '0' && *pnt <= '9')
			pnt++;
		pazzle->cols = ft_atoi(++pnt);
	}
	free(line);
	ft_dprintf(map->fd, "	init piece:[%d, %d]\n", pazzle->rows, pazzle->cols);
}

void			parse_pazzle(t_map *map, t_pazzle *pazzle)
{
	char	*line;
	int		i;
	int		j;
	int		size;

	int		y;

	y = -1;
	ft_dprintf(map->fd, "PARSE PAZZLE:\n");

	init_piece(	map, pazzle);
	if (!(pazzle->piece = malloc(sizeof(char*) * pazzle->rows)))
		return ;
	while (++y < pazzle->rows)
	{
		get_next_line(0, &line);

		ft_dprintf(map->fd, "__%s\n", line);
		
		pazzle->piece[y] = ft_strdup(line);
		free(line);
	}
}


/*	while ((size = get_line(0, &line)))
	{
		if (line[0] == '0')
		{
			//vs_cells(++i, line + 4);
			ft_strcpy(map->map[++i], line + 4);
		}
		else if (ft_strstr(line, "Piece"))
			parse_piece(pazzle, line);
		else if (line[0] == '.' || line[0] == '*')
		{
			ft_strcpy(pazzle->piece[++j], line);
			if (j == pazzle->rows - 1)
			{
				ft_strdel(&line);
				break ;
			}
		}
		ft_strdel(&line);
	}
	*/
