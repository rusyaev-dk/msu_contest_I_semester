#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define epsilon 10E-9

typedef struct Point
{
	double x, y;
} Point;

typedef struct Vector
{
	double x, y;
} Vector;

Vector create_vector(Point pt_1, Point pt_2)
{
    Vector vector;
    vector.x = pt_2.x - pt_1.x;
    vector.y = pt_2.y - pt_1.y;
    return vector;
}

int are_equal(double num_1, double num_2)
{
	if (fabs(num_1 - num_2) < epsilon)
	{
		return 1;
	}
	return 0;
}

double vectors_scalar_product(Vector vec_1, Vector vec_2)
{
	return vec_1.x * vec_2.y - vec_2.x * vec_1.y;
}

int vectors_turn_direction(Vector vec_1, Vector vec_2)
{
	double product = vectors_scalar_product(vec_1, vec_2);
	if (product < 0)
	{
		return -1;
	}
	else if (are_equal(product, 0))
	{
		return 0;
	}
	return 1;
}

int is_convex(Point* points_arr, int points_quantity)
{	
	if (points_quantity < 3)
	{
		return 0;
	}

	Vector vec_1, vec_2;
	int zero_turn_counter = 0, reference_turn = 0, cyclic_turn;

	for (int i = 0; i < points_quantity - 2; i++)
	{
		vec_1 = create_vector(points_arr[i], points_arr[i + 1]);
		vec_2 = create_vector(points_arr[i + 1], points_arr[i + 2]);
		if (reference_turn == 0)
		{	
			reference_turn = vectors_turn_direction(vec_1, vec_2);
			continue;
		}
		cyclic_turn = vectors_turn_direction(vec_1, vec_2);	
		if (cyclic_turn == 0)
		{	
			zero_turn_counter++;
		}
		else if (cyclic_turn != reference_turn)
		{	
			return 0;
		}	
	}
	vec_1 = create_vector(points_arr[points_quantity - 2], points_arr[0]);
	vec_1 = create_vector(points_arr[0], points_arr[1]);
	cyclic_turn = vectors_turn_direction(vec_2, vec_1);

	if (cyclic_turn != reference_turn)
	{
		return 0;
	}

	if (zero_turn_counter == points_quantity - 2)
	{
		return 0;
	}
	return 1;
}

int read_from_file(const char* filename, Point** points_arr, int* points_quantity)
{
	FILE* fin;
	fin = fopen(filename, "r");
	if (fin)
	{	
		if (fscanf(fin, "%d", points_quantity) > 0)
		{	
			*points_quantity = abs(*points_quantity);
			*points_arr = (Point*)malloc(sizeof(Point) * (*points_quantity + 1));
			Point scanfed_point;
			int i;
			while ((i < *points_quantity) && fscanf(fin, "%lf %lf", &scanfed_point.x, &scanfed_point.y) == 2)
			{
				(*points_arr)[i] = scanfed_point;
				i++;
			}
			if (i != 0)
			{
				(*points_arr)[i] = (*points_arr)[0];
				i++;
			}
			else if (i == 0)
			{
				free(*points_arr);
				fclose(fin);
				return -3;
			}
			
			if (i < *points_quantity)
			{
				*points_arr = (Point*)realloc(*points_arr, i);
			}
			
			fclose(fin);
			*points_quantity = i;
			return 0;
		}
		return -2;
	}
	return -1;
}

int write_to_file(const char* filename, int result)
{
	FILE* fout;
	fout = fopen(filename, "w");
	if (fout)
	{
		fprintf(fout, "%d", result);
		fclose(fout);
		return 0;
	}
	return -1;
}

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		int read_err, write_err, points_quantity = 0;
		Point* points_arr;
		read_err = read_from_file(argv[1], &points_arr, &points_quantity);
		if (read_err == 0)
		{	
			write_err = write_to_file(argv[2], is_convex(points_arr, points_quantity));
			free(points_arr);
		}		
		else
		{
			write_err = write_to_file(argv[2], 0);
		}

		if (write_err == 0)
		{
			return 0;
		}
	}
	return -1;
}
