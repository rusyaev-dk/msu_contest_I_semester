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
      int position = 1, counter = 1;
      double max_value = 0, next_elem;
      if (fscanf(fin, "%lf", &max_value) > 0)
      {
        while (fscanf(fin, "%lf", &next_elem) > 0)
        {  
          counter++;
          if (next_elem > max_value)
          {
            max_value = next_elem;
            position = counter;
          }
        }
      }
      else
      {
        position = 0;
      }
      fclose(fin);

      FILE* fout;
      fout = fopen(argv[2], "w");
      if (fout)
      {
        fprintf(fout, "%d", position);
        fclose(fout);
      }
      else
      {
        return -1;
      }
    }
  }
  return 0;
}