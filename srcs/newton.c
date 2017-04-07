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

/*
**	Nx and ny stand for new x and new y respectively. X corresponds to
**	the real component of the complex coordinate and y corresponds to the
**	imaginary component of the complex coordinate. Ox and oy stand for old x
**	old y respectively. The pixel coordinate values are obtained from the
**	iterator variable by normalizing against the x-dimension of the
**	image/window. It is then tranformated to a coordinate in the complex plane
**	using the image/window size, range variable, offset variable, and zoom
**	offset variable (d->xr = range, d->xo = offset, d->xoff = zoom offset).
**
**	In the while loop, nx and ny are updated according to the formula defining
**	the fractal until either the maximum number of iterations is reached or the
**	escape/boundary condition is reached. The number of iterations is then
**	scaled against the color range (with option for a smoothing function) and
**	added to the color offset. This value is assigned at that specific pixel
**	in the image data address.
*/

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
	while (iter < d->miter && (nx - ox) * (nx - ox) + (ny - oy) *
		(ny - oy) >= NTOL)
	{
		ox = nx;
		oy = ny;
		nx = (2 * ox + (ox * ox - oy * oy) / (ox * ox * ox * ox +
			2 * ox * ox * oy * oy + oy * oy * oy * oy)) / 3;
		ny = (2 * oy - (2 * ox * oy) / (ox * ox * ox * ox +
			2 * ox * ox * oy * oy + oy * oy * oy * oy)) / 3;
		iter++;
	}
	if (iter < d->miter)
		*(d->imgd + i) = mlx_get_color_value(d->mlx, (unsigned int)(CR *
			(double)(CSMOOTH ? CS : CI) / d->miter) + CO);
	else
		*(d->imgd + i) = mlx_get_color_value(d->mlx, CR + CO);
}
