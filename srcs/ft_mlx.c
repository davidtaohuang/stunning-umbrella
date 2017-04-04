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
	// d->xoff = -(double)WINX;
	// d->yoff = -(double)WINY;
	d->xo = (TYPE == 'n' ? NXO : XO);
	d->xr = (TYPE == 'n' ? NXR : XR);
	d->yo = (TYPE == 'n' ? NYO : YO);
	d->yr = (TYPE == 'n' ? NYR : YR);
	d->zoom = ZOOM;
	// d.mdown = 0;
	// d.mbutton = 0;
	// d.xp = 0;
	// d.yp = 0;
	d->imgd = (unsigned int*)mlx_get_data_addr(d->img, &(d->bbp), &(d->line), &(d->endian));
	// ft_mlxprint(d);
	// mlx_hook(d.win, 2, 1, ft_kdown, (void*)&d);
	// mlx_hook(d.win, 6, 1, ft_drag, (void*)&d);
	// mlx_hook(d.win, 5, 1, ft_mouseup, (void*)&d);
	// mlx_hook(d.win, 4, 1, ft_mousedown, (void*)&d);
	// mlx_loop(d.mlx);
	return (d);
}
