/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:44:46 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/07 11:29:50 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define TRUE 1
# define FALSE 0

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "vs_const.h"

# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include <stdio.h>

# define MY_NAME "bcharity.filler"
# define CH_P1 "Oo"
# define CH_P2 "Xx"
# define NUM_P1 01
# define NUM_P2 10

typedef struct	s_vs
{
	int			end_game;
	int			cycle;
	int			my_num;
	int			my_cells[100];
	int			opp_num;
	int			opp_cells[200];
	int			fd;
}				t_vs;

typedef struct	s_map
{
	int			fd;
	char		**map;
	char		**old_map;
	int			**heat;

	char		*ch_player;
	int			num_player;
	char		*ch_opp;
	int			num_opp;

	int			rows;
	int			cols;
	int			fin_x;
	int			fin_y;
	t_vs		vs;

}				t_map;

typedef struct	s_pazzle
{
	char		**piece;
	int			rows;
	int			cols;
	int			up;
	int			left;
	int			down;
	int			right;

}				t_pazzle;

/*
** end_game.c
*/
int				handle_error(t_map *map, t_pazzle *pazzle, char *s);
void			ft_free2d(void **array, int len);
void			free_map(t_map *map, t_pazzle *pazzle);

/*
** vs_itoa_fd.c
*/
int				vs_itoa_fd(int fd, int n);

/*
** vs_utilites.c
*/
int				count_dig(size_t val);
int				vs_putstr_fd(int fd, char const *s);
/*
** vs_package.c
*/
void			put_opp_cells(t_vs *vs);
void			put_my_cells(t_vs *vs);
void			put_map_const(t_map *map, t_vs *vs);
void			put_file(t_map *map);
int				vs_pack_cell(int y, int x, t_map *map, int type);
int				send_vs(t_map *map, t_pazzle *pazzle);

/*
** research.c
*/
void			real_pazzle_size(t_map *map, t_pazzle *pazzle);
int				valid_place(t_map *map, t_pazzle *pazzle, int x, int y);
int				solve(t_map *map, t_pazzle *pazzle);
int				research(t_map *map, t_pazzle *pazzle);

/*
** heat_map.c
*/
void			set_zeros(t_map *map);
void			set_neighbor(t_map *map);
void			set_first(t_map *map);
void			heat_map(t_map *map);

/*
** parse.c
*/
int				parse_pazzle(t_map *map, t_pazzle *pazzle);

/*
** create_map.c
*/
int				init_player(t_map *map);
int				create_map(t_map *map);

/*
** main.c
*/
void			print_coord(t_map *map, t_pazzle *pazzle);

/*
** get_line.c
*/
int				get_line(const int fd, char **row);

/*
** print_memory.c
*/
void			print_memory(const void *addr, size_t size);

#endif
