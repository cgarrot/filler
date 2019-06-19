/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   filler.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/10 10:50:02 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/19 13:23:04 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/includes/ft_printf.h"
# include "./libft/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct s_parse_info
{
	char			caract;
	char			enemy;
	char			*piece_str;
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
	int				c1;
	int				c2;
	int				c3;
	int				c4;
}				t_parse_info;

#endif
