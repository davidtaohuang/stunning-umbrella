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

/*
**	1.	ft_mmove handles mousemovement; tracks x and y position for key zoom
**		options and changes julia parameter for mouse click and drag
**	2.	ft_mzoom handles zooming in and out with the scroll wheel; the extra
**		calculations guarantee zooming in on the point of the mouse
**	3.	ft_mdown tracks which mouse buttons are pressed and whether they're
**		currently held down; it initiates mouse zoom and redrawing for scroll
**		wheel actions
**	4.	ft_mup tracks when a mouse button has been released; x, y, and button
**		are superfluous but need to be used for compiler flag compatibility
**		according to our style guide. The mouse hook functions are required to
**		include button, x, and y as inputs by the MLX library.
*/

int		ft_mmove(int x, int y, t_fmeta *meta)
{
	if (x >= 0 && x <= WIN2X && y >= 0 && y <= WIN2Y)
	{
		meta->d->xm = x;
		meta->d->ym = y;
		if (meta->type == 'j' && !(meta->lock) && meta->mbutton == 1)
		{
			meta->d->x = x / (double)WIN2X * meta->d->xr + meta->d->xo -
							XOFFSET;
			meta->d->y = y / (double)WIN2Y * -meta->d->yr - meta->d->yo +
							YOFFSET;
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
	XOFFSET -= (x / (double)WIN2X * meta->d->xr + meta->d->xo);
	YOFFSET -= (y / (double)WIN2Y * meta->d->yr + meta->d->yo);
	meta->d->xr = XR / meta->d->zoom * ZOOM;
	meta->d->yr = YR / meta->d->zoom * ZOOM;
	meta->d->xo = XO / meta->d->zoom * ZOOM;
	meta->d->yo = YO / meta->d->zoom * ZOOM;
	XOFFSET += (x / (double)WIN2X * meta->d->xr + meta->d->xo);
	YOFFSET += (y / (double)WIN2Y * meta->d->yr + meta->d->yo);
}

int		ft_mdown(int button, int x, int y, t_fmeta *meta)
{
	meta->mbutton = button;
	meta->mdown = 1;
	if (button == 4 || button == 5)
	{
		ft_mzoom(button, x, y, meta);
		mlx_clear_window(meta->d->mlx, meta->d->win);
		mlxdraw(meta);
	}
	return (0);
}

int		ft_mup(int button, int x, int y, t_fmeta *meta)
{
	meta->mbutton = 0;
	meta->mdown = 0;
	x = y;
	button = y;
	return (0);
}
