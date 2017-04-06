/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:49:31 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/29 17:49:31 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	newton(t_mlxdata *d, int i)
{
	double			ox;
	double			oy;
	double			nx;
	double			ny;
	unsigned int	iter;

	nx = (i % WIN2X) / (double)(WIN2X) * d->xr + d->xo - d->xoff;
	ny = -((i / WIN2X) / (double)(WIN2Y) * d->yr + d->yo - d->yoff);
	iter = 0;
	while (iter < d->miter && (nx - ox) * (nx - ox) + (ny - oy) * (ny - oy) >= NTOL)
	{
		ox = nx;
		oy = ny;
		nx = (2 * ox + (ox * ox - oy * oy) / (ox * ox * ox * ox +
			2 * ox * ox * oy * oy + oy * oy * oy * oy)) / 3;
		ny = (2 * oy - (2 * ox * oy) / (ox * ox * ox * ox +
			2 * ox * ox * oy * oy + oy * oy * oy * oy))/ 3;
		iter++;
	}
	if (iter < d->miter)
		*(d->imgd + i) = mlx_get_color_value(d->mlx, (unsigned int)(CR * (CI
			/ (double)MITER) + CO));
	else
		*(d->imgd + i) = mlx_get_color_value(d->mlx, CR + CO);
}
