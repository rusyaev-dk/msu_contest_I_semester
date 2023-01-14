#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		FILE* fin;
		fin = fopen(argv[1], "r");
		if (fin)
		{
			double sum = 0, D = 0, x; 
			int counter = 0;
			while (fscanf(fin, "%lf", &x) > 0)
			{
				sum += x;
				D += x * x;
				counter++;
			}
			if (counter) 
			{
				D += -1 * sum * sum / counter;
			}
			fclose(fin);

			FILE* fout;
			fout = fopen(argv[2], "w");
			if (fout)
			{
				fprintf(fout, "%lf", D);
				fclose(fout);
			}
			else
			{
				return -2;
			}
		}
		return -1;
	}
	return 0;
}