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
# include <pthread.h>
# include "../libft/includes/libft.h"
# include "mlx.h"

// The only reason why the meta struct exists for multi-threading basically,
// and mainly because I wanted to simplify some of the organization.

typedef struct	s_mlxdata
{
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
	unsigned int	miter;
	// int				mdown;
	// int				mbutton;
	// int				xp;
	// int				yp;
}				t_mlxdata;

// dz is scale change, zoom change, for keeping relative position

typedef struct	s_fmeta
{
	char			type;
	t_mlxdata		*d;
	void			(*frac)(t_mlxdata*, int);
}				t_fmeta;

typedef struct	s_thread
{
	int				tid;
	t_mlxdata		*d;
	void			(*frac)(t_mlxdata*, int);
}				t_thread;

# define THREAD_COUNT 16
# define MITER 50
# define WINY 400
# define WINX 400
# define WIN2Y 800
# define WIN2X 800
# define CHUNK WIN2X * WIN2Y / THREAD_COUNT
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
# define NTOL (double)0.00000001
# define JCRE d->x
# define JCIM d->y
# define ENDIAN 0
# define BBP 32
# define LINE WIN2X * 4
# define CR 0x0000FFFF
# define CO 0x00FF0000

int			ft_kdown(int key, t_fmeta *meta);
int			ft_mmove(int x, int y, t_fmeta *meta);
int			ft_mdown(int button, int x, int y, t_fmeta *meta);
// int			ft_mup(int button, int x, int y, t_mlxdata *d);
t_mlxdata	*mlxsetup();
void		mlxdraw(t_fmeta *meta);
void		julia(t_mlxdata *d, int i);
void		newton(t_mlxdata *d, int i);
void		mandelbrot(t_mlxdata *d, int i);

#endif
