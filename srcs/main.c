/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:38:52 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/28 16:38:52 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	putusage(void)
{
	ft_putendl_fd("Usage: ./fractol [fractal type]", 2);
	ft_putendl_fd("Fractal type: Mandelbrot, Julia, or ???", 2);
}

static void	findtype(int ac, char **av, t_fmeta *meta)
{
	int		i;

	if (ac >= 2)
	{
		i = 0;
		while (av[1][i])
			ft_tolower(av[1][i++]);
		if (!ft_strcmp(av[1], "julia"))
			meta->type = 'j';
		else if (!ft_strcmp(av[1], "mandelbrot"))
			meta->type = 'm';
		else if (!ft_strcmp(av[1], "newton"))
			meta->type = 'n';
		else
		{
			ft_putendl_fd("Sorry, this fractal is not yet supported.", 2);
			exit(1);
		}
	}
}

// WHy not just assign the function pointers when I assigned the types?
// 25 line limits for functions, brackets included and must take up an entire line by themselves. UGH.
// Types are used later to save on redrawing.

void		*fractalcalc(void *arg)
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
	{
		pthread_join(thr[i], NULL);
		i++;
	}
	mlx_put_image_to_window(meta->d->mlx, meta->d->win, meta->d->img, 0, 0);
	mlx_hook(meta->d->win, 2, 1, ft_kdown, (void*)meta);
	mlx_hook(meta->d->win, 6, 1, ft_mmove, (void*)meta);
	// mlx_hook(meta->d->win, 5, 1, ft_mup, (void*)meta);
	mlx_hook(meta->d->win, 4, 1, ft_mdown, (void*)meta);
	mlx_loop(meta->d->mlx);
}

int			main(int ac, char **av)
{
	t_fmeta		meta;

	if (ac >= 2)
	{
		meta.d = mlxsetup();
		findtype(ac, av, &meta);
		if (meta.type == 'j')
			meta.frac = &julia;
		else if (meta.type == 'm')
			meta.frac = &mandelbrot;
		else if (meta.type == 'n')
			meta.frac = &newton;
		mlxdraw(&meta);
	}
	else
		putusage();
	return (0);
}
