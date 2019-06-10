/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoinfree.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cgarrot <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/05 15:35:58 by cgarrot      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/06 15:55:41 by cgarrot     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, char i)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (i == 1 || i == 3)
		ft_strdel(&s1);
	if (i == 2 || i == 3)
		ft_strdel(&s2);
	return (tmp);
}
