/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_put_numbers.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 05:52:32 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/27 10:11:27 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_putnb(t_printf *p)
{
	t_intmax nb;

	if (*p->format == 'u')
	{
		pf_put_unsigned(p);
		return ;
	}
	else if (p->f & F_LONG || p->f & F_LONG2)
		(nb = (p->f & F_LONG2) ? va_arg(p->ap, t_intmax) : va_arg(p->ap, long));
	else if (p->f & F_USHORT || p->f & F_USHORT2)
		(nb = (p->f & F_USHORT2) ? (signed char)va_arg(p->ap, int) :
		(signed short)va_arg(p->ap, int));
	else
		nb = (t_intmax)va_arg(p->ap, int);
	if ((*p->format == 'i' || *p->format == 'd')
			&& !(p->f & F_LONG) && !(p->f & F_USHORT) &&
			!(p->f & F_LONG) && !(p->f & F_LONG2))
	{
		nb > INT_MAX ? nb = (2147483649 - (nb - 2147483647)) * -1 : 0;
		nb < INT_MIN ? nb = (2147483649 - (-nb - 2147483647)) : 0;
		p->f & F_PRECI && p->f & F_ZERO ? p->f &= ~F_ZERO : 0;
	}
	pf_itoa((t_uintmax)nb, p, 1);
}

void		pf_put_unsigned(t_printf *p)
{
	t_uintmax nb;

	if (*p->format == 'u')
	{
		if (p->f & F_LONG || p->f & F_LONG2)
			nb = (p->f & F_LONG2) ? va_arg(p->ap, t_uintmax) :
			va_arg(p->ap, t_size);
		else if (p->f & F_USHORT || p->f & F_USHORT2)
			nb = (p->f & F_USHORT2) ?
				(unsigned char)va_arg(p->ap, int) :
				(unsigned short)va_arg(p->ap, int);
		else
			nb = (t_uintmax)va_arg(p->ap, unsigned int);
		if (!(p->f & F_LONG) && !(p->f & F_LONG2) && !(p->f & F_USHORT) &&
				!(p->f & F_USHORT2))
			nb > UINT_MAX ? nb = nb - 4294967296 : 0;
		p->f &= ~F_PLUS;
		p->f &= ~F_SPACE;
		pf_itoa_unsigned(nb, p, 1);
	}
}

void		pf_putnb_base(t_printf *p, char *base, int upcase)
{
	t_uintmax nb;

	upcase > 0 ? p->f |= F_UPCASE : 0;
	if (p->f & F_LONG || p->f & F_LONG2)
		nb = (p->f & F_LONG2) ? va_arg(p->ap, t_uintmax) :
			va_arg(p->ap, t_size);
	else if (p->f & F_USHORT || p->f & F_USHORT2)
		nb = (p->f & F_USHORT2) ? (unsigned char)va_arg(p->ap, int) :
			(unsigned short)va_arg(p->ap, int);
	else
		nb = (t_uintmax)va_arg(p->ap, unsigned int);
	if (!(p->f & F_LONG) && !(p->f & F_LONG2) && !(p->f & F_USHORT) &&
			!(p->f & F_USHORT2))
		nb > UINT_MAX ? nb = nb - 4294967296 : 0;
	else if (p->f & F_LONG)
	{
		nb > ULONG_MAX ? nb = 100000000 + (nb - ULONG_MAX - 1) : 0;
		pf_itoa(nb, p, 1);
		return ;
	}
	if (*p->format == 'o')
		pf_itoa_base_octal(nb, base, p);
	else
		pf_itoa_base(nb, base, p);
}

void		pf_print_ptr_adress(t_printf *p)
{
	void		*pointer;

	pointer = va_arg(p->ap, void *);
	p->f &= ~F_SHARP;
	p->min_lenght -= p->f & F_ZERO ? 2 : 0;
	p->padding = p->printed > p->min_lenght - 3 ? 0 : p->min_lenght -
		3 - p->printed;
	p->f |= F_POINTER;
	pf_itoa_base((t_uintmax)pointer, LOWCASE_HEX_BASE, p);
}
