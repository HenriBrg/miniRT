/*
int	isobstructed(t_data *data, t_light *light, t_interobject *object, t_camera *cam, t_vector3 ray)
{
	t_vector3	start;
	t_vector3	light_ray;
	t_vector3	normal;
	t_interobject obstacle;
	t_vector3	hit;

	hit = getpointfromray(cam->pos, ray, object->distance);
	if (object->type == SPHERE)
		normal = getnormalsphere((t_sphere*)(object->ptr), hit);
	else if (object->type == PLANE)
		normal = ((t_plane*)(object->ptr))->normal;
	else if (object->type == SQUARE)
		normal = ((t_square*)(object->ptr))->normal;
	else if (object->type == TRIANGLE)
		normal = getnormaltriangle((t_triangle*)(object->ptr));
	else
		normal = getnormalcylinder((t_cylinder*)(object->ptr), hit);
	normal = norm(normal);

	start = getpointfromray(cam->pos, ray, object->distance);
	light_ray = norm(subvec(light->pos, start));
	start = addvec(start,
			mult1vec(normal, 0.01));

	obstacle = intersearch(data, light->pos, light_ray);
	if (obstacle.inter == TRUE)
		if (obstacle.distance > 0)
			if (distance(start, light->pos) > distance(start, getpointfromray(start, light_ray, obstacle.distance)))
				return (1);
	return (0);
}
*/
