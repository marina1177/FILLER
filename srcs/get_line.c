/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcharity <marvin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 16:18:39 by bcharity          #+#    #+#             */
/*   Updated: 2020/05/06 16:49:33 by bcharity         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static char	*ft_strchrs(const char *s, int c)
{
	if (!s)
		return (NULL);
	return (ft_strchr(s, c));
}

static char	*ft_strjoint(char const *s1, char const *s2)
{
	char	*result;
	char	*start;

	if (!s1 && !s2)
		return (NULL);
	result = ft_strnew((s1 ? ft_strlen(s1) : 0) + (s2 ? ft_strlen(s2) : 0));
	if ((start = result))
	{
		if (s1)
			while (*s1)
				*result++ = *s1++;
		if (s2)
			while (*s2)
				*result++ = *s2++;
		*result = '\0';
	}
	return (start);
}

static int	divide_str(char **str, char **row)
{
	char	*new;
	char	*div;

	div = ft_strchrs(*str, '\n');
	div++;
	if (!(*row = ft_strsub(*str, 0, div - *str)))
		return (-1);
	if (!ft_strlen(div))
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	new = ft_strdup(div);
	free(*str);
	*str = new;
	return ((new) ? 1 : -1);
}

static int	gg_norma(char **str)
{
	if (*str != NULL)
		free(*str);
	return (-1);
}

int			get_line(const int fd, char **row)
{
	static char		*str = NULL;
	char			buff[BUFF_SIZE + 1];
	ssize_t			size;
	char			*tmp;

	if (fd < 0 || !row || read(fd, buff, 0) < 0)
		return (gg_norma(&str));
	while (!ft_strchrs(str, '\n'))
	{
		if (!(size = read(fd, buff, BUFF_SIZE)))
		{
			if (!(*row = str))
				return (0);
			str = NULL;
			return (1);
		}
		buff[size] = '\0';
		tmp = str;
		str = ft_strjoint(tmp, buff);
		free(tmp);
		if (!str)
			return (-1);
	}
	return (divide_str(&str, row));
}
