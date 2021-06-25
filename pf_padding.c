/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_padding.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 05:42:18 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/27 01:09:31 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_padding(t_printf *p, short t_bool)
{
	if (p->padding > -1)
	{
		if (p->f & F_WILDCARD || (p->f & F_MINUS && t_bool) ||
				((p->f & F_ZERO && !t_bool) || t_bool == -1) ||
				(!t_bool && p->padding >= 0 && !(p->f & F_MINUS)))
			p->len += p->padding;
		if (p->f & F_WILDCARD)
			pf_padding_wildcard(p);
		if (p->f & F_MINUS && t_bool)
			while (p->padding--)
				p->buffer[p->buffer_index++] = ESPACE;
		else if ((p->f & F_ZERO && !t_bool) || t_bool == -1)
			while (p->padding--)
				p->buffer[p->buffer_index++] = ZERO;
		else if (!t_bool && p->padding >= 0 && !(p->f & F_MINUS))
			while (p->padding--)
				p->buffer[p->buffer_index++] = ESPACE;
	}
}

void	pf_padding_wildcard(t_printf *p)
{
	if (p->f & F_ZERO)
		p->c = ZERO;
	else
		p->c = ESPACE;
	while (p->padding--)
		p->buffer[p->buffer_index++] = p->c;
}

void	pf_padding_sharp(t_printf *p)
{
	p->len += 2;
	p->buffer[p->buffer_index++] = ZERO;
	if (!(p->f & F_UPCASE))
		p->c = 'x';
	else if (p->f & F_UPCASE)
		p->c = 'X';
	p->buffer[p->buffer_index++] = p->c;
}
