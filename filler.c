/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 14:00:11 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/19 21:51:59 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

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

void	aff_map(int fd, t_parse_info *inf)
{
	int		i;
	int		j;

	j = 0;
	while (j < inf->size_y)
	{
		i = 0;
		while (i < inf->size_x)
		{
			dprintf(fd, "%d ", inf->tab[j][i]);
			i++;
		}
		dprintf(fd, "\n");
		j++;
	}
}

void	set_map(int fd, t_parse_info *inf)
{
	int		i;
	int		j;

	j = 0;
	inf->tab = malloc((sizeof(int*) * inf->size_y));
	while (j < inf->size_y)
	{
		i = 0;
		inf->tab[j] = malloc((sizeof(int) * inf->size_x));
		ft_memset(inf->tab[i], 0, inf->size_x);
		while (i < inf->size_x)
		{
			dprintf(fd, "%d ", inf->tab[j][i]);
			i++;
		}
		dprintf(fd, "\n");
		j++;
	}
	inf->tab[inf->start_y][inf->start_x] = 1;
	inf->tab[inf->enemy_y][inf->enemy_x] = 1;
}

int		main(int ac, char **av)
{
	t_parse_info inf;
	int		fd = open("/Users/cgarrot/filler/info.log", O_WRONLY | O_APPEND);

	dprintf(fd, "-----------INFO---------\n");
	parse(fd, &inf);
	set_map(fd, &inf);
	printf_info(fd, inf);
	aff_map(fd, &inf);
	//algool_test(fd, &inf);
	return (0);
}
