/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs_utilites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:18:54 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/07 13:46:02 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		count_dig(size_t val)
{
	int		i;
	size_t	n;

	i = 0;
	n = val;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int		vs_putstr_fd(int fd, const char *s)
{
	size_t i;

	if (!s || !*s)
		return (0);
	i = ft_strlen(s);
	write(fd, s, i);
	return (i);
}
