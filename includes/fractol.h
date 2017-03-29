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
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*imgd;
	int				bbp;
	int				endian;
	int				xmax;
	int				ymax;
	int				line;
	// int				mdown;
	// int				mbutton;
	// int				xp;
	// int				yp;
}				t_mlxdata;

# define MITER 400
# define WINY 800
# define WINX 800
# define CI (iter + 1 - (log(2) / (nre * nre + nim * nim)) / log (2))
# define JX 2
# define JY -2
# define JCRE (double)-0.7
# define JCIM (double)0.27015
# define MX 2
# define MY -2
# define MCRE (i % WINX) / (double)(WINX / 2 / MX) - MX
# define MCIM (i / WINY) / (double)(WINY / 2 / MY) - MY
# define ENDIAN 0
# define BBP 32
# define LINE WINX * 4
# define CR 0x0000FFFF
# define CO 0x00FF0000

int			ft_kdown(int key, t_mlxdata *d);
t_mlxdata	*ft_mlxsetup();
void		julia(void);
void		mandelbrot(void);

#endif
