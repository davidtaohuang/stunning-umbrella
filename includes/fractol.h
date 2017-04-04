/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:34:51 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/28 16:34:51 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdlib.h>
# include "../libft/includes/libft.h"
# include "mlx.h"

typedef struct	s_mlxdata
{
	char			type;
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*imgd;
	int				bbp;
	int				endian;
	double			x;
	double			y;
	int				line;
	double			xr;
	double			xo;
	double			yr;
	double			yo;
	int				xm;
	int				ym;
	double			xoff;
	double			yoff;
	int				mbutton;
	int				mdown;
	int				zoom;
	double			dz;
	char			lock;
	// int				mdown;
	// int				mbutton;
	// int				xp;
	// int				yp;
}				t_mlxdata;

// dz is scale change, zoom change, for keeping relative position

# define MITER 50
# define WINY 400
# define WINX 400
# define WIN2Y 800
# define WIN2X 800
// # define JCI (iter + 1 - (log(2) / cabs(nz)) / log (2))
# define CI (iter + 1 - (log(2) / (nx * nx + ny * ny)) / log (2))
# define TYPE d->type
# define XO (double)-2
# define XR (double)4
# define YO (double)-2
# define YR (double)4
# define NXO (double) -4
# define NXR (double) 8
# define NYO (double) -4
# define NYR (double) 8
# define ZOOM (double)100
// # define JCRE (double)-0.7
// # define JCIM (double)0.27015
# define NTOL (double)0.00000001
# define JCRE d->x
# define JCIM d->y
# define MCRE (i % WINX) / (double)(WINX / 2 / MX) - MX
# define MCIM (i / WINY) / (double)(WINY / 2 / MY) - MY
# define ENDIAN 0
# define BBP 32
# define LINE WIN2X * 4
# define CR 0x0000FFFF
# define CO 0x00FF0000

int			ft_kdown(int key, t_mlxdata *d);
int			ft_mmove(int x, int y, t_mlxdata *d);
int			ft_mdown(int button, int x, int y, t_mlxdata *d);
int			ft_mup(int button, int x, int y, t_mlxdata *d);
t_mlxdata	*mlxsetup();
void		mlxdraw(t_mlxdata *d);
void		julia(t_mlxdata *d);
void		newton(t_mlxdata *d);

void		ztest(t_mlxdata *d);
void		mandelbrot(t_mlxdata *d);

#endif
