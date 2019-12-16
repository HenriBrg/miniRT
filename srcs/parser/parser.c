/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:40:02 by henri             #+#    #+#             */
/*   Updated: 2019/12/15 20:00:39 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"


/*
** Applique une rotation sur l'axe x, y et z au
** vecteur d'orientation de la camera
** A la sortie au obtient un répère 3D avec
** data->cameras->vecx : RAYX --> (1.000000, 0.000000, 0.000000)
** data->cameras->vecy : RAYY --> (0.000000, 1.000000, 0.000000)
** data->cameras->vecz : RAYZ --> (0.000000, 0.000000, 1.000000)
printf("RAYX --> (%lf, %lf, %lf)\n", data->cameras->vecx.x, data->cameras->vecx.y, data->cameras->vecx.z);
printf("RAYY --> (%lf, %lf, %lf)\n", data->cameras->vecy.x, data->cameras->vecy.y, data->cameras->vecy.z);
printf("RAYZ --> (%lf, %lf, %lf)\n", data->cameras->vecz.x, data->cameras->vecz.y, data->cameras->vecz.z);
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
	// printf("current ray : |%10.6g|%10.6g|%10.6g|\n", new.x, new.y, new.z);
	return (new);
}

/*
printf("\n----------------- CAMERA SETUP --------------------\n");
printf("Cam->vecx (x/y/z) = (%lf, %lf, %lf)\n", data->cameras->vecx.x, data->cameras->vecx.y, data->cameras->vecx.z);
printf("Cam->vecy (x/y/z) = (%lf, %lf, %lf)\n", data->cameras->vecy.x, data->cameras->vecy.y, data->cameras->vecy.z);
printf("Cam->vecz (x/y/z) = (%lf, %lf, %lf)\n", data->cameras->vecz.x, data->cameras->vecz.y, data->cameras->vecz.z);
printf("-----------------------------------------------------\n\n");
*/

void setup(t_data *data)
{
	data->cameras = malloc(sizeof(t_camera));

	data->res.width = 800;
	data->res.height = 800;
	data->cameras->fov = 55;
	data->cameras->pos = newvec(-5,3,3);
	data->cameras->orientation = newvec(-0.032,0.15,-0.07);
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

	// cy	10.0,-5,-3	0,0,0 	    1.75 	3		255,255,255

	t_cylinder *cyl1;
	cyl1 = malloc(sizeof(t_cylinder));
	cyl1->next = NULL;
	cyl1->colour = RGBTOI(140,100,255);
	cyl1->center = newvec(10.0,-5,-3);
	cyl1->orientation = reorientate(newvec(0,1,0), newvec(0,0,0));
	cyl1->diameter = 1.75;
	cyl1->height = 3;
	data->cylinders = cyl1;

}
