#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define epsilon 0.000000000001

int read_from_file(const char* filename, double** array, int* array_size)
{
	FILE* fin;
	fin = fopen(filename, "r");
	if (fin)
	{
		if (fscanf(fin, "%d", array_size) > 0)
		{
			*array = (double*)malloc(sizeof(double) * (*array_size));
			int i = 0;
			while ((i < *array_size) && (fscanf(fin, "%lf", (*array) + i) > 0))
			{
				i++;
			}
			if (i == 0)
			{
				fclose(fin);
				return -3;
			}
			else if (i < *array_size)
			{
				*array_size = i;
				*array = (double*)realloc(*array, sizeof(double) * (*array_size));
			}
			fclose(fin);
			return 0;
		}
		fclose(fin);
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
		fprintf(fout, "%d ", result);
		fclose(fout);
		return 0;
	}
	else
	{
		return -1;
	}
}

int check_symmetry(double* array, int array_size)
{
	for (int i = 0; i < array_size/2; i++) 
	{	
		if (fabs(array[i] - array[array_size - 1 - i]) > epsilon)
		{	
			return 0;
		}
	}
	return 1;
}

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		double* array; int array_size = 0;
		int read_err = read_from_file(argv[1], &array, &array_size), write_err;
		if (read_err == 0)
		{
			write_err = write_to_file(argv[2], check_symmetry(array, array_size));
			free(array);
		}
		else if (read_err == -3)
		{
			write_err = write_to_file(argv[2], 1);
			free(array);
		}
		else if (read_err == -2)
		{
			write_err = write_to_file(argv[2], 0);
		}
		else
		{
			write_err = write_to_file(argv[2], 0);
		}
		
		if (write_err != 0)
		{
			return -1;
		}
	}
	return 0;
}