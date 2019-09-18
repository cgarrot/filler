/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 14:00:11 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 16:43:10 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/filler.h"

int		test_piece(t_parse_info *inf, t_algo_info *algo)
{
	t_count			c;

	c.j = -1;
	inf->res = 0;
	inf->tmp2 = 2147483646;
	calcul_coor_piece(inf, algo, &c);
	c.k = -1;
	c.i = 0;
	c.j = 0;
	while (inf->p_str[++c.k])
	{
		if (inf->p_str[c.k] == '*' && (((int)algo->coor_y + c.j < inf->size_y)
					&& ((int)algo->coor_x + c.i < inf->size_x)))
			inf->tab[algo->coor_y + c.j][algo->coor_x + c.i] = 1;
		if (inf->p_str[c.k] == 'R')
		{
			c.i = -1;
			c.j++;
		}
		c.i++;
	}
	return (1);
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

void	heatmap(t_parse_info *inf)
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
				if (inf->map[c.j][c.i] == c.k - 1 && (c.j - 1 >= 0
							&& c.i - 1 >= 0 && c.j + 1 < inf->size_y
							&& c.i + 1 < inf->size_x))
					set_heatmap(inf, &c);
		}
		c.k++;
	}
}

int		setup_and_parse(t_parse_info *inf)
{
	if (inf->first == 0)
	{
		if (parse(inf) == 0)
			return (0);
		set_map(inf);
		set_tab(inf);
		heatmap(inf);
	}
	if (inf->first == 1)
	{
		clear_heatmap(inf);
		set_map(inf);
		if (parse_piece(inf) == 0)
			return (0);
		heatmap(inf);
	}
	inf->first = 1;
	return (1);
}

int		main(void)
{
	t_parse_info		inf;
	t_algo_info			algo;

	inf.first = 0;
	while (1)
	{
		if (setup_and_parse(&inf) == 0)
			break ;
		if (test_piece(&inf, &algo) == 0)
			break ;
		free_str(&inf);
		ft_putnbr(algo.coor_y);
		ft_putchar(' ');
		ft_putnbr(algo.coor_x);
		ft_putchar('\n');
	}
	clear_heatmap(&inf);
	clear_tab(&inf);
	return (0);
}
