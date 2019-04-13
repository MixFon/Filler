
#include "visual.h"

int	print_line(int x0, int x1, int y0, int y1)
{
	int		dx;
	int		dy;
	int		y;
	int		diry;
	double	er; 
	double	der; 

	dx = ABS((x1 - x0));
	dy = ABS((y1 - y0));
	der = dy;
	er = 0;
	y = y0;
	diry = y1 - y0;
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	while (x0 != x1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y, 100);
		er = er + der;
		if (2 * er >= dx)
		{
			y = y + diry;
			er = er - dx;
		}
		x0 > x1 ? x0-- : x0++;
	}
	return (0);
}

/*
** Print rectengle whith coordinates (x, y).
*/

void	print_rectengle(int x, int y, int heith, int width, int color)
{
	int i;
	int j;

	i = x;
	while (++i < heith + x)
	{
		j = y - 1;
		while (++j < width + y)
			mlx_pixel_put(mlx_ptr, win_ptr, i, j, color);
	}
}

/*
** Print matrics of rectengle. Starn coordinate matrics (x, y).
** Count lines - row. Count colloms - col.
*/

void	print_mat(int x, int y, int row, int col)
{
	int i;
	int j;
	int x_it;
	int y_it;
	void	*img_ptr;
	int		heith;
	int		width;

	i = -1;
	x_it = x;
	y_it = y;
	img_ptr = mlx_xpm_file_to_image(mlx_ptr, "./1.xpm", &heith, &width);
	while (++i < row)
	{
		j = -1;
		while (++j < col)
		{
			mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, x_it, y_it);
			//print_rectengle(x_it, y_it, 10, 10, 90);
			y_it += 30;
		}
		y_it = y; 
		x_it += 30;
	}	
}

int		main(void)
{
	int		i;
	int		heith;
	int		width;
	void	*img_back;

	i = -1;
	heith = 3;
	width = 5;
	mlx_ptr = mlx_init();
	img_back = mlx_xpm_file_to_image(mlx_ptr, "./background.xpm", &heith, &width);
	printf(" h = %d, w = %d\n", heith, width);
	printf(" h = %d, w = %d\n", heith, width);
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEITH, "Filler");
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_back, 0, 0);
	print_mat(10, 10, 10, 10);
//	while (++i < 80)
//		mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr2, 250 + i, 150 + i);
	mlx_loop(mlx_ptr);
}
/*
 *
int	print_hello(int key, void *par, void *par2)
{
	char *str = "Hello";
	static int i = 10;

	mlx_string_put(mlx_ptr, win_ptr, 10 + i, 200 - i, 0xFFFFFF, str);
	i += 10;
	printf("%d\n", ABS( (-3 + 1)));
	puts("Hello");
	return (0);
}
 */
