#include <stdio.h>
#include <stdlib.h>

/*
    How I personally like to define structs - I use a typedef and give it a name at the bottom.
    In this case 'image' as this means I don't need to use 'struct' all over the code which can cause
    issues when you're using pointers.

    Note that now in my code, 'image' and 'struct __Image' are two separate things, so you can't mix and match.
*/
typedef struct __Image
{
    int **pixel_data;
    int height;
    int width;
    char magic_number[2];
    int maxgrey;
} image;

/*
    This is how you allocate a 2D array - height first, then width.
*/
int allocate_image(image *img)
{
    img->pixel_data = malloc(img->height * sizeof(int));
    for (int i = 0; i < img->height; i++)
    {
        img->pixel_data[i] = malloc(img->width * sizeof(int));
    }
    if (!img->pixel_data)
    {
        printf("Error: malloc failed\n");
        return 1;
    }
    return 0;
}

int read_header(FILE *f, image *img)
{
    int check = fscanf(f, "%c%c ", &img->magic_number[0], &img->magic_number[1]);
    if (check - 2)
    {
        printf("Error: bad MN\n");
        return 1;
    }

    check = fscanf(f, "%d %d", &img->width, &img->height);
    if (check - 2 ||
        img->width > 10000 ||
        img->width < 1 ||
        img->height > 10000 ||
        img->width < 1)
    {
        printf("Error: bad dims\n");
        return 1;
    }

    check = fscanf(f, "%d", &img->maxgrey);
    if (check - 1)
    {
        printf("Error: bad max grey\n");
        return 1;
    }

    return 0;
}

int read_pixels(FILE *f, image *img)
{
    for (int i = 0; i < img->height; i++)
    {
        for (int j = 0; j < img->width; j++)
        {
            int check = fscanf(f, "%d", &img->pixel_data[i][j]);
            if (check - 1 || img->pixel_data[i][j] < 0 || img->pixel_data[i][j] > img->maxgrey)
            {
                printf("Error: bad pixel data\n");
                return 1;
            }
        }
    }
    return 0;
}

/*
    We want to avoid memory leaks, so we always make sure we tidy up anything which has been dynamically allocated.

    It's standard to write a function to do this because you need to do it every time you exit the program.

*/
void free_image(image *img) {
    
    // always check it isn't already null - you will segfault.
    if (img == NULL) {
        return;
    }

    if (img->pixel_data != NULL) {
        for (int i = 0; i < img->height; i++) {
            free(img->pixel_data[i]);
            // we set each pointer to NULL after freeing
            img->pixel_data[i] = NULL;
        }

        // Free array of row pointers
        free(img->pixel_data);
        img->pixel_data = NULL;
    }

    // and finally free the image pointer itself
    free(img);
}

int main(int argc, char *argv[])
{
    if (argc - 2)
    {
        printf("Usage: ./pgmCheck <filename>\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input)
    {
        printf("Error: Bad filename\n");
        return 1;
    }

    /*
        This is how we initialise a pointer to a struct - in this case, an image.

        This gives you a pointer but also creates space in memory for the image struct
    */
    image *image1 = malloc(sizeof(image));

    int check = read_header(input, image1);
    if (check)
    {
        // after this point, we should be freeing because at least one thing has been dynamically allocated.
        free_image(image1);
        return 1;
    }

    check = allocate_image(image1);
    if (check)
    {
        free_image(image1);
        return 1;
    }

    check = read_pixels(input, image1);
    if (check)
    {
        free_image(image1);
        return 1;
    }

    
    // if it got this far, then the image is probably valid and we can print, free and exit.
    printf("Image valid.\n");
    free_image(image1);
    return 0;
}