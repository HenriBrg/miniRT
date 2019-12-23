/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2019/12/23 02:23:37 by henri            ###   ########.fr       */
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
	ray = addvec(basedir, mult1vec(cam->vecz,
				((2 * (y + 0.5) - data->res->width) / 2) * pixshift));
	ray = addvec(ray, mult1vec(cam->vecy,
				((-2 * (x + 0.5) + data->res->height) / 2) * pixshift));
	ray = norm(ray);
	return (ray);
}

void	raytrace(t_data *data)
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
			object = intersearch(data, get_current_camera(data), ray);
			if (object.inter == TRUE)
				colorize(pixels, object.colour, y);
			else
				colorize(pixels, 255, y);
		}
		pixels += data->pixsizeline;
	}
	if (data->save_bmp == 1)
		save_to_bmp(data);
}

static int compute(t_data *data)
{
	data->ptr = mlx_init();
	data->win = mlx_new_window(data->ptr, data->res->width, data->res->height, "miniRT");
	data->img = mlx_new_image(data->ptr, data->res->width, data->res->height);
	data->pixtab = mlx_get_data_addr(data->img, &data->pixsize, &data->pixsizeline, &data->endian);
	raytrace(data);
	mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
	mlx_key_hook(data->win, keys, data);
	mlx_loop(data->ptr);
	return (0);
}

void final_free(t_data *data)
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

// TODO : ambiant - keys echap puis ensuite leaks et finir par lights shadow
// erreur : on voit la sphere alors qu'on ne devrait pas :
// c	20,0,0			0,0,0			70
// sp	8.0,0,0		2.75				255,0,255


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
	data->save_bmp = (av[2] != 0 && ft_strcmp(av[2], "--save") == 0) ? 1 : 0;
	parse(data, av[1]);
	compute(data);
	final_free(data);
    return (0);
}
