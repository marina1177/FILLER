/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <bcharity@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 22:44:46 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/03 13:35:15 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# define TRUE 1
# define FALSE 0

//# include "../libft/includes/libft.h"

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# include <stdio.h>

# define EOC	"\033[0m"
# define RED	"\033[1;31m"
# define YELLOW	"\033[1;33m"
# define WHITE	"\033[1;37m"
# define BLACK	"\033[0;30m"
# define GREEN	"\033[0;32m"
# define BLUE	"\033[0;34m"
# define PURPUL	"\033[0;35m"
# define CYAN	"\033[0;36m"
# define GRAY	"\033[1;30m"

# define MY_NAME "bcharity.filler"
# define CH_P1 "Oo"
# define CH_P2 "Xx"
# define NUM_P1 01
# define NUM_P2 10


typedef struct	s_map
{
	char		**map;
	int			**heat;

	char		*ch_player;
	int			num_player;
	char		*ch_opp;
	int			num_opp;


	int			rows;//consts
	int			cols;

	int			fin_x;
	int			fin_y;
	//t_vis		*vis;

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

/*typedef struct	s_vis
{
	char		*my_player;
	char		*op_player;

	int			my_cells[100];
	int			opp_cells[100];

	t_pazzle	*opp_pazzles;
	t_pazzle	*my_pazzles;

}				t_vis;*/

/*
** research.c
*/
void			real_pazzle_size(t_pazzle *pazzle);
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
void			parse_pazzle(t_map *map, t_pazzle *pazzle);

/*
** create_map.c
*/
int				create_map(t_map *map);

/*
** get_line.c
*/
int				get_line(const int fd, char **row);

/*
** print_memory.c
*/
void			print_memory(const void *addr, size_t size);

#endif
