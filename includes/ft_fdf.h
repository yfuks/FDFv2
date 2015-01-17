/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:20:44 by yfuks             #+#    #+#             */
/*   Updated: 2015/01/17 00:39:08 by yfuks            ###   ########.fr       */
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
	int				line_size;
	int				padding;
	int				power;
	int				show;
	t_pixel			***map;
}					t_env;
int					expose_hook(t_env *e);
int					key_hook(int keycode, t_env *e);
void				map_pixels(t_env *e);
void				put_map(t_env *e);
void				map_ch(t_env *e);
void				reset_param(t_env *e);
void				ft_put_error(char *argv, char *str1);
void				map_nb_line(t_env *e);
int					size_line(t_env *e);
void				init_padding(t_env *e);
#endif
