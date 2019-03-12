/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_3dreflect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 23:01:22 by istalevs          #+#    #+#             */
/*   Updated: 2018/05/15 23:06:47 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vmth.h"

t_v3d		vec_3dreflect(t_v3d v, t_v3d norm)
{
	t_v3d temp;

	temp = vec_3fmul(norm, -2.0 * vec_3dot(v, norm));
	temp = vec_3add(temp, v);
	return (temp);
}
