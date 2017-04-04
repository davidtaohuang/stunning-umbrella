/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_khooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 19:03:51 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/28 19:03:51 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_keyexit(t_mlxdata *d)
{
	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->win);
	ft_memdel((void**)&d);
	exit(1);
}

void	ft_keyzoom(int key, t_mlxdata *d)
{
	d->dz = d->zoom;
	if (key == 6)
		d->zoom = ZOOM;
	if (key == 126)
		d->zoom += 100;
	if (key == 125)
		d->zoom -= 50;
	if (d->zoom <= 0)
		d->zoom = 10;
	d->xoff -= (d->xm / (double)WIN2X * d->xr + d->xo);
	d->yoff -= (d->ym / (double)WIN2Y * d->yr + d->yo);
	d->xr = (TYPE == 'n' ? NXR : XR) / d->zoom * ZOOM;
	d->yr = (TYPE == 'n' ? NYR : YR) / d->zoom * ZOOM;
	d->xo = (TYPE == 'n' ? NXO : XO) / d->zoom * ZOOM;
	d->yo = (TYPE == 'n' ? NYO : YO) / d->zoom * ZOOM;
	d->xoff += (d->xm / (double)WIN2X * d->xr + d->xo);
	d->yoff += (d->ym / (double)WIN2Y * d->yr + d->yo);
	if (d->type == 'j' || d->type == 'z')
	{
		// d->x = d->xoff / (double)WINX * d->xr + d->xo;
		// d->y = d->yoff / (double)WINY * d->yr + d->yo;
		mlx_clear_window(d->mlx, d->win);
		mlxdraw(d);
	}
}

int		ft_kdown(int key, t_mlxdata *d)
{
	ft_putnbrnl(key);
	if (key == 257)
		d->lock = (!(d->lock) ? 1 : 0);
	if (key == 12)
		d->zoom = ZOOM;
	if ((key >= 125 && key <= 126) || key == 6)
		ft_keyzoom(key, d);
	if (key == 53)
		ft_keyexit(d);
	return (0);
}
