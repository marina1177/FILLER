#include "filler.h"

static void		parse_piece(t_pazzle *pazzle, char *line)
{
	int		i;
	char	*pnt;

	pnt = line + 6;
	pazzle->rows = ft_atoi(pnt);
	while (*pnt >= '0' && *pnt <= '9')
		pnt++;
	pazzle->cols = ft_atoi(++pnt);
	pazzle->piece = (char **)malloc(sizeof(char *) * pazzle->rows);
	i = -1;
	while (++i < pazzle->rows)
		pazzle->piece[i] = (char *)malloc(sizeof(char) * pazzle->cols + 2);
}

void			parse_pazzle(t_map *map, t_pazzle *pazzle)
{
	char	*line;
	int		i;
	int		j;
	int		size;

	i = -1;
	j = -1;
	while ((size = get_line(0, &line)))
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
	if (size == -1)
		return ;
}
