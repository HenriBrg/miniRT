/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:40:02 by henri             #+#    #+#             */
/*   Updated: 2019/12/18 17:18:19 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"


/* -------------------- Description --------------------
**
** Applique une rotation sur l'axe x, y et z au
** vecteur d'orientation de la camera
** A la sortie au obtient un répère 3D avec
** data->cameras->vecx --> (1.000000, 0.000000, 0.000000)
** data->cameras->vecy --> (0.000000, 1.000000, 0.000000)
** data->cameras->vecz --> (0.000000, 0.000000, 1.000000)
*/

t_vector3 reorientate(t_vector3 base, t_vector3 orientation)
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

/*

void setup(t_data *data)
{
	data->cameras = malloc(sizeof(t_camera));

	data->res->width = 800;
	data->res->height = 800;
	data->cameras->fov = 55;
	data->cameras->pos = newvec(-10,0,0);
	data->cameras->orientation = newvec(0.2,0.1,0.1);
	data->cameras->vecx = reorientate(newvec(1, 0, 0), data->cameras->orientation);
	data->cameras->vecy = reorientate(newvec(0, 1, 0), data->cameras->orientation);
	data->cameras->vecz = reorientate(newvec(0, 0, 1), data->cameras->orientation);

	data->spheres = malloc(sizeof(t_sphere));
	data->spheres->next = NULL;
	data->spheres->radius = 1;
	data->spheres->center = newvec(2,0.5,0);
	data->spheres->colour = RGBTOI(255,0,255);

	// t_plane *plane1;
	// plane1 = malloc(sizeof(t_plane));
	// plane1->next = NULL;
	// plane1->center = newvec(0,-1,0);
	// plane1->normal = reorientate(newvec(0, 1, 0), newvec(0,0,0));
	// plane1->colour = RGBTOI(255,255,255);
	// data->planes = plane1;

	t_square *square1;
	square1 = malloc(sizeof(t_square));
	square1->next = NULL;
	square1->height = 4;
	square1->colour = RGBTOI(25,255,255);
	square1->center = newvec(0,0,-2);
	square1->normal = reorientate(newvec(0, 1, 0), newvec(0,1,0));
	square1->x = reorientate(newvec(1, 0, 0), 	   newvec(0,1,0));
	square1->x = mult1vec(square1->x, square1->height);
	square1->z = reorientate(newvec(0, 0, 1), 	   newvec(0,1,0));
	square1->z = mult1vec(square1->z, square1->height);
	data->squares = square1;

	t_triangle *tri1;
	tri1 = malloc(sizeof(t_triangle));
	tri1->next = NULL;
	tri1->colour = RGBTOI(255,0,0);
	tri1->p1 = newvec(0,0,-2);
	tri1->p2 = newvec(4,0,-2);
	tri1->p3 = newvec(2,2,0);
	data->triangles = tri1;

	t_triangle *tri2;
	tri2 = malloc(sizeof(t_triangle));
	tri2->next = NULL;
	tri2->colour = RGBTOI(0,255,0);
	tri2->p1 = newvec(0,0,2);
	tri2->p2 = newvec(4,0,2);
	tri2->p3 = newvec(2,2,0);
	tri1->next = tri2;

	t_triangle *tri3;
	tri3 = malloc(sizeof(t_triangle));
	tri3->next = NULL;
	tri3->colour = RGBTOI(0,0,255);
	tri3->p1 = newvec(4,0,-2);
	tri3->p2 = newvec(4,0,2);
	tri3->p3 = newvec(2,2,0);
	tri2->next = tri3;



	t_cylinder *cyl1;
	cyl1 = malloc(sizeof(t_cylinder));
	cyl1->next = NULL;
	cyl1->colour = RGBTOI(140,100,255);
	cyl1->center = newvec(20, 0, 0);

	cyl1->orientation = reorientate(newvec(0.9,1,0.4), newvec(0,0,0));
	cyl1->diameter = 3;
	cyl1->radius = cyl1->diameter / 2;
	cyl1->height = 10;
	cyl1->pb = addvec(cyl1->center, mult1vec(cyl1->orientation, cyl1->height));

	data->cylinders = cyl1;

}

*/

void corrupted(t_data *data, char **tab, char *message)
{
	(void)data;
	(void)tab;
	free(data->res);
	free(data->amb);
	free_camera(data);
	free(data);
	ft_strsfree(tab);
	putexit(message);
}


void	store(t_data *data, char **tab)
{
	if (ft_strcmp(tab[0], "R") == 0)
		parse_resolution(data, tab);
	else if (ft_strcmp(tab[0], "A") == 0)
		parse_ambiant(data, tab);
	else if (ft_strcmp(tab[0], "c") == 0)
		add_camera(data, tab);
	else if (ft_strcmp(tab[0], "l") == 0)
		add_light(data, tab);
	else if (ft_strcmp(tab[0], "sp") == 0)
		add_sphere(data, tab);
	else if (ft_strcmp(tab[0], "pl") == 0)
		add_plane(data, tab);
	else if (ft_strcmp(tab[0], "sq") == 0)
		add_square(data, tab);
	else if (ft_strcmp(tab[0], "tr") == 0)
		add_triangle(data, tab);
	else if (ft_strcmp(tab[0], "cy") == 0)
		add_cylinder(data, tab);
	else if (ft_strcmp(tab[0], "#") == 0)
		return ;
	else
		corrupted(data, tab, "Unknow keyword");
}

void debug(t_data *data)
{

	t_light		*lights;
	t_camera	*cameras;
	t_plane 	*planes;
	t_sphere	*spheres;
	t_square	*squares;
	t_cylinder 	*cylinders;
	t_triangle 	*triangles;


	printf("Résolution	: w = %d et h = %d\n", data->res->width, data->res->height);
	printf("Ambiant		: ratio = %lf et colour = %d\n", data->amb->ratio,  data->amb->colour);

	cameras = data->cameras;
	while (cameras)
	{
		printf("Camera		: pos (x:%lf, y:%lf, z:%lf) et vector(x:%lf, y:%lf, z:%lf) et fov = %lf\n", cameras->pos.x, cameras->pos.y, cameras->pos.z, cameras->orientation.x, cameras->orientation.y, cameras->orientation.z, cameras->fov);
		cameras = cameras->next;
	}

	lights = data->lights;
	while (lights)
	{
		printf("Light		: pos (x:%lf, y:%lf, z:%lf) et ratio = %lf et RGB(%d)\n", lights->pos.x, lights->pos.y, lights->pos.z, lights->ratio, lights->colour);
		lights = lights->next;
	}

	spheres = data->spheres;
	while (spheres)
	{
		printf("Sphere		: pos (x:%lf, y:%lf, z:%lf) et radius = %lf et RGB(%d)\n", spheres->center.x, spheres->center.y, spheres->center.z, spheres->radius, spheres->colour);
		spheres = spheres->next;
	}

	planes = data->planes;
	while (planes)
	{
		printf("Plane		: center (x:%lf, y:%lf, z:%lf) et normal computed(x:%lf, y:%lf, z:%lf) et RGB(%d)\n", planes->center.x, planes->center.y, planes->center.z, planes->normal.x, planes->normal.y, planes->normal.z, planes->colour);
		planes = planes->next;
	}

	squares = data->squares;
	while (squares)
	{
		printf("Square		: center (x:%lf, y:%lf, z:%lf) et normal computed (x:%lf, y:%lf, z:%lf) et height = %lf et RGB(%d)\n", squares->center.x, squares->center.y, squares->center.z, squares->normal.x, squares->normal.y, squares->normal.z, squares->height, squares->colour);
		squares = squares->next;
	}

	triangles = data->triangles;
	while (triangles)
	{
		printf("triangle		: pos_a (x:%lf, y:%lf, z:%lf) et pos_b (x:%lf, y:%lf, z:%lf) et pos_c (x:%lf, y:%lf, z:%lf) et RGB(%d)\n", triangles->p1.x, triangles->p1.y, triangles->p1.z, triangles->p2.x, triangles->p2.y, triangles->p2.z, triangles->p3.x, triangles->p3.y, triangles->p3.z , triangles->colour);
		triangles = triangles->next;
	}
	cylinders = data->cylinders;
	while (cylinders)
	{
		printf("Cylinder		: center (x:%lf, y:%lf, z:%lf) et vector (x:%lf, y:%lf, z:%lf) et RGB(%d) et diam = %lf et height = %lf\n", cylinders->center.x, cylinders->center.y, cylinders->center.z, cylinders->orientation.x, cylinders->orientation.y, cylinders->orientation.z, cylinders->colour, cylinders->radius, cylinders->height);
		cylinders = cylinders->next;
	}


}

int	parse(t_data *data, char *filename)
{
	int 	fd;
	char	*line;
	char	**tab;

	if (ft_strcmp(ft_strchr(filename, '.'), ".rt") != 0)
		putexit("Filename must ends with .rt");
	if (!(fd = open(filename, O_RDONLY)))
		putexit("Can't open file");
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line) > 0)
		{
			tab = ft_strsplit(line, " \t");
			free(line);
			store(data, tab);
			ft_strsfree(tab);
		}
	}
	if (close(fd) == -1)
		putexit("Can't close file");
	debug(data);
	return (0);
}

void configuration(t_data *data)
{

	printf("Résolution 		: x = %d et y = %d\n", data->res->width, data->res->height);
	printf("Lumière Ambiante	: ratio = %lf et colour = %d\n", data->amb->ratio,  data->amb->colour);
	/*

	t_light		*lights;
	t_camera	*cameras;
	t_plane 	*planes;
	t_sphere	*spheres;
	t_square	*squares;
	t_cylinder 	*cylinders;
	t_triangle 	*triangles;

	cameras = tab->cameras;
	while (cameras)
	{
		printf("Camera			: pos (x:%lf, y:%lf, z:%lf) et vector(x:%lf, y:%lf, z:%lf) et fov = %lf\n", cameras->pos.x, cameras->pos.y, cameras->pos.z, cameras->vector.x, cameras->vector.y, cameras->vector.z, cameras->fov);
		cameras = cameras->next;
	}
	planes = tab->planes;
	while (planes)
	{
		printf("Plane			: pos (x:%lf, y:%lf, z:%lf) et vector(x:%lf, y:%lf, z:%lf) et RGB(%d, %d, %d)\n", planes->pos.x, planes->pos.y, planes->pos.z, planes->vector.x, planes->vector.y, planes->vector.z, planes->rgb[0], planes->rgb[1], planes->rgb[2]);
		planes = planes->next;
	}
	lights = tab->lights;
	while (lights)
	{
		printf("Light			: pos (x:%lf, y:%lf, z:%lf) et ratio = %lf et RGB(%d, %d, %d)\n", lights->pos.x, lights->pos.y, lights->pos.z, lights->ratio, lights->rgb[0], lights->rgb[1], lights->rgb[2]);
		lights = lights->next;
	}
	spheres = tab->spheres;
	while (spheres)
	{
		printf("Sphere			: pos (x:%lf, y:%lf, z:%lf) et ratio = %lf et RGB(%d, %d, %d)\n", spheres->pos.x, spheres->pos.y, spheres->pos.z, spheres->diameter, spheres->rgb[0], spheres->rgb[1], spheres->rgb[2]);
		spheres = spheres->next;
	}
	squares = tab->squares;
	while (squares)
	{
		printf("Square			: pos (x:%lf, y:%lf, z:%lf) et vector(x:%lf, y:%lf, z:%lf) et height = %lf et RGB(%d, %d, %d)\n", squares->pos.x, squares->pos.y, squares->pos.z, squares->vector.x, squares->vector.y, squares->vector.z, squares->height, squares->rgb[0], squares->rgb[1], squares->rgb[2]);
		squares = squares->next;
	}
	cylinders = tab->cylinders;
	while (cylinders)
	{
		printf("Cylinder		: pos (x:%lf, y:%lf, z:%lf) et vector (x:%lf, y:%lf, z:%lf) et RGB(%d, %d, %d) et diam = %lf et height = %lf\n", cylinders->pos.x, cylinders->pos.y, cylinders->pos.z, cylinders->vector.x, cylinders->vector.y, cylinders->vector.z, cylinders->rgb[0], cylinders->rgb[1], cylinders->rgb[2], cylinders->diameter, cylinders->height);
		cylinders = cylinders->next;
	}
	triangles = tab->triangles;
	while (triangles)
	{
		printf("triangles		: pos_a (x:%lf, y:%lf, z:%lf) et pos_b (x:%lf, y:%lf, z:%lf) et pos_c (x:%lf, y:%lf, z:%lf) et RGB(%d, %d, %d)\n", triangles->pos_a.x, triangles->pos_a.y, triangles->pos_a.z, triangles->pos_b.x, triangles->pos_b.y, triangles->pos_b.z, triangles->pos_c.x, triangles->pos_c.y, triangles->pos_c.z , triangles->rgb[0], triangles->rgb[1], triangles->rgb[2]);
		triangles = triangles->next;
	}

	*/
}
