#include "../heads_global/minirt.h"

void	print_scene(t_scene *s);
void	print_camera(t_camera *cam);
void	print_light(t_light *l);
void	print_shape(t_shape *sh);
void	print_material(t_matrl *m);
void	print_matrix(t_matrix *m);
void	print_tuple(t_tuple *t);
void	print_intersect_list(t_intersection_list *list);
void	print_world(t_world *w);
void	print_intersect_list(t_intersection_list *intersect);
void	print_intersection(t_intersection *intersect, int i);
void	print_computations(t_computations *comp);
void	print_ray(t_ray *ray, int y, int x);

void	print_scene(t_scene *s)
{
	printf("====================\n\tt_scene:\n");
	printf("\tres x:[%d], y:[%d]\n", s->resolution_x, s->resolution_y);
	printf("\tambi ratio:[%.2f]\n", s->ambi_ratio);
	printf("\tambi_color:");
	print_tuple(&s->ambi_color);
	printf("\tcamera counter:[%d]\n", s->camera_count);
	for (int i = 0; i < s->camera_count; i++) {
		print_camera(s->cameras[i]);
	}
	printf("\tlight counter:[%d]\n", s->light_count);
	for (int i = 0; i < s->light_count; i++) {
		print_light(s->lights[i]);
	}
	printf("\tshape counter:[%d]\n", s->shape_count);
	for (int i = 0; i < s->shape_count; i++) {
		print_shape(s->shapes[i]);
	}
	printf("====================\n");
}

void	print_camera(t_camera *cam)
{
	printf("\t\t=========================\n");
	printf("\t\tCAMERA\n");
	printf("\t\ttuple from:");
	print_tuple(&cam->from);
	printf("\t\tname:[%s]\n", cam->name);
	printf("\t\tsize h:[%d], v:[%d], pix_size:[%.2f]\n", cam->h_size, cam->v_size, cam->pix_size);
	printf("\t\ttransform:\n");
	print_matrix(&cam->transform);
	printf("\t\thalf:[%.2f], h_w:[%.2f], h_h:[%.2f], aspect:[%.2f]\n", cam->half, cam->half_w, cam->half_h, cam->aspect);
	printf("\t\t= = = = = = = = = = = = =\n");
}

void	print_light(t_light *l)
{
	printf("\t\t========================\n");	
	printf("\t\tpos: ");
	print_tuple(&l->position);
	printf("\t\tcol: ");
	print_tuple(&l->color);
	printf("\t\t= = = = = = = = = = = = =\n");
}

void	print_shape(t_shape *sh)
{
	printf("\t\t======================\n");
	printf("\t\ttype:[%c]\n", sh->type);
	printf("\t\tmaterial:\n");
	print_material(&sh->matrl);
	printf("\t\ttrans:\n");
	print_matrix(&sh->trans);
	printf("\t\tshape @ [%p]\n", sh->shape);

	printf("\t\t= = = = = = = = = = = = =\n");
}

void	print_material(t_matrl *m)
{
	printf("\t\t========================\n");
	printf("\t\tMATERIAL\n");
	printf("\t\tcolor: ");
	print_tuple(&m->color);
	printf("\t\tdiffuse:[%.2f], amb:[%.2f], spec:[%.2f], shin:[%.2f]\n", m->diffuse, m->ambient, m->specular, m->shininess);
	printf("\t\t= = = = = = = = = = = = =\n");
}

void	print_matrix(t_matrix *m)
{
	int	h = 0;
	int	w = 0;

	printf("\tm->h: [%d], m->w: [%d]\n", m->h, m->w);
	while (h < m->h)
	{
		printf("\t[ ");
		w = 0;
		while (w < m->w)
		{
			printf("%.2f", m->mtx[h][w]);
			if (m->w > 1)
				printf("\t");
			w++;
		}
		printf("\t]\n");
		h++;
	}
	printf("\n");
}

void	print_tuple(t_tuple *t)
{
	printf("\ttuple x:[%.2f], y:[%.2f], z:[%.2f], type:[%d]\n", t->x, t->y, t->z, t->type);
}

/* ***** */
/* ***** */

void	print_world(t_world *w)
{
	printf("\t\t========================\n");
	printf("\t\tWORLD\n");
	printf("\t\tshape_count:[%d], light_count:[%d]\n", w->shape_counter, w->lights_counter);
	for (int i = 0; i < w->shape_counter; i++) {
		print_shape(w->shapes[i]);
	}
	for (int i = 0; i < w->lights_counter; i++) {
		print_light(w->lights[i]);
	}
	printf("\t\tambi:");
	print_light(&w->amb);
	/*
	printf("intersection MERGED:\n");
	print_intersect_list(w->merged);
	printf("intersection UNSORTED:\n");
	if (w->unsorted)
	{
		for (int i = 0; i < w->shape_counter; i++) {
			print_intersect_list(w->unsorted[i]);
		}
	}
	else
	{
		printf("\t\t NO Unsorted intersections:\n");
	}
	*/
	printf("\t\t= = = = = = = = = = = = =\n");
}

void	print_intersect_list(t_intersection_list *intersect)
{
	if (intersect)
	{
		printf("\tIntersections:\n");
		printf("\t*inersect @ [%p] \n", intersect);
		printf("\tsize:[%d]\n", intersect->size);
		printf("\t**list @ [%p]\n", intersect->list);
		printf("\t*list @ [%p]\n", intersect->list[0]);
	}
	else
	{
		printf("\t\t NO intersections:\n");
	}
}

void	print_intersection(t_intersection *intersect, int i)
{
	printf("\ti: [%d]\t", i);
	printf("intersect @ [%p]\n", intersect);
}

void	print_computations(t_computations *comp)
{
	printf("\t\t========================\n");
	printf("\t\tCOMPUTATIONS\n");
	printf("\t\tt: [%.2f], inside: [%d]\n", comp->t, comp->inside);
	print_shape(comp->shape);
	printf("\t\tpoint:");
	print_tuple(&comp->point);
	printf("\t\teyev :");
	print_tuple(&comp->eyev);
	printf("\t\tnormv:");
	print_tuple(&comp->normv);
	printf("\t\tover :");
	print_tuple(&comp->overpoint);
	printf("\t\t= = = = = = = = = = = = =\n");
}

void	print_ray(t_ray *ray, int y, int x)
{
	printf("\t\t========================\n");
	printf("\t\tRAY [%d][%d]\n", y, x);
	printf("\t\torigin :");
	print_tuple(&ray->origin);
	printf("\t\tdirect :");
	print_tuple(&ray->dir);
	printf("\t\t= = = = = = = = = = = = =\n");
}