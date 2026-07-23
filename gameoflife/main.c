#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



int     if_nighbors(int width, int hieght, int map[hieght][width], int x, int y)
{
    int count = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = - 1; j < 2; j++)
        {
            if (j == 0 && i == 0)
                continue;
            int pos_x = x + j;
            int pos_y = i + y;

            if ((pos_x >= 0 && pos_x < width) && (pos_y >= 0 && pos_y < hieght))
            {
                if (map[pos_y][pos_x] == 1)
                    count++;
            }
        }
    }
    return (count);
}




void    simulation(int width, int hieght, int map[hieght][width], int temp[hieght][width])
{
    int count;
    for (int i = 0; i < hieght; i++)
    {
        for (int j = 0; j < width; j++)
        {
            count = if_nighbors(width, hieght, map, j, i);
            temp[i][j] = (count == 3 || (map[i][j] && count == 2));
        }
    }
}


int main(int arc, char **arv)
{
    if (arc < 4)
        return (1);

    int width = atoi(arv[1]);
    int hieght = atoi(arv[2]);
    int iterator = atoi(arv[3]);

    int map[hieght][width];
    int temp[hieght][width];
    memset(temp, 0, sizeof(temp));
    memset(map, 0, sizeof(map));
    char    c;
    int     y = 0;
    int     x = 0;
    int     is_pen = 0;

    while (read(0, &c, 1) > 0)
    {
        if (c == 'w' && y > 0) y--;
        else if (c == 's' && y < hieght - 1) y++;
        else if (c == 'd' && x < width - 1) x++;
        else if (c == 'a' && x > 0) x--;
        else if (c == 'x') is_pen = !is_pen;
        if (is_pen)
            map[y][x] = is_pen;
    }


    while (iterator)
    {
        simulation(width, hieght, map, temp);
        memcpy(map, temp, sizeof(map));
        iterator --;
    }



    for (int    i = 0; i < hieght; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (map[i][j] == 1)
                printf("%c", 'o');
            else
                printf (" ");
        }
        printf ("\n");
    }
}