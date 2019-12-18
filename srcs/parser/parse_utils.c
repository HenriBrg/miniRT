/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:23 by henri             #+#    #+#             */
/*   Updated: 2019/12/18 15:42:56 by henri            ###   ########.fr       */
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

int	str_to_rgb(char *s)
{
	int i;
	int r;
	int g;
	int b;
	int colour;

	i = 0;
	r = ft_atoi(s + i);
	while (s[i] != '\0' && ft_isdigit(s[i]))
		i++;
	i++;
	g = ft_atoi(s + i);
	while (s[i] != '\0' && ft_isdigit(s[i]))
		i++;
	i++;
	b = ft_atoi(s + i);
	colour = ((((r << 8) + g) << 8) + b);
	return (colour);
}

int	rgb_format(char *s)
{
	int i;

	if ((i = -1) && ft_stroccurs(s, ',') != 2)
		return (-1);
	while (s[++i])
		if (ft_isdigit(s[i]) == 0 && s[i] != ',')
			return (-1);
	if (!(i = 0) && ft_isdigit(s[i]) == 0)
		return (-1);
	if (ft_atoi(s + i) > 255)
		return (-1);
	while (s[i] != '\0' && ft_isdigit(s[i]))
		i++;
	i++;
	if (ft_atoi(s + i) > 255)
		return (-1);
	while (s[i] != '\0' && ft_isdigit(s[i]))
		i++;
	i++;
	if (ft_atoi(s + i) > 255)
		return (-1);
	return (0);
}

int	check_range_vec3_orient(t_vector3 *vec)
{
	if (vec->x >= -1 && vec->x <= 1 &&
		vec->y >= -1 && vec->y <= 1 &&
		vec->z >= -1 && vec->x <= 1)
		return (0);
	return (-1);
}

int skip_double(char *s, int i)
{
	while (s[i] != '\0' && (ft_isdigit(s[i]) == 1 || s[i] == '.' || s[i] == '-'))
			i++;
	return (i);
}

int vec3_format(char *s, t_vector3 *vec)
{
	int			i;

	if ((i = -1) && ft_stroccurs(s, ',') != 2)
		return (-1);
	while (s[++i] != '\0')
		if (ft_isdigit(s[i]) == 0 && s[i] != ',' && s[i] != '.' && s[i] != '-')
			return (-1);
	if (!(i = 0) && (ft_isdigit(s[i]) == 1 || s[i] == '-'))
		vec->x = ft_atod(s + i);
	else
		return (-1);
	i = skip_double(s, i);
	i++;
	if (ft_isdigit(s[i]) == 1 || s[i] == '-')
		vec->y = ft_atod(s + i);
	else
		return (-1);
	i = skip_double(s, i);
	i++;
	if (ft_isdigit(s[i]) == 1 || s[i] == '-')
		vec->z = ft_atod(s + i);
	else
		return (-1);
	return (0);
}
