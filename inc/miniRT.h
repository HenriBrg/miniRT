/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:46:24 by hberger           #+#    #+#             */
/*   Updated: 2019/12/19 23:30:21 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <math.h>
# include <stdio.h>

# include "libft.h"
# include "mlx.h"

# define TRUE 1
# define FALSE 0

# define KEY_ESC 53
# define KEY_ARROW_LEFT 123
# define KEY_ARROW_RIGHT 124


# define SCREENSIZE 10
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
	struct 		s_light		*next;
}				t_light;

typedef struct	s_camera
{
	t_vector3	pos;
	t_vector3	orientation;
	double		fov;
	t_vector3	vecx;
	t_vector3	vecy;
	t_vector3	vecz;
	struct 		s_camera		*next;
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
	t_vector3				pb;
	t_vector3				center;
	t_vector3				orientation;
	double					diameter;
	double					radius;
	double					height;
	int						colour;
	struct		s_cylinder	*next;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vector3				p1;
	t_vector3				p2;
	t_vector3				p3;
	t_vector3				normal;
	int						colour;
	struct 		s_triangle	*next;
}				t_triangle;

typedef struct s_interobject
{
	void 		*ptr;
	int			type;
	int			inter;
	int			colour;
	int			intercount;
	double		distance;
	t_vector3	ray;
	t_vector3	origin;
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
	int				parse_res_doublon;
	int				parse_amb_doublon;

	int				camera_num;
	t_camera		*currentcam;

	t_resolution	*res;
	t_ambiant_light	*amb;
	t_light			*lights;
	t_camera		*cameras;
	t_sphere		*spheres;
	t_plane			*planes;
	t_square		*squares;
	t_cylinder		*cylinders;
	t_triangle		*triangles;
}				t_data;

/*
** maths/
*/

int			solvequadratic(t_vector3 abc, double *t0, double *t1);
double		absd(double n);
double		veclen(t_vector3 vec);
double		rad(double degree);
double		dot(t_vector3 vec1, t_vector3 vec2);
double		dotsame(t_vector3 vec1);
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

void 			try_spheres(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj);
void 			try_planes(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj);
void 			try_squares(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj);
void 			try_triangles(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj);
void 			try_cylinders(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj);
t_interobject 	intersearch(t_data *data, t_camera *cam, t_vector3 ray);


/*
** keys.c
*/

int			camera_count(t_data *data);
t_camera 	*get_current_camera(t_data *data);

/*
** parser
*/

void		parse_ambiant(t_data *data, char **tab, int fd);
void		parse_resolution(t_data *data, char **tab, int fd);
void		add_sphere(t_data *data, char **tab, int fd);
void		add_plane(t_data *data, char **tab, int fd);
void		add_square(t_data *data, char **tab, int fd);
void		add_triangle(t_data *data, char **tab, int fd);
void		add_cylinder(t_data *data, char **tab, int fd);
void		add_light(t_data *data, char **tab, int fd);
void		add_camera(t_data *data, char **tab, int fd);

void		free_light(t_data *data);
void		free_camera(t_data *data);
void		free_sphere(t_data *data);
void		free_plane(t_data *data);
void		free_square(t_data *data);
void		free_triangle(t_data *data);
void		free_cylinder(t_data *data);


int			parse(t_data *data, char *filename);
int			uint_format(char *s);
int			double_format(char *s);
int			str_to_rgb(char *s);
int			rgb_format(char *s);
int			uint_format(char *s);
int			double_format(char *s);
int			str_to_rgb(char *s);
int			rgb_format(char *s);
int			check_range_vec3_orient(t_vector3 *vec);
int			vec3_format(char *s, t_vector3 *vec);
int			skip_double(char *s, int i);
void 		corrupted(t_data *data, char **tab, char *message, int fd);
void 		putexit(char *msg);

# endif
