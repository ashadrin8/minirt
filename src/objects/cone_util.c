/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:53:56 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/17 11:55:13 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects_internal.h"

int	estimate_ts(t_cone_hit *hit, double *t_out)
{
	if (hit->t0 < 0)
	{
		if (hit->t1 < 0)
			return (0);
		*t_out = hit->t1;
		return (1);
	}
	if (hit->t1 < 0)
	{
		*t_out = hit->t0;
		return (1);
	}
	if (hit->t0 < hit->t1)
	{
		*t_out = hit->t0;
		return (1);
	}
	*t_out = hit->t1;
	return (1);
}
