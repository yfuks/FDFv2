/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:23:09 by yfuks             #+#    #+#             */
/*   Updated: 2015/01/17 01:17:50 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	fill_img(t_env *e)
{
	if (!(e->data = mlx_get_data_addr
		(e->img, &e->bpp, &e->sizeline, &e->endian)))
		perror(strerror(errno));
	else
		put_map(e);
}

static void	draw(t_env *e)
{
	e->img = mlx_new_image(e->mlx, W_HEIGTH, W_WIDTH);
	fill_img(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	if (e->show)
	{
		mlx_string_put(e->mlx, e->win, 20, 40, 0xFFFFFF, "MAP PATH");
		mlx_string_put(e->mlx, e->win, 65, 55, 0xFFFF00, e->argv);
		mlx_string_put(e->mlx, e->win, 20, 90, 0xFFFFFF, "CONTROLS");
		mlx_string_put(e->mlx, e->win, 65, 105, 0xFFFF00,
				"- zoom               + / -");
		mlx_string_put(e->mlx, e->win, 65, 120, 0xFFFF00,
				"- position           Arrow Keys");
		mlx_string_put(e->mlx, e->win, 65, 135, 0xFFFF00,
				"- depth              Page Up / Page Down");
		mlx_string_put(e->mlx, e->win, 65, 150, 0xFFFF00,
				"- reset              r");
		mlx_string_put(e->mlx, e->win, 65, 165, 0xFFFF00,
				"- quit               Esc");
		mlx_string_put(e->mlx, e->win, 65, 180, 0xFFFF00,
				"- show / hide infos  s");
	}
	mlx_destroy_image(e->mlx, e->img);
}

int			expose_hook(t_env *e)
{
	draw(e);
	return (0);
}

int			key_hook(int keycode, t_env *e)
{
	(keycode == 114) ? reset_param(e) : 0;
	(keycode == 65365) ? e->power++ : 0;
	if (keycode == 115)
		e->show = (e->show) ? 0 : 1;
	else if (keycode == 65366)
		e->power--;
	else if (keycode == 65451)
		e->padding += e->padding;
	else if (keycode == 65453 && e->padding > 1)
		e->padding -= e->padding / 2;
	else if (keycode == 65362)
		e->y--;
	else if (keycode == 65361)
		e->x--;
	else if (keycode == 65364)
		e->y++;
	else if (keycode == 65363)
		e->x++;
	else if (keycode == 65307)
		exit(0);
	if (keycode == 65365 || keycode == 65366 || keycode == 65451 ||
		keycode == 65453 || (keycode >= 65361 && keycode <= 65364)
		|| keycode == 114 || keycode == 115)
		draw(e);
	return (0);
}
