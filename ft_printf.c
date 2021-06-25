/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 21:10:05 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/27 02:13:14 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	t_printf p;

	ft_bzero(&p, sizeof(p));
	p.fd = 1;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
		{
			if (*(p.format + 1))
				pf_optionals_parse(&p);
		}
		else
			pf_buffer(&p, p.format, 1);
		++p.format;
	}
	write(p.fd, p.buffer, p.buffer_index);
	va_end(p.ap);
	return (p.len);
}
