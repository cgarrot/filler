/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/07 05:21:02 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 16:45:47 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/filler.h"
#include <string.h>

int		hori_or_verti(t_parse_info *inf, t_count *count, char *line)
{
	if (inf->loop == 0)
		inf->p_str = ft_strcpy(inf->p_str, line);
	if (inf->loop == 1)
		if (!(inf->p_str = ft_strjoinfree(inf->p_str, line, 1)))
			return (0);
	inf->loop = 1;
	if ((inf->piece_y - 1) != count->i)
		if (!(inf->p_str = ft_strjoinfree(inf->p_str, "R", 1)))
			return (0);
	if (ft_strchr(line, '*'))
	{
		count->k = -1;
		while (line[++count->k])
			if (line[count->k] == '*')
				inf->str[count->k] = '1';
		if (count->j == 0)
			count->lower = count->i;
		if (count->j == 0)
			count->j++;
		if (count->i > count->upper)
			count->upper = count->i;
	}
	inf->piece_verti = count->upper - count->lower + 1;
	return (1);
}

int		size_piece_info(t_parse_info *inf)
{
	char		*line;
	t_count		count;

	count.i = 0;
	count.j = 0;
	count.upper = 0;
	inf->loop = 0;
	if (!(inf->str = (char*)malloc(sizeof(char) * (inf->piece_x + 1))))
		return (0);
	if (!(inf->p_str = (char*)malloc(sizeof(char) * ((inf->piece_x + 1)))))
		return (0);
	inf->str = ft_memset(inf->str, '0', inf->piece_x);
	while (count.i < inf->piece_y)
	{
		if ((get_next_line(0, &line) <= 0))
			return (0);
		if (hori_or_verti(inf, &count, line) == 0)
			return (0);
		ft_strdel(&line);
		count.i++;
	}
	inf->p_str[inf->piece_y * (inf->piece_x + 1) - 1] = '\0';
	inf->str[inf->piece_x] = '\0';
	inf->piece_hori = count_caract(inf->str, '1');
	return (1);
}

int		parse(t_parse_info *inf)
{
	char	*line;

	init(inf);
	line = NULL;
	if ((get_next_line(0, &line) <= 0))
		return (0);
	player_one_or_two(inf, line);
	ft_strdel(&line);
	if ((get_next_line(0, &line) <= 0))
		return (0);
	inf->size_y = ft_atoi_2(line, inf);
	inf->size_x = ft_atoi_2(line, inf);
	while (inf->i < inf->size_y + 2)
	{
		ft_strdel(&line);
		if ((get_next_line(0, &line) <= 0))
			return (0);
		info_start_co(inf, line);
		inf->i++;
	}
	free_split(inf, line);
	ft_strdel(&line);
	size_piece_info(inf);
	return (1);
}

int		get_co_enemy(t_parse_info *inf)
{
	ft_strdel(&inf->line);
	if ((get_next_line(0, &inf->line) <= 0))
		return (0);
	inf->j = 0;
	while (inf->j < inf->size_x + 4)
	{
		if (inf->line[inf->j] == inf->enemy)
		{
			inf->tmp_x = inf->j - 4;
			inf->tmp_y = inf->i;
			if ((inf->tmp_y < inf->size_y) && (inf->tmp_x < inf->size_x))
				inf->tab[inf->tmp_y][inf->tmp_x] = 2;
			if ((inf->tmp_y < inf->size_y) && (inf->tmp_x < inf->size_x))
				inf->map[inf->tmp_y][inf->tmp_x] = -1;
		}
		inf->j++;
	}
	return (1);
}

int		parse_piece(t_parse_info *inf)
{
	inf->i = 0;
	inf->line = NULL;
	ft_strdel(&inf->line);
	if ((get_next_line(0, &inf->line) <= 0))
		return (0);
	ft_strdel(&inf->line);
	if ((get_next_line(0, &inf->line) <= 0))
		return (0);
	while (inf->i < inf->size_y)
	{
		if (get_co_enemy(inf) == 0)
			return (0);
		inf->i++;
	}
	ft_strdel(&inf->line);
	if ((get_next_line(0, &inf->line) <= 0))
		return (0);
	free_split(inf, inf->line);
	ft_strdel(&inf->line);
	size_piece_info(inf);
	return (1);
}
