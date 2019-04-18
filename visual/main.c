
#include "visual.h"

void	new_map(t_vis *vis)
{
	int i;

	i = -1;
	vis->map = (char **)malloc(sizeof(char*) * (vis->row + 1));
	while (++i < vis->row)
		vis->map[i] = ft_strnew(vis->col);
	vis->map[i] = NULL;
}

/*
**  Rewrite bourd. No malloc.
*/

void	rewrite_arr(t_vis *vis)
{
	int		i;
	char	*line;

	if (vis->map == NULL)
		new_map(vis);
	i = -1;
	while (++i < vis->row)
	{
		get_next_line(0, &line);
		ft_strcpy(vis->map[i], line + 4);
		//write(2, arr[i], ft_strlen(arr[i]));
		//write(2, "\n", 1);
		//ft_printf("i = %d line {%s}\n", i, arr[i]);
		ft_strdel(&line);
	}
	vis->map[i] = NULL;
}

char	**crea_color_map(int heith, int width, const char *color)
{
	char	**map;
	int		i;
	int		j;

	map = (char **)malloc(sizeof(char *) * (heith + 3));
	map[0] = ft_multi_strdup(4, ft_itoa(heith), " ", ft_itoa(width), " 1 1 "); 
	ft_printf("s = {%s}\n", map[0]);
	map[1] = ft_multi_strdup(2, "b c #", color);
	ft_printf("s = {%s}\n", map[1]);
	i = 1;
	while (++i < heith + 2)
	{
		j = -1;
		map[i] = ft_strnew(width);
		while (++j < width)
			map[i][j] = 'b';
		ft_printf("i = %d s = {%s}\n",i,  map[i]);
	}
	map[i] = NULL;
	ft_printf("s = {%s}\n", "map[i]");
	return (map);
}

void	colc_size_squre(t_vis *vis)
{
	if (vis->col < vis->row)
	{
		vis->heith = HEITH / (vis->row + 2);
		vis->width = vis->heith;
	}
	else
	{
		vis->width = WIDTH / (vis->col + 2);
		vis->heith = vis->width;
	}

}

/*
** Init image size 10x10.
*/

int		init_image_squer(t_vis *vis)
{
	colc_size_squre(vis);
	vis->map_bourd = crea_color_map(vis->heith, vis->width, "6A4849");
	if(!(vis->img_bourd = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_bourd, &vis->heith, &vis->width)))
		return (0);
	vis->map_obd = crea_color_map(vis->heith, vis->width, "2056B6");
	if(!(vis->img_obd = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_obd, &vis->heith, &vis->width)))
		return (0);
	vis->map_obl = crea_color_map(vis->heith, vis->width, "2E94E9");
	if(!(vis->img_obl = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_obl, &vis->heith, &vis->width)))
		return (0);
	vis->map_xp = crea_color_map(vis->heith, vis->width, "FF6C98");
	if(!(vis->img_xp = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_xp, &vis->heith, &vis->width)))
		return (0);
	vis->map_xr = crea_color_map(vis->heith, vis->width, "BF2956");
	if(!(vis->img_xr = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_xr, &vis->heith, &vis->width)))
	{
		ft_printf("error image\n");
		return (0);
	}
	ft_putstr("222hello\n");
	return (1);
}

/*
** Read input. Create size bourd.Create map.
*/

int		read_input(t_vis *vis)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		//ft_printf("line1 {%s}\n", line);
		if (*line == '<')
			return (0);
		if(!ft_strncmp(line, "    0", 5))
			rewrite_arr(vis);
		if(!ft_strncmp(line, "== O fin", 8))
			exit(0);
		ft_strdel(&line);
	}
	//print_arr(vis->map);
	return (0);
}

/*
** Calculates the coordinates of the Bourd in the Centr.
** heith - heith bourd, width - width bourd.
*/

void	coor_centr(int *x, int *y, int heith, int width)
{
	*y = (HEITH / 2) - (heith / 2);
	*x = (WIDTH / 2) - (width / 2);
}

/*
** Print matrics of rectengle. Starn coordinate matrics (x, y).
** Count lines - row. Count colloms - col.
*/

int		print_bourd(t_vis *vis)
{
	int		i;
	int		j;
	int		y;
	int		x;
	int		x_it;
	int		y_it;

	i = -1;
	y = 0;
	read_input(vis);
	//ft_printf("col = %d, row = %d\n", col, row);
	coor_centr(&x, &y, vis->row * vis->heith + 1, vis->col * vis->width + 1);
	y_it = y;
	x_it = x;
	while (++i < vis->row)
	{
		j = -1;
		while (++j < vis->col)
		{
			if (vis->map[i][j] == '.')
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_bourd, x_it, y_it);
			if (vis->map[i][j] == 'X')
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_xr, x_it, y_it);
			if (vis->map[i][j] == 'x')
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_xp, x_it, y_it);
			if (vis->map[i][j] == 'O')
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_obd, x_it, y_it);
			if (vis->map[i][j] == 'o')
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_obl, x_it, y_it);
			x_it += vis->width + 1;
		}
		x_it = x; 
		y_it +=  vis->heith + 1;
	}
	//if (vis->map)
	//	dell_arr(vis->map);
	return (0);
}

/*
** Init background and menu.
*/

int		init_back(t_vis *vis)
{
	if(!(vis->img_back = mlx_xpm_file_to_image(vis->mlx_ptr,
			"./back3.xpm", &vis->heith, &vis->width)))
		return (0);
	//vis->map_back = crea_color_map(vis->heith, vis->width, "862F1D");
	/*
	if(!(vis->img_bourd = mlx_xpm_to_image(vis->mlx_ptr,
			vis->map_bourd, &vis->heith, &vis->width)))
		return (0);
		*/
	return (1);
}

void	init_image(t_vis *vis)
{
	//infill_map(vis);
	if(!(init_back(vis)))
		exit(0);
	if(!(init_image_squer(vis)))
		exit(0);
}

t_vis	*create_vis(void)
{
	t_vis	*vis;
	char	*line;

	if(!(vis = (t_vis*)malloc(sizeof(t_vis))))
		return (NULL);
	vis->heith = 0;
	vis->width = 0;
	vis->col = 0;
	vis->row= 0;
	vis->map = NULL;
	vis->mlx_ptr = mlx_init();
	vis->win_ptr = mlx_new_window(vis->mlx_ptr, WIDTH, HEITH, "Filler");
	while (get_next_line(0, &line))
	{
		if(!ft_strncmp(line, "Plateau", 7))
		{
			parsing_wh(line, &vis->col, &vis->row);
			ft_strdel(&line);
			break;
		}
		ft_strdel(&line);
	}
	//ft_printf("%d %d\n", vis->col, vis->row);
	init_image(vis);
	return (vis);
}

int		exit_key(int key, void *par)
{
	if (key == 65307)
		exit(0);
	return (0);
}

int		main(void)
{
	int		i;
	t_vis	*vis;

	if(!(vis = create_vis()))
		exit(0);
	mlx_put_image_to_window(vis->mlx_ptr, vis->win_ptr, vis->img_back, 0, 0);
	//print_bourd(vis);
	mlx_key_hook(vis->win_ptr, exit_key, (void*)0);
	mlx_loop_hook(vis->mlx_ptr, print_bourd, vis);
	mlx_loop(vis->mlx_ptr);
}

/*
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
*/
/*
** Print rectengle whith coordinates (x, y).
*/
/*
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
*/
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
