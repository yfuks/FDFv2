/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:57:00 by yfuks             #+#    #+#             */
/*   Updated: 2014/12/01 21:54:28 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static	void	init_env(t_env *e, char *argv)
{
	e->img = NULL;
	e->x = 0;
	e->y = 0;
	e->nb_line = 0;
	e->argv = ft_strdup(argv);
	e->power = 4;
	e->padding = 10;
	e->map = NULL;
}

static void		ft_put_error(char *argv, char *str1)
{
	if (argv != NULL && str1 != NULL)
	{
		ft_putstr_fd(ft_strappend(argv, ": "), 2);
		ft_putstr_fd("\x1B[31m", 2);
		ft_putendl_fd(str1, 2);
		ft_putstr_fd("\x1B[37m", 2);
		exit(0);
	}
}

int				main(int ac, char *argv[])
{
	t_env	e;

	if (ac > 1)
	{
		if ((e.fd = open(argv[1], O_RDWR)) == -1)
			ft_put_error(argv[1], strerror(errno));
	}
	else
		ft_put_error("Usage", ft_strjoin(argv[0], " file.fdf"));
	if ((e.mlx = mlx_init()) && e.fd > 0 && ac > 1)
	{
		if (!(e.win = mlx_new_window(e.mlx, W_HEIGTH, W_WIDTH, "fdf 42")))
			ft_put_error(argv[1], strerror(errno));
		else
		{
			init_env(&e, argv[1]);
			mlx_mouse_hook(e.win, mouse_hook, &e);
			mlx_key_hook(e.win, key_hook, &e);
			mlx_expose_hook(e.win, expose_hook, &e);
			mlx_loop(e.mlx);
		}
	}
	else
		ft_put_error(argv[0], "Mlx initialization failed");
	return (0);
}
