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
# include "../ft_printf/includes/ft_printf.h"
# include "mlx.h"

/*
**	t_mlxdata store most of the data needed for displaying the image using
**	the MiniLibX graphic library
**
**	1.	mlx - pointer defining a graphics instance
**	2.	win - pointer defining a window
**	3.	img - pointer defining an image
**	4.	imdg - pointer to where the pixel color data of the image is stored
**	5.	bbp - bits per pixel, needed to create imgd
**	6.	endian - endian of the machine, needed create imgd
**	7.	line - length of a row of pixels in the image in bytes, needed to
**		create imgd
**	8.	miter - current number of maximum iterations for fractal calculations
**	9.	xr - domain of the current image in the complex plane
**	10.	xo - offset added to xr to find x values in the complex plane
**	11.	yr - range of the current image in the complex plane
**	12.	yo - offset added to yr to find y values in the complex plane
**	13.	x - keeps track of the x value for varying the parameter for the
**		Julia fractal (in terms of the complex plane)
**	14. y - keeps track of the y value for varying the parameter for the
**		Julia fractal (in terms of the complex plane)
**	15.	xm - tracks mouse x pixel position for key zoom option
**	16.	ym - tracks mouse y pixel position for key zoom option
**	17.	xoff - stores x offset to allow zooming in on the mouse pointer
**	18.	yoff - stores y offset to allow zooming in on the mouse pointer
**	19.	zoom - store current zoom value
**	20. dz - store old zoom value, used for calculations allowing zooming
**		in on the mouse pointer
*/

typedef struct	s_mlxdata
{
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*imgd;
	int				bbp;
	int				endian;
	int				line;
	unsigned int	miter;
	double			xr;
	double			xo;
	double			yr;
	double			yo;
	double			x;
	double			y;
	int				xm;
	int				ym;
	double			xoff;
	double			yoff;
	int				zoom;
	double			dz;
}				t_mlxdata;

/*
**	The only reason why the meta struct exists for multi-threading
**	basically, and mainly because I wanted to simplify some of the
**	organization.
**
**	1.	type stores a character representing the fractal type
**	2.	lock is a toggle for whether the julia parameter is locked or not
**	3.	info is a toggle for whether to display the iteration and zoom
**		information in the image window
**	4.	mbutton keeps track of which mouse button is currently held down
**	5.	mdown keeps track of whether any mouse button is currently held
**		down
**	6.	d is a struct containing the rest of mlx data (see above)
**	7.	frac is a function pointer to the corresponding fractal
**		calculating function
*/

typedef struct	s_fmeta
{
	char			type;
	char			lock;
	char			info;
	int				mbutton;
	int				mdown;
	t_mlxdata		*d;
	void			(*frac)(t_mlxdata*, int);
}				t_fmeta;

/*
**	t_thread is a basic struct for multi-threading
**
**	1.	tid is the thread id
**	2.	d is the mlx data that frac needs to do calculations
**	3.	frac is the pointer to corresponding fractal calculating function
*/

typedef struct	s_thread
{
	int				tid;
	t_mlxdata		*d;
	void			(*frac)(t_mlxdata*, int);
}				t_thread;

/*
**	The following macros can be modified to change the viewing experience.
**
**	1.	THREAD_COUNT - the number of threads created for multi-threading
**	2.	CSMOOTH - toggles whether the color-smoothing option is used (can
**		be 0 or 1)
**	3.	MITER - specifies maximum iterations used in fractal calculations
**	4.	WIN2X - horizontal size of the image/window in pixels
**	5.	WIN2Y - vertical size of the image/window in pixels
**	6.	NTOL - tolerance used in the boundary condition in calculating the
**		newton fractol
**	7.	CR - color range
**	8.	CO - color offset
**	9.	XO - specifies intial value for x-range, used in conjunction with
**		XR to specify initial domain (in terms of the complex plane)
**	10.	XR - specifies initial domain in the complex plane displayed in the
**		image/window
**	11.	YO - specifies intial value for y-range, used in conjunction with
**		YR to specify initial range (in terms of the complex plane)
**	12.	YR - specifies initial range in the complex plane displayed in the
**		image/window
**	13.	ZOOM - constant for zoom calculations
**	14.	ENDIAN - hardware specific
**	15. BBP - bits per pixel (you can change this, but mlx might break)
**
**	XO, XR, YO, YR example:
**
**	XO = -2, XR = 4 for example specifies that the initial domain starts at
**	-2 and has a range of 4, meaning that the domain is (-2, -2 + 4) =
**	(-2, 2)
**
**	YO and YR function roughly the same way
*/

# define THREAD_COUNT 16
# define CSMOOTH 1
# define MITER 50
# define WIN2Y 800
# define WIN2X 800
# define NTOL (double)0.00000001
# define CR 0x0000FFFF
# define CO 0x00FF0000
# define XO (double)-2
# define XR (double)4
# define YO (double)-2
# define YR (double)4
# define ZOOM (double)100
# define ENDIAN 0
# define BBP 32

/*
**	These macros are all derived and thus really shouldn't be modified.
**
**	1.	WINX - used to simplify calculations
**	2.	WINY - used to simplify calculations
**	3.	CHUNK - specifies how many pixels are calulated and assigend by
**		each thread
**	4.	CI - simple color assignment
**	5.	CS - color smoothing calculation
**	6.	XOFFSET - used to help keep functions within line and column limits
**	7.	YOFFSET - used to help keep functions within line and column limits
**	8.	LINE - calculates width of an image in terms of bytes, used to
**		create imgd
*/

# define WINY WIN2Y / 2
# define WINX WIN2X / 2
# define CHUNK WIN2X * WIN2Y / THREAD_COUNT
# define CI	iter
# define CS (iter + 1 - (log(2) / (nx * nx + ny * ny)) / log (2))
# define XOFFSET meta->d->xoff
# define YOFFSET meta->d->yoff
# define LINE WIN2X * BBP / 8

/*
**	Hook functions
*/

int				ft_kdown(int key, t_fmeta *meta);
int				ft_mmove(int x, int y, t_fmeta *meta);
int				ft_mdown(int button, int x, int y, t_fmeta *meta);
int				ft_mup(int button, int x, int y, t_fmeta *meta);

/*
**	Drawing/MLX functions
*/

void			mlxdraw(t_fmeta *meta);

/*
**	Fractal calculator functions
*/

void			julia(t_mlxdata *d, int i);
void			newton(t_mlxdata *d, int i);
void			mandelbrot(t_mlxdata *d, int i);

#endif
