/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2020/01/27 20:30:29 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini_rt.h"

void				raytrace(t_data *data)
{
	int				x;
	int				y;
	int				*pixels;
	t_vector3		ray;
	t_interobject	object;

	x = -1;
	pixels = data->pixtab;
	while (++x < data->res->height)
	{
		if (x)
			pixels += data->pixsizeline / 4;
		y = -1;
		while (++y < data->res->width)
		{
			ray = getray(data, get_current_camera(data), x, y);
			object = intersearch(data, get_current_camera(data)->pos, ray);
			if (object.inter == TRUE)
				pixels[y] = lighting(data, &object, get_current_camera(data),
									ray);
			else
				pixels[y] = encodergb(177, 177, 177);
		}
	}
}

void				clear(t_data *data)
{
	if (data->img != 0)
		mlx_destroy_image(data->ptr, data->img);
	if (data->win != 0)
		mlx_destroy_window(data->ptr, data->win);
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

int					compute(t_data *data)
{
	raytrace(data);
	if (data->save_bmp == 1)
	{
		save_to_bmp(data);
		return (0);
	}
	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, keys, data);
	mlx_hook(data->win, 17, (1L << 17), clearbis, data);
	mlx_loop(data->ptr);
	return (0);
}

void				init(t_data *data, char **av)
{
	data->res = 0;
	data->amb = 0;
	data->cameras = 0;
	data->lights = 0;
	data->spheres = 0;
	data->planes = 0;
	data->squares = 0;
	data->triangles = 0;
	data->cylinders = 0;
	data->parse_res_doublon = 0;
	data->parse_amb_doublon = 0;
	data->camera_num = 1;
	parse(data, av[1]);
	data->save_bmp = (av[2] != 0 && ft_strcmp(av[2], "-save") == 0) ? 1 : 0;
	data->ptr = mlx_init();
	data->win = mlx_new_window(data->ptr, data->res->width,
		data->res->height, "miniRT");
	data->img = mlx_new_image(data->ptr, data->res->width, data->res->height);
	data->pixtab = (int*)(mlx_get_data_addr(data->img, &data->pixsize,
							&data->pixsizeline, &data->endian));
}

int					main(int ac, char **av)
{
	t_data			*data;

	if (ac < 2)
	{
		ft_putstr("Argument missing\n");
		return (-1);
	}
	data = NULL;
	data = malloc(sizeof(t_data));
	init(data, av);
	compute(data);
	clear(data);
	return (0);
}

/*
** __attribute__((destructor)) static void myDestructor() {
** 	printf("Destructor Loop ... \n");
** 	while (1)
**   		;
** }
*/
