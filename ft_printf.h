/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_printf.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/14 14:41:28 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/30 16:01:53 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

# define TRUE						1
# define FALSE						0
# define ESPACE						' '
# define ZERO						'0'
# define INTEGER_ZERO_PADDING		(-1)
# define DECIMAL_BASE				"0123456789"
# define UPCASE_HEX_BASE			"0123456789ABCDEF"
# define LOWCASE_HEX_BASE			"0123456789abcdef"
# define OCTAL_BASE					"01234567"
# define INT_MAX					2147483647
# define INT_MIN					(-2147483648)
# define UINT_MAX					4294967295
# define ULONG_MAX					4294967295
# define ULLONG_MAX					9223372036854775807
# define UCHAR_MAX					255
# define USHRT_MAX					32767
# define MAX(a, b)					(a > b ? a : b)
# define MIN(a ,b)					(a < b ? a : b)
# define ABS(a)						( a < 0 ? -a : a)
# define NEG(a)						(a < 0 ? a : -a)
# define F_MINUS					(1 << 0)
# define F_ZERO						(1 << 1)
# define F_WILDCARD					(1 << 2)
# define F_SPACE					(1 << 3)
# define F_SHARP					(1 << 4)
# define F_PLUS						(1 << 5)
# define F_UPCASE					(1 << 6)
# define F_USHORT					(1 << 7)
# define F_USHORT2					(1 << 8)
# define F_LONG						(1 << 9)
# define F_LONG2					(1 << 10)
# define F_SIZE_T					(1 << 11)
# define F_PRECI					(1 << 12)
# define F_POINTER					(1 << 13)
# define F_WILDCARD2				(1 << 14)
# define PF_SIZE_BUFFER				1024

typedef unsigned long				t_size;
typedef long long int				t_intmax;
typedef unsigned long long			t_uintmax;

typedef struct						s_printf
{
	int								len;
	int								f;
	short							n;
	int								min_lenght;
	int								precision;
	int								padding;
	int								printed;
	int								fd;
	int								buffer_index;
	char							buffer[PF_SIZE_BUFFER];
	va_list							ap;
	char							*format;
	unsigned						c;
}									t_printf;

int									ft_printf(const char *format, ...);
void								pf_optionals_parse(t_printf *p);
void								pf_cs_not_found(t_printf *p);
void								pf_putnb(t_printf *p);
void								pf_putnb_base(t_printf *p, char *base,
		int upcase);
void								pf_itoa(t_intmax nb, t_printf *p, int len);
void								pf_put_unsigned(t_printf *p);
void								pf_itoa_unsigned(t_uintmax nb, t_printf *p,
		int len);
void								pf_itoa_base(t_uintmax nb, char *b,
		t_printf *p);
void								pf_double_percent(t_printf *p);
void								pf_itoa_base_octal(t_uintmax nb, char *b,
		t_printf *p);
void								pf_itoas_fill(t_uintmax nb, char *base,
		char *srt, t_printf *p);
void								pf_putnb_double(t_printf *p);
void								pf_secure_putstr(t_printf *p);
void								pf_putstr(t_printf *p, int min);
void								pf_putchar(t_printf *p, unsigned c);
short								ft_strchri(char *str, int c, int i);
void								pf_print_ptr_adress(t_printf *p);
void								pf_putdouble(t_printf *p);
void								pf_buffer(t_printf *p, void *elem,
		t_size size);
void								pf_wildcard(t_printf *p);
void								pf_padding(t_printf *p, short t_bool);
void								pf_padding_wildcard(t_printf *p);
void								pf_padding_sharp(t_printf *p);
void								ft_bzero(void *str, t_size n);
void								*ft_memcpy(void *s1, const void *s2,
		t_size n);
void								*ft_memset(void *str, int c, t_size n);
int									ft_atoi(const char *str);
t_size								ft_strlen(const char *str);

#endif
