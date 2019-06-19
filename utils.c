/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 21:15:54 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/19 21:20:10 by cgarrot     ###    #+. /#+    ###.fr     */
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
