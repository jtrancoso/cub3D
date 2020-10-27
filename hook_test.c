#include "mlx/mlx.h"
#include <stdio.h>

typedef struct		s_vars 
{
	void	*mlx;
	void	*win;
}					t_vars;


int		key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		ft_close(vars);
	}
	return(0);
}

int hola(void)
{
	printf("hola\n");
	return(0);
}

int		ft_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return(0);
}

int		mouse_hook(int mousecode, t_vars *vars)
{
	printf("mouse: %i\n", mousecode);
	return(0);
}
int main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "ete sech");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 17, 0L, ft_close, &vars);
	mlx_hook(vars.win, 25, 0L, hola, &vars);
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
}