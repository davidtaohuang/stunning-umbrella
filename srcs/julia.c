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

static void	jescape(t_mlxdata *d, int i)
{
	// double complex	oz;
	// double complex	nz;

	double	ox;
	double	oy;
	int		iter;
	double	nx;
	double	ny;

	// nz = CMPLX((i % WINX) / (double)(WINX / 2 / JX) - JX, (i / WINY) / (double)(WINY / 2 / JY) - JY);
	nx = (i % WIN2X) / (double)(WIN2X) * d->xr + d->xo - d->xoff;
	ny = -((i / WIN2X) / (double)(WIN2Y) * d->yr + d->yo - d->yoff);
	iter = 0;
	while (iter < MITER)
	{
		ox = nx;
		oy = ny;
		// oz = nz;
		// nz = cpow(oz, 2) + CMPLX(JCRE, JCIM);
		nx = ox * ox - oy * oy + JCRE;
		ny = 2 * ox * oy + JCIM;
		if (nx * nx + ny * ny > 2)
		// if (cabs(nz) > 4)
			break;
		iter++;
	}
	if (iter < MITER)
		*(d->imgd + i) = mlx_get_color_value(d->mlx, (unsigned int)(CR * (CI / (double)MITER) + CO));
	else
		*(d->imgd + i) = mlx_get_color_value(d->mlx, CR + CO);
}

void	julia(t_mlxdata *d)
{
	int			i;

	i = 0;
	while (i < WIN2X * WIN2Y)
		jescape(d, i++);
	ft_putendl("Done drawing a julia fractal!");
}
