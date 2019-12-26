/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:40:02 by henri             #+#    #+#             */
/*   Updated: 2019/12/26 19:45:14 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"


/* -------------------- Description --------------------
**
** Applique une rotation sur l'axe x, y et z au
** vecteur d'orientation de la camera
*/

t_vector3		reorientate(t_vector3 base, t_vector3 orientation)
{
	t_vector3	new;
	double		tmp;
	double		angle;

	angle = orientation.x * M_PI;
	new.x = base.x;
	new.y = base.y * cos(angle) - base.z * sin(angle);
	new.z = base.y * sin(angle) + base.z * cos(angle);
	angle = orientation.y * M_PI;
	tmp = new.x * cos(angle) + new.z * sin(angle);
	new.z = -new.x * sin(angle) + new.z * cos(angle);
	new.x = tmp;
	angle = orientation.z * M_PI;
	tmp = new.x * cos(angle) - new.y * sin(angle);
	new.y = new.x * sin(angle) + new.y * cos(angle);
	new.x = tmp;
	return (new);
}

void			corrupted(t_data *data, char **tab, char *message, int fd)
{
	free(data->res);
	free(data->amb);
	free_camera(data);
	free_light(data);
	free_sphere(data);
	free_plane(data);
	free_square(data);
	free_triangle(data);
	free_cylinder(data);
	free(data);
	if (tab)
		ft_strsfree(tab);
	if (close(fd) == -1)
		putexit("Can't close file");
	putexit(message);
}


void			store(t_data *data, char **tab, int fd)
{
	if (ft_strcmp(tab[0], "R") == 0)
		parse_resolution(data, tab, fd);
	else if (ft_strcmp(tab[0], "A") == 0)
		parse_ambiant(data, tab, fd);
	else if (ft_strcmp(tab[0], "c") == 0)
		add_camera(data, tab, fd);
	else if (ft_strcmp(tab[0], "l") == 0)
		add_light(data, tab, fd);
	else if (ft_strcmp(tab[0], "sp") == 0)
		add_sphere(data, tab, fd);
	else if (ft_strcmp(tab[0], "pl") == 0)
		add_plane(data, tab, fd);
	else if (ft_strcmp(tab[0], "sq") == 0)
		add_square(data, tab, fd);
	else if (ft_strcmp(tab[0], "tr") == 0)
		add_triangle(data, tab, fd);
	else if (ft_strcmp(tab[0], "cy") == 0)
		add_cylinder(data, tab, fd);
	else if (ft_strcmp(tab[0], "#") == 0)
		return ;
	else
		corrupted(data, tab, "Unknow keyword", fd);
}

void			reading(int fd, t_data *data)
{
	char		*line;
	char		**tab;

	while (get_next_line(fd, &line) > 0)
		if (ft_strlen(line) > 0 && check_not_only_space_tabs(line) == 1)
		{
			tab = ft_strsplit(line, " \t");
			free(line);
			store(data, tab, fd);
			ft_strsfree(tab);
		}
		else
			free(line);
	if (ft_strlen(line) > 0 && check_not_only_space_tabs(line) == 1)
	{
		tab = ft_strsplit(line, " \t");
		free(line);
		store(data, tab, fd);
		ft_strsfree(tab);
	}
	else
		free(line);
}

int				parse(t_data *data, char *filename)
{
	int 		fd;

	if (ft_strcmp(ft_strchr(filename, '.'), ".rt") != 0)
		putexit("Filename must ends with .rt");
	if ((fd = open(filename, O_RDONLY)) == -1)
		putexit("Can't open file");
	reading(fd, data);
	if (data->parse_res_doublon == 0 || data->parse_amb_doublon == 0)
		corrupted(data, NULL, "Il faut une résolution et une lumière amb", fd);
	if (camera_count(data) == 0)
		corrupted(data, NULL, "Il faut au moins 1 camera", fd);
	if (close(fd) == -1)
		corrupted(data, NULL, "", fd);
	return (0);
}
