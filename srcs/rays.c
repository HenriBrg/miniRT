t_vector3	addvec(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3 new;

	new.x = vec1.x + vec2.x;
	new.y = vec1.y + vec2.y;
	new.z = vec1.z + vec2.z;
	return (new);
}

t_vector3 compute_ray(t_data *env, t_camera *cam, int x, int y)
{
	double normalized_i;
	double normalized_j;
	t_vector3 tmp;

	normalized_i = (x / env->res->x) - 0.5;
	normalized_j = (y / env->res->y) - 0.5;
	tmp
}

Ray ComputeCameraRay(int i, int j) {
  const float width = 512.0;  // pixels across
  const float height = 512.0;  // pixels high
  double normalized_i = (i / width) - 0.5;
  double normalized_j = (j / height) - 0.5;
  Vector3 image_point = normalized_i * camera_right +
                        normalized_j * camera_up +
                        camera_position + camera_direction;
  Vector3 ray_direction = image_point - camera_position;
  return Ray(camera_position, ray_direction);
}

/*
** We adopt a standard vertical FOV of 40
** We will rotate around the Y axis for horizontal FOV and around the X axis for vertical FOV
*/
