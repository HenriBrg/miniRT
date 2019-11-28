/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2019/11/28 16:12:49 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*
static int	hits(t_data *data)
{
	int	hit;

	hit = 0;
	(void)data;
	for obj in objects
	{
		if (ray his obj)
		{
			hit = 1;
			*color = obj.color;
		}
	}
	return (hit);
}

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
** 1) On détermine les angles par rapport au vecteur de direction de la camera
**	  qui pointe par défaut au centre du plan
**    Un angle H de -20 signifie que par rapport au du "X" vecteur de direction
**	  de la camera, on élargit de 20° à gauche
**    Un angle V de -20 signifie que par rapport au "Y" vecteur de direction
** 	  de la camera, on descend de 20° en bas
**
**    Explication partielle ici :
**	  https://upload.wikimedia.org/wikipedia/commons/thumb/6/64/Mog_rotacion_vector.jpg/263px-Mog_rotacion_vector.jpg

t_vector3	getray(t_data *data, t_camera *cam, double x, double y)
{
	double		h;
	double		v;
	double		tmp;
	t_vector3	ray;

	h = (1.0 - x / ((data->res.width - 1.0) /  2.0)) * cam->fov / 2.0;
	v = (1.0 - y / ((data->res.height - 1.0) / 2.0)) * cam->fov / 2.0 *
		(data->res.height / data->res.width);
	tmp = cam->orientation.x;
	ray.x = tmp * cos(RAD(h)) + cam->orientation.z * sin(RAD(h));
	ray.y = cam->orientation.y;
	ray.z = -tmp * sin(RAD(h)) + cam->orientation.z * cos(RAD(h));
	tmp = ray.x;
	ray.x = ray.x * cos(RAD(v)) - ray.y * sin(RAD(v));
	ray.y = tmp * sin(RAD(v)) + ray.y * cos(RAD(v));
	return (norm(ray));
}
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
	h = w * (data->res.width / data->res.height);
	pixshift = w / ((double)data->res.height - 1);
	ray = addvec(basedir, mult1vec(cam->vecz, ((2 * (x + 0.5) - data->res.width) / 2 ) * pixshift));
	ray = addvec(ray, mult1vec(cam->vecy, ((2 * (y + 0.5) - data->res.height) / 2 ) * pixshift));
	return (norm(ray));
}

/*
** Un ray peut s'exprimer par la formule : OrigineCam + t*RayVector
** avec t le nombre de période ray(t) = OrigineCam + t*RayVector
*/
int	raytrace(t_data *data)
{
	int	x;
	int	y;
	int i;
	t_vector3 ray;

	i = 0;
	x = -1;
	while (++x < data->res.width)
	{
		y = -1;
		while (++y < data->res.height)
		{
			ray = getray(data, data->cameras, x, y);
			if (intersphere(data, data->cameras, ray) == 1)
				mlx_pixel_put(data->ptr, data->win, x, y, data->spheres->colour);
			# if DEBUG == 1
				if ((x == 0 && y == 0) || (x == 0 && y == data->res.height - 1) ||
					(x == data->res.width - 1 && y == 0) || (x == data->res.width - 1 && y == data->res.height - 1))
				{
					printf("Ray en X = %d et Y = %d\n", x, y);
					printf("Ray[%d] --> (%lf, %lf, %lf)\n", i, ray.x, ray.y, ray.z);
					printf("--------------------------------------------------------\n");
					printf("\n\n");
					i++;
				}
			# endif
		}
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
	raytrace(data);
	mlx_key_hook(data->win, 0, 0);
	mlx_loop(data->ptr);
	return (0);
}

static void setup(t_data *data)
{
	data->cameras = malloc(sizeof(t_camera));

	data->res.width = 300;
	data->res.height = 300;
	data->cameras->fov = 40;
	data->cameras->pos = newvec(0, 0, 0);
	data->cameras->orientation = norm(newvec(0, 0.5, 0));
	data->cameras->vecx = reorientate(newvec(1, 0, 0), data->cameras->orientation);
	data->cameras->vecy = reorientate(newvec(0, 1, 0), data->cameras->orientation);
	data->cameras->vecz = reorientate(newvec(0, 0, 1), data->cameras->orientation);
	# if DEBUG == 1
		printf("\n--------------------------------------------------------\n");
		printf("Cam->vecx (x/y/z) = (%lf, %lf, %lf)\n", data->cameras->vecx.x, data->cameras->vecx.y, data->cameras->vecx.z);
		printf("Cam->vecy (x/y/z) = (%lf, %lf, %lf)\n", data->cameras->vecy.x, data->cameras->vecy.y, data->cameras->vecy.z);
		printf("Cam->vecz (x/y/z) = (%lf, %lf, %lf)\n", data->cameras->vecz.x, data->cameras->vecz.y, data->cameras->vecz.z);
		printf("--------------------------------------------------------\n\n");
	# endif
	data->spheres = malloc(sizeof(t_sphere));
	data->spheres->radius = 2;
	data->spheres->center = newvec(15, 2, 0);
	data->spheres->colour = RGBTOI(255,255,255);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data *data;

	data = malloc(sizeof(t_data));
	setup(data);
	compute(data);
    return (0);
}
