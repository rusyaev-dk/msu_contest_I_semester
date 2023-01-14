#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define get_max(a, b) (a) > (b) ? (a) : (b)
#define get_min(a, b) (a) < (b) ? (a) : (b)
#define pi 3.14159265358979323846
#define epsilon 10E-9

typedef struct Point
{
	double x, y;
} Point;

typedef struct Segment
{
	Point begin, end;
} Segment;

typedef struct Vector
{
	double x, y, length;
} Vector;

typedef struct Polygon
{   
    int points_quantity;
	Point* points_arr;
} Polygon;

Point difference_point(Point p1, Point p2)
{
	Point difference_point;
	difference_point.x = p1.x - p2.x;
	difference_point.y = p1.y - p2.y;
	return difference_point;
}

Segment create_segment(Point p_1, Point p_2)
{
    Segment segment;
    segment.begin = p_1;
    segment.end = p_2;
    return segment;
}

Vector create_vector(Point pt_1, Point pt_2)
{
    Vector vector;
    vector.x = pt_2.x - pt_1.x;
    vector.y = pt_2.y - pt_1.y;
    return vector;
}

double find_arr_min(double* arr, int arr_size)
{
	double min = arr[0];
	for (int i = 1; i < arr_size; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	return min;
}

int are_equal(double a, double b)
{
	if (fabs(a - b) <= epsilon)
	{
		return 1;
	}
	return 0;
}

int is_bigger(double a, double b, int strictly)
{
	if (strictly == 0)
	{   
		if (a > b || are_equal(a, b))
			return 1;
	}
	else
	{ 	
		if (a > b)
			return 1;
	}
	return 0;
}

void swap(double* coor_1, double* coor_2)
{
	double temp = *coor_1;
	*coor_1 = *coor_2;
	*coor_2 = temp;
}

void swap_vectors(Vector *vec_1, Vector* vec_2)
{	
	Vector buffer_vec = *vec_1;
	*vec_1 = *vec_2;
	*vec_2 = buffer_vec;
}

double vector_length(Vector vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}

double vectors_scalar_product(Vector vec_1, Vector vec_2)
{
	return vec_1.x * vec_2.x + vec_1.y * vec_2.y;
}

int is_acute_angled(Vector vec_1, Vector vec_2, Vector vec_3)
{	
	if (vec_3.length < vec_2.length)
	{
		swap_vectors(&vec_3, &vec_2);
	}
	if (vec_3.length < vec_1.length)
	{
		swap_vectors(&vec_3, &vec_1);
	}
	if ((vec_1.length * vec_1.length + vec_2.length * vec_2.length) < (vec_3.length * vec_3.length))
	{	
		return 0;
	}
	return 1;
}

int belongs_to_segment(Point p, Point seg_begin, Point seg_end) 
{
	Vector vec_1 = create_vector(seg_begin, p);
	Vector vec_2 = create_vector(seg_begin, seg_end);
	double vectors_product = vec_1.x * vec_2.y - vec_1.y * vec_2.x;
	if (are_equal(vectors_product, 0))
	{
		if (is_bigger(get_max(seg_begin.x, seg_end.x), p.x, 0) && is_bigger(p.x, get_min(seg_begin.x, seg_end.x), 0)
		&& is_bigger(get_max(seg_begin.y, seg_end.y), p.y, 0) && is_bigger(p.y, get_min(seg_begin.y, seg_end.y), 0))
		{	
			return 1;
		}
	}
    return 0;
}



double cross_product(Point p1, Point p2)
{	
	// Положительное значение векторного произведения указывает 
	// на ориентацию по часовой стрелке и поворот вправо
	return p1.x * p2.y - p2.x * p1.y;
}

double direction(Point p1, Point p2, Point p3)
{	
	// Определяется относительное расположение отрезков:
	return cross_product(difference_point(p3, p1), difference_point(p2, p1));
}

int segments_crossing(Segment seg_1, Segment seg_2)
{	
	Point p1 = seg_1.begin;
	Point p2 = seg_1.end;
	Point p3 = seg_2.begin;
	Point p4 = seg_2.end;

	// вычисляется относительное расположение каждой конечной точки относительно другого отрезка:

	double d1 = direction(p3, p4, p1);
	double d2 = direction(p3, p4, p2);
	double d3 = direction(p1, p2, p3);
	double d4 = direction(p1, p2, p4);

	// рассматриваются полуплоскости у каждого отрезка и проверяется принадлежность точки соот-й полуплоскости
	// Отрезок p1р2 пересекает прямую, содержащую отрезок p3p4, если направленные отрезки p3p1 и p3p2 имеют
	// противоположные направления относительно p3p4, т.е. тогда мы получаем разные знаки у d1 и d2
	
	// Обработка общего случая:
	if ( ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
	((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0)) )
		return 1;
	// Обработка граничных случаев:
	// здесь di == 0 - проверка на коллинеарность
    else if (fabs(d1) + fabs(d2) + fabs(d3) + fabs(d4) < epsilon)
		// наложение отрезков друг на друга
        return 0;
    else if(are_equal(d1, 0) && belongs_to_segment(p1, p3, p4))
        return 1;
    else if(are_equal(d2, 0) && belongs_to_segment(p2, p3, p4))
        return 1;
    else if(are_equal(d3, 0) && belongs_to_segment(p3, p1, p2))
        return 1;
    else if(are_equal(d4, 0) && belongs_to_segment(p4, p1, p2))
        return 1;
    return 0;
}



double point_to_point_distance(Point p_1, Point p_2)
{
    return sqrt((p_1.x - p_2.x) * (p_1.x - p_2.x) + (p_1.y - p_2.y) * (p_1.y - p_2.y));
}

double point_to_segment_distance(Point p, Segment seg)
{	
	if (seg.begin.x > seg.end.x)
	{
		swap(&seg.begin.x, &seg.end.x);
		swap(&seg.begin.y, &seg.end.y);
	}
	double x, h;
	Vector A, B, C;
	
	A = create_vector(p, seg.begin);
	A.length = vector_length(A);
	B = create_vector(p, seg.end);
	B.length = vector_length(B);
	C = create_vector(seg.begin, seg.end); 
	C.length = vector_length(C);

	if (vectors_scalar_product(A, B) < 0 || is_acute_angled(A, B, C))
	{
		x = ((A.length * A.length - B.length * B.length + C.length * C.length) / (2 * C.length));
		h = sqrt(A.length * A.length - x * x);
		return h;
	}
	double distance_1, distance_2;
	distance_1 = point_to_point_distance(p, seg.begin);
	distance_2 = point_to_point_distance(p, seg.end);
	if (distance_1 > distance_2)
	{
		return distance_2;
	}
	return distance_1;
}

double segment_to_segment_distance(Segment seg_1, Segment seg_2)
{	
	if (segments_crossing(seg_1, seg_2))
	{	
		printf("SEGMENTS CROSSING");
		return 0;
	}
	double distances_arr[6];

	distances_arr[0] = point_to_segment_distance(seg_1.begin, seg_2);
	distances_arr[1] = point_to_segment_distance(seg_1.end, seg_2);

	distances_arr[2] = point_to_point_distance(seg_1.begin, seg_2.end);
	distances_arr[3] = point_to_point_distance(seg_1.end, seg_2.begin);

	distances_arr[4] = point_to_segment_distance(seg_2.begin, seg_1);
	distances_arr[5] = point_to_segment_distance(seg_2.end, seg_1);

	return find_arr_min(distances_arr, 6);
}

double vectors_angle(Vector vec_1, Vector vec_2)
{
    double cos = (vectors_scalar_product(vec_1, vec_2)) / (vector_length(vec_1) * vector_length(vec_2));
	double sign = vec_1.x * vec_2.y - vec_1.y * vec_2.x;

	if (sign > 0)
	{
		return acos(cos);
	}
	return -1 * acos(cos);
}

int belongs_to_polygon(Point p, Polygon *polygon)
{
	double angle_sum = 0;
	Vector vec_1, vec_2;
	for (int i = 0; i < polygon->points_quantity; i++)
	{	
		if (belongs_to_segment(p, polygon->points_arr[i], polygon->points_arr[i + 1]))
		{	
			return 1;
		}
		vec_1 = create_vector(polygon->points_arr[i], p);
		vec_2 = create_vector(polygon->points_arr[i + 1], p);
		angle_sum += vectors_angle(vec_1, vec_2);
	}
	if (are_equal(fabs(angle_sum), 2 * pi))
	{
		return 1;
	}
	return 0;
}

double polygon_to_polygon_distance(Polygon polygon_1, Polygon polygon_2)
{	
	for (int i = 0; i < polygon_1.points_quantity; i++)
	{
		if (belongs_to_polygon(polygon_1.points_arr[i], &polygon_2))
		{	
			return 0;
		}
	}
	for (int i = 0; i < polygon_2.points_quantity; i++)
	{
		if (belongs_to_polygon(polygon_2.points_arr[i], &polygon_1))
		{	
			return 0;
		}
	}
	
	Segment seg_1, seg_2; double distance, distance_1;
	seg_1 = create_segment(polygon_1.points_arr[0], polygon_1.points_arr[1]);
	seg_2 = create_segment(polygon_2.points_arr[0], polygon_2.points_arr[1]);
	distance_1 = segment_to_segment_distance(seg_1, seg_2);

	for (int i = 0; i < polygon_1.points_quantity; i++)
	{
		for (int c = 0; c < polygon_2.points_quantity; c++)
		{	
			seg_1 = create_segment(polygon_1.points_arr[i], polygon_1.points_arr[i + 1]);
			seg_2 = create_segment(polygon_2.points_arr[c], polygon_2.points_arr[c + 1]);
			distance = segment_to_segment_distance(seg_1, seg_2);
			if (are_equal(distance, 0))
			{	
				return 0;
			}
			else if (distance > distance_1)
			{
				distance = distance_1;
			}
			else
			{
				distance_1 = distance;
			}
		}
	}
	return distance;
}

int read_from_file(const char* filename, Polygon* polygon_1, Polygon* polygon_2)
{
	FILE* fin;
	fin = fopen(filename, "r");
	if (fin)
	{   
        if (fscanf(fin, "%d", &(polygon_1->points_quantity)) > 0)
        {	
			polygon_1->points_quantity = abs(polygon_1->points_quantity);
            polygon_1->points_arr = (Point*)malloc(sizeof(Point) * (polygon_1->points_quantity + 1));
            Point scanfed_point;
			int i = 0;
			while (i < polygon_1->points_quantity && fscanf(fin, "%lf %lf", &(scanfed_point.x), &(scanfed_point.y)) == 2)
			{
				polygon_1->points_arr[i] = scanfed_point;
				i++;
			}
			if (i < polygon_1->points_quantity)
			{	
				fclose(fin);
				free(polygon_1->points_arr);
				return -4;
			}
			polygon_1->points_arr[i] = polygon_1->points_arr[0];
			
			if (fscanf(fin, "%d", &(polygon_2->points_quantity)) > 0)
        	{	
				polygon_2->points_quantity = abs(polygon_2->points_quantity);
				i = 0;
				polygon_2->points_arr = (Point*)malloc(sizeof(Point) * (polygon_2->points_quantity + 1));
				Point scanfed_point;
				while (i < polygon_2->points_quantity && fscanf(fin, "%lf %lf", &(scanfed_point.x), &(scanfed_point.y)) == 2)
				{
					polygon_2->points_arr[i] = scanfed_point;
					i++;
				}
				if (i == 0)
				{	
					fclose(fin);
					free(polygon_1->points_arr);
					free(polygon_2->points_arr);
					return -4;
				}
				if (i < polygon_2->points_quantity)
				{	
					Point* buffer;
					buffer = (Point*)realloc(polygon_2->points_arr, sizeof(Point) * (i + 1));
					if (buffer)
					{
						polygon_2->points_arr = buffer;
					}
					polygon_2->points_quantity = i;
				}
				polygon_2->points_arr[i] = polygon_2->points_arr[0];	

				fclose(fin);
				return 0;
        	}
			fclose(fin);
			return -3;
        }
		fclose(fin);
		return -2;
	}
	return -1;
}

int write_to_file(const char* filename, double distance)
{
	FILE* fout;
	fout = fopen(filename, "w");
	if (fout)
	{
		fprintf(fout, "%lf", distance);
		fclose(fout);
		return 0;
	}
	return -1;
}

int main(int argc, char* argv[])
{	
	if (argc == 3)
	{
		Polygon polygon_1, polygon_2;
		int read_err, write_err; 
		read_err = read_from_file(argv[1], &polygon_1, &polygon_2);
		if (read_err == 0)
		{	
			write_err = write_to_file(argv[2], polygon_to_polygon_distance(polygon_1, polygon_2));
			free(polygon_1.points_arr);
			free(polygon_2.points_arr);
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