/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/10 10:50:02 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/17 17:04:02 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_count
{
	int				i;
	int				j;
	int				k;
	int				i_tmp;
	int				j_tmp;
	int				point;
	int				lower;
	int				upper;
	int				tmp;
}				t_count;

typedef struct	s_parse_info
{
	char			caract;
	char			enemy;
	char			*p_str;
	char			*str;
	char			*line;
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
	int				tmp_x;
	int				tmp_y;
	int				init_pos;
	int				t_enemy;
	int				i;
	int				j;
	int				first;
	int				loop;
}				t_parse_info;

typedef struct	s_algo_info
{
	unsigned int	coor_y;
	unsigned int	coor_x;
}				t_algo_info;

int				ft_atoi_2(char *str, t_parse_info *inf);
int				count_caract(char *str, char c);
void			set_map(t_parse_info *inf);
void			set_tab(t_parse_info *inf);
int				parse(t_parse_info *inf);
int				size_piece_info(t_parse_info *inf);
int				parse_piece(t_parse_info *inf);
void			info_start_co(t_parse_info *inf, char *line);
void			free_split(t_parse_info *inf, char *line);
void			player_one_or_two(t_parse_info *inf, char *line);
int				hori_or_verti(t_parse_info *inf, t_count *count, char *line);
int				get_co_enemy(t_parse_info *inf);
void			algo_piece(t_parse_info *inf, t_count *c);
void			player_one_or_two(t_parse_info *inf, char *line);
void			calcul_coor_piece(t_parse_info *inf,
		t_algo_info *algo, t_count *c);
void			init(t_parse_info *inf);
void			init_calcul(t_parse_info *inf, t_count *c);
void			clear_heatmap(t_parse_info *inf);
void			clear_tab(t_parse_info *inf);
void			free_str(t_parse_info *inf);

#endif
