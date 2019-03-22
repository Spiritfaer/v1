/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_3drot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:58:09 by istalevs          #+#    #+#             */
/*   Updated: 2018/05/15 22:10:02 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vmth.h"

void		vec_3drot(t_v3d *v, int32_t axle, double_t f)
{
	t_v3d	temp;

	f *= DEG_TO_RAD;
	temp = (t_v3d){v->x, v->y, v->z};
	if (axle == X)
	{
		temp.y = v->y * cos(f) - v->z * sin(f);
		temp.z = v->y * sin(f) + v->z * cos(f);
	}
	if (axle == Y)
	{
		temp.x = v->x * cos(f) - v->z * sin(f);
		temp.z = v->x * sin(f) + v->z * cos(f);
	}
	if (axle == Z)
	{
		temp.x = v->x * cos(f) - v->y * sin(f);
		temp.y = v->x * sin(f) + v->y * cos(f);
	}
	*v = temp;
}
