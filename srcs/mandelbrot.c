/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:17:09 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/28 17:17:09 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	mescape(t_mlxdata *d, int i)
{
	double	ox;
	double	oy;
	int		iter;
	double	nx;
	double	ny;

	nx = 0;
	ny = 0;
	iter = 0;
	while (iter < MITER && (nx * nx + ny * ny <= 4))
	{
		ox = nx;
		oy = ny;
		nx = ox * ox - oy * oy + ((i % WIN2X) / (double)(WIN2X) * d->xr + d->xo - d->xoff);
		ny = 2 * ox * oy - ((i / WIN2X) / (double)(WIN2Y) * d->yr + d->yo - d->yoff);
		iter++;
	}
	if (iter < MITER)
		*(d->imgd + i) = mlx_get_color_value(d->mlx, (unsigned int)(CR * (CI / (double)MITER) + CO));
	else
		*(d->imgd + i) = mlx_get_color_value(d->mlx, CR + CO);
}

void	mandelbrot(t_mlxdata *d)
{
	int			i;

	i = 0;
	while (i < WIN2X * WIN2Y)
		mescape(d, i++);
	ft_putendl("Done drawing a mandelbrot fractal!");
}