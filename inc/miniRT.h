/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:46:24 by hberger           #+#    #+#             */
/*   Updated: 2019/12/09 22:54:00 by henri            ###   ########.fr       */
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

# define TRUE 1
# define FALSE 0

# define SCREENSIZE 10
# define RGBTOI(r, g, b) ((((r << 8) + g) << 8) + b)
# define RAD(degree)	(degree * M_PI / 180)

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
	t_vector3	orientation;
	double		fov;
	t_vector3	vecx;
	t_vector3	vecy;
	t_vector3	vecz;
}				t_camera;

typedef struct	s_sphere
{
	t_vector3				center;
	double					radius;
	int						colour;
	struct 		s_sphere	*next;
}				t_sphere;

typedef struct	s_plane
{
	t_vector3				center;
	t_vector3				normal;
	int						colour;
	struct 		s_plane		*next;
}				t_plane;

typedef struct	s_square
{
	t_vector3				x;
	t_vector3				z;
	t_vector3				center;
	t_vector3				normal;
	double					height;
	int						colour;
	struct 		s_square	*next;
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
	t_vector3	normal;
	int			colour;
	struct 		s_triangle	*next;
}				t_triangle;

typedef struct s_interobject
{
	int			inter;
	t_vector3	ray;
	t_vector3	origin;
	void 		*ptr;
	int			colour;
	double		distance;
}				t_interobject;

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
double		dot(t_vector3 vec1, t_vector3 vec2);

t_vector3	newvec(double x, double y, double z);
t_vector3	addvec(t_vector3 vec1, t_vector3 vec2);
t_vector3	norm(t_vector3 vec);
t_vector3 	cross(t_vector3 a, t_vector3 b);
t_vector3	subvec(t_vector3 vec1, t_vector3 vec2);
t_vector3 	reorientate(t_vector3 base, t_vector3 orientation);
t_vector3	mult1vec(t_vector3 vec, double x);
t_vector3	mult2vec(t_vector3 vec1, t_vector3 vec2);
t_vector3 	getdirectionalvector(t_vector3 a, t_vector3 b);
t_vector3 	getpointfromray(t_vector3 origin, t_vector3 ray, double t);

int			rgbtoi(int red, int green, int blue);

/*
** srcs/intersections/
*/

double		intersphere(t_sphere *sp, t_camera *cam, t_vector3 ray);
void 		try_spheres(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj);
void 		try_planes(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj);
void 		try_squares(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj);
void 		try_triangles(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj);

t_interobject intersearch(t_data *data, t_camera *cam, t_vector3 ray);


void setup(t_data *data);

# endif
