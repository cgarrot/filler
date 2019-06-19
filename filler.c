/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 14:00:11 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/19 16:39:40 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"
#include "libft/includes/ft_printf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int		ft_atoi_2(char *str, t_parse_info *inf)
{
	int		nbr;

	nbr = 0;
	while (str[inf->tmp] != '9' && str[inf->tmp] != '1' && str[inf->tmp] != '2'
			&& str[inf->tmp] != '3' && str[inf->tmp] != '4' && str[inf->tmp] != '5'
			&& str[inf->tmp] != '6' && str[inf->tmp] != '7' && str[inf->tmp] != '8')
		inf->tmp++;
	while (str[inf->tmp] >= '0' && str[inf->tmp] <= '9')
		nbr = nbr * 10 + str[inf->tmp++] - '0';
	return (nbr);
}

void	printf_info(int fd, t_parse_info inf)
{
	dprintf(fd, "Caract : [%c]\n", inf.caract);
	dprintf(fd, "Size y : [%u]\n", inf.size_y);
	dprintf(fd, "Size x : [%u]\n", inf.size_x);
	dprintf(fd, "Start y : [%u]\n", inf.start_y);
	dprintf(fd, "Start x : [%u]\n", inf.start_x);
	dprintf(fd, "Enemy y : [%u]\n", inf.enemy_y);
	dprintf(fd, "Enemy x : [%u]\n", inf.enemy_x);
	dprintf(fd, "Piece y : [%u]\n", inf.piece_y);
	dprintf(fd, "Piece x : [%u]\n", inf.piece_x);
	//dprintf(fd, "[%d]---[%d]\n |     | ", inf.c1, inf.c2);
	//dprintf(fd, "\n[%d]---[%d]\n", inf.c3, inf.c4);
	dprintf(fd, "Piece : [%s]\n", inf.piece_str);
	dprintf(fd, "Size Piece Vertical : [%u]\n", inf.piece_verti);
	dprintf(fd, "Size Piece Horizontal : [%u]\n", inf.piece_hori);
}

void	init(t_parse_info *inf)
{
	inf->piece_hori = 1;
	inf->piece_verti = 1;
	inf->tmp = 0;
	inf->c1 = 0;
	inf->c2 = 0;
	inf->c3 = 0;
	inf->c4 = 0;
}

void	algool_test(int fd, t_parse_info *inf)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(0, &line) == 1)
	{
		dprintf(fd, "Line %d : [%s]\n", i, line);
		ft_strdel(&line);
		i++;
	}
}

void	hori_or_verti(int fd, t_parse_info *inf)
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
}

void	get_coin(int fd, t_parse_info *inf)
{
	char	*line;
	int		i;
	int		j;
	int		lower;
	int		upper;

	i = 0;
	j = 0;
	upper = 0;
	inf->piece_str = malloc(sizeof(char) * (inf->piece_y * inf->piece_x + 1));
	while (i < inf->piece_y)
	{
		get_next_line(0, &line);
		inf->piece_str = ft_strcat(inf->piece_str, line);
		//if ((size = ft_strlen(line) - ft_strlen(ft_strchr(line, '*'))))
		if (ft_strchr(line, '*'))
		{
			if (j == 0)
			{
				lower = i;
				j++;
			}
			if (i > upper)
				upper = i;
			dprintf(fd, "size * : [%d]\n", i);
		}
		ft_strdel(&line);
		i++;
	}
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
	get_coin(fd, inf);
	hori_or_verti(fd, inf);
}

int		main(int ac, char **av)
{
	t_parse_info inf;
	int		fd = open("/Users/cgarrot/filler/info.log", O_WRONLY | O_APPEND);

	dprintf(fd, "-----------INFO---------\n");
	parse(fd, &inf);
	printf_info(fd, inf);
	//algool_test(fd, &inf);
	return (0);
}
