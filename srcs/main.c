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

/*
**	1.	findtype determines which fractal to calculate and display
**	2.	mlxsetup allocates memory for the mlx data struct and initializes
**		key values
**	3.	instructions outputs an explanation of the implemented key and mouse
**		commands to the console
*/

static void			findtype(char **av, t_fmeta *meta)
{
	int		i;

	i = -1;
	while (av[1][++i])
		av[1][i] = ft_tolower(av[1][i]);
	if (!ft_strcmp(av[1], "julia"))
	{
		meta->type = 'j';
		meta->frac = &julia;
	}
	else if (!ft_strcmp(av[1], "mandelbrot"))
	{
		meta->type = 'm';
		meta->frac = &mandelbrot;
	}
	else if (!ft_strcmp(av[1], "newton"))
	{
		meta->type = 'n';
		meta->frac = &newton;
	}
	else
	{
		ft_putendl_fd("Sorry, this fractal is not yet supported.", 2);
		exit(1);
	}
}

/*
**	Why not just assign the function pointers when I assign the types?
**	25 line limits for functions, brackets included and must take up an
**	entire line by themselves. UGH. See norme.en.pdf.
**	Types are used later to save on redrawing (since only the julia fractal
**	needs to be redrawn for mouse movement.
*/

static t_mlxdata	*mlxsetup(void)
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
	d->imgd = (unsigned int*)mlx_get_data_addr(d->img, &(d->bbp), &(d->line),
		&(d->endian));
	return (d);
}

void				instructions(void)
{
	ft_printf("INSTRUCTIONS:\n\n");
	ft_printf("SCROLL WHEEL = zoom in/out on the mouse pointer\n");
	ft_printf("UP/DOWN ARROW = zoom in/out on the mouse pointer\n");
	ft_printf("Z = reset zoom level\n");
	ft_printf("+/- = increase/decrease maximum iterations\n");
	ft_printf("TAB = show number of maximum iterations and zoom level\n");
	ft_printf("ESC = exit\n\n");
	ft_printf("Julia-specific instructions:\n\n");
	ft_printf("CLICK + DRAG = vary julia parameter\n");
	ft_printf("SHIFT = lock julia parameter\n");
}

int					main(int ac, char **av)
{
	t_fmeta		meta;

	if (ac >= 2)
	{
		meta.d = mlxsetup();
		findtype(av, &meta);
		instructions();
		mlxdraw(&meta);
	}
	else
	{
		ft_putendl_fd("Usage: ./fractol [fractal type]", 2);
		ft_putendl_fd("Fractal type: Mandelbrot, Julia, or Newton", 2);
	}
	return (0);
}
