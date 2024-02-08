#include "fdf.h"

t_point	*create_border(double x, double y)
{
	t_point	*p;

	p = malloc(sizeof(t_point));
	if (!p)
		return (NULL);
	p->x = x;
	p->y = y;
	return (p);
}

t_point	*min_border(t_matrix *mat, double xmin, double ymin)
{
	int		i;
	int		j;
	t_point	*p;

	j = -1;
	while (++j < mat->y)
	{
		i = -1;
		while (++i < mat->x)
		{
			if ((i - j) * cos(ANG) < xmin)
				xmin = (i - j) * cos(ANG);
			if ((i + j) * sin(ANG) - ft_atoi(mat->rows[j][i]) *
				mat->z_scale < ymin)
				ymin = (i + j) * sin(ANG)
					- ft_atoi(mat->rows[j][i]) * mat->z_scale;
		}
	}
	p = create_border(xmin, ymin);
	if (!p)
		return (NULL);
	return (p);
}

t_point	*max_border(t_matrix *mat, double xmax, double ymax)
{
	int		i;
	int		j;
	t_point	*p;

	j = -1;
	xmax = 0;
	ymax = -1 * ft_atoi(mat->rows[0][0]) * mat->z_scale;
	while (++j < mat->y)
	{
		i = -1;
		while (++i < mat->x)
		{
			if ((i - j) * cos(ANG) > xmax)
				xmax = (i - j) * cos(ANG);
			if ((i + j) * sin(ANG) - ft_atoi(mat->rows[j][i])
				* mat->z_scale > ymax)
				ymax = (i + j) * sin(ANG) - ft_atoi(mat->rows[j][i])
					* mat->z_scale;
		}
	}
	p = create_border(xmax, ymax);
	if (!p)
		return (NULL);
	return (p);
}

int	splitrowlen(char **splitrow)
{
	int	i;

	i = -1;
	while (splitrow[++i])
		;
	return (i);
}

t_matrix	*make_matrix(int fd)
{
	char		*row;
	char		**splitrow;
	t_matrix	*mat;

	mat = init_matrix();
	if (!mat)
		return (NULL);
	row = get_next_line(fd);
	while (row)
	{
		splitrow = ft_split(row, ' ');
		free(row);
		if (!splitrow)
			return (destroy_matrix(mat));
		if (!mat->x)
			mat->x = splitrowlen(splitrow);
		if (splitrowlen(splitrow) != mat->x)
		{
			destroy_matrix(mat);
			return (destroy_rows(&splitrow, 1));
		}
		mat->rows[mat->y++] = splitrow;
		row = get_next_line(fd);
	}
	return (mat);
}
