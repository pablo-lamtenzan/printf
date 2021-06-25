/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/29 17:08:15 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/26 07:10:01 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_bzero(void *str, t_size n)
{
	unsigned char *start;

	start = str;
	while (n-- > 0)
		*start++ = 0;
}

void	*ft_memset(void *str, int c, t_size n)
{
	unsigned char *start;

	start = str;
	while (n-- > 0)
		*start++ = c;
	return (str);
}

void	*ft_memcpy(void *s1, const void *s2, t_size n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	if (!n || s1 == s2)
		return (s1);
	while (n--)
		*ptr1++ = *ptr2++;
	return (s1);
}

int		ft_atoi(const char *str)
{
	t_size				i;
	unsigned long int	nb;
	int					sing;
	char				*s;

	sing = 1;
	nb = 0;
	i = 0;
	s = (char *)str;
	while ((s[i] == ' ') || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sing = -sing;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		nb = nb * 10 + s[i++] - '0';
	if ((sing > 0 && nb <= 9223372036854775807L) ||
			(sing < 0 && nb <= 9223372036854775808UL))
		return (sing * nb);
	return (sing < 0 ? 0 : -1);
}

t_size	ft_strlen(const char *str)
{
	t_size i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
