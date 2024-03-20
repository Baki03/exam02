#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	ft_printchar(char c)
{
	write (1, &c, 1);
	return (1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_printstr(char	*str)
{
	int	len;

	len = 0;
	if (str == NULL)
	{
		write (1, "(null)", 6);
		return (6);
	}
	while (str[len])
	{
		write(1, &str[len], 1);
		len++;
	}
	return (len);
}

int	find_len(long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	if (nb == 0)
		return (1);
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*nbr;

	nb = n;
	i = find_len(nb);
	nbr = malloc(sizeof(char) * (i + 1));
	if (!nbr)
		return (NULL);
	nbr[i] = '\0';
	i--;
	if (nb < 0)
	{
		nbr[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		nbr[0] = '0';
	while (nb > 0)
	{
		nbr[i--] = '0' + (nb % 10);
		nb /= 10;
	}
	return (nbr);
}

int	ft_printnbr(int nb)
{
	char	*nbr;
	int		len;

	len = 0;
	nbr = ft_itoa(nb);
	len = ft_printstr(nbr);
	free(nbr);
	return (len);
}

int	find_len_hexa(unsigned int nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

void	ft_puthexa(unsigned int nb)
{
	if (nb >= 16)
	{
		ft_puthexa(nb / 16);
		ft_puthexa(nb % 16);
	}
	else
	{
		if (nb <= 9)
		{
			ft_putchar(nb + '0');
		}
		else
		{
			ft_putchar(nb - 10 + 'a');
		}
	}
}

int	ft_printhexa(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
	{
		write(1, "0", 1);
		len += 1;
	}
	else
	{
		len += find_len_hexa(nb);
		ft_puthexa(nb);
	}
	return (len);
}



int	after_percent(const char format, va_list arg)
{
	int	len;

	len = 0;
	if (format == 'd')
		len += ft_printnbr(va_arg(arg, int));
	if (format == 's')
		len += ft_printstr(va_arg(arg, char *));
	if (format == 'x')
		len += ft_printhexa(va_arg(arg, unsigned int));
	if (format == '%')
		len += ft_printpercent();
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		len;
	int		i;

	va_start(arg, format);
	len = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			len += after_percent(format[i + 1], arg);
			i++;
		}
		else
			len += ft_printchar(format[i]);
		i++;
	}
	va_end(arg);
	return (len);
}
