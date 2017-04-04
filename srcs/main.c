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

static void	findtype(int ac, char **av, t_mlxdata *d)
{
	int		i;

	if (ac >= 2)
	{
		i = 0;
		while (av[1][i])
			ft_tolower(av[1][i++]);
		if (!ft_strcmp(av[1], "julia"))
			d->type = 'j';
		else if (!ft_strcmp(av[1], "mandelbrot"))
			d->type = 'm';
		else if (!ft_strcmp(av[1], "newton"))
			d->type = 'n';
		else if (!ft_strcmp(av[1], "z"))
			d->type = 'z';
		else
		{
			ft_putendl_fd("Sorry, this fractal is not yet supported.", 2);
			exit(1);
		}
	}
}

void		mlxdraw(t_mlxdata *d)
{
	if (d->type == 'j')
		julia(d);
	else if (d->type == 'm')
		mandelbrot(d);
	else if (d->type == 'n')
		newton(d);
	else if (d->type == 'z')
		ztest(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	mlx_hook(d->win, 2, 1, ft_kdown, (void*)d);
	mlx_hook(d->win, 6, 1, ft_mmove, (void*)d);
	mlx_hook(d->win, 5, 1, ft_mup, (void*)d);
	mlx_hook(d->win, 4, 1, ft_mdown, (void*)d);
	mlx_loop(d->mlx);
}

int			main(int ac, char **av)
{
	t_mlxdata	*d;

	if (ac >= 2)
	{
		d = mlxsetup();
		findtype(ac, av, d);
		mlxdraw(d);
	}
	else
		putusage();
	return (0);
}
