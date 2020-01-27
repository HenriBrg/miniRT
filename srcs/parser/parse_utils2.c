/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 23:10:22 by hberger           #+#    #+#             */
/*   Updated: 2020/01/27 18:02:59 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int			str_to_rgb(char *s)
{
	int		i;
	int		r;
	int		g;
	int		b;
	int		colour;

	i = 0;
	r = ft_atoi(s + i);
	while (s[i] != '\0' && ft_isdigit(s[i]) == 1)
		i++;
	i++;
	g = ft_atoi(s + i);
	while (s[i] != '\0' && ft_isdigit(s[i]) == 1)
		i++;
	i++;
	b = ft_atoi(s + i);
	colour = ((((r << 8) + g) << 8) + b);
	return (colour);
}

int			rgb_format(char *s)
{
	int		i;

	if ((i = -1) && checkintminus(s) == 0)
		return (-1);
	if (ft_stroccurs(s, ',') != 2)
		return (-1);
	while (s[++i] != '\0')
		if (ft_isdigit(s[i]) == 0 && s[i] != ',')
			return (-1);
	i = 0;
	if (ft_isdigit(s[i]) == 0)
		return (-1);
	if (ft_atoi(s + i) > 255)
		return (-1);
	while (s[i] != '\0' && ft_isdigit(s[i]) == 1)
		i++;
	i++;
	if (ft_atoi(s + i) > 255)
		return (-1);
	while (s[i] != '\0' && ft_isdigit(s[i]) == 1)
		i++;
	i++;
	if (ft_atoi(s + i) > 255)
		return (-1);
	return (0);
}

int			check_range_vec3_orient(t_vector3 *vec)
{
	if (vec->x >= -1 && vec->x <= 1 &&
		vec->y >= -1 && vec->y <= 1 &&
		vec->z >= -1 && vec->x <= 1)
		return (0);
	return (-1);
}

int			skip_double(char *s, int i)
{
	while (s[i] != 0 && (ft_isdigit(s[i]) == 1 || s[i] == '.' || s[i] == '-'))
		i++;
	return (i);
}

int			vec3_format(char *s, t_vector3 *vec)
{
	int		i;

	if (checkintminus(s) == 0)
		return (-1);
	if ((i = -1) && ft_stroccurs(s, ',') != 2)
		return (-1);
	while (s[++i] != '\0')
		if (ft_isdigit(s[i]) == 0 && s[i] != ',' && s[i] != '.' && s[i] != '-')
			return (-1);
	i = 0;
	if (ft_isdigit(s[i]) == 1 || s[i] == '-')
		vec->x = ft_atod(s);
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
