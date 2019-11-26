/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:46:24 by hberger           #+#    #+#             */
/*   Updated: 2019/11/26 17:47:38 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <math.h>
# include <stdio.h>

# include "libft.h"
# include "mlx.h"

# ifndef DEBUG
#	define DEBUG 0
# endif

typedef struct	s_resolution
{
	int			width;
	int 		height;
}				t_resolution;

typedef struct	s_vector3
{
	double		x;
	double		y;
	double		z;
}				t_vector3;

typedef struct	s_ambiant_light
{
	double		ratio;
	int			colour;
}				t_ambiant_light;

typedef struct	s_light
{
	t_vector3	pos;
	double		ratio;
	int			colour;
}				t_light;

typedef struct	s_camera
{
	t_vector3	pos;
	t_vector3	vector;
	double		fov;
}				t_camera;

typedef struct	s_phere
{
	t_vector3	center;
	double		radius;
	int			colour;
}				t_sphere;

typedef struct	s_plane
{
	t_vector3	centre;
	t_vector3	orientation;
	int			colour;
}				t_plane;

typedef struct	s_quare
{
	t_vector3	centre;
	t_vector3	orientation;
	double		height;
	int			colour;
}				t_square;

typedef struct	s_cylinder
{
	t_vector3	centre;
	t_vector3	orientation;
	double		diameter;
	double		height;
	int			colour;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vector3	p1;
	t_vector3	p2;
	t_vector3	p3;
	int			colour;
}				t_triangle;

typedef struct	s_data
{
	void			*ptr;
	void 			*win;
	void			*img;
	int				pixsize;
	int				pixsizeline;
	int				endian;
	char 			*pixtab;

	t_resolution	res;
	t_ambiant_light	amb;
	t_light			*lights;
	t_camera		*cameras;
	t_sphere		*spheres;
	t_plane			*planes;
	t_square		*squares;
	t_cylinder		*cylinders;
	t_triangle		*triangles;
}				t_data;

double		veclen(t_vector3 vec);
double		rad(double degree);
double		scalar(t_vector3 vec1, t_vector3 vec2);

t_vector3	newvec(double x, double y, double z);
t_vector3	norm(t_vector3 vec);
t_vector3	multvec(t_vector3 vec1, t_vector3 vec2);
t_vector3	crossvec(t_vector3 vec1, t_vector3 vec2);
t_vector3	subvec(t_vector3 vec1, t_vector3 vec2);

int			rgbtoi(int red, int green, int blue);
int			intersphere(t_data *data, t_camera *cam, t_vector3 ray);

# endif
