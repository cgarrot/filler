/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 14:00:11 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 21:43:22 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

void	printf_info(int fd, t_parse_info inf, t_algo_info algo)
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
	//dprintf(fd, "Piece : [%s]\n", inf.p_str);
	//dprintf(fd, "Piece 2: [%s]\n", inf.piece_str);
	dprintf(fd, "Size Piece Vertical : [%u]\n", inf.piece_verti);
	dprintf(fd, "Size Piece Horizontal : [%u]\n", inf.piece_hori);
	dprintf(fd, "Res : [%d]\n", inf.res);
	dprintf(fd, "Min res : [%d]\n", inf.tmp2);

}

void	init(t_parse_info *inf)
{
	inf->piece_hori = 1;
	inf->piece_verti = 1;
	inf->tmp = 0;
}

void	init_calcul(t_parse_info *inf, t_count *c)
{
	c->k = -1;
	c->j_tmp = 0;
	c->i_tmp = c->i;
	inf->res = 0;
	c->point = 0;
}

void	calcul_coor_piece(int fd, t_parse_info *inf, t_algo_info *algo, t_count *c)
{
	int		test;

	while (++c->j < (inf->size_y - inf->piece_y + 1))
	{
		c->i = -1;
		while (++c->i < (inf->size_x - inf->piece_x + 1))
		{
			test = 0;
			init_calcul(inf, c);
			while (inf->p_str[++(c->k)])
			{

				if (inf->tab[c->j + c->j_tmp][c->i_tmp] == 2 && inf->p_str[c->k] == '*')
					test++;

				//dprintf(fd, "total = %d\n", c->j + c->j_tmp);
				//dprintf(fd, "c->i_tmp = %d\n", c->i_tmp);
				if (inf->tab[c->j + c->j_tmp][c->i_tmp] == 1 && inf->p_str[c->k] == '*')
					c->point++;
				if (inf->p_str[c->k] == '*' && c->point <= 1)
					inf->res += inf->map[c->j + c->j_tmp][c->i_tmp];
				if (inf->p_str[c->k] == 'R')
					c->i_tmp = c->i;
				if (inf->p_str[c->k] == 'R')
					c->j_tmp++;
				else if (c->i_tmp < inf->size_x - 1)
					c->i_tmp++;
			}
			if ((inf->res < inf->tmp2) && c->point == 1 && test == 0)
			{
				inf->tmp2 = inf->res;
				algo->coor_y = c->j;
				algo->coor_x = c->i;
				//dprintf(fd, "Piece place x: [%u]\n", algo->coor_x);
				//dprintf(fd, "Piece place y: [%u]\n", algo->coor_y);
			}
		}
	}
}

void	test_piece(int fd, t_parse_info *inf, t_algo_info *algo)
{
	t_count			c;

	c.j = -1;
	inf->res = 0;
	inf->tmp2 = 2147483646;
	calcul_coor_piece(fd, inf, algo, &c);
	c.k = -1;
	c.i = 0;
	c.j = 0;
	while (inf->p_str[++c.k])
	{
		if (inf->p_str[c.k] == '*')
			inf->tab[algo->coor_y + c.j][algo->coor_x + c.i] = 1;
		if (inf->p_str[c.k] == 'R')
		{
			c.i = -1;
			c.j++;
		}
		c.i++;
	}
}

void	set_heatmap(t_parse_info *inf, t_count *c)
{
	if (inf->map[c->j - 1][c->i - 1] == -2)
		inf->map[c->j - 1][c->i - 1] = c->k;
	if (inf->map[c->j - 1][c->i] == -2)
		inf->map[c->j - 1][c->i] = c->k;
	if (inf->map[c->j - 1][c->i + 1] == -2)
		inf->map[c->j - 1][c->i + 1] = c->k;
	if (inf->map[c->j][c->i - 1] == -2)
		inf->map[c->j][c->i - 1] = c->k;
	if (inf->map[c->j][c->i + 1] == -2)
		inf->map[c->j][c->i + 1] = c->k;
	if (inf->map[c->j + 1][c->i - 1] == -2)
		inf->map[c->j + 1][c->i - 1] = c->k;
	if (inf->map[c->j + 1][c->i] == -2)
		inf->map[c->j + 1][c->i] = c->k;
	if (inf->map[c->j + 1][c->i + 1] == -2)
		inf->map[c->j + 1][c->i + 1] = c->k;
}

void	heatmap(int fd, t_parse_info *inf)
{
	t_count		c;

	c.tmp = inf->size_x;
	if (inf->size_y > inf->size_x)
		c.tmp = inf->size_y + 1;
	c.k = 0;
	while (--c.tmp)
	{
		c.j = -1;
		while (++c.j < inf->size_y)
		{
			c.i = -1;
			while (++c.i < inf->size_x)
				if (inf->map[c.j][c.i] == c.k - 1 && (c.j - 1 >= 0 && c.i - 1 >= 0 && c.j + 1 < inf->size_y && c.i + 1 < inf->size_x))
					set_heatmap(inf, &c);
		}
		c.k++;
	}
}

void	clear_heatmap(int fd, t_parse_info *inf)
{
	int i;

	i = 0;
	while (i < inf->size_y)
	{
		free(inf->map[i]);
		//free(inf->map[i]);
		//ft_memset(inf->tab[i], -2, inf->size_x);
		i++;
	}
	//free(inf->map);
	free(inf->map);
}

int		parse_piece(int fd, t_parse_info *inf)
{
	char	*line;
	char	**split;
	int		i;
	int		j;
	
	i = 0;
	line = NULL;
	while (i < inf->size_y + 2)
	{
		//dprintf(fd, "---------------[%s]\n", inf->p_str);
		ft_strdel(&line);
		if ((get_next_line(0, &line) <= 0))
		{
			return (0);
		}
		//dprintf(fd, "2 LINE LINE [%s]\n", line);
		j = 0;
		while (j < inf->size_x + 4)
		{
			dprintf(fd, "%c", line[j]);
			if (line[j] == inf->enemy)
			{
				inf->tmp_x = j - 4;
				inf->tmp_y = i - 2;
				inf->map[inf->tmp_y][inf->tmp_x] = -1;
				inf->tab[inf->tmp_y][inf->tmp_x] = 2;
			}
			j++;
		}
		dprintf(fd, "\n");
		i++;
	}
	ft_strdel(&line);
	get_next_line(0, &line);
	//inf->tmp = 0;
	split = ft_strsplit(line, ' ');
	inf->piece_y = atoi(split[1]);
	inf->piece_x = atoi(split[2]);
	ft_strdel(&line);
	size_piece_info(fd, inf);
	return (1);
}

void	test_gnl(int fd, t_parse_info *inf)
{
	char *line;
	ft_strdel(&line);
	get_next_line(0, &line);
		dprintf(fd, "LINE LINE [%s]\n", line);
		ft_strdel(&line);
}

void	free_zob(int fd, t_parse_info *inf)
{
	if (inf->str)
		ft_strdel(&inf->str);
	if (inf->p_str)
		ft_strdel(&inf->p_str);
}

int		main(int ac, char **av)
{
	t_parse_info		inf;
	t_algo_info			algo;
	char		*line;
	int		fd = open("/Users/cgarrot/filler/info.log", O_WRONLY | O_APPEND);
	
	
	dprintf(fd, "-----------INFO---------\n");
	int		first = 0;
	int i = 0;
	while (1)
	{
		if (first == 0)
		{
			parse(fd, &inf);
			set_map(fd, &inf);
			set_tab(fd, &inf);
			heatmap(fd, &inf);
			//printf_info(fd, inf, algo);
		}
		if (first == 1)
		{
			clear_heatmap(fd, &inf);
			set_map(fd, &inf);
			//aff_map(fd, &inf, inf.tab);
			if (parse_piece(fd, &inf) == 0)
				return (0);
			heatmap(fd, &inf);
			aff_map(fd, &inf, inf.map);
			//printf_info(fd, inf, algo);
		}
		first = 1;


		test_piece(fd, &inf, &algo);
		free_zob(fd, &inf);



		aff_map(fd, &inf, inf.tab);
		dprintf(fd, "\n");
		//aff_map(fd, &inf, inf.map);


		//dprintf(fd, "Co Piece Y & X: [%u] [%u]\n", algo.coor_y, algo.coor_x);
		ft_putnbr(algo.coor_y);
		ft_putchar(' ');
		ft_putnbr(algo.coor_x);
		ft_putchar('\n');
		//printf("%d %d\n", algo.coor_y, algo.coor_x);

		//printf_info(fd, inf, algo);

		//test_gnl(fd, &inf);
	}
	return (0);
}
