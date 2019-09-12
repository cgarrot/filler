/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/10 10:50:02 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 19:58:18 by cgarrot     ###    #+. /#+    ###.fr     */
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
	int		i_tmp;
	int		j_tmp;
	int		point;
	int		lower;
	int		upper;
	int		tmp;
}				t_count;

typedef struct s_parse_info
{
	char			caract;
	char			enemy;
	char			*piece_str;
	char			*p_str;
	char			*str;
	int				**tab;
	int				**map;
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
	int				tmp2;
	int				res;
	int				first;
	unsigned int	tmp_x;
	unsigned int	tmp_y;
}				t_parse_info;

typedef struct s_algo_info
{
	unsigned int	coor_y;
	unsigned int	coor_x;
}				t_algo_info;

//utils
int		ft_atoi_2(char *str, t_parse_info *inf);
int		ft_atoi_3(char *str);
int		count_caract(int fd, char *str, char c);
void	aff_map(int fd, t_parse_info *inf, int **tab);
void	set_map(int fd, t_parse_info *inf);
void	set_tab(int fd, t_parse_info *inf);

//parse
void	parse(int fd, t_parse_info *inf);
int		size_piece_info(int fd, t_parse_info *inf);

void	init(t_parse_info *inf);

#endif
