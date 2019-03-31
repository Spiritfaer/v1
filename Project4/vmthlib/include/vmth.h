/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vmth.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 23:25:38 by istalevs          #+#    #+#             */
/*   Updated: 2018/05/20 14:48:14 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VMTH_H
# define VMTH_H

# include <math.h>
# include <float.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>

# define PI 3.14159265358979323846264338327950288
# define DEG_TO_RAD PI / 180
# define RAD_TO_DEG 180 / PI

enum e_xyz		{X, Y, Z, VECTOR};

typedef struct	s_v3d
{
	double_t	x;
	double_t	y;
	double_t	z;
}				t_v3d;

typedef struct	s_v3i
{
	int32_t		x;
	int32_t		y;
	int32_t		z;
}				t_v3i;

typedef struct	s_v2d
{
	double_t	x;
	double_t	y;
}				t_v2d;

typedef struct	s_v2i
{
	int32_t		x;
	int32_t		y;
}				t_v2i;

typedef struct s_matrix
{
	double_t	**matrix;
	double_t	**invert_matrix;
	int32_t		size;
}				t_matrix;

double_t		deg_to_rad(const double_t deg);

t_v3d			vec_1up(void);
t_v3d			vec_1back(void);
t_v3d			vec_1right(void);
t_v3d			vec_1zero(void);
t_v3d			vec_1double(double_t d);

t_v3d			vec_reflect(t_v3d vector, t_v3d normal);
t_v3d			vec_inters(t_v3d v1, t_v3d v2);

t_v2d			vec_2d(double_t x, double_t y);
t_v2i			vec_2i(t_v2d vec);
t_v2d			vec_2add(t_v2d v1, t_v2d v2);
t_v2d			vec_2sub(t_v2d v1, t_v2d v2);
t_v2d			vec_2mul(t_v2d v1, t_v2d v2);
t_v2d			vec_2fmul(t_v2d v, double_t m);
double_t		vec_2magnitude(t_v2d v);
t_v2d			vec_2norm(t_v2d v);
void			vec_2normalize(t_v2d *v);
double_t		vec_2dot(t_v2d v1, t_v2d v2);
void			vec_2drot(t_v2d *v, double_t f);
t_v2d			vec_2dscale(t_v2d v, double_t scale);

t_v3d			vec_3d(double_t x, double_t y, double_t z);
t_v3i			vec_3i(t_v3d vec);
t_v3d			vec_3add(t_v3d v1, t_v3d v2);
t_v3d			vec_3sub(t_v3d v1, t_v3d v2);
t_v3d			vec_3mul(t_v3d v1, t_v3d v2);
t_v3d			vec_3fmul(t_v3d v, double_t m);
double_t		vec_3magnitude(t_v3d v);
t_v3d			vec_3norm(t_v3d v);
void			vec_3normalize(t_v3d *v);
double_t		vec_3dot(t_v3d v1, t_v3d v2);
void			vec_3drot(t_v3d *v, int32_t axle, double_t f);
void			vec_3drotate(t_v3d *v, t_v3d rot);
t_v3d			vec_3dscale(t_v3d v, double_t scale);
t_v3d			vec_3dreflect(t_v3d v, t_v3d norm);

t_v3d			vec_3invert_dir(const t_v3d *dir);

double_t**		get_new_m(uint8_t n);
t_matrix*		get_new_matrix(uint8_t n);
t_matrix*		get_copy_matryx(t_matrix *m);

void			get_rows(t_matrix *m, int32_t y, double_t *buffer);
void			get_colums(t_matrix *m, int32_t x, double_t *buffer);
void			set_rows_buffer(double_t *src, int32_t size, double_t *buffer, double_t mult);

double_t		get_discriminant(t_matrix *m);
double_t		get_minor(t_matrix *m, t_v2i i);
t_matrix*		get_minors_matrix(t_matrix *m);

void			destroy_matrix(t_matrix **m);
void			free_mat(double_t **data, int32_t size);

void			change_symbol(t_matrix *m);
t_matrix*		transposed_matrix(t_matrix *m);
t_matrix*		mult_m_to_m(t_matrix *one, t_matrix *two);

void			minus_matrix_buffer(double_t *src, double_t *dst, int32_t size);
void			swap_for_rows(t_matrix *m, t_v2i i);
void			invert_matrix(t_matrix *m);

double_t		mult_for_double_buffer(double_t *src, double_t *dst, int32_t size);
t_v3d			mult_vect_matrix_3_3(t_v3d world_centr, double_t **invert_matrix);
t_v3d			mult_vect_matrix_4_4(t_v3d world_centr, double_t **invert_matrix);

void			fill_vertical_matrix(t_matrix *m);
#endif
