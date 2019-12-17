/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:21:23 by henri             #+#    #+#             */
/*   Updated: 2019/12/17 18:16:35 by henri            ###   ########.fr       */
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
	while (s)
	{
		if (!ft_isdigit(*s))
			return (-1);
		s++;
	}
	return (0);
}

int	double_format(char *s)
{
	if (*s == '.')
		return (-1);
	while (s)
	{
		if (!ft_isdigit(*s) && *s != '.')
			return (-1);
		s++;
	}
	s--;
	if (*s == '.')
		return (-1);
	return (0);
}

int	str_to_rgb(char *s)
{
	int r;
	int g;
	int b;
	int colour;

	r = ft_atoi(s);
	while (s && ft_isdigit(*s))
		s++;
	s++;
	g = ft_atoi(s);
	while (s && ft_isdigit(*s))
		s++;
	s++;
	b = ft_atoi(s);
	colour = ((((r << 8) + g) << 8) + b);
	return (colour);
}

int	rgb_format(char *s)
{
	int i;

	i = -1;
	if (ft_stroccurs(s, ',') != 2)
		return (-1);
	while (s[++i])
		if (!ft_isdigit(s[i]) && s[i] != ',')
			return (-1);
	if (!ft_isdigit(*s))
		return (-1);
	if (ft_atoi(s) > 255)
		return (-1);
	while (s && ft_isdigit(*s))
		s++;
	if (ft_atoi(s) > 255)
		return (-1);
	while (s && ft_isdigit(*s))
		s++;
	if (ft_atoi(s) > 255)
		return (-1);
	while (s && ft_isdigit(*s))
		s++;
	if (!ft_isdigit(*s))
		return (-1);
	return (0);
}

char *skip_double(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0' && (ft_isdigit(s[i] || s[i] == '.' || s[i] == '-')))
			i++;
	return (&s[i]);
}

int	check_range_vec3_orient(t_vector3 *vec)
{
	if ((vec->x <= -1 || vec->x >= 1) ||
		(vec->y <= -1 || vec->y >= 1) ||
		(vec->z <= -1 || vec->z >= 1))
		return (-1);
	return (0);
}

int vec3_format(char *s, t_vector3 *vec)
{
	int			i;

	i = 0;
	while (s[++i])
		if (!ft_isdigit(s[i]) && s[i] != ',' && s[i] != '.')
			return (-1);
	if (ft_stroccurs(s, ',') != 2)
		return (-1);
	if (ft_isdigit(*s) || *s == '-')
		vec->x = ft_atod(s);
	else
		return (-1);
	s = skip_double(s);
	s++;
	if (ft_isdigit(*s) || *s == '-')
		vec->y = ft_atod(s);
	else
		return (-1);
	s = skip_double(s);
	s++;
	if (ft_isdigit(*s) || *s == '-')
		vec->z = ft_atod(s);
	else
		return (-1);
	return (0);
}
