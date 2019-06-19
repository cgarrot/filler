/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/10 10:50:02 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/19 21:24:32 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include "libft/includes/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_count
{
	int		i;
	int		j;
	int		k;
	int		lower;
	int		upper;
}				t_count;

typedef struct s_parse_info
{
	char			caract;
	char			enemy;
	char			*piece_str;
	char			*str;
	int				**tab;
	unsigned int	start_y;
	unsigned int	start_x;
	unsigned int	enemy_y;
	unsigned int	enemy_x;
	unsigned int	size_y;
	unsigned int	size_x;
	unsigned int	piece_y;
	unsigned int	piece_x;
	unsigned int	coor_y;
	unsigned int	coor_x;
	unsigned int	piece_verti;
	unsigned int	piece_hori;
	int				tmp;
}				t_parse_info;

//utils
int		ft_atoi_2(char *str, t_parse_info *inf);
int		count_caract(int fd, char *str, char c);

//parse
void	parse(int fd, t_parse_info *inf);
void	size_piece_info(int fd, t_parse_info *inf);

void	init(t_parse_info *inf);

#endif
