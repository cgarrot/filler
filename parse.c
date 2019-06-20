/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 21:15:59 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/20 13:45:12 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

void	size_piece_info(int fd, t_parse_info *inf)
{
	char		*line;
	t_count		count;

	count.i = 0;
	count.j = 0;
	count.upper = 0;
	//inf->piece_str = (char*)malloc(sizeof(char) * (inf->piece_y * inf->piece_x + 1));
	inf->str = (char*)malloc(sizeof(char) * (inf->piece_x + 1));
	inf->str = ft_memset(inf->str, '0', inf->piece_x + 1);
	while (count.i < inf->piece_y)
	{
		get_next_line(0, &line);
		//inf->piece_str = ft_strcat(inf->piece_str, line);
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
	inf->str[inf->piece_x] = '\0';
	dprintf(fd,"Horizontal str : [%s]\n", inf->str);
	inf->piece_hori = count_caract(fd, inf->str, '1');
	//ft_strdel(&inf->str);
}

void	parse(int fd, t_parse_info *inf)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	init(inf);
	get_next_line(0, &line);
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
	inf->size_y = ft_atoi_2(line, inf);
	inf->size_x = ft_atoi_2(line, inf);
	while (i != inf->size_y + 2)
	{
		ft_strdel(&line);
		get_next_line(0, &line);
		if ((tmp = ft_strchr(line, inf->caract)))
		{
			inf->start_x = ft_strlen(line) - ft_strlen(tmp) - 4;
			inf->tmp = 0;
			inf->start_y = ft_atoi_2(line, inf);
		}
		if ((tmp = ft_strchr(line, inf->enemy)))
		{
			inf->enemy_x = ft_strlen(line) - ft_strlen(tmp) - 4;
			inf->tmp = 0;
			inf->enemy_y = ft_atoi_2(line, inf);
		}
		i++;
	}
	inf->piece_y = ft_atoi_2(line, inf);
	inf->piece_x = ft_atoi_2(line, inf);
	size_piece_info(fd, inf);
	//hori_or_verti(fd, inf);
}

/*void	hori_or_verti(int fd, t_parse_info *inf)
{
	int		x;
	int		y;
	int		k;
	int		i;
	int		tmp;

	k = 0;
	i = 0;
	while (i < inf->piece_y)
	{
		x = 0;
		while (k < inf->piece_x * (i + 1))
		{
			if (inf->piece_str[k] == '*')
				x++;
			k++;
		}
		if (x > inf->piece_hori)
			inf->piece_hori = x;
		//dprintf(fd,"x : [%d]\n", x);
		//dprintf(fd,"k : [%d]\n", k);
		i++;
	}
	k = 0;
	i = 0;
	tmp = -(inf->piece_x);
	while (i < inf->piece_x)
	{
		y = 0;
		k = inf->piece_x + tmp;
		while (k < inf->piece_y * inf->piece_x + tmp)
		{
			if (inf->piece_str[k] == '*')
				y++;
			k += inf->piece_x;
		}
		if (y > inf->piece_verti)
			inf->piece_verti = y;
		//dprintf(fd,"x : [%d]\n", x);
		//dprintf(fd,"k : [%d]\n", k);
		i++;
		tmp++;
	}
}*/
