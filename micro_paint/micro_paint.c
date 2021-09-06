#include "micro_paint.h"

int canva_dime_check(FILE *file, t_canva *canva_dim)
{
	int ret;
	char c;

	ret = fscanf(file, "%d %d %c\n", &canva_dim->width, &canva_dim->height, &canva_dim->background);
	if(ret != 3)
		return(0);
	if(canva_dim->width < 0 && canva_dim->width > 300 
	&& canva_dim->height < 0 && canva_dim->height > 300)
		return (0);
	if(ret == -1)
		return (0);
	return (1);
}

int		shape_dim_check(t_shape *shape_dim, FILE *file)
{
	int ret = fscanf(file, "%c %f %f %f %f %c", &shape_dim->type, &shape_dim->x, &shape_dim->y, &shape_dim->width, 
	&shape_dim->height, &shape_dim->background);
	if(shape_dim->width < 0.0 && shape_dim->height < 0.0)
	    return (0);
	if(shape_dim->x > shape_dim->width && shape_dim->y > shape_dim->height)
		return (0);
	if(ret != 6)
		return (0);
	if(ret == -1)
		return (0);
	return (1);
}

char    **background_draw(FILE *file, t_canva canva_dim)
{
	int i = 0;
	int j = 0;
	int k;
	char **buffer;
	int check;

	buffer = malloc(sizeof(*buffer) * canva_dim.height + 1);
	for (k = 0; k < canva_dim.height; k++)
		buffer[k] = malloc(sizeof(**buffer) * canva_dim.width);
	buffer[k] = 0;
	for(i = 0; i < canva_dim.height; i++)
	{
		for(j = 0; j < canva_dim.width; j++)
		{
			buffer[i][j] = canva_dim.background;
		}
	}
	return (buffer);
}

void	shape_draw(char **buffer, t_shape shape_dim)
{
	int	width;
	int	height;
	int	x;
	int	y;

	width = shape_dim.width;
	height = shape_dim.height;
	x = shape_dim.x;
	y = shape_dim.y;

	if(shape_dim.type == 'R')
	{
		for(int i = y; i < y + height; i++)
		{
			for(int j = x; j < x + width; j++)
			{
				buffer[i][j] = shape_dim.background;
			}
		}
	}
	if(shape_dim.type == 'r')
	{
		for(int i = y; i < y + height; i++)
		{
			for(int j = x; j < x + width; j++)
			{
				if((j == x || j == x + width - 1))
					buffer[i][j] = shape_dim.background;
				if(i == y || i == y + width - 1)
					buffer[i][j] = shape_dim.background;
			}
		}
	}
}

int	final_draw_check(t_shape *shape_dim, FILE *file, char **buffer, t_canva canva_dim)
{
	int ret;
	while((ret = fscanf(file, "%c %f %f %f %f %c\n", &shape_dim->type, &shape_dim->x, &shape_dim->y, &shape_dim->width, 
	&shape_dim->height, &shape_dim->background)) == 6)
	{
		if(shape_dim->width < 0.0 && shape_dim->height < 0.0)
			return (0);
		if(shape_dim->x > shape_dim->width && shape_dim->y > shape_dim->height)
			return (0);
		if(ret == -1)
			return (0);
		shape_draw(buffer, *shape_dim);
		for(int i = 0; i < canva_dim.height; i++)
		{
			for(int j = 0; j < canva_dim.width; j++)
				printf("%c", buffer[i][j]);
			printf("\n");
		}
		printf("\nstop Wtf\n");
	}
	return (1);
}

int main(int argc, char **argv)
{
	FILE    *file;
	t_canva canva_dim;
	t_shape shape_dim;
	char    **buffer;
	char	**shape;

	if(argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	else if(!(file = fopen(argv[1], "r")))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	else if(!canva_dime_check(file, &canva_dim))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	buffer = background_draw(file, canva_dim);
	if(!final_draw_check(&shape_dim, file, buffer, canva_dim))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	// printf("%c \n", shape_dim.type);
	// printf("%f \n", shape_dim.x);
	// printf("%f \n", shape_dim.y);
	// printf("%f \n", shape_dim.width);
	// printf("%f \n", shape_dim.height);
	// printf("%c \n", shape_dim.background);
	// printf("|------------------------------------------|\n");
	// for(int i = 0; i < canva_dim.height; i++)
	// {
	// 	for(int j = 0; j < canva_dim.width; j++)
	// 		printf("%c", buffer[i][j]);
	// 	printf("\n");
	// }
	// else if(shape_dim.width < 0.0 && shape_dim.height < 0.0)
	//     return (0);
	return (0);
}