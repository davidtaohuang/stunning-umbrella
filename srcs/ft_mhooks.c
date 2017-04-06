/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mhooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:10:13 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/29 17:10:13 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdio.h>

int		ft_mmove(int x, int y, t_fmeta *meta)
{
	if (!(meta->d->lock) && x >= 0 && x <= WIN2X && y >= 0 && y <= WIN2Y)
	{
		meta->d->xm = x;
		meta->d->ym = y;
		if (meta->type == 'j')
		{
			// printf("x: %d, y: %d\n", x, y);
			meta->d->x = x / (double)WINX * meta->d->xr + meta->d->xo - meta->d->xoff;
			meta->d->y = y / (double)WINY * meta->d->yr + meta->d->yo - meta->d->yoff;
			mlx_clear_window(meta->d->mlx, meta->d->win);
			mlxdraw(meta);
		}
	}
	return (0);
}

void	ft_mzoom(int button, int x, int y, t_fmeta *meta)
{
	meta->d->dz = meta->d->zoom;
	if (button == 5)
		meta->d->zoom++;
	if (button == 4)
		meta->d->zoom--;
	if (meta->d->zoom <= 0)
		meta->d->zoom = 1;
	meta->d->xoff -= (x / (double)WIN2X * meta->d->xr + meta->d->xo);
	meta->d->yoff -= (y / (double)WIN2Y * meta->d->yr + meta->d->yo);
	meta->d->xr = XR / meta->d->zoom * ZOOM;
	meta->d->yr = YR / meta->d->zoom * ZOOM;
	meta->d->xo = XO / meta->d->zoom * ZOOM;
	meta->d->yo = YO / meta->d->zoom * ZOOM;
	meta->d->xoff += (x / (double)WIN2X * meta->d->xr + meta->d->xo);
	meta->d->yoff += (y / (double)WIN2Y * meta->d->yr + meta->d->yo);
	// printf("dz: %f dxoff: %f dyoff: %f\n", d->dz, d->xoff, d->yoff);
}

int		ft_mdown(int button, int x, int y, t_fmeta *meta)
{
	meta->d->mbutton = button;
	meta->d->mdown = 1;
	if (button == 4 || button == 5)
	{
		ft_mzoom(button, x, y, meta);
		mlx_clear_window(meta->d->mlx, meta->d->win);
		mlxdraw(meta);
	}
	return (0);
}

// int		ft_mup(int button, int x, int y, t_mlxdata *d)
// {
// 	d->mbutton = 0;
// 	d->mdown = 0;
// 	button = x;
// 	button = y;
// 	return (0);
// }
