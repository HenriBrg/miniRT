/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2019/12/07 22:02:06 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*
static int init(t_data *data)
{
	int i;
	int j;
	char *pixdata;
	unsigned char c[4];

	data->ptr = mlx_init();
	data->win = mlx_new_window(data->ptr, data->res.x, data->res.y, "RT");
	data->img = mlx_new_image(data->ptr, data->res.x, data->res.y);
	data->pixdata = mlx_get_data_addr(data->img, &data->pixsize, &data->pixsizeline, &data->endian);

	c[0] = 255;
	c[1] = 0;
	c[2] = 0;
	c[3] = '\0';
	i = 0;
	pixdata = data->pixdata;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			pixdata[j * 4] = c[0]; //blue
			pixdata[1 + j * 4] = c[3]; //green
			pixdata[2 + j * 4] = c[2]; //red
			j++;
		}
		pixdata += data->pixsizeline;
		i++;
	}

	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, events, 0);
	mlx_loop(data->ptr);
	return (0);
}
*/

/*
** Un ray peut s'exprimer par la formule : OrigineCam + t*RayVector
** avec t le nombre de période ray(t) = OrigineCam + t*RayVector
*/

t_vector3 getray(t_data *data, t_camera *cam, double x, double y)
{
	double 		w;
	double 		h;
	double 		pixshift;
	t_vector3	basedir;
	t_vector3	ray;

	basedir = mult1vec(cam->vecx, (double)SCREENSIZE);
	w = (double)SCREENSIZE * tan(RAD(cam->fov / 2)) * 2;
	h = w * (data->res.height / data->res.width);
	pixshift = w / ((double)data->res.width - 1);
	ray = addvec(basedir, mult1vec(cam->vecz, ((2 * (y + 0.5) - data->res.width) / 2) * pixshift));
	ray = addvec(ray, mult1vec(cam->vecy, ((-2 * (x + 0.5) + data->res.height) / 2) * pixshift));
	# if DEBUG == 1
			// CREUSER ICI : affichier les intermediaire du calcul ray avant addvec, milieu et apres
			printf("------------------ RAY CONFIG ---------------------------\n");
			printf("BaseDir --> (%lf, %lf, %lf)\n", basedir.x, basedir.y, basedir.z);
			printf("H = %lf et W = %lf\n", h, w);
			printf("Pixshift = %lf\n", pixshift);
	# endif
	ray = norm(ray);
	//printf("Ray[x=%lf;y=%lf] --> (%lf, %lf, %lf)\n", x, y, ray.x, ray.y, ray.z);
	return (ray);
}

int	raytrace(t_data *data)
{
	int			x;
	int			y;
	int 		i;
	char		*pixels;
	t_vector3	ray;
	t_interobject	object;

	i = 0;
	x = -1;
	pixels = data->pixtab;
	while (++x < data->res.height)
	{
		y = -1;
		while (++y < data->res.width)
		{
			ray = getray(data, data->cameras, x, y);
			object = intersearch(data, data->cameras, ray);
			// printf("RAY[x=%d;y=%d] --> (%lf, %lf, %lf)\n", x, y, ray.x, ray.y, ray.z);
			// printf("Object found\nInter = %d\nDistance = %lf\nColour = %d\n", object.inter, object.distance, object.colour);
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

/*
** MLX Init
**
** data->img = mlx_new_image(data->ptr, data->res.width, data->res.height);
** data->pixtab = mlx_get_data_addr(data->img, &data->pixsize, &data->pixsizeline, &data->endian);
** mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
*/

static int compute(t_data *data)
{
	data->ptr = mlx_init();
	data->win = mlx_new_window(data->ptr, data->res.width, data->res.height, "miniRT");

	data->img = mlx_new_image(data->ptr, data->res.width, data->res.height);
	data->pixtab = mlx_get_data_addr(data->img, &data->pixsize, &data->pixsizeline, &data->endian);
	raytrace(data);
	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);

	mlx_key_hook(data->win, 0, 0);
	mlx_loop(data->ptr);
	return (0);
}

static void setup(t_data *data)
{
	data->cameras = malloc(sizeof(t_camera));

	data->res.width = 300;
	data->res.height = 200;
	data->cameras->fov = 70;
	data->cameras->pos = newvec(0,0,0);
	data->cameras->orientation = newvec(0,0,0);
	data->cameras->vecx = reorientate(newvec(1, 0, 0), data->cameras->orientation);
	data->cameras->vecy = reorientate(newvec(0, 1, 0), data->cameras->orientation);
	data->cameras->vecz = reorientate(newvec(0, 0, 1), data->cameras->orientation);
	# if DEBUG == 1
		printf("\n--------------------------------------------------------\n");
		printf("\n----------------- CAMERA SETUP -------------------------\n");
		printf("Cam->vecx (x/y/z) = (%lf, %lf, %lf)\n", data->cameras->vecx.x, data->cameras->vecx.y, data->cameras->vecx.z);
		printf("Cam->vecy (x/y/z) = (%lf, %lf, %lf)\n", data->cameras->vecy.x, data->cameras->vecy.y, data->cameras->vecy.z);
		printf("Cam->vecz (x/y/z) = (%lf, %lf, %lf)\n", data->cameras->vecz.x, data->cameras->vecz.y, data->cameras->vecz.z);
		printf("--------------------------------------------------------\n\n");
	# endif
	/*

	data->spheres = malloc(sizeof(t_sphere));
	data->spheres->next = NULL;
	data->spheres->radius = 1;
	data->spheres->center = newvec(1,-0.5,0);
	data->spheres->colour = RGBTOI(255,0,255);

	t_sphere *second;
	second = malloc(sizeof(t_sphere));
	second->next = NULL;
	second->radius = 5;
	second->center = newvec(15, 1, -1);
	second->colour = RGBTOI(100,0,255);
	data->spheres->next = second;
	*/

	t_plane *plane1;
	plane1 = malloc(sizeof(t_plane));
	plane1->next = NULL;
	plane1->center = newvec(2,-10,0);
	plane1->normal = reorientate(newvec(0, 1, 0), newvec(0.768,0,0)); // Range [-1;1]
	plane1->colour = RGBTOI(0, 255, 0);
	data->planes = plane1;

	t_plane *plane2;
	plane2 = malloc(sizeof(t_plane));
	plane2->next = NULL;
	plane2->center = newvec(1,3,0);
	plane2->normal = reorientate(newvec(0, 1, 0), newvec(0, 0, 0));
	plane2->colour = RGBTOI(0,120,0);
	data->planes->next = plane2;


	// sq	18,-5,0 	0.5,0.25,0.0 	10	255,255,255
	// sq 	18,-5,0 	0.5,-0.25,0.0	10	255,255,255
	// sq 	18,-5,0 	0.0,0.25,0.0	10	255,255,255

	t_square *square1;
	square1 = malloc(sizeof(t_square));
	square1->next = NULL;
	square1->height = 10;
	square1->colour = RGBTOI(0, 255, 0);
	square1->center = newvec(18,-5,0);
	square1->normal = reorientate(newvec(0, 1, 0), newvec(0.5,0.25,0.0));
	square1->x = reorientate(newvec(1, 0, 0), 	   newvec(0.5,0.25,0.0));
	square1->x = mult1vec(square1->x, square1->height);
	square1->z = reorientate(newvec(0, 0, 1), 	   newvec(0.5,0.25,0.0));
	square1->z = mult1vec(square1->z, square1->height);
	data->squares = square1;
	// sq	18,-5,0 	0.5,0.25,0.0 	10	255,255,255

}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data *data;

	data = NULL;
	data = malloc(sizeof(t_data));
	setup(data);
	compute(data);
	free(data->cameras);


	free(data->spheres->next);
	free(data->spheres);


	free(data);
    return (0);
}
