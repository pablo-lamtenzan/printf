/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_wildcard.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 05:48:15 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/29 15:03:18 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void			pf_wildcard(t_printf *p)
{
	if (p->f & F_WILDCARD)
	{
		if ((p->n = (int)va_arg(p->ap, int)) < 0)
		{
			p->f |= F_MINUS;
			p->f & F_ZERO ? p->f &= ~F_ZERO : 0;
			p->n = ABS(p->n);
		}
		if (!(p->f & F_PRECI))
			p->min_lenght = p->n;
		else
		{
			p->precision = p->n;
			(p->f = (p->n) ? p->f | F_PRECI : p->f & ~F_PRECI);
		}
		p->f &= ~F_WILDCARD;
	}
}

short			ft_strchri(char *str, int c, int i)
{
	while (str[++i])
	{
		if (str[i] == c)
			return ((short)i);
	}
	return (-1);
}
