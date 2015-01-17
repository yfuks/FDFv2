/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfuks <yfuks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 23:34:46 by yfuks             #+#    #+#             */
/*   Updated: 2015/01/17 06:55:19 by yfuks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static t_pixel	*new_pixel(int x, int y, int power, t_env *e)
{
	t_pixel		*new;

	new = NULL;
	if ((new = (t_pixel *)malloc(sizeof(t_pixel))))
	{
		y += (W_WIDTH / e->padding) / 2;
		x = (x * 2);
		new->x = (x * e->padding) + (y * e->padding * 2)
			- e->line_size * e->padding * 2;
		new->y = (y * e->padding) - (x * e->padding / 2)
			- power * e->power * e->padding / 5;
		new->power = power;
	}
	return (new);
}

void			map_nb_line(t_env *e)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(e->fd, &line))
		i++;
	e->fd = open(e->argv, O_RDWR);
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
				- e->line_size * 2 * e->padding + (e->x * 30);
			e->map[y][x]->y = (ytmp * e->padding) - (xtmp * e->padding / 2)
				- (e->map[y][x]->power * e->power * e->padding / 5) + (e->y * 30);
			x++;
		}
		y++;
	}
}

void			map_pixels(t_env *e)
{
	char	*number;
	int		x[3];
	char	*line;
	char	**split;

	x[1] = 0;
	(e->nb_line == 0) ? ft_put_error(e->argv, "empty map") : 0;
	e->map = (t_pixel ***)malloc(sizeof(t_pixel **) * e->nb_line);
	while (get_next_line(e->fd, &line))
	{
		e->map[x[1]] = (t_pixel **)malloc(sizeof(t_pixel *) * ft_strlen(line));
		x[0] = 0;
		x[2] = 0;
		split = ft_strsplit(line, ' ');
		while ((number = split[x[2]]))
		{
			e->map[x[1]][x[0]] = new_pixel(x[0], x[1], ft_atoi(number), e);
			x[0]++;
			x[2]++;
		}
		e->map[x[1]][x[0]] = NULL;
		free(*split);
		x[1]++;
		e->map[x[1]] = NULL;
	}
}

int				size_line(t_env *e)
{
	char	*line;
	int		i;
	char	**split;

	if (!get_next_line(e->fd, &line))
		return (0);
	i = 0;
	split = ft_strsplit(line, ' ');
	while (split[i])
		i++;
	free(*split);
	e->fd = open(e->argv, O_RDWR);
	e->line_size = i;
	return (i);
}
