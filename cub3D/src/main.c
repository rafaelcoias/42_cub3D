/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvicente <mvicente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:10:12 by mvicente          #+#    #+#             */
/*   Updated: 2023/07/06 16:19:19 by mvicente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	vars_init(t_data *data)
{
	int	i;

	i = 0;
	data->mlx = 0;
	data->win = 0;
	data->img.offset_r = -2;
	data->img.offset_i = 2;
	data->angle_d = 90;
	data->angle_r = (data->angle_d * PI) / 180;
	data->distance = 0;
	data->height = 0;
	data->start = 0;
	data->end = 0;
	data->hit = 0;
	data->step_x = 0;
	data->step_y = 0;
	data->side = -1;
	data->letter = 0;
	data->textures = malloc(sizeof(char) * 4);
	data->colors = malloc(sizeof(int) * 2);
	while (i != 4)
		data->textures[i++] = 0;
	i = 0;
	while (i != 2)
		data->colors[i++] = 0;
}

int	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	calculations(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	return (1);
}

void	get_dir(t_data *data)
{
	if (data->letter == 'N')
	{
		data->dirX = 0;
		data->dirY = 1;
		data->planeX = 0.66;
		data->planeY = 0;
	}
	else if (data->letter == 'S')
	{
		data->dirX = 0;
		data->dirY = -1;
		data->planeX = -0.66;
		data->planeY = 0;
	}
	else if (data->letter == 'E')
	{
		data->dirX = 1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = -0.66;
	}
	else if (data->letter == 'O')
	{
		data->dirX = -1;
		data->dirY = 0;
		data->planeX = 0;
		data->planeY = 0.66;
	}
	data->colors = malloc(sizeof(int) * 2);
	data->colors[0] = get_rgb(255, 255, 255);
	data->colors[1] = get_rgb(128, 128, 128);
}

int	main(int argc, char **argv)
{
	t_data	data;

	vars_init(&data);
	parse_all(&data, argc, argv[1]);
	get_dir(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	data.img.mlx_img = mlx_new_image(data.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 17, exit_cub, &data);
	mlx_loop(data.mlx);
}
