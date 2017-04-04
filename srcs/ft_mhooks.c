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

int		ft_mmove(int x, int y, t_mlxdata *d)
{
	if (!(d->lock) && x >= 0 && x <= WIN2X && y >= 0 && y <= WIN2Y)
	{
		d->xm = x;
		d->ym = y;
		printf("x: %d, y: %d\n", x, y);
		if (d->type == 'j')
		{
			d->x = x / (double)WINX * d->xr + d->xo - d->xoff;
			d->y = y / (double)WINY * d->yr + d->yo + d->yoff;
			mlx_clear_window(d->mlx, d->win);
			mlxdraw(d);
		}
	}
	return (0);
}

void	ft_mzoom(int button, int x, int y, t_mlxdata *d)
{
	// double	dx;
	// double	dy;

	d->dz = d->zoom;
	if (button == 5)
		d->zoom++;
	if (button == 4)
		d->zoom--;
	if (d->zoom <= 0)
		d->zoom = 1;
	d->xoff -= (x / (double)WIN2X * d->xr + d->xo);
	d->yoff -= (y / (double)WIN2Y * d->yr + d->yo);
	d->xr = (TYPE == 'n' ? NXR : XR) / d->zoom * ZOOM;
	d->yr = (TYPE == 'n' ? NYR : YR) / d->zoom * ZOOM;
	d->xo = (TYPE == 'n' ? NXO : XO) / d->zoom * ZOOM;
	d->yo = (TYPE == 'n' ? NYO : YO) / d->zoom * ZOOM;
	d->xoff += (x / (double)WIN2X * d->xr + d->xo);
	d->yoff += (y / (double)WIN2Y * d->yr + d->yo);
	printf("dz: %f dxoff: %f dyoff: %f\n", d->dz, d->xoff, d->yoff);
}

int		ft_mdown(int button, int x, int y, t_mlxdata *d)
{
	d->mbutton = button;
	d->mdown = 1;
	// if (button == 1)
	// {
	// 	d->f->xo = round((x - d->oxmax - OFFSET));
	// 	d->f->yo = round((y - d->oymax - OFFSET));
	// }
	if (button == 4 || button == 5)
		ft_mzoom(button, x, y, d);
	// if (button == 6)
	// 	d->f->xo += 20;
	// if (button == 7)
	// 	d->f->xo -= 20;
	// if (d->type == 'j')
	// {
	// 	d->x = x / (double)WINX * d->xr + d->xo - d->xoff;
	// 	d->y = y / (double)WINY * d->yr + d->yo + d->yoff;
	// }
	if (button == 4 || button == 5)
	{
		mlx_clear_window(d->mlx, d->win);
		mlxdraw(d);
	}
	return (0);
}

int		ft_mup(int button, int x, int y, t_mlxdata *d)
{
	d->mbutton = 0;
	d->mdown = 0;
	button = x;
	button = y;
	return (0);
}
