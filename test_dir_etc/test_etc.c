#include <stdio.h>
#include <math.h>
#include <stdlib.h>
typedef struct point{
    double x , y;
}point;


point dif(point p1 , point p2){
    point dif;
    dif.x = p1.x - p2.x;
    dif.y = p1.y - p2.y;
    return dif;
}


double vec_mult(point p1 , point p2){
    double result = p1.x * p2.y - p2.x * p1.y;
    return result;
}


double direction(point p1 ,point p2 , point p3){
    double product = vec_mult(dif(p3 , p1),dif(p2  ,p1 ));
    return product;
}


int on_segment(point p1, point p2, point p3){
    if((fmin(p1.x , p2.x) <= p3.x && p3.x <= fmax(p1.x , p2.x) && (fmin(p1.y , p2.y) <= p3.x && p3.y <= fmax(p1.y ,p2.y))))
       return 1;
       else return 0;
}       


int peresechenie_segmentov(point p1 , point p2 , point p3 , point p4){
    double EPS = 1E-9;
    double d1 = direction(p3 , p4 , p1);
    double d2 = direction(p3 , p4 , p2);
    double d3 = direction(p1 , p2 , p3);
    double d4 = direction(p1 , p2 , p4);
    if((d1 * d2 < (- EPS) ) && (d3 * d4 < (-EPS)))
        return 1;
    else
        if (fabs(d1) + fabs(d2) + fabs(d3) + fabs(d4) < EPS)
            return 0;
    else
        if(fabs(d1) <= EPS && on_segment(p3 , p4 ,p1)==1)
            return 1;
    else
        if(fabs(d2) <= EPS && on_segment(p3 , p4 ,p2)==1)
            return 1;
    else
        if(fabs(d3) <= EPS && on_segment(p1 , p2 ,p3)==1)
            return 1;
    else
        if(fabs(d4) <= EPS && on_segment(p1 , p2 ,p4)==1)
            return 1;
        else return 0;
}


void read_from_file(const char* filename , point** arr , int* size){
    point m;
    int i = 0;
    FILE* fin = fopen( filename , "r" );
    if(!fin)
    {
        fclose(fin);
        return;
    }
    if(fscanf(fin , "%d " , size)==0)
    {
        fclose(fin);
    }
    else
    {
        *arr=(point*)malloc(sizeof(point)*(*size));
    }
    if (!(*arr))
    {
        fclose(fin);
        return;
    }
    else
    {
        for(; i < (*size) ; i++)
        {
            fscanf( fin , "%lf " "%lf " , &m.x ,&m.y);
            (*arr)[i] = m;
        
        }
    }
    if ( i < *size)
    {
        *arr=(point*)realloc(*arr, sizeof(point)*i);
        *size = i ;
    }
}


int find_result(point *arr ,int *size){
    point p1 , p2 , p3 , p4;
    if(*size > 3)
    {
        for(int i = *size-1 ; i >= 3 ; i--)
        {
                    p4 = arr[i];
                    p3 = arr[i - 1];
                    for(int k = i ; k >= 3 ;k--)
                    {
                        p1 = arr[k - 3];
                        p2 = arr[k - 2];
                        if(peresechenie_segmentov(p1 , p2, p3 , p4)==1)
                        {
                            return 1;
                        }
                        
                    }
        }
        return 0;
    }
    else
    {
        return 0;
    }
}


void write_to_file (const char* filename ,int result){
    FILE* fout = fopen( filename , "w" );
    if(!fout)
    {
        fclose(fout);
        return;
    }
    if(result==1)
    {
        fprintf( fout , "1");
    }
    else
        fprintf( fout , "0");
    fclose(fout);
}


int main( int argc , const char* argv[] ){
    if(argc==3)
    {
        point *arr;
        int result;
        int size;
        read_from_file(argv[1] , &arr ,&size);
        result = find_result(arr ,&size);
        write_to_file(argv[2] , result);
        free(arr);
        return 0;
    }
    else return 0;
}