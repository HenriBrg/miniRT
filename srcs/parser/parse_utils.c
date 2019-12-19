/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:23 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 23:10:28 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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
