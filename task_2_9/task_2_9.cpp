#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define epsilon 0.0000000001

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
        else
        {
            fclose(fin);
            return -2;
        }
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

void edit_array(double* arr, int arr_size)
{   
    if (arr_size == 1)
    {
        return;
    }
    double buffer; int c, h, k, positive_counter;
    for (int i = 0; i < arr_size; i++)
    {
        if (arr[i] < 0)
        {   
            positive_counter = 0; c = i;
            for (int a = i + 1; a < arr_size; a++)
            {
                if (arr[a] > 0 || fabs(arr[a]) < epsilon)
                {
                    positive_counter++;
                }
                if (arr[c] < 0)
                {
                    c++;
                }
            }
            if (positive_counter == 0)
            {
                return;
            }
            k = c;
            for (h = 0; h < c - i; h++)
            {                   
                buffer = arr[k];
                arr[k] = arr[k - 1];
                arr[k - 1] = buffer;
                k--;
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
            edit_array(arr, arr_size);
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