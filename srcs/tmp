void debug(t_data *data)
{
	t_light		*lgt;
	t_camera	*cam;
	t_plane 	*planes;
	t_sphere	*spheres;
	t_square	*squares;
	t_cylinder 	*cylinders;
	t_triangle 	*triangles;

	printf("Résolution	: w = %d et h = %d\n", data->res->width, data->res->height);
	printf("Ambiant		: ratio = %lf et colour = %d\n", data->amb->ratio,  data->amb->colour);

	cam = data->cameras;
	while (cam)
	{
		printf("Camera		: pos (x:%lf, y:%lf, z:%lf) et vector(x:%lf, y:%lf, z:%lf) et fov = %lf\n", cam->pos.x, cam->pos.y, cam->pos.z, cam->orientation.x, cam->orientation.y, cam->orientation.z, cam->fov);
		cam = cam->next;
	}

	lgt = data->lights;
	while (lgt)
	{
		printf("Light		: pos (x:%lf, y:%lf, z:%lf) et ratio = %lf et RGB(%d)\n", lgt->pos.x, lgt->pos.y, lgt->pos.z, lgt->ratio, lgt->colour);
		lgt = lgt->next;
	}

	spheres = data->spheres;
	while (spheres)
	{
		printf("Sphere		: pos (x:%lf, y:%lf, z:%lf) et radius = %lf et RGB(%d)\n", spheres->center.x, spheres->center.y, spheres->center.z, spheres->radius, spheres->colour);
		spheres = spheres->next;
	}

	planes = data->planes;
	while (planes)
	{
		printf("Plane		: center (x:%lf, y:%lf, z:%lf) et normal computed(x:%lf, y:%lf, z:%lf) et RGB(%d)\n", planes->center.x, planes->center.y, planes->center.z, planes->normal.x, planes->normal.y, planes->normal.z, planes->colour);
		planes = planes->next;
	}

	squares = data->squares;
	while (squares)
	{
		printf("Square		: center (x:%lf, y:%lf, z:%lf) et normal computed (x:%lf, y:%lf, z:%lf) et height = %lf et RGB(%d)\n", squares->center.x, squares->center.y, squares->center.z, squares->normal.x, squares->normal.y, squares->normal.z, squares->height, squares->colour);
		squares = squares->next;
	}

	triangles = data->triangles;
	while (triangles)
	{
		printf("triangle		: pos_a (x:%lf, y:%lf, z:%lf) et pos_b (x:%lf, y:%lf, z:%lf) et pos_c (x:%lf, y:%lf, z:%lf) et RGB(%d)\n", triangles->p1.x, triangles->p1.y, triangles->p1.z, triangles->p2.x, triangles->p2.y, triangles->p2.z, triangles->p3.x, triangles->p3.y, triangles->p3.z , triangles->colour);
		triangles = triangles->next;
	}
	cylinders = data->cylinders;
	while (cylinders)
	{
		printf("Cylinder		: center (x:%lf, y:%lf, z:%lf) et vector (x:%lf, y:%lf, z:%lf) et RGB(%d) et diam = %lf et height = %lf\n", cylinders->center.x, cylinders->center.y, cylinders->center.z, cylinders->orientation.x, cylinders->orientation.y, cylinders->orientation.z, cylinders->colour, cylinders->radius, cylinders->height);
		cylinders = cylinders->next;
	}


}

void setup(t_data *data)
{
	data->cameras = malloc(sizeof(t_camera));
	data->res = malloc(sizeof(t_resolution));

	data->res->width = 800;
	data->res->height = 800;
	data->cameras->fov = 55;
	data->cameras->pos = newvec(-10,0,0);
	data->cameras->orientation = newvec(0.2,0.1,0.1);
	data->cameras->vecx = reorientate(newvec(1, 0, 0), data->cameras->orientation);
	data->cameras->vecy = reorientate(newvec(0, 1, 0), data->cameras->orientation);
	data->cameras->vecz = reorientate(newvec(0, 0, 1), data->cameras->orientation);

	data->spheres = malloc(sizeof(t_sphere));
	data->spheres->next = NULL;
	data->spheres->radius = 1;
	data->spheres->center = newvec(2,0.5,0);
	data->spheres->colour = RGBTOI(255,0,255);

	// t_plane *plane1;
	// plane1 = malloc(sizeof(t_plane));
	// plane1->next = NULL;
	// plane1->center = newvec(0,-1,0);
	// plane1->normal = reorientate(newvec(0, 1, 0), newvec(0,0,0));
	// plane1->colour = RGBTOI(255,255,255);
	// data->planes = plane1;

	t_square *square1;
	square1 = malloc(sizeof(t_square));
	square1->next = NULL;
	square1->height = 4;
	square1->colour = RGBTOI(25,255,255);
	square1->center = newvec(0,0,-2);
	square1->normal = reorientate(newvec(0, 1, 0), newvec(0,1,0));
	square1->x = reorientate(newvec(1, 0, 0), 	   newvec(0,1,0));
	square1->x = mult1vec(square1->x, square1->height);
	square1->z = reorientate(newvec(0, 0, 1), 	   newvec(0,1,0));
	square1->z = mult1vec(square1->z, square1->height);
	data->squares = square1;

	t_triangle *tri1;
	tri1 = malloc(sizeof(t_triangle));
	tri1->next = NULL;
	tri1->colour = RGBTOI(255,0,0);
	tri1->p1 = newvec(0,0,-2);
	tri1->p2 = newvec(4,0,-2);
	tri1->p3 = newvec(2,2,0);
	data->triangles = tri1;

	t_triangle *tri2;
	tri2 = malloc(sizeof(t_triangle));
	tri2->next = NULL;
	tri2->colour = RGBTOI(0,255,0);
	tri2->p1 = newvec(0,0,2);
	tri2->p2 = newvec(4,0,2);
	tri2->p3 = newvec(2,2,0);
	tri1->next = tri2;

	t_triangle *tri3;
	tri3 = malloc(sizeof(t_triangle));
	tri3->next = NULL;
	tri3->colour = RGBTOI(0,0,255);
	tri3->p1 = newvec(4,0,-2);
	tri3->p2 = newvec(4,0,2);
	tri3->p3 = newvec(2,2,0);
	tri2->next = tri3;



	t_cylinder *cyl1;
	cyl1 = malloc(sizeof(t_cylinder));
	cyl1->next = NULL;
	cyl1->colour = RGBTOI(140,100,255);
	cyl1->center = newvec(20, 0, 0);

	cyl1->orientation = reorientate(newvec(0.9,1,0.4), newvec(0,0,0));
	cyl1->diameter = 3;
	cyl1->radius = cyl1->diameter / 2;
	cyl1->height = 10;
	cyl1->pb = addvec(cyl1->center, mult1vec(cyl1->orientation, cyl1->height));

	data->cylinders = cyl1;

}
