/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 18:24:58 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/28 18:24:58 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_mlxdata	*mlxsetup()
{
	t_mlxdata	*d;

	d = (t_mlxdata*)ft_memalloc(sizeof(t_mlxdata));
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, WIN2X, WIN2Y, "fractol");
	d->img = mlx_new_image(d->mlx, WIN2X, WIN2Y);
	d->bbp = BBP;
	d->line = LINE;
	d->endian = ENDIAN;
	d->xo = XO;
	d->xr = XR;
	d->yo = YO;
	d->yr = YR;
	d->zoom = ZOOM;
	d->miter = MITER;
	// d.mdown = 0;
	// d.mbutton = 0;
	// d.xp = 0;
	// d.yp = 0;
	d->imgd = (unsigned int*)mlx_get_data_addr(d->img, &(d->bbp), &(d->line),
		&(d->endian));
	return (d);
}
