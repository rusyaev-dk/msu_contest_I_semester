#include <stdio.h>
#include <stdlib.h>
//#include <limits.h>

int read_from_file(const char* filename, unsigned long long int* decimal)
{
    FILE* fin;
    fin = fopen(filename, "r");
    if (fin)
    {
        if (fscanf(fin, "%llu", decimal) > 0)
        {
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

int is_even(unsigned long long int decimal)
{
    int counter = 0, i = 0;
    while (decimal)
    {
        if (decimal & 1)
        {
            counter++;
        }
        decimal >>= 1;  // целочисленное деление на 2 (побитовый сдвиг влево на 1 позицию)
    }
    if (counter % 2 == 0)
    {
        return 0;
    }
    return 1;
    //return counter % 2
}

int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        int read_err, write_err;
        unsigned long long int decimal;
        read_err = read_from_file(argv[1], &decimal);
        if (read_err == 0)
        {   
            write_err = write_to_file(argv[2], is_even(decimal));
        }
        else
        {
            write_err = write_to_file(argv[2], 0);
        }
        if (write_err != 0)
        {
            return -2;
        }
        return 0;
    }
	return -1;
}