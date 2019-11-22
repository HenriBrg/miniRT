/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2019/11/23 00:26:51 by henri            ###   ########.fr       */
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

t_vector3	getray(t_data *data, t_camera *cam, double x, double y)
{
	double		h;
	double		v;
	double		tmp;
	t_vector3	ray;

	h = (1.0 - x / (((double)data->res.width - 1.0) /  2.0)) * cam->fov / 2.0;
	v = (1.0 - y / (((double)data->res.height - 1.0) / 2.0)) * cam->fov / 2.0 * ((double)data->res.height / (double)data->res.width);
	// printf("Angle H = %lf et Angle V = %lf\n", h, v);
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
t_vector3 compute_ray(const t_data *data, const double x, const double y)
{
	double angle_h;
	double angle_v;
	t_vector3 ray;
	double temp;

	//printf("After Y axis rotation initia is      |%10.7g|%10.7g|%10.7g|\n", data->cameras->vector.x, data->cameras->vector.y, data->cameras->vector.z);
	angle_h = (1.0 - x / (((double)data->res.x - 1.0)/ 2.0)) * data->cameras->fov / 2.0;
	//printf("\nangle is %8.5g ", angle_h);
	angle_v = (1.0 - y / (((double)data->res.y - 1.0)/ 2.0)) * data->cameras->fov / 2.0 * ((double)data->res.y /(double)data->res.x);
	temp = data->cameras->vector.x;
	ray.x = temp * cos(to_rad(angle_h)) + data->cameras->vector.z * sin(to_rad(angle_h));
	ray.y = data->cameras->vector.y;
	ray.z = -temp * sin(to_rad(angle_h)) + data->cameras->vector.z * cos(to_rad(angle_h));
	//printf("x rot for %3g;%3g is |%10.7g|%10.7g|%10.7g|\n", x, y, ray.x, ray.y, ray.z);
	// temp = ray.y;
	// ray.y = ray.y * cos(to_rad(angle_v)) - ray.z * sin(to_rad(angle_v));
	// ray.z = temp * sin(to_rad(angle_v)) + ray.z * cos(to_rad(angle_v));
	temp = ray.x;
	ray.x = ray.x * cos(to_rad(angle_v)) - ray.y * sin(to_rad(angle_v));
	ray.y = temp * sin(to_rad(angle_v)) + ray.y * cos(to_rad(angle_v));
	//printf("angle is %8.5g", angle_v);
	//printf("y rot for %3g;%3g is |%10.7g,%10.7g,%10.7g|\n", x, y, ray.x, ray.y, ray.z);
	return (normalise_vector(ray));
}
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
			// printf("--------------------------------------------------------\n");
			// printf("Ray en X = %d et Y = %d\n", x, y);
			ray = getray(data, data->cameras, x, y);
			// printf("Ray --> (%lf, %lf, %lf)\n", ray.x, ray.y, ray.z);
			// printf("--------------------------------------------------------\n");
			// printf("\n\n");
			i++;
		}
	}
	return (0);
}


static int compute(t_data *data)
{
	data->ptr = mlx_init();
	data->win = mlx_new_window(data->ptr, data->res.width, data->res.height, "RT");
	data->img = mlx_new_image(data->ptr, data->res.width, data->res.height);
	data->pixtab = mlx_get_data_addr(data->img, &data->pixsize, &data->pixsizeline, &data->endian);

	raytrace(data);

	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
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

	data->res.width = 10;
	data->res.height = 10;
	data->cameras->fov = 40;
	data->cameras->pos = newvec(0, 5, 0);
	data->cameras->vector = norm(newvec(1, 0, 0));

	compute(data);
    return (0);
}
