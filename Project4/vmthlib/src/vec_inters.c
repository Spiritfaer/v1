/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_inters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 14:34:44 by istalevs          #+#    #+#             */
/*   Updated: 2018/05/20 20:31:11 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** U1 = (a1, b1, c1)
** U2 = (a2, b2, c2)
** P' = (Ap, Bp, Cp) = U1 * U2 = (b1c2 - b2c1, a2c1 - a1c2, a1b2 - a2b1)
*/

#include "vmth.h"

t_v3d		vec_inters(t_v3d v1, t_v3d v2)
{
	t_v3d	inters;

	inters.x = v1.y * v2.z - v2.y * v1.z;
	inters.y = v2.x * v1.z - v1.x * v2.z;
	inters.z = v1.x * v2.y - v2.x * v1.y;
	return (inters);
}
