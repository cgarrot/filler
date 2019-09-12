/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/10 10:50:02 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 23:58:20 by cgarrot     ###    #+. /#+    ###.fr     */
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
	int				start_y;
	int				start_x;
	int				enemy_y;
	int				enemy_x;
	int				size_y;
	int				size_x;
	int				piece_y;
	int				piece_x;
	int				coor_y;
	int				coor_x;
	int				piece_verti;
	int				piece_hori;
	int				tmp;
	int				tmp2;
	int				res;
	int				first;
	int				tmp_x;
	int				tmp_y;
}				t_parse_info;

typedef struct s_algo_info
{
	unsigned int	coor_y;
	unsigned int	coor_x;
}				t_algo_info;

//utils
int		ft_atoi_2(char *str, t_parse_info *inf);
int		count_caract(char *str, char c);
void	aff_map(t_parse_info *inf, int **tab);
void	set_map(t_parse_info *inf);
void	set_tab(t_parse_info *inf);

//parse
int		parse(t_parse_info *inf);
int		size_piece_info(t_parse_info *inf);
int		parse_piece(t_parse_info *inf);

void	init(t_parse_info *inf);
void	init_calcul(t_parse_info *inf, t_count *c);
void	clear_heatmap(t_parse_info *inf);
void	clear_tab(t_parse_info *inf);
void	free_zob(t_parse_info *inf);

#endif
