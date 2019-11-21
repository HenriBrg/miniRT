/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2019/11/21 16:56:26 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int events(int key, void *data)
{
	(void)key;
	(void)data;
	return (0);
}



/*
** Pseudo Code http://www.cs.utah.edu/~shirley/books/fcg2/rt.pdf
*/

/*
** On itère sur chaque élément pour voir s'il y a une collision
*/

int	hits(t_data *tab)
{
	int	hit;

	hit = 0;
	(void)tab;
	/*
	for obj in objects
	{
		if (ray his obj)
		{
			hit = 1;
			*color = obj.color;
		}
	}
	*/
	return (hit);
}

/* Cesar

** We adopt a standard vertical FOV of 40
** We will rotate around the Y axis for horizontal FOV and around the X axis for vertical FOV

t_vector3 compute_ray(const t_data *data, const int x, const int y)
{
    double angle_h;
    double angle_v;
    t_vector3 ray_vector;

    angle_h = (1 - x / (data->res.x / 2)) * data->cameras->fov;
    angle_v = (1 - y / (data->res.y / 2)) * 40;
    ray_vector.x = data->cameras->vector.x * cos(angle_h) + data->cameras->vector.z * sin(angle_h);
    ray_vector.y = data->cameras->vector.y;
    ray_vector.z = -data->cameras->vector.x * sin(angle_h) + data->cameras->vector.z * cos(angle_h);
    ray_vector.y = ray_vector.y * cos(angle_v) - ray_vector.z * sin(angle_v);
    ray_vector.z = ray_vector.y * sin(angle_v) + ray_vector.z * cos(angle_v);
    return (ray_vector);
}
*/


// TODO : APPROFONDIR CE LIEN : https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
// float imageAspectRatio = imageWidth / (float)imageHeight; // assuming width > height
// float Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio;
// float Py = (1 - 2 * ((y + 0.5) / imageHeight) * tan(fov / 2 * M_PI / 180);
// Vec3f rayOrigin(0);
// Vec3f rayDirection = Vec3f(Px, Py, -1) - rayOrigin; // note that this just equal to Vec3f(Px, Py, -1);
// rayDirection = normalize(rayDirection); // it's a direction so don't forget to normalize

t_vector3 newvec(double x, double y, double z)
{
	t_vector3 new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

double veclen(t_vector3 vec)
{
	double len;

	len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (len);
}

t_vector3 norm(t_vector3 vec)
{
	double len;

	len = veclen(vec);
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vector3 multvec(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3 new;

	new.x = vec1.x * vec2.x;
	new.y = vec1.y * vec2.y;
	new.z = vec1.z * vec2.z;
	return (new);
}

double dot(t_vector3 vec1, t_vector3 vec2)
{
	double dot;

	dot = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (dot);
}

t_vector3 subvec(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3 new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	new.z = vec1.z - vec2.z;
	return (new);
}

/*
static int init(t_data *tab)
{
	int i;
	int j;
	char *pixtab;
	unsigned char c[4];

	tab->ptr = mlx_init();
	tab->win = mlx_new_window(tab->ptr, tab->res.x, tab->res.y, "RT");
	tab->img = mlx_new_image(tab->ptr, tab->res.x, tab->res.y);
	tab->pixtab = mlx_get_data_addr(tab->img, &tab->pixsize, &tab->pixsizeline, &tab->endian);

	c[0] = 255;
	c[1] = 0;
	c[2] = 0;
	c[3] = '\0';
	i = 0;
	pixtab = tab->pixtab;
	while (i < 100)
	{
		j = 0;
		while (j < 100)
		{
			pixtab[j * 4] = c[0]; //blue
			pixtab[1 + j * 4] = c[3]; //green
			pixtab[2 + j * 4] = c[2]; //red
			j++;
		}
		pixtab += tab->pixsizeline;
		i++;
	}

	mlx_put_image_to_window(tab->ptr, tab->win, tab->img, 0, 0);
	mlx_key_hook(tab->win, events, 0);
	mlx_loop(tab->ptr);
	return (0);
}
*/

/*
float imageAspectRatio = imageWidth / imageHeight; // assuming width > height
float Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio;
float Py = (1 - 2 * ((y + 0.5) / imageHeight) * tan(fov / 2 * M_PI / 180);
Vec3f rayOrigin = Point3(0, 0, 0);
Matrix44f cameraToWorld;
cameraToWorld.set(...); // set matrix
Vec3f rayOriginWorld, rayPWorld;
cameraToWorld.multVectMatrix(rayOrigin, rayOriginWorld);
cameraToWorld.multVectMatrix(Vec3f(Px, Py, -1), rayPWorld);
Vec3f rayDirection = rayPWorld - rayOriginWorld;
rayDirection.normalize(); // it's a direction so don't forget to normalize
*/

t_vector3 getray(t_data *tab, t_camera *cam, int x, int y)
{

	double normx;
	double normy;
	double ratio;
	t_vector3 origin;
	t_vector3 direction;

	ratio = (double)tab->res.width / (double)tab->res.height;
	normx = (2 * ((x + 0.5) / (double)tab->res.width) -1) * tan(cam->fov / 2 * M_PI / 180) * ratio;
	normy = (1 - 2 * ((y + 0.5) / (double)tab->res.height) -1) * tan(cam->fov / 2 * M_PI / 180);
	//origin = newvec(cam->vector.x, cam->vector.y, cam->vector.z);
	origin = newvec(0.0, 0.0, 0.0);
	direction = subvec(newvec(normx, normy, 1), origin);
	direction = norm(direction);
	return (direction);
}

int	raytrace(t_data *tab)
{
	int	x;
	int	y;
	int i;
	t_vector3 ray;

	i = 0;
	x = -1;
	while (++x < tab->res.width)
	{
		y = -1;
		while (++y < tab->res.height)
		{

			if (x == 0 || y == 0)
			{
				ray = getray(tab, tab->cameras, x, y);
				printf("RAY[%d] --> (%lf, %lf, %lf)\n",i, ray.x, ray.y, ray.z);
				i++;
			}

		}
	}
	return (0);
}


static int init(t_data *tab)
{
	tab->ptr = mlx_init();
	tab->win = mlx_new_window(tab->ptr, tab->res.width, tab->res.height, "RT");
	tab->img = mlx_new_image(tab->ptr, tab->res.width, tab->res.height);
	tab->pixtab = mlx_get_data_addr(tab->img, &tab->pixsize, &tab->pixsizeline, &tab->endian);

	raytrace(tab);

	mlx_put_image_to_window(tab->ptr, tab->win, tab->img, 0, 0);
	mlx_key_hook(tab->win, events, 0);
	mlx_loop(tab->ptr);
	return (0);
}

int main(int ac, char **av)
{
	t_data *tab;

	(void)ac;
	(void)av;
	tab = NULL;

	tab = malloc(sizeof(t_data));
	tab->cameras = malloc(sizeof(t_camera));

	tab->res.width = 100;
	tab->res.height = 100;
	tab->cameras->fov = 70;
	tab->cameras->vector.x = 0.0;
	tab->cameras->vector.y = 0.0;
	tab->cameras->vector.z = 1.0;

	init(tab);

    return (0);
}
