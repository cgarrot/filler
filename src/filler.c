/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 14:00:11 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 23:55:40 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

void	calcul_coor_piece(t_parse_info *inf, t_algo_info *algo, t_count *c)
{
	int		t_enemy;

	while (++c->j < (inf->size_y - inf->piece_y + 1))
	{
		c->i = -1;
		while (++c->i < (inf->size_x - inf->piece_x + 1))
		{
			t_enemy = 0;
			init_calcul(inf, c);
			while (inf->p_str[++(c->k)])
			{
				if (inf->tab[c->j + c->j_tmp][c->i_tmp] == 2 && inf->p_str[c->k] == '*')
					t_enemy++;
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
			if ((inf->res < inf->tmp2) && c->point == 1 && t_enemy == 0)
			{
				inf->tmp2 = inf->res;
				algo->coor_y = c->j;
				algo->coor_x = c->i;
			}
		}
	}
}

void	test_piece(t_parse_info *inf, t_algo_info *algo)
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
				if (inf->map[c.j][c.i] == c.k - 1 && (c.j - 1 >= 0 && c.i - 1 >= 0 && c.j + 1 < inf->size_y && c.i + 1 < inf->size_x))
					set_heatmap(inf, &c);
		}
		c.k++;
	}
}

int		main(void)
{
	t_parse_info		inf;
	t_algo_info			algo;
	int					first;

	first = 0;
	while (1)
	{
		if (first == 0)
		{
			if (parse(&inf) == 0)
				break;
			set_map(&inf);
			set_tab(&inf);
			heatmap(&inf);
		}
		if (first == 1)
		{
			clear_heatmap(&inf);
			set_map(&inf);
			if (parse_piece(&inf) == 0)
				break;
			heatmap(&inf);
		}
		first = 1;
		test_piece(&inf, &algo);
		free_zob(&inf);
		ft_putnbr(algo.coor_y);
		ft_putchar(' ');
		ft_putnbr(algo.coor_x);
		ft_putchar('\n');
	}
	clear_heatmap(&inf);
	clear_tab(&inf);
	return (0);
}
