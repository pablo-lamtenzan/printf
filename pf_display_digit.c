/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   nb_fct.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/17 15:52:01 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/29 15:00:05 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_itoa_norme(t_printf *p)
{
	p->len += p->precision ? p->precision : 0;
	while (p->f & F_PRECI && p->precision--)
		p->buffer[p->buffer_index++] = '0';
}

void		pf_itoa(t_intmax nb, t_printf *p, int len)
{
	char		s[64];
	t_uintmax	aux;

	aux = ABS(nb);
	while (aux /= 10)
		++len;
	p->printed += nb != 0 ? len : 1;
	p->precision == 0 && nb == 0 ? p->printed-- : 0;
	p->precision -= p->precision > p->printed ? p->printed : p->precision;
	if (nb < 0 || p->f & F_PLUS || p->f & F_SPACE)
		++p->len && (nb < 0 || p->f & F_PLUS || p->f & F_SPACE) ?
			p->min_lenght-- : 0;
	p->padding = p->precision > -1 && (p->min_lenght - (p->precision +
			p->printed)) >= 0 ? p->min_lenght - (p->precision + p->printed) : 0;
	!(p->f & F_ZERO) ? pf_padding(p, FALSE) : 0;
	aux = ABS(nb);
	pf_itoas_fill(aux, DECIMAL_BASE, s, p);
	((nb < 0) ? p->buffer[p->buffer_index++] = '-' : 0);
	((p->f & F_PLUS && nb >= 0) ? p->buffer[p->buffer_index++] = '+' : 0);
	((p->f & F_SPACE) && nb >= 0 ? p->buffer[p->buffer_index++] = ' ' : 0);
	p->f & F_ZERO ? pf_padding(p, INTEGER_ZERO_PADDING) : 0;
	pf_padding(p, FALSE);
	pf_itoa_norme(p);
	pf_buffer(p, s, p->printed);
	pf_padding(p, TRUE);
}

void		pf_itoa_unsigned(t_uintmax nb, t_printf *p, int len)
{
	char		s[64];
	t_uintmax	aux;

	aux = ABS(nb);
	while (aux /= 10)
		++len;
	p->f & F_PRECI ? p->f &= ~F_ZERO : 0;
	p->printed += nb != 0 ? len : 1;
	p->precision == 0 && nb == 0 ? p->printed-- : 0;
	p->precision -= p->precision > p->printed ? p->printed : p->precision;
	p->padding = p->precision > -1 && (p->min_lenght - (p->precision +
			p->printed)) >= 0 ? p->min_lenght - (p->precision + p->printed) : 0;
	!(p->f & F_ZERO) ? pf_padding(p, FALSE) : 0;
	aux = ABS(nb);
	pf_itoas_fill(aux, DECIMAL_BASE, s, p);
	p->f & F_ZERO ? pf_padding(p, INTEGER_ZERO_PADDING) : 0;
	pf_padding(p, FALSE);
	pf_itoa_norme(p);
	pf_buffer(p, s, p->printed);
	pf_padding(p, TRUE);
}

void		pf_itoas_fill(t_uintmax nb, char *base, char *str, t_printf *p)
{
	int len;
	int base_len;

	base_len = ft_strlen(base);
	len = p->printed;
	if (nb == 0)
	{
		str[--len] = '0';
		return ;
	}
	while (len--)
	{
		str[len] = base_len != 10 ? base[nb % base_len] : nb % 10 + '0';
		nb /= base_len;
	}
}

void		pf_itoa_base(t_uintmax nb, char *b, t_printf *p)
{
	char		s[64];
	t_uintmax	aux;

	aux = nb;
	p->f & F_PRECI ? p->f &= ~F_ZERO : 0;
	while (nb && ++p->printed)
		nb /= ft_strlen(b);
	aux == 0 ? p->f &= ~F_SHARP : 0;
	aux == 0 ? p->printed++ : 0;
	p->precision == 0 && aux == 0 ? p->printed-- : 0;
	p->precision -= p->precision > p->printed ? p->printed : p->precision;
	(p->f & F_POINTER || p->f & F_SHARP) && ft_strlen(b) == 16 ?
		p->min_lenght -= 2 : 0;
	p->padding = p->precision > -1 && (p->min_lenght - (p->precision +
		p->printed)) >= 0 ? p->min_lenght - (p->precision + p->printed) : 0;
	!(p->f & F_ZERO) ? pf_padding(p, FALSE) : 0;
	p->f & F_POINTER ? pf_buffer(p, "0x", 2) : 0;
	pf_itoas_fill(ABS(aux), b, s, p);
	p->f & F_SHARP && !(p->f & F_POINTER) ? pf_padding_sharp(p) : 0;
	p->f & F_ZERO ? pf_padding(p, INTEGER_ZERO_PADDING) : 0;
	p->len += p->precision ? p->precision : 0;
	while (p->f & F_PRECI && p->precision--)
		p->buffer[p->buffer_index++] = '0';
	pf_buffer(p, s, p->printed);
	pf_padding(p, TRUE);
}
