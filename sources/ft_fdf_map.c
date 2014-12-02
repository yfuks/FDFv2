/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 23:34:46 by yfuks             #+#    #+#             */
/*   Updated: 2014/12/01 19:11:06 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static t_pixel	*new_pixel(int x, int y, int power, t_env *e)
{
	t_pixel		*new;
	float		x1;
	float		y1;

	new = NULL;
	if ((new = (t_pixel *)malloc(sizeof(t_pixel))))
	{
		y += (W_WIDTH / e->padding) / 2;
		x = (x * 2);
		new->x = (x * e->padding) + (y * e->padding * 2) - 600;
		new->y = (y * e->padding) - (x * e->padding) - (power * e->power);
		new->power = power;
	}
	return (new);
}

static void		map_nb_line(t_env *e)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(e->fd, &line))
		i++;
	close(e->fd);
	e->fd = open(e->argv, S_IRWXU);
	e->nb_line = i;
}

void			map_ch(t_env *e)
{
	int		x;
	int		y;
	int		xtmp;
	int		ytmp;

	y = 0;
	while (e->map[y])
	{
		x = 0;
		while (e->map[y][x])
		{
			ytmp = y + ((W_WIDTH / e->padding) / 2);
			xtmp = (x * 2);
			e->map[y][x]->x = (xtmp * e->padding) + (ytmp * e->padding * 2)
				- 600;
			e->map[y][x]->y = (ytmp * e->padding) - (xtmp * e->padding)
				- (e->map[y][x]->power * e->power);
			x++;
		}
		y++;
	}
}

void			map_pixels(t_env *e)
{
	char	*number;
	int		x;
	int		y;
	char	*line;
	int		i;

	y = 0;
	if (!e->nb_line)
		map_nb_line(e);
	e->map = (t_pixel ***)malloc(sizeof(t_pixel **) * e->nb_line);
	while (get_next_line(e->fd, &line))
	{
		e->map[y] = (t_pixel **)malloc(sizeof(t_pixel *) * ft_strlen(line));
		x = 0;
		i = 0;
		while ((number = ft_strsplit(line, ' ')[i]))
		{
			e->map[y][x] = new_pixel(x, y, ft_atoi(number), e);
			x++;
			e->map[y][x] = NULL;
			i++;
		}
		y++;
		e->map[y] = NULL;
	}
}
