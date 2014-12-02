/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:20:44 by yfuks             #+#    #+#             */
/*   Updated: 2014/11/29 02:37:29 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H
# include <mlx.h>
# include <errno.h>
# include <stdio.h>
# include "get_next_line.h"
# include <math.h>
# define W_WIDTH 1330
# define W_HEIGTH 2560

typedef struct		s_pixel
{
	float			x;
	float			y;
	int				power;
}					t_pixel;
typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				fd;
	char			*argv;
	int				nb_line;
	int				bpp;
	int				sizeline;
	int				endian;
	float			x;
	float			y;
	int				padding;
	int				power;
	t_pixel			***map;
}					t_env;
int					expose_hook(t_env *e);
int					key_hook(int keycode, t_env *e);
int					mouse_hook(int button, int x, int y, void *param);
void				map_pixels(t_env *e);
void				put_map(t_env *e);
#endif
