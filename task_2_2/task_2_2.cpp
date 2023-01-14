#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		else
		{	
			fclose(fin);
			return -2;
		}
	}
	return -1;
}

int write_to_file(const char* filename, double* array, int array_size)
{
	FILE* fout;
	fout = fopen(filename, "w");
	if (fout)
	{	
		fprintf(fout, "%d ", array_size);
		for (int i = 0; i < array_size; i++)
		{
			fprintf(fout, "%lf ", array[i]);
		}
		fclose(fout);
		return 0;
	}
	else
	{
		return -1;
	}
}

void inverse_array(double* array, int array_size) 
{	
	double buffer;
	for (int i = 0; i < array_size/2; i++)
	{
		buffer = array[i]; 
		array[i] = array[array_size - 1 - i];
		array[array_size - 1 - i] = buffer;
	}
}

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		double* array; int array_size = 0;
		int read_err = read_from_file(argv[1], &array, &array_size), write_err;
		if (read_err == 0)
		{	
			inverse_array(array, array_size);
			write_err = write_to_file(argv[2], array, array_size);
			free(array);
		}
		else
		{	
			write_err = write_to_file(argv[2], NULL, 0);
		}
		
		if (write_err != 0)
		{
			return -2;
		}
		return 0;
	}
	return -1;
}