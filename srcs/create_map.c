
#include "filler.h"

void	init_player(t_map *map)
{
	char	*line;
	char	ret;

	ft_dprintf(map->fd, "%s\n", "INIT PLAYER:");
	if ((ret = get_next_line(0, &line)) == -1)
		return ;
	ft_dprintf(map->fd, "	__%s\n", line);
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
	ft_dprintf(map->fd, "num player = %d\n", map->num_player);
}

static void	init_map(t_map *map)
{
	char	*pnt;
	char	*line;
	char	ret;

	pnt = NULL;

	if ((ret = get_next_line(0, &line) == -1))
		return ;
	if (ft_strstr(line, "Plateau"))
	{
		pnt = line + 8;
		map->rows = ft_atoi(pnt);
		while (*pnt >= '0' && *pnt <= '9')
			pnt++;
		map->cols = ft_atoi(++pnt);
	}
	free(line);
	ft_dprintf(map->fd, "	init map:[%d, %d]\n", map->rows, map->cols);

}

int		create_map(t_map *map)
{
	char	*line;
	int		y;
	int		size;

	ft_dprintf(map->fd, "%s:\n", "CREATE MAP");
	
	y = -1;
	init_map(map);

	if (!(map->map = malloc(sizeof(char*) * map->rows + 1)))
		return (0);
	while (++y < map->rows + 1)
	{
		get_next_line(0, &line);
		
		if (y > 0 && y < map->rows + 1)
		{
			ft_dprintf(map->fd, "__%s\n", line);
			map->map[y - 1] = ft_strdup(line + 4);
			//ft_dprintf(map->fd, "++%s\n", map->map[y-1]);
		}
		free(line);
	}
	y = -1;
	map->heat = (int **)malloc(sizeof(int *) * map->rows);
	while (++y < map->cols)
		map->heat[y] = malloc(sizeof(int) * map->cols);
	return (1);
}


	/*while ((size = get_line(0, &line)))
	{
		init_map(map, line);
		
		ft_strdel(&line);
	}
	if (size == -1)
		return ;
}*/