/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_putchar.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 20:17:29 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/30 16:04:28 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_putchar(t_printf *p, unsigned c)
{
	p->printed = 1;
	if ((p->padding = p->min_lenght - p->printed) < 0)
		p->padding = 0;
	pf_padding(p, FALSE);
	pf_buffer(p, &c, 1);
	pf_padding(p, TRUE);
}

void		pf_secure_putstr(t_printf *p)
{
	int		min;
	char	*str;

	min = p->precision >= 0 ? p->precision : 6;
	if (p->precision == 0 && p->min_lenght == 0)
	{
		p->buffer[p->buffer_index] = '\0';
		str = (char *)va_arg(p->ap, unsigned*);
	}
	else
		pf_putstr(p, min);
}

void		pf_putstr(t_printf *p, int min)
{
	unsigned	*s;
	int			len;
	int			aux;

	if (!(s = va_arg(p->ap, unsigned*)))
	{
		if (!(p->f & F_ZERO))
			pf_buffer(p, "(null)", MIN(6, min));
		else
			while (p->min_lenght--)
				pf_buffer(p, "0", 1);
		return ;
	}
	else
	{
		aux = MIN((int)ft_strlen((const char *)s), p->precision);
		len = (p->precision < 0) ? (int)ft_strlen((const char *)s) : aux;
		p->padding = (p->min_lenght - len) > 0 ? (p->min_lenght - len) : 0;
	}
	pf_padding(p, FALSE);
	pf_buffer(p, s, len);
	pf_padding(p, TRUE);
}

void		pf_double_percent(t_printf *p)
{
	p->padding = p->min_lenght - 1;
	pf_padding(p, FALSE);
	p->buffer[p->buffer_index++] = '%';
	pf_padding(p, TRUE);
	p->len++;
}
