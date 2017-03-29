/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_khooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuang <dhuang@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 19:03:51 by dhuang            #+#    #+#             */
/*   Updated: 2017/03/28 19:03:51 by dhuang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	ft_keyexit(t_mlxdata *d)
{
	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->win);
	ft_memdel((void**)&d);
	exit(1);
}

int		ft_kdown(int key, t_mlxdata *d)
{
	if (key == 53)
		ft_keyexit(d);
	return (0);
}
