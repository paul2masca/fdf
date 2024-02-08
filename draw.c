#include "fdf.h"

void	dda(t_data *img, t_point *pixel, double dx, double dy)
{
	double	steps;
	double	x_inc;
	double	y_inc;
	int		i;

	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	i = 0;
	while (i < steps && pixel->x < (double)WINDOW_X
		&& pixel->y < (double)WINDOW_Y)
	{
		my_mlx_pixel_put(img, img->center_x + (int)round(pixel->x),
			img->center_y + (int)round(pixel->y), pixel->color);
		pixel->x += x_inc;
		pixel->y += y_inc;
		++i;
	}
}

void	draw_line(t_data *img, t_point *p1, t_point *p2)
{
	double	dx;
	double	dy;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	dda(img, p1, dx, dy);
}

void	draw_right(t_data *img, t_matrix *mat, int x, int y)
{
	t_point	*p1;
	t_point	*p2;

	if (x == mat->x - 1)
		return ;
	p1 = create_point(x * img->scale, y * img->scale, img->scale
			* ft_atoi(mat->rows[y][x]) * mat->z_scale,
			get_color(mat->rows[y][x], EGYPT_BLUE));
	if (!p1)
		return ;
	p2 = create_point((x + 1) * img->scale, y * img->scale, img->scale
			* ft_atoi(mat->rows[y][x + 1]) * mat->z_scale,
			get_color(mat->rows[y][x + 1], EGYPT_BLUE));
	if (!p2)
		return ;
	draw_line(img, p1, p2);
	free(p1);
	free(p2);
}

void	draw_down(t_data *img, t_matrix *mat, int x, int y)
{
	t_point	*p1;
	t_point	*p2;

	if (y == mat->y - 1)
		return ;
	p1 = create_point(x * img->scale, y * img->scale, img->scale
			* ft_atoi(mat->rows[y][x]) * mat->z_scale,
			get_color(mat->rows[y][x], EGYPT_BLUE));
	if (!p1)
		return ;
	p2 = create_point(x * img->scale, (y + 1) * img->scale, img->scale
			* ft_atoi(mat->rows[y + 1][x]) * mat->z_scale, get_color(mat->rows[y
				+ 1][x], EGYPT_BLUE));
	if (!p2)
		return ;
	draw_line(img, p1, p2);
	free(p1);
	free(p2);
}

void	draw_matrix(t_vars *vars, t_data img, t_matrix *mat)
{
	int	i;
	int	j;

	img.scale = find_scale(mat);
	img.center_x = find_center_x(mat, img.scale);
	img.center_y = find_center_y(mat, img.scale);
	j = -1;
	while (++j < mat->y)
	{
		i = -1;
		while (++i < mat->x)
		{
			draw_right(&img, mat, i, j);
			draw_down(&img, mat, i, j);
		}
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, img.img, 0, 0);
	vars->data.img = mlx_new_image(vars->mlx_ptr, WINDOW_X, WINDOW_Y);
	vars->data.addr = mlx_get_data_addr(vars->data.img,
			&(vars->data.bpp), &(vars->data.line_length),
			&(vars->data.endian));
}
