/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 20:23:43 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vector3 getray(t_data *data, t_camera *cam, double x, double y)
{
	double 		w;
	double 		pixshift;
	t_vector3	basedir;
	t_vector3	ray;

	basedir = mult1vec(cam->vecx, (double)SCREENSIZE);
	w = (double)SCREENSIZE * tan(RAD(cam->fov / 2)) * 2;
	pixshift = w / ((double)data->res->width - 1);
	ray = addvec(basedir, mult1vec(cam->vecz, ((2 * (y + 0.5) - data->res->width) / 2) * pixshift));
	ray = addvec(ray, mult1vec(cam->vecy, ((-2 * (x + 0.5) + data->res->height) / 2) * pixshift));
	ray = norm(ray);
	return (ray);
}

int	raytrace(t_data *data)
{
	int				x;
	int				y;
	char			*pixels;
	t_vector3		ray;
	t_interobject	object;

	x = -1;
	pixels = data->pixtab;
	while (++x < data->res->height)
	{
		y = -1;
		while (++y < data->res->width)
		{
			ray = getray(data, data->cameras, x, y);
			object = intersearch(data, data->cameras, ray);
			if (object.inter == TRUE)
			{
				pixels[0 + y * 4] = (char)((object.colour & 0xFF));
				pixels[1 + y * 4] = (char)((object.colour & 0xFF00) >> 8);
				pixels[2 + y * 4] = (char)((object.colour & 0xFF0000) >> 16);
			}
			else
			{
				pixels[0 + y * 4] = (char)255;
				pixels[1 + y * 4] = (char)0;
				pixels[2 + y * 4] = (char)0;
			}
		}
		pixels += data->pixsizeline;
	}
	return (0);
}

static int compute(t_data *data)
{
	data->ptr = mlx_init();
	data->win = mlx_new_window(data->ptr, data->res->width, data->res->height, "miniRT");

	data->img = mlx_new_image(data->ptr, data->res->width, data->res->height);
	data->pixtab = mlx_get_data_addr(data->img, &data->pixsize, &data->pixsizeline, &data->endian);
	raytrace(data);
	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);

	mlx_key_hook(data->win, 0, 0);
	mlx_loop(data->ptr);
	return (0);
}

void final_free(t_data *data)
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
}

void setup(t_data *data)
{
	data->cameras = malloc(sizeof(t_camera));
	data->res = malloc(sizeof(t_resolution));

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

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data *data;

	data = NULL;
	data = malloc(sizeof(t_data));
	data->parse_res_doublon = 0;
	data->parse_amb_doublon = 0;
	data->camera_num = 1;

	parse(data, "scene.rt");
	// setup(data);
	compute(data);
	
	final_free(data);
    return (0);
}
