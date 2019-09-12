/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 21:15:54 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 19:47:13 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "filler.h"

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

int		ft_atoi_3(char *str)
{
	int		nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (str[i] != '9' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		nbr = nbr * 10 + str[i++] - '0';
	return (nbr);
}

int		count_caract(int fd, char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			j++;
		i++;
	}
	return (j);
}

void	set_tab(int fd, t_parse_info *inf)
{
	int		i;
	int		j;

	j = 0;
	inf->tab = malloc((sizeof(int*) * inf->size_y));
	while (j < inf->size_y)
	{
		i = 0;
		inf->tab[j] = malloc((sizeof(int) * inf->size_x));
		while (i < inf->size_x)
		{
			inf->tab[j][i] = 0;
			i++;
		}
		j++;
	}
	inf->tab[inf->enemy_y][inf->enemy_x] = 2;
	inf->tab[inf->start_y][inf->start_x] = 1;
}

void	set_map(int fd, t_parse_info *inf)
{
	int		i;
	int		j;

	j = 0;
	inf->map = malloc((sizeof(int*) * inf->size_y));
	while (j < inf->size_y)
	{
		i = 0;
		inf->map[j] = malloc((sizeof(int) * inf->size_x));
		while (i < inf->size_x)
		{
			inf->map[j][i] = -2;
			i++;
		}
		j++;
	}
	inf->map[inf->enemy_y][inf->enemy_x] = -1;
}

void	aff_map(int fd, t_parse_info *inf, int **tab)
{
	int		i;
	int		j;

	j = 0;
	while (j < inf->size_y)
	{
		i = 0;
		while (i < inf->size_x)
		{
			dprintf(fd, "%d ", tab[j][i]);
			i++;
		}
		dprintf(fd, "\n");
		j++;
	}
}
