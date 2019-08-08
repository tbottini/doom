#include "libft.h"
#include "vector.h"

void		ft_putdouble(double num)
{
	int		i;

	i = 4;
	ft_putnbr((int)num);
	num = num - (int)num;
	ft_putchar('.');
	while (--i)
	{
		ft_putchar((int)(num * 10.0) + '0');
		num *= 10;
		num -= (int)num;
	}
}

void		double_msg(char *msg, double num)
{
	ft_putstr(msg);
	ft_putchar(' ');
	ft_putdouble(num);
	ft_putchar('\n');
}

void		fvct2_print(t_fvct2 vct)
{
	ft_putdouble(vct.x);
	ft_putchar(' ');
	ft_putdouble(vct.y);
}

void		fvct2_msg(char *msg, t_fvct2 vct)
{
	ft_putstr(msg);
	ft_putstr(" : ");
	fvct2_print(vct);
	ft_putchar('\n');
}

void		fvct3_print(t_fvct3 vector)
{
	ft_putstr(" .x ");
	ft_putdouble(vector.x);
	ft_putstr(" .y ");
	ft_putdouble(vector.y);
	ft_putstr(" .z ");
	ft_putdouble(vector.z);
}

void		fvct3_msg(char *msg, t_fvct3 vector)
{
	ft_putstr(msg);
	ft_putstr(" : ");
	fvct3_print(vector);
	ft_putchar('\n');
}