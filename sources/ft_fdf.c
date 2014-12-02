/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:23:09 by yfuks             #+#    #+#             */
/*   Updated: 2014/12/02 16:32:21 by yfuks            ###   ########.fr       */
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
	mlx_clear_window(e->mlx, e->win);
	mlx_put_image_to_window(e->mlx, e->win, e->img, e->x * 50, e->y * 50);
	mlx_string_put(e->mlx, e->win, 20, 40, 0xFFFFFF, "MAP PATH");
	mlx_string_put(e->mlx, e->win, 65, 55, 0xFFFF00, e->argv);
	mlx_string_put(e->mlx, e->win, 20, 90, 0xFFFFFF, "CONTROLS");
	mlx_string_put(e->mlx, e->win, 65, 105, 0xFFFF00, "- zoom       + / -");
	mlx_string_put(e->mlx, e->win, 65, 120, 0xFFFF00,
				"- position   Arrow Keys");
	mlx_string_put(e->mlx, e->win, 65, 135, 0xFFFF00,
				"- depth      Page Up / Page Down");
	mlx_string_put(e->mlx, e->win, 65, 150, 0xFFFF00, "- quit       Esc");
	mlx_destroy_image(e->mlx, e->img);
}

int			expose_hook(t_env *e)
{
	draw(e);
	return (0);
}

int			key_hook(int keycode, t_env *e)
{
	if (keycode == 65365 || keycode == 61)
		e->power++;
	else if (keycode == 65366 || keycode == 45)
		e->power--;
	else if (keycode == 65451)
		e->padding++;
	else if (keycode == 65453 && e->padding > 1)
		e->padding--;
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
		keycode == 65453 || (keycode >= 65361 && keycode <= 65364))
		draw(e);
	return (0);
}

int			mouse_hook(int button, int x, int y, void *param)
{
	(void)button;
	(void)x;
	(void)y;
	(void)param;
	return (0);
}
