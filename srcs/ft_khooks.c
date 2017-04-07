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

/*
**	Key 257 = shift, locks point for julia
**	Key 53 	= escape, exits program
**	Key 125	= down arrow, zooms out
**	Key 126	= up arrow, zooms in
**	Key 6	= z, zoom reset
**	Key 78	= - from numpad, decreases maximum iterations for escape calcs
**	Key 69	= + from numpad, increases maximum iterations for escape calcs
**	Key 27	= alphanumeric -, decreases maximum iterations for escape calcs
**	Key 24	= alphanumeric +, increases maximum iterations for escape calcs
**
**	1.	ft_keyexit is called when escape is pressed; it frees memory and then
**		exits the program
**	2.	ft_keyzoom is called when either are of the arrow keys are pressed and
**		updates the zoom value, calculates offset to enable zooming on the
**		mouse pointer, and redrawing the image
**	3.	ft_changeiter updates the maximum iterations value when the + or -
**		keys are pressed and redraws the image
**	4.	ft_kdown detects all of the key presses and calls the functions
**		associated with them. It also toggles display of the iteration and
**		zoom on the image and the julia paramter lock
*/

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
	XOFFSET -= (meta->d->xm / (double)WIN2X * meta->d->xr + meta->d->xo);
	YOFFSET -= (meta->d->ym / (double)WIN2Y * meta->d->yr + meta->d->yo);
	meta->d->xr = XR / meta->d->zoom * ZOOM;
	meta->d->yr = YR / meta->d->zoom * ZOOM;
	meta->d->xo = XO / meta->d->zoom * ZOOM;
	meta->d->yo = YO / meta->d->zoom * ZOOM;
	XOFFSET += (meta->d->xm / (double)WIN2X * meta->d->xr + meta->d->xo);
	YOFFSET += (meta->d->ym / (double)WIN2Y * meta->d->yr + meta->d->yo);
	mlx_clear_window(meta->d->mlx, meta->d->win);
	mlxdraw(meta);
}

void	ft_changeiter(int key, t_fmeta *meta)
{
	if ((key == 78 || key == 27) && meta->d->miter)
		meta->d->miter--;
	if (key == 69 || key == 24)
		meta->d->miter++;
	mlx_clear_window(meta->d->mlx, meta->d->win);
	mlxdraw(meta);
}

int		ft_kdown(int key, t_fmeta *meta)
{
	if (key == 257)
		meta->lock = (!(meta->lock) ? 1 : 0);
	if (key == 48)
	{
		meta->info = (!(meta->info) ? 1 : 0);
		mlx_clear_window(meta->d->mlx, meta->d->win);
		mlxdraw(meta);
	}
	if ((key >= 125 && key <= 126) || key == 6)
		ft_keyzoom(key, meta);
	if (key == 78 || key == 69 || key == 27 || key == 24)
		ft_changeiter(key, meta);
	if (key == 53)
		ft_keyexit(meta->d);
	return (0);
}
