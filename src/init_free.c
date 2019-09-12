/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_free.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 23:53:03 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 23:57:14 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

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

void	clear_heatmap(t_parse_info *inf)
{
	int i;

	i = 0;
	while (i < inf->size_y)
	{
		free(inf->map[i]);
		i++;
	}
	free(inf->map);
}

void	clear_tab(t_parse_info *inf)
{
	int i;

	i = 0;
	while (i < inf->size_y)
	{
		free(inf->tab[i]);
		i++;
	}
	free(inf->tab);
}

void	free_zob(t_parse_info *inf)
{
	if (inf->str)
		ft_strdel(&inf->str);
	if (inf->p_str)
		ft_strdel(&inf->p_str);
}
