/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_reflect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 14:02:58 by istalevs          #+#    #+#             */
/*   Updated: 2018/05/20 20:31:10 by istalevs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** V == vector
** N == normal
** c1 - скалярное произведение
** Rl - вектор, отраженный лучь
** c1 = -dot_product( N, V )
** Rl = V + (2 * N * c1 )
*/

#include "vmth.h"

t_v3d		vec_reflect(t_v3d vector, t_v3d normal)
{
	t_v3d new;

	new = vec_3fmul(normal, -2.0 * vec_3dot(vector, normal));
	new = vec_3add(new, vector);
	return (new);
}
