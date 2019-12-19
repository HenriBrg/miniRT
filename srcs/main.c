/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 22:20:41 by hberger          ###   ########.fr       */
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
