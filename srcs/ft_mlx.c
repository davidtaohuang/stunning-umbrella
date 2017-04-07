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

/*
**	1.	fractalcalc is initiated by the newly the created thread and loads
**		the image data address with color values based on the number of
**		iterations required to satisfy the boundary condition at that pixel
**	2.	mlxputinfo displays the maximum iteration and zoom info in the image
**		window
**	3.	mlxdraw creates an array of threads to handle all of the fractal
**		calculations to assign color values to each pixel in the image and
**		starts the functions to detect event hooks
*/

static void	*fractalcalc(void *arg)
{
	t_thread	*data;
	int			i;
	int			end;

	data = (t_thread*)arg;
	i = data->tid * CHUNK;
	end = i + CHUNK;
	while (i < end)
		data->frac(data->d, i++);
	pthread_exit(NULL);
}

static void	mlxputinfo(t_fmeta *meta)
{
	char		*str;

	ft_asprintf(&str, "Maximum iterations = %d Zoom = %.2f", meta->d->miter,
		meta->d->zoom / ZOOM);
	mlx_string_put(meta->d->mlx, meta->d->win, 0, 0, 0, str);
	free(str);
}

void		mlxdraw(t_fmeta *meta)
{
	pthread_t	thr[THREAD_COUNT];
	t_thread	tdata[THREAD_COUNT];
	int			i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		tdata[i].tid = i;
		tdata[i].d = meta->d;
		tdata[i].frac = meta->frac;
		pthread_create(&thr[i], NULL, fractalcalc, &tdata[i]);
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
		pthread_join(thr[i++], NULL);
	mlx_put_image_to_window(meta->d->mlx, meta->d->win, meta->d->img, 0, 0);
	if (meta->info)
		mlxputinfo(meta);
	mlx_hook(meta->d->win, 2, 1, ft_kdown, (void*)meta);
	mlx_hook(meta->d->win, 6, 1, ft_mmove, (void*)meta);
	mlx_hook(meta->d->win, 5, 1, ft_mup, (void*)meta);
	mlx_hook(meta->d->win, 4, 1, ft_mdown, (void*)meta);
	mlx_loop(meta->d->mlx);
}
