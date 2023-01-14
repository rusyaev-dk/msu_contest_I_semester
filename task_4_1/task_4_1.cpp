#include <stdlib.h>
#include <stdio.h>

int read_from_file(const char* filename, double** arr, int* arr_size)
{
	FILE* fin;
	fin = fopen(filename, "r");
	if (fin)
	{
		if (fscanf(fin, "%d", arr_size) > 0)
		{
			*arr = (double*)malloc(sizeof(double) * (*arr_size));
			int i = 0;
			while ((i < *arr_size) && (fscanf(fin, "%lf", (*arr) + i) > 0))
			{
				i++;
			}
			if (i == 0)
			{
				fclose(fin);
				free(*arr);
				return -3;
			}
			else if (i < *arr_size)
			{
				*arr_size = i;
				*arr = (double*)realloc(*arr, sizeof(double) * (*arr_size));
			}
			fclose(fin);
			return 0;
		}
		fclose(fin);
		return -2;
	}
	return -1;
}

int write_to_file(const char* filename, double* arr, int arr_size)
{
	FILE* fout;
	fout = fopen(filename, "w");
	if (fout)
	{
		fprintf(fout, "%d ", arr_size);
		if (arr)
		{
			for (int i = 0; i < arr_size; i++)
			{
				fprintf(fout, "%lf ", arr[i]);
			}
		}
		fclose(fout);
		return 0;
	}
	else
	{
		return -1;
	}
}

void exchange_sort(double* arr, int arr_size)
{
	double buffer;
	for (int i = 0; i < arr_size - 1; i++)
	{
		for (int j = i + 1; j < arr_size; j++)
		{
			if (arr[j] < arr[i])
			{
				buffer = arr[j];
				arr[j] = arr[i];
				arr[i] = buffer;
			}
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		double* arr; int arr_size, read_err, write_err;
		read_err = read_from_file(argv[1], &arr, &arr_size);
		if (read_err == 0)
		{
			exchange_sort(arr, arr_size);
			write_err = write_to_file(argv[2], arr, arr_size);
			free(arr);
		}
		else if (read_err == -2)
		{
			write_err = write_to_file(argv[2], NULL, 0);
		}
		else if (read_err == -3)
		{
			write_err = write_to_file(argv[2], NULL, 0);
		}
		else
		{
			return -2;
		}

		if (write_err == 0)
		{
			return 0;
		}
	}
	return -1;
}
