/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 20:48:23 by yfuks             #+#    #+#             */
/*   Updated: 2014/12/02 16:35:05 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	put_pixel(t_env *e, int x, int y, int coloration)
{
	int				r;
	int				g;
	int				b;

	b = 0xFF - (coloration % 255);
	coloration /= 255;
	g = 0xFF - (coloration % 255);
	coloration /= 255;
	r = 0xFF - (coloration % 255);
	if (x >= 0 && y >= 0 && x <= W_HEIGTH * 2 && y <= W_WIDTH)
	{
		ft_memcpy(&e->data[(y * e->sizeline) + (4 * x) - 2], &r, 1);
		ft_memcpy(&e->data[(y * e->sizeline) + (4 * x)], &b, 1);
		ft_memcpy(&e->data[(y * e->sizeline) + (4 * x) - 3], &g, 1);
	}
}

static void	put_hori_line(t_env *e, t_pixel *pixel1, t_pixel *pixel2)
{
	float			x[3];
	float			y1;
	float			y2;
	unsigned int	color;

	x[1] = pixel1->x;
	y1 = pixel1->y;
	x[2] = pixel2->x;
	y2 = pixel2->y;
	x[0] = x[1];
	color = 0xFFFFFF;
	while (x[0] < x[2])
	{
		if (pixel1->power == pixel2->power)
			color = 0xFFFFFF - (pixel1->power * 0xFFFF);
		put_pixel(e, x[0], y1 + (((y2 - y1) * (x[0] - x[1])) / (x[2] - x[1]))
				, color);
		if (color > 0 && pixel1->power > pixel2->power)
			color -= 0xFFFF;
		else if (color >= 0xFFFFFF)
			color += 0xFFFF;
		x[0] += 0.1;
	}
}

static void	put_verti_line(t_env *e, t_pixel *pixel1, t_pixel *pixel2)
{
	put_hori_line(e, pixel1, pixel2);
}

void		put_map(t_env *e)
{
	int		x;
	int		y;

	if (!e->map)
		map_pixels(e);
	else
		map_ch(e);
	y = 0;
	while (e->map[y])
	{
		x = 0;
		while (e->map[y][x])
		{
			if (x > 0)
				put_hori_line(e, e->map[y][x - 1], e->map[y][x]);
			if (y > 0)
				put_verti_line(e, e->map[y - 1][x], e->map[y][x]);
			x++;
		}
		y++;
	}
}
