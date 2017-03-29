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

static void	switchboard(int ac, char **av)
{
	int		i;

	if (ac >= 2)
	{
		i = 0;
		while (av[1][i])
			ft_tolower(av[1][i++]);
		if (!ft_strcmp(av[1], "julia"))
		{
			ft_putendl("Calculating julia fractal...");
			julia();
		}
		else if (!ft_strcmp(av[1], "mandelbrot"))
		{
			ft_putendl("Calculating mandelbrot fractal...");
			mandelbrot();
		}
		else
		{
			ft_putendl_fd("Sorry, this fractal is not yet supported.", 2);
			exit(1);
		}
	}
}

int			main(int ac, char **av)
{
	if (ac >= 2)
	{
		switchboard(ac, av);
	}
	else
		putusage();
	return (0);
}
