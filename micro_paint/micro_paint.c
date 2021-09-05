#include "micro_paint.h"

int draw_canva(FILE *file, t_canva *canva_dim)
{
    int ret;
    if(ret = fscanf(file, "%d %d %c", &canva_dim->width, &canva_dim->height, &canva_dim->background) != 3)
        return(0);
    return (1);
}

int main(int argc, char **argv)
{
    FILE    *file;
    t_canva canva_dim;
    t_shape shape_dim;

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
    else if(!draw_canva(file, &canva_dim))
    {
        write(1, "Error: Operation file corrupted\n", 32);
        return (1);
    }
    printf("%d \n", canva_dim.height);
    printf("%d \n", canva_dim.width);
    printf("%c \n", canva_dim.background);
    // else if(canva_dim.width < 0 && canva_dim.width > 300 
    // && canva_dim.height < 0 && canva_dim.height > 300)
    //     return (0);
    // else if(shape_dim.width < 0.0 && shape_dim.height < 0.0)
    //     return (0);
    return (0);
}