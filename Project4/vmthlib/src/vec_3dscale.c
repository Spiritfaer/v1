/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_3dscale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 22:14:50 by istalevs          #+#    #+#             */
/*   Updated: 2018/05/15 22:16:27 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vmth.h"

t_v3d		vec_3dscale(t_v3d v, double_t scale)
{
	vec_3normalize(&v);
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;
	return (v);
}
