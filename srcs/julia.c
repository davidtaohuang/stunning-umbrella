/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:17:05 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/28 17:17:05 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	jescape(t_mlxdata *d, int i)
{
	double	ore;
	double	oim;
	int		iter;
	double	nre;
	double	nim;

	nre = (i % WINX) / (double)(WINX / 2 / JX) - JX;
	nim = (i / WINY) / (double)(WINY / 2 / JY) - JY;
	iter = 0;
	while (iter < MITER)
	{
		ore = nre;
		oim = nim;
		nre = ore * ore - oim * oim + JCRE;
		nim = 2 * ore * oim + JCIM;
		if (nre * nre + nim * nim > 4)
		{
			// ft_putnbr(iter);
			// ft_putstr("\n\0");
			break;
		}
		iter++;
	}
	if (iter < MITER)
		*(d->imgd + i) = mlx_get_color_value(d->mlx, (unsigned int)(CR * (CI / (double)MITER) + CO));
	else
		*(d->imgd + i) = mlx_get_color_value(d->mlx, CR + CO);
}

void	julia(void)
{
	t_mlxdata	*d;
	int			i;

	d = ft_mlxsetup();
	i = 0;
	while (i < WINX * WINY)
		jescape(d, i++);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	mlx_hook(d->win, 2, 1, ft_kdown, (void*)d);
	mlx_loop(d->mlx);
	ft_putendl("Done!");
}
