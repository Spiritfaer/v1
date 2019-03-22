/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_2drot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:22:52 by istalevs          #+#    #+#             */
/*   Updated: 2018/05/15 22:09:51 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vmth.h"

void		vec_2drot(t_v2d *v, double_t f)
{
	t_v2d tmp;

	f *= DEG_TO_RAD;
	tmp.x = v->x * cos(f) - v->y * sin(f);
	tmp.y = v->x * sin(f) + v->y * cos(f);
	*v = tmp;
}
