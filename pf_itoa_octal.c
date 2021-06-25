/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   itoa_aux.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/27 07:44:44 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/27 09:42:45 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_itoa_base_octal(t_uintmax nb, char *b, t_printf *p)
{
	char		s[64];
	t_uintmax	aux;

	aux = nb;
	while (nb && ++p->printed)
		nb /= ft_strlen(b);
	aux == 0 ? p->printed++ : 0;
	p->precision == 0 && aux == 0 ? p->printed-- : 0;
	p->f & F_SHARP ? p->precision-- : 0;
	p->precision -= p->precision > p->printed ? p->printed : p->precision;
	((p->f & F_SHARP) && ft_strlen(b) == 8 && (!(p->f & F_ZERO)) ?
		p->min_lenght -= 1 : 0);
	p->padding = p->precision > -1 && (p->min_lenght - (p->precision +
		p->printed)) >= 0 ? p->min_lenght - (p->precision + p->printed) : 0;
	pf_padding(p, FALSE);
	pf_itoas_fill(ABS(aux), b, s, p);
	p->f & F_SHARP ? p->buffer[p->buffer_index++] = '0' : 0;
	p->f & F_SHARP ? p->len++ : 0;
	p->len += p->precision ? p->precision : 0;
	while (p->f & F_PRECI && p->precision--)
		p->buffer[p->buffer_index++] = '0';
	pf_buffer(p, s, p->printed);
	pf_padding(p, TRUE);
}
