
#include "filler.h"

static void	init_player(t_map *map, char *line)
{
	if (ft_strstr(line, "p1 : [./bcharity.filler"))
	{
		map->num_player = 1;
		map->ch_player = CH_P1;
		map->num_opp = 2;
		map->ch_opp = CH_P2;
	}
	else if (ft_strstr(line, "p2 : [./bcharity.filler"))
	{
		map->num_player = 1;
		map->ch_player = CH_P1;
		map->num_opp = 2;
		map->ch_opp = CH_P2;
	}
}

static void	init_map(t_map *map, char *line)
{
	char	*pnt;

	pnt = NULL;
	if (ft_strstr(line, "Plateau"))
	{
		pnt = line + 8;
		map->rows = ft_atoi(pnt);
		while (*pnt >= '0' && *pnt <= '9')
			pnt++;
		map->cols = ft_atoi(++pnt);
	}
}

int		create_map(t_map *map)
{
	char	*line;
	int		i;
	int		size;

	while ((size = get_line(0, &line)))
	{
		init_player(map, line);
		init_map(map, line);
		ft_strdel(&line);
	}
	if (size == -1)
	{
		return (0);
	}
	map->map = (char**)malloc(sizeof(char *) * map->rows);
	i = -1;
	while (++i < map->rows)
		map->map[i] = (char *)malloc(sizeof(char) * map->cols + 1);
	map->heat = (int **)malloc(sizeof(int *) * map->rows);
	while (--i > -1)
		map->heat[i] = malloc(sizeof(int) * map->cols);
	return (1);
}

