#include <stdio.h>
#include <stdlib.h>

void generate_transpositions(FILE* fout, int number)
{   
    int size = 1 << number; 
    for (int i = 0; i < size; i++)
    {   
        for (int j = 0; j < number; j++)
        {
            if (i & ((1 << number-1) >> j))
            {
                fprintf(fout, "%d ", number-j);
            }
            else
            {
                fprintf(fout, "%d ", 0);
            }
        }
        fprintf(fout, "\n");
    }
}


int read_from_file(const char* filename, int* number)
{
    FILE* fin;
    fin = fopen(filename, "r");
    if (fin)
    {
        if (fscanf(fin, "%d", number) > 0)
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

int write_to_file(const char* filename, int number)
{
    FILE* fout;
    fout = fopen(filename, "w");
    if (fout)
    {   
        if (number <= 0)
        {
            fprintf(fout, "%d", 0);
        }
        else
        {
            generate_transpositions(fout, number);
        }
        fclose(fout);
        return 0;
    }
    return -1;
}

int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        int read_err, write_err, number;
        read_err = read_from_file(argv[1], &number);
        if (read_err == 0)
        {
            write_err = write_to_file(argv[2], number);
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
