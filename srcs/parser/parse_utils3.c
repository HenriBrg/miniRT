/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 16:54:02 by hberger           #+#    #+#             */
/*   Updated: 2020/01/27 20:44:02 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	checkintminus(char *str)
{
	int	i;

	i = 0;
	if (str == 0 || *str == 0)
		return (1);
	while (str[i] != '\0')
	{
		if (i != 0)
			if ((ft_isdigit(str[i - 1]) || str[i - 1] == '.') && str[i] == '-')
				return (0);
		i++;
	}
	return (1);
}

int	checktwodots(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (str == 0 || *str == 0)
		return (1);
	while (str[i] != '\0')
	{
		j = 1;
		if (i != 0 && str[i] == '.' && str[i + 1] != '\0')
			while (str[i + j] != '\0')
			{
				if (str[i + j] == ',')
					break ;
				else if (str[i + j] == '.')
					return (0);
				j++;
			}
		i++;
	}
	return (1);
}
