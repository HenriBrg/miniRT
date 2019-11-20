/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 00:56:43 by henri             #+#    #+#             */
/*   Updated: 2019/11/20 14:49:04 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int events(int key, void *data)
{
	(void)key;
	(void)data;
	return (0);
}

static int init(t_data *tab)
{
	int i;
	int j;
	char *pixtab;
	unsigned char c[4];


	tab->ptr = mlx_init();
	tab->win = mlx_new_window(tab->ptr, tab->res->x, tab->res->y, "RT");
	tab->img = mlx_new_image(tab->ptr, tab->res->x, tab->res->y);
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
			pixtab[1 + j * 4] = c[3];//green
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

int	raytrace(t_data *tab)
{
	int	x;
	int	y;

	x = -1;
	while (++x < tab->res->x)
	{
		y = -1;
		while (++y < tab->res->y)
		{
			// https://stackoverflow.com/questions/12892906/generate-a-vector/12892966#12892966
			// normcamera();

			// ray = compute();
			// if (hits() == 1)
			// 	pixelate(tab, x, y);
			// else
			// 	pixelate();
		}
	}
	return (0);
}

int main(int ac, char **av)
{
	t_data *tab;

	tab = NULL;
	(void)ac;
	(void)av;
	if (!(tab = malloc(sizeof(t_data))))
		return (-1);
	if (!(tab->res = malloc(sizeof(t_resolution))))
		return (-1);
	tab->res->x = 1000;
	tab->res->y = 1000;
	init(tab);
    return (0);
}
