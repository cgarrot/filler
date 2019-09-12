/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/07 05:21:02 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 19:46:29 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

int		size_piece_info(int fd, t_parse_info *inf)
{
	char		*line;
	t_count		count;

	count.i = 0;
	count.j = 0;
	count.upper = 0;
	
//	dprintf(fd, "---------------[%s]\n", inf->p_str);
//	dprintf(fd, "+++++++++++++++[%s]\n", inf->str);
	if (!(inf->str = (char*)malloc(sizeof(char) * (inf->piece_x + 1))))
		return (0);
	if (!(inf->p_str = (char*)malloc(sizeof(char) * ((inf->piece_y * (inf->piece_x + 1))))))
		return (0);
	inf->str = ft_memset(inf->str, '0', inf->piece_x);
	//dprintf(fd, "BUGGGGGG LINE [%s]\n", line);
	while (count.i < inf->piece_y)
	{
		get_next_line(0, &line);
		//dprintf(fd, "4 LINE LINE [%s]\n", line);
		inf->p_str = ft_strcat(inf->p_str, line);
		if ((inf->piece_y - 1) != count.i)
			inf->p_str = ft_strcat(inf->p_str, "R");
		if (ft_strchr(line, '*'))
		{
			count.k = 0;
			while (line[count.k])
			{
				if (line[count.k] == '*')
					inf->str[count.k] = '1';
				count.k++;
			}
			if (count.j == 0)
			{
				count.lower = count.i;
				count.j++;
			}
			if (count.i > count.upper)
				count.upper = count.i;
		}
		inf->piece_verti = count.upper - count.lower + 1;
		ft_strdel(&line);
		count.i++;
	}
	//inf->p_str = ft_strcat(inf->p_str, "\0");
	inf->p_str[inf->piece_y * (inf->piece_x + 1) - 1] = '\0';
	inf->str[inf->piece_x] = '\0';
	inf->piece_hori = count_caract(fd, inf->str, '1');
	return (1);
}

void	parse(int fd, t_parse_info *inf)
{
	char	**split;
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	init(inf);
	get_next_line(0, &line);
	//dprintf(fd, "1 LINE LINE [%s]\n", line);
	if (line[10] == '1')
	{
		inf->caract = 'O';
		inf->enemy = 'X';
	}
	else
	{
		inf->caract = 'X';
		inf->enemy = 'O';
	}
	ft_strdel(&line);
	get_next_line(0, &line);
	//dprintf(fd, "2 LINE LINE [%s]\n", line);
	inf->size_y = ft_atoi_2(line, inf);
	inf->size_x = ft_atoi_2(line, inf);
	while (i < inf->size_y + 2)
	{
		ft_strdel(&line);
		get_next_line(0, &line);
		//dprintf(fd, "3 LINE LINE [%s]\n", line);
		if ((tmp = ft_strchr(line, inf->caract)) && inf->first == 0)
		{
			inf->start_x = ft_strlen(line) - ft_strlen(tmp) - 4;
			inf->tmp = 0;
			inf->start_y = ft_atoi_2(line, inf);
		}
		if ((tmp = ft_strchr(line, inf->enemy)) && inf->first == 0)
		{
			inf->enemy_x = ft_strlen(line) - ft_strlen(tmp) - 4;
			inf->tmp = 0;
			inf->enemy_y = ft_atoi_2(line, inf);
		}
		if ((tmp = ft_strchr(line, inf->enemy)) && inf->first == 1)
		{
			inf->tmp_x = ft_strlen(line) - ft_strlen(tmp) - 4;
			inf->tmp = 0;
			inf->tmp_y = ft_atoi_2(line, inf);
			inf->map[inf->tmp_y][inf->tmp_x] = -1;
			inf->tab[inf->tmp_y][inf->tmp_x] = 2;
		}
		i++;
	}
	split = ft_strsplit(line, ' ');
	inf->piece_y = atoi(split[1]);
	inf->piece_x = atoi(split[2]);
	ft_strdel(&line);
	size_piece_info(fd, inf);
}
