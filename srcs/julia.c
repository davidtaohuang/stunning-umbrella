/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:17:05 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/28 17:17:05 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <complex.h>

void	julia(t_mlxdata *d, int i)
{
	double			ox;
	double			oy;
	double			nx;
	double			ny;
	unsigned int	iter;

	nx = (i % WIN2X) / (double)(WIN2X) * d->xr + d->xo - d->xoff;
	ny = -((i / WIN2X) / (double)(WIN2Y) * d->yr + d->yo - d->yoff);
	iter = 0;
	while (iter < d->miter && nx * nx + ny * ny <= 4)
	{
		ox = nx;
		oy = ny;
		nx = ox * ox - oy * oy + JCRE;
		ny = 2 * ox * oy + JCIM;
		iter++;
	}
	if (iter < d->miter)
		*(d->imgd + i) = mlx_get_color_value(d->mlx, (unsigned int)(CR *
			(CI / (double)MITER) + CO));
	else
		*(d->imgd + i) = mlx_get_color_value(d->mlx, CR + CO);
}
