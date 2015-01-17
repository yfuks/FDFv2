/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 20:48:23 by yfuks             #+#    #+#             */
/*   Updated: 2015/01/17 06:54:04 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	put_pixel(t_env *e, int x, int y, int coloration)
{
	int				r;
	int				g;
	int				b;

	r = (coloration & 0xFF0000) >> 16;
	g = (coloration & 0xFF00) >> 8;
	b = (coloration & 0xFF);
	if (x >= 0 && y >= 0 && x < W_HEIGTH && y <= W_WIDTH)
	{
		e->data[(y * e->sizeline) + (4 * x) + 2] = r;
		e->data[(y * e->sizeline) + (4 * x) + 1] = g;
		e->data[(y * e->sizeline) + (4 * x)] = b;
	}
}

static void	put_line(t_env *e, t_pixel *pixel1, t_pixel *pixel2)
{
	float			x[3];
	float			y[2];
	unsigned int	color;

	x[1] = pixel1->x;
	y[0] = pixel1->y;
	x[2] = pixel2->x;
	y[1] = pixel2->y;
	x[0] = x[1];
	if (pixel1->power <= -250)
		color = 0x000000;
	else if (pixel1->power < 0 || pixel2->power < 0)
		color = 0x0000FF + pixel1->power;
	else if (pixel1->power <= 50)
		color = (0xFF - pixel1->power * 3) << 8;
	else if (pixel1->power <= 120)
		color = ((0x80 - pixel1->power) << 16) + (33 << 8);
	else
		color = 0xFFFFFF;
	while (x[0] < x[2])
	{
		put_pixel(e, x[0], y[0] + (((y[1] - y[0]) *
								(x[0] - x[1])) / (x[2] - x[1])), color);
		x[0] += 0.1;
	}
}

void		put_map(t_env *e)
{
	int		x;
	int		y;

	if (!e->map)
	{
		map_nb_line(e);
		map_pixels(e);
	}
	else
		map_ch(e);
	y = 0;
	while (e->map[y])
	{
		x = 0;
		while (e->map[y][x])
		{
			if (x > 0 && e->map[y][x - 1])
				put_line(e, e->map[y][x - 1], e->map[y][x]);
			if (y > 0 && e->map[y - 1][0] && e->map[y - 1][x])
				put_line(e, e->map[y - 1][x], e->map[y][x]);
			x++;
		}
		y++;
	}
}
