/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2019/11/27 14:55:57 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*
int rgbtoi(int red, int green, int blue)
{
	return ((((red << 8) + green) << 8) + blue);
}
*/


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
*/

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

/*
** Version 2 : https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
** As you can see though in figure 2, the film or image plane is centred around the world's origin.
** In other words, pixels located on the left of the image should have negative x-coordinates,
** while those located on the right should have positive x-coordinates.
*/

t_vector3 newgetray(t_data *data, t_camera *cam, double x, double y)
{
	double xpix;
	double ypix;
	double ratio;
	t_vector3 origin;
	t_vector3 direction;

	ratio = data->res.width / data->res.height;
	xpix = (2 * ((x + 0.5) / data->res.width) - 1) * tan((cam->fov / 2) * (M_PI / 180)) * ratio;
	xpix = (1 - 2 * (y + 0.5) / data->res.height) * tan((cam->fov / 2) * (M_PI / 180));

	origin = newvec(0, 0, 0);
	direction = newvec(0, 0, 0);

	norm(ray);
	return (ray);
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
			#endif
		}
	}
	return (0);
}

static int compute(t_data *data)
{
	data->ptr = mlx_init();
	data->win = mlx_new_window(data->ptr, data->res.width, data->res.height, "RT");
	// data->img = mlx_new_image(data->ptr, data->res.width, data->res.height);
	// data->pixtab = mlx_get_data_addr(data->img, &data->pixsize, &data->pixsizeline, &data->endian);
	raytrace(data);
	// mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, 0, 0);
	mlx_loop(data->ptr);
	return (0);
}

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

static void setup(t_data *data)
{
	data = malloc(sizeof(t_data));
	data->cameras = malloc(sizeof(t_camera));

	data->res.width = 300;
	data->res.height = 300;
	data->cameras->fov = 90;
	data->cameras->pos = newvec(0, 0, 0);
	data->cameras->orientation = norm(newvec(0, 0.5, 0));
	data->cameras->vecx = reorientate(newvec(1, 0, 0), data->cameras->orientation);
	data->cameras->vecy = reorientate(newvec(0, 1, 0), data->cameras->orientation);
	data->cameras->vecz = reorientate(newvec(0, 0, 1), data->cameras->orientation);

	data->spheres = malloc(sizeof(t_sphere));
	data->sphere->radius = 5;
	data->sphere->center = newvec(1, 0, 10);
	data->sphere->colour = RGBTOI(255, 0, 0);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data *data;

	data = NULL;
	setup(data);
	compute(data);
    return (0);
}
