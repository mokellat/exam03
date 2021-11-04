#include "mini_paint.h"

int canva_dime_check(FILE *file, t_canva *canva_dim)
{
	int ret;

	ret = fscanf(file, "%d %d %c\n", &canva_dim->width, &canva_dim->height, &canva_dim->background);
	if(ret != 3)
		return(0);
	if(canva_dim->width < 0 || canva_dim->width > 300 
	|| canva_dim->height < 0 || canva_dim->height > 300)
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
	int y = 0;
	int x;
	float distance;

	if(shape_dim.type == 'C')
	{
		while (y < canva.height)
		{
			x = 0;
			while (x < canva.width)
			{
				distance = sqrtf(powf(x - shape_dim.x, 2.0) + powf(y - shape_dim.y, 2.0));
				if (distance <= shape_dim.radius)
				{
					buffer[y][x] = shape_dim.background;
				} 
				x++;
			}
			y++;
		}
	}
	if(shape_dim.type == 'c')
	{
		while (y < canva.height)
		{
			x = 0;
			while (x < canva.width)
			{
				distance = sqrtf(powf(x - shape_dim.x, 2.0) + powf(y - shape_dim.y, 2.0));
				if (distance <= shape_dim.radius)
				{
					if (shape_dim.radius - distance < 1.0)
					{
						buffer[y][x] = shape_dim.background;
					} 
				}
				x++;
			}
			y++;
		}
	}
}

int	final_draw_check(t_shape *shape_dim, FILE *file, char **buffer, t_canva canva_dim)
{
	int ret;
	
	while((ret = fscanf(file, "%c %f %f %f %c\n", &shape_dim->type, &shape_dim->x, &shape_dim->y, &shape_dim->radius, 
		&shape_dim->background)) == 5)
	{
		if(shape_dim->radius <= 0)
			return (0);
		if(shape_dim->type != 'C' && shape_dim->type != 'c')
			return (0);
		shape_draw(buffer, *shape_dim, canva_dim);
	}
	if(ret != -1)
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