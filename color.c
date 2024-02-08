#include "fdf.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

int	index_of(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}

int	in_string(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (1);
}

int	hex_to_int(char *s)
{
	char	*hex;
	int		res;
	int		i;

	res = 0;
	hex = "0123456789abcdef";
	i = 0;
	while (s[i])
	{
		res = res * 16 + index_of(hex, ft_tolower(s[i]));
		i++;
	}
	return (res);
}

int	get_color(char *s, int base_color)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ',')
		i++;
	if (!s[i])
		return (base_color);
	return (hex_to_int(s + i + 2));
}
