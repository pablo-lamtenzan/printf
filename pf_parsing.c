/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing_functions.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 20:23:46 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/29 12:59:56 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void				pf_conversion(t_printf *p)
{
	p->c = *p->format;
	if (p->c == 's')
		pf_secure_putstr(p);
	else if (p->c == 'c')
		pf_putchar(p, va_arg(p->ap, unsigned));
	else if (p->c == 'p')
		pf_print_ptr_adress(p);
	else if (p->c == 'i' || p->c == 'd')
		pf_putnb(p);
	else if (p->c == 'u')
		pf_putnb(p);
	else if (p->c == 'o')
		pf_putnb_base(p, OCTAL_BASE, FALSE);
	else if (p->c == 'x' || p->c == 'X')
		p->c == 'X' ? pf_putnb_base(p, UPCASE_HEX_BASE, TRUE) :
			pf_putnb_base(p, LOWCASE_HEX_BASE, FALSE);
	else if (p->c == '%')
		pf_double_percent(p);
	else
		pf_cs_not_found(p);
}

static void			pf_prezi(t_printf *p)
{
	if ('0' <= *p->format && '9' >= *p->format)
	{
		p->min_lenght = MAX(1, ft_atoi(p->format));
		while ('0' <= *p->format && '9' >= *p->format)
			++p->format;
	}
	if (*p->format == '.')
	{
		p->f |= F_PRECI;
		++p->format;
		if (*p->format == '*')
		{
			p->n = (int)va_arg(p->ap, int);
			if (p->n < 0)
				p->f &= ~F_PRECI;
			else
				p->precision = p->n;
		}
		else
			p->precision = MAX(0, ft_atoi(p->format));
		while ('0' <= *p->format && '9' >= *p->format)
			++p->format;
	}
	else
		p->f &= ~F_PRECI;
}

static void			pf_manage_flags(t_printf *p)
{
	while ((p->n = ft_strchri("-0* #+", *p->format, -1)) > -1 && ++p->format)
		p->f |= (1 << p->n);
	((p->f & F_MINUS) && !(p->f & F_WILDCARD) ? p->f &= ~F_ZERO : 0);
	(p->f & F_PLUS ? p->f &= ~F_SPACE : 0);
	pf_wildcard(p);
}

void				pf_optionals_parse(t_printf *p)
{
	p->format++;
	p->f = 0;
	p->min_lenght = 0;
	p->precision = -1;
	p->printed = 0;
	pf_manage_flags(p);
	pf_prezi(p);
	p->precision == -1 && p->f & F_PRECI ? p->precision = 0 : 0;
	while (TRUE)
	{
		if (*p->format == 'l')
			(p->f |= (p->format[1] == 'l') ? F_LONG2 : F_LONG);
		if (*p->format == 'h')
			(p->f |= (p->format[1] == 'h') ? F_USHORT2 : F_USHORT);
		else
			break ;
		++p->format;
	}
	p->f & F_LONG2 || p->f & F_USHORT2 ? p->format++ : 0;
	if (ft_strchri("%scpidufgneorxX", *p->format, -1) == -1)
		++p->format;
	p->precision = p->precision < 0 ? -1 : p->precision;
	pf_conversion(p);
}

void				pf_cs_not_found(t_printf *p)
{
	if ((p->padding = p->min_lenght) - 1 > 0)
	{
		pf_padding(p, FALSE);
		pf_buffer(p, p->format, 1);
		pf_padding(p, TRUE);
		return ;
	}
	pf_buffer(p, p->format, 1);
}
