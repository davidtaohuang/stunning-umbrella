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

void	ft_keyzoom(int key, t_fmeta *meta)
{
	meta->d->dz = meta->d->zoom;
	if (key == 6)
		meta->d->zoom = ZOOM;
	if (key == 126)
		meta->d->zoom += 10;
	if (key == 125)
		meta->d->zoom -= 10;
	if (meta->d->zoom <= 0)
		meta->d->zoom = 10;
	meta->d->xoff -= (meta->d->xm / (double)WIN2X * meta->d->xr + meta->d->xo);
	meta->d->yoff -= (meta->d->ym / (double)WIN2Y * meta->d->yr + meta->d->yo);
	meta->d->xr = XR / meta->d->zoom * ZOOM;
	meta->d->yr = YR / meta->d->zoom * ZOOM;
	meta->d->xo = XO / meta->d->zoom * ZOOM;
	meta->d->yo = YO / meta->d->zoom * ZOOM;
	meta->d->xoff += (meta->d->xm / (double)WIN2X * meta->d->xr + meta->d->xo);
	meta->d->yoff += (meta->d->ym / (double)WIN2Y * meta->d->yr + meta->d->yo);
	mlx_clear_window(meta->d->mlx, meta->d->win);
	mlxdraw(meta);
}

int		ft_kdown(int key, t_fmeta *meta)
{
	ft_putnbrnl(key);
	if (key == 257)
		meta->d->lock = (!(meta->d->lock) ? 1 : 0);
	if ((key >= 125 && key <= 126) || key == 6)
		ft_keyzoom(key, meta);
	if (key == 53)
		ft_keyexit(meta->d);
	return (0);
}
