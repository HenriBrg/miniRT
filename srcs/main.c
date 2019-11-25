/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2019/11/25 13:57:46 by henri            ###   ########.fr       */
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
** 2) ... après faudrait quelques explications sur le combo cos & rad
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
	tmp = cam->vector.x;
	ray.x = tmp * cos(rad(h)) + cam->vector.z * sin(rad(h));
	ray.y = cam->vector.y;
	ray.z = -tmp * sin(rad(h)) + cam->vector.z * cos(rad(h));
	tmp = ray.x;
	ray.x = ray.x * cos(rad(v)) - ray.y * sin(rad(v));
	ray.y = tmp * sin(rad(v)) + ray.y * cos(rad(v));
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
			// if (intersphere(data, data->cameras, ray) == 1)
			// 	mlx_pixel_put(data->ptr, data->win, x, y, data->spheres->colour);
			# if DEBUG == 1
				if ((x == 0 && y == 0) || (x == 0 && y == data->res.height - 1) || (x == data->res.height - 1 && y == 0) || (x == data->res.width - 1 && y == data->res.height - 1))
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

int main(int ac, char **av)
{
	t_data *data;

	(void)ac;
	(void)av;
	data = NULL;

	data = malloc(sizeof(t_data));
	data->cameras = malloc(sizeof(t_camera));

	data->res.width = 500;
	data->res.height = 250;
	data->cameras->fov = 40;
	data->cameras->pos = newvec(0, 5, 0);
	data->cameras->vector = norm(newvec(1, 0, 0));

	t_sphere *sphere;
	sphere = malloc(sizeof(t_sphere));
	sphere->center = newvec(10, 5, 3);
	sphere->colour = rgbtoi(255, 255, 0);
	sphere->radius = 0.75;
	data->spheres = sphere;

	compute(data);
    return (0);
}
