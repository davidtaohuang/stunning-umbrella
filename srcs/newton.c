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

static void	nescape(t_mlxdata *d, int i)
{
	double	ox;
	double	oy;
	int		iter;
	double	nx;
	double	ny;

	nx = ((i % WIN2X) / (double)(WIN2X) * d->xr + d->xo - d->xoff);
	ny = -((i / WIN2X) / (double)(WIN2Y) * d->yr + d->yo - d->yoff);
	iter = 0;
	while (iter < MITER && fabs(nx * nx + ny * ny - ox * ox - oy * oy) >= NTOL)
	{
		ox = nx;
		oy = ny;
		nx = (2 * ox + (ox * ox - oy * oy) / (ox * ox * ox * ox +
			2 * ox * ox + oy * oy + oy * oy * oy * oy)) / 3;
		ny = (2 * oy - (2 * ox * oy) / (ox * ox * ox * ox +
			2 * ox * ox + oy * oy + oy * oy * oy * oy))/ 3;
		iter++;
	}
	if (iter < MITER)
		*(d->imgd + i) = mlx_get_color_value(d->mlx, (unsigned int)(CR * (CI / (double)MITER) + CO));
	else
		*(d->imgd + i) = mlx_get_color_value(d->mlx, CR + CO);
}

void	newton(t_mlxdata *d)
{
	int			i;

	i = 0;
	d->xo = NXO;
	d->xr = NXR;
	d->yo = NYO;
	d->yr = NYR;
	while (i < WIN2X * WIN2Y)
		nescape(d, i++);
	ft_putendl("Done drawing a newton fractal!");
}
