/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pf_buffer.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/26 05:44:43 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 05:45:22 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_buffer(t_printf *p, void *new, t_size size)
{
	ft_memcpy(&(p->buffer[p->buffer_index]), new, size);
	p->buffer_index += size;
	p->len += size;
}
