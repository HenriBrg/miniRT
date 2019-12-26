/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:23 by henri             #+#    #+#             */
/*   Updated: 2019/12/26 19:38:58 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int		check_not_only_space_tabs(char *line)
{
	int	i;

	i = -1;
	while (line[++i] != 0)
		if (line[i] != '\t' && line[i] != ' ')
			return (1);
	return (0);
}

void putexit(char *msg)
{
	ft_putendl_fd(msg, 1);
	exit(1);
}

int	uint_format(char *s)
{
	int i;

	i = 0;
	while (s[i] != 0)
	{
		if (ft_isdigit(s[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

int		ft_strtablen(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != NULL)
		i++;
	return (i);
}

int	double_format(char *s)
{
	int i;

	i = 0;
	if (s[i] == '.')
		return (-1);
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0 && s[i] != '.')
			return (-1);
		i++;
	}
	 if (s[--i] == '.')
	 	return (-1);
	return (0);
}
