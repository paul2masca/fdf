#include "fdf.h"

void	ft_free(char **res)
{
	int	i;

	i = -1;
	while (res[++i])
		free(res[i]);
	free(res);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				final_value;
	long long int	nbr;

	nbr = 0;
	i = 0;
	final_value = 1;
	while (str[i] && ft_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			final_value = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
		if (nbr < -INT_MIN && final_value == -1)
			return (0);
		if (nbr > INT_MAX && final_value == 1)
			return (-1);
	}
	return (nbr * final_value);
}

void	*destroy_rows(char ***rows, int y)
{
	int	i;

	i = -1;
	if (!rows)
		return (NULL);
	while (++i < y)
		ft_free(rows[i]);
	free(rows);
	rows = NULL;
	return (NULL);
}

void	*destroy_matrix(t_matrix *mat)
{
	destroy_rows(mat->rows, mat->y);
	mat->rows = NULL;
	free(mat);
	return (NULL);
}

t_matrix	*init_matrix(void)
{
	t_matrix	*mat;

	mat = malloc(sizeof(t_matrix));
	if (!mat)
		return (NULL);
	mat->rows = malloc(MAX_Y * sizeof(char **));
	mat->z_scale = BASE_Z_SCALE;
	mat->x = 0;
	mat->y = 0;
	return (mat);
}
