#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define points_distance(x1, x2, y1, y2) sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))

typedef struct Point
{
    double x, y;
} Point;

typedef struct Cirle
{
    struct Point center;
    double R;
} Circle;

int growing_circles(Point* points_arr)
{
    //double distance = points_distance(points_arr[0].x, points_arr[1].x, points_arr[0].y, points_arr[1].y);
    return 0;
}

int read_from_file(const char* filename, Point** points_arr, int* points_quantity)
{
	FILE* fin;
	fin = fopen(filename, "r");
	if (fin)
	{	   
        if (fscanf(fin, "%d", points_quantity) > 0)
        {
            *points_arr = (Point*)malloc(sizeof(Point) * (*points_quantity));
            Point scanfed_point;
            double x, y;
            for (int i = 0; i < *points_quantity; i++)
            {
                if (fscanf(fin, "%lf %lf", &x, &y) == 2)
                {
                    scanfed_point.x = x;
                    scanfed_point.y = y;
                    (*points_arr)[i] = scanfed_point;
                }
                else
                {
                    fclose(fin);
                    return -3;
                }
            }
            fclose(fin);
            return 0;
        }
       
        fclose(fin);
        return -2;
	}
	return -1;
}

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		int read_err, write_err, points_quantity;
		Point* points_arr;
		read_err = read_from_file(argv[1], &points_arr, &points_quantity);
		if (read_err == 0)
		{	
			return 0;
		}		

		if (write_err == 0)
		{
			return 0;
		}
	}
	return -1;
}
