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

# define PI 3.1415926
# define DEG_TO_RAD PI / 180
# define RAD_TO_DEG 180 / PI

enum e_xyz		{X, Y, Z, VECTOR};

typedef struct	s_v3d
{
	double		x;
	double		y;
	double		z;
}				t_v3d;

typedef struct	s_v3i
{
	int			x;
	int			y;
	int			z;
}				t_v3i;

typedef struct	s_v2d
{
	double		x;
	double		y;
}				t_v2d;

typedef struct	s_v2i
{
	int			x;
	int			y;
}				t_v2i;

typedef struct s_matrix
{
	double		**matrix;
	double		**invert_matrix;
	int			size;
}				t_matrix;

t_v3d			vec_1up(void);
t_v3d			vec_1back(void);
t_v3d			vec_1right(void);
t_v3d			vec_1zero(void);

t_v3d			vec_reflect(t_v3d vector, t_v3d normal);
t_v3d			vec_inters(t_v3d v1, t_v3d v2);

t_v2d			vec_2d(double x, double y);
t_v2i			vec_2i(t_v2d vec);
t_v2d			vec_2add(t_v2d v1, t_v2d v2);
t_v2d			vec_2sub(t_v2d v1, t_v2d v2);
t_v2d			vec_2mul(t_v2d v1, t_v2d v2);
t_v2d			vec_2fmul(t_v2d v, double m);
double			vec_2magnitude(t_v2d v);
t_v2d			vec_2norm(t_v2d v);
void			vec_2normalize(t_v2d *v);
double			vec_2dot(t_v2d v1, t_v2d v2);
void			vec_2drot(t_v2d *v, double f);
t_v2d			vec_2dscale(t_v2d v, double scale);

t_v3d			vec_3d(double x, double y, double z);
t_v3i			vec_3i(t_v3d vec);
t_v3d			vec_3add(t_v3d v1, t_v3d v2);
t_v3d			vec_3sub(t_v3d v1, t_v3d v2);
t_v3d			vec_3mul(t_v3d v1, t_v3d v2);
t_v3d			vec_3fmul(t_v3d v, double m);
double			vec_3magnitude(t_v3d v);
t_v3d			vec_3norm(t_v3d v);
void			vec_3normalize(t_v3d *v);
double			vec_3dot(t_v3d v1, t_v3d v2);
void			vec_3drot(t_v3d *v, int axle, double f);
void			vec_3drotate(t_v3d *v, t_v3d rot);
t_v3d			vec_3dscale(t_v3d v, double scale);
t_v3d			vec_3dreflect(t_v3d v, t_v3d norm);


#endif
