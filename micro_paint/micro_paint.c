#include "micro_paint.h"

int canva_dime_check(FILE *file, t_canva *canva_dim)
{
	int ret;

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

char    **background_draw(t_canva canva_dim)
{
	int i = 0;
	int j = 0;
	int k;
	char **buffer;

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

void	shape_draw(char **buffer, t_shape shape_dim, t_canva canva)
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
		for(int i = y; i <= y + height; i++)
		{
			for(int j = x; j <= x + width; j++)
			{
				if(i < canva.height && j < canva.width && i >= 0 && j >= 0)
					buffer[i][j] = shape_dim.background;
			}
		}
	}
	if(shape_dim.type == 'r')
	{
		for(int i = y; i <= y + height; i++)
		{
			for(int j = x; j <= x + width; j++)
			{
				if(i < canva.height && j < canva.width  && i >= 0 && j >= 0)
				{
					if ((j == x || j == x + width))
						buffer[i][j] = shape_dim.background;
					if (i == y || i == y + height)
						buffer[i][j] = shape_dim.background;
				}
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
		if(shape_dim->type != 'R' || shape_dim->type != 'r')
			return (0);
		shape_draw(buffer, *shape_dim, canva_dim);
	}
	if(ret == -1)
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	FILE    *file;
	t_canva canva_dim;
	t_shape shape_dim;
	char    **buffer;

	if(argc != 2)
	{
		write(1, "Error: argument\n", 16);
		return (1);
	}
	if(!(file = fopen(argv[1], "r")))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	if(!canva_dime_check(file, &canva_dim))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	buffer = background_draw(canva_dim);
	if(!final_draw_check(&shape_dim, file, buffer, canva_dim))
	{
		write(1, "Error: Operation file corrupted\n", 32);
		return (1);
	}
	for(int i = 0; i < canva_dim.height; i++)
	{
		for(int j = 0; j < canva_dim.width; j++)
			printf("%c", buffer[i][j]);
		printf("\n");
	}
	return (0);
}