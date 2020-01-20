int		add_lights(int a, int b)
{
	t_rgb l_a;
	t_rgb l_b;

	decode_rgb(a, &(l_a.r), &(l_a.g), &(l_a.b));
	decode_rgb(b, &(l_b.r), &(l_b.g), &(l_b.b));
	l_a.r += l_b.r;
	l_a.g += l_b.g;
	l_a.b += l_b.b;
	if (l_a.r > 255)
		l_a.r = 255;
	if (l_a.g > 255)
		l_a.g = 255;
	if (l_a.b > 255)
		l_a.b = 255;
	return (encode_rgb(l_a.r, l_a.g, l_a.b));
}

int		apply_intensity_rgb(int colour, double intensity)
{
	int red;
	int green;
	int blue;

	decode_rgb(colour, &red, &green, &blue);
	red = (double)red * intensity;
	green = (double)green * intensity;
	blue = (double)blue * intensity;
	return (encode_rgb(red, green, blue));
}

int		filter_colours_rgb(int source, t_geo *obj, int lvl)
{
	t_rgb	src;
	t_rgb	surf;

	decode_rgb(source, &(src.r), &(src.g), &(src.b));
	decode_rgb(obj->colour, &(surf.r), &(surf.g), &(surf.b));
	if (surf.r > src.r)
		surf.r = src.r;
	if (surf.g > src.g)
		surf.g = src.g;
	if (surf.b > src.b)
		surf.b = src.b;
	if (lvl)
	{
		surf.r = (double)surf.r * pow(0.995, lvl);
		surf.g = (double)surf.g * pow(0.995, lvl);
		surf.b = (double)surf.b * pow(0.995, lvl);
	}
	return (encode_rgb(surf.r, surf.g, surf.b));
}

// COLOR -----------------------------------------------------------------------

t_vector3	point_from_ray(t_vector3 origin, t_vector3 ray, double t)
{
	origin.x += ray.x * t;
	origin.y += ray.y * t;
	origin.z += ray.z * t;
	return (origin);
}

/*
** Returns a vector with a direction set by points a and b
** (vector going from a to b)
*/

t_vector3	direction_vector(t_vector3 a, t_vector3 b)
{
	b.x -= a.x;
	b.y -= a.y;
	b.z -= a.z;
	return (b);
}

t_vector3	get_normal_vector(t_vector3 point, t_geo *geo, t_data *d)
{
	t_vector3 normal;

	normal = geo->get_normal_vector(point, geo->obj);
	// ???????????????
	if (dot(normal, d->ray) > 0)
		normal = scalar_vect(normal, -1.0);
	// --
	return (normalise_vector(normal));
}

double		distance(t_vector3 a, t_vector3 b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2)));
}

double		magnitude(t_vector3 a)
{
	return (distance(a, create_vector(0, 0, 0)));
}

double		angle_between_vectors(t_vector3 a, t_vector3 b)
{
	double	d;
	double	angle;

	d = dot(a, b) / (magnitude(a) * magnitude(b));
	angle = acos(d);
	return (angle);
}

double		get_light_angle(t_data data, t_light *light, double t,
			t_geo *rt_obj)
{
	t_vector3	inter_point;
	t_vector3	norm_vect;

	inter_point = point_from_ray(data.ray_origin, data.ray, t);
	norm_vect = get_normal_vector(inter_point, rt_obj, &data);
	return (angle_between_vectors(norm_vect,
								direction_vector(inter_point, light->pos)));
}

double		get_valid_t(t_rt_param param)
{
	double valid;

	valid = -1.0;
	if (param.i > 0 && param.v && (valid < 0 || param.i < valid))
		valid = param.i;
	if (param.i_2 > 0 && param.v_2 && (valid < 0 || param.i_2 < valid))
		valid = param.i_2;
	if (param.i_3 > 0 && param.v_3 && (valid < 0 || param.i_3 < valid))
		valid = param.i_3;
	if (param.i_4 > 0 && param.v_4 && (valid < 0 || param.i_4 < valid))
		valid = param.i_4;
	return (valid);
}

int			is_light_obstructed(t_data data, t_geo *rt_obj, t_light *light)
{
	t_vector3	start;
	t_vector3	light_ray;
	t_list		*ele;
	t_rt_param	param;
	double		valid_t;

	start = point_from_ray(data.ray_origin, data.ray, data.t);
	light_ray = normalise_vector(direction_vector(start, light->pos));
	start = add_vect(start,
			scalar_vect(get_normal_vector(start, rt_obj, &data), 0.01));
	ele = data.objects;
	while (ele)
	{
		param = set_param(start, light_ray, -1, 0);
		if (raytrace(ele->content, &param))
		{
			valid_t = get_valid_t(param);
			if (valid_t > 0)
				if (distance(start, light->pos) >
					distance(start, point_from_ray(start, light_ray, valid_t)))
					return (1);
		}
		ele = ele->next;
	}
	return (0);
}

int			calc_colour_from_light(t_data data, t_geo *rt_obj)
{
	t_list	*first;
	t_light	*light;
	double	ang;
	int		final_light;
	int		l_val;

	final_light = 0;
	first = data.lights;
	while (first && data.render_mode)
	{
		light = first->content;
		if (!is_light_obstructed(data, rt_obj, light))
		{
			ang = get_light_angle(data, light, data.t, rt_obj);
			printf("ang = %d\n", ang);
			if (ang < M_PI_2 && ang > -M_PI_2)
			{
				l_val = apply_intensity_rgb(light->colour, sin(M_PI_2 - ang));
				final_light = add_lights(final_light, l_val);
			}
		}
		first = first->next;
	}
	// final_light = add_lights(final_light,
	//				!data.render_mode ? data.no_render_amb : data.amb.colour);
	// return (filter_colours_rgb(final_light, rt_obj, data.ref_lvl));
	return (final_light);
}
