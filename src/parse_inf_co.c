/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_inf_co.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/16 17:11:34 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 16:44:01 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/filler.h"

void	free_split(t_parse_info *inf, char *line)
{
	char	**split;

	split = NULL;
	split = ft_strsplit(line, ' ');
	inf->piece_y = ft_atoi(split[1]);
	inf->piece_x = ft_atoi(split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
}

void	info_start_co(t_parse_info *inf, char *line)
{
	char	*tmp;

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
}

void	player_one_or_two(t_parse_info *inf, char *line)
{
	if (line[10] == '1')
		inf->caract = 'O';
	if (line[10] == '1')
		inf->enemy = 'X';
	if (line[10] == '2')
		inf->caract = 'X';
	if (line[10] == '2')
		inf->enemy = 'O';
}

void	algo_piece(t_parse_info *inf, t_count *c)
{
	if (inf->tab[c->j + c->j_tmp][c->i_tmp] == 2 && inf->p_str[c->k] == '*')
		inf->t_enemy++;
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

void	calcul_coor_piece(t_parse_info *inf, t_algo_info *algo, t_count *c)
{
	while (++c->j < (inf->size_y - inf->piece_y + 1))
	{
		c->i = -1;
		while (++c->i < (inf->size_x - inf->piece_x + 1))
		{
			inf->t_enemy = 0;
			init_calcul(inf, c);
			while (inf->p_str[++(c->k)])
				algo_piece(inf, c);
			if ((inf->res < inf->tmp2) && c->point == 1 && inf->t_enemy == 0)
			{
				inf->tmp2 = inf->res;
				algo->coor_y = c->j;
				algo->coor_x = c->i;
			}
		}
	}
}
