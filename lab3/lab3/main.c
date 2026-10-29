#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include "main1.h"

FILE *A;
char krr[256];

float** memory1(int n)
{
	int i;
	float **x = (float**)malloc(n*sizeof(float*));
	if (x==NULL)
	{
		printf("\nНедостаточно памяти!\n");
		return 0;
	}
    for (i=0; i<n; i++)
	{
		x[i] = (float*)malloc(n*sizeof(float));
		if (x[i]==NULL)
		{
			printf("\nНедостаточно памяти!\n");
			return 0;
		}
	}
    return x;
}

int* memory2(int n)
{
	int *x = (int*)malloc(n*sizeof(int));
	if (x==NULL)
	{
		printf("\nНедостаточно памяти!\n");
		return 0;
	}
    return x;
}

float** input(int* n)
{
    int i, j, u, temp = 0;
	u = 1;

	printf("\nВведите название файла, из которого будут взяты значения логической функции:\n");
	aa:scanf("%s", &krr);
	A = fopen(krr, "r");
	if(A==NULL)
	{
	    temp = temp+1;
	    if(temp==10)
	    {
	    	printf("\nКоличество попыток на введение истекло! Не удалось связаться с файлом!\n");
	        return 0;
	    }
	    printf("\nНе удалось открыть файл или файл не найден! Попробуйте еще раз:\n");
	    goto aa;
	}

	printf("\nВведите количество вершин:\n");
	bb:u = scanf("%d", n);
    if(u==0)
    {
		while(getchar()!='\n');
    	printf("\nВведен символ вместо числа! Попробуйте еще раз:\n");
        goto bb;
    }
	if((*n)<=1)
	{
		temp = 0;
	    temp = temp+1;
	    if(temp==10)
	    {
	    	printf("\nКоличество попыток на введение истекло!\n");
	        return 0;
	    }
	    printf("\nНеверно! Попробуйте еще раз:\n");
	    goto bb;
	}
	float **array;
	array = memory1(*n);
	if(array==0)
    {
    	printf("\nНедостаточно памяти для ввода матрицы смежности!\n");
        return 0;
    }
	for(i=0; i<(*n); i++)
	{
		for(j=0; j<(*n); j++)
		{
			temp = 0;
		    cc:u = fscanf(A, "%f", &array[i][j]);
		    if(u==EOF)
		    {
		        printf ("\nЗначений в файле недостаточно!\n");
	            return 0;
			}
			if(u==0)
	        {
	        	while(getchar()!='\n');
	        	printf("\nДанные файла некорректны! Введен символ вместо числа!\n");
	            return 0;
	        }
		}
	}
    return array;
}

void output(float** array, int n, FILE *A)
{
    int i, j;
	for(i=0; i<n; i++)
    {
		for (j=0; j<n; j++)
        {
        	if(array[i][j]<999999999)
        	{
        		fprintf(A, "    ");
			}
		    fprintf(A, "%.0f   ", array[i][j]);
		    if(array[i][j]<999999999)
        	{
        		fprintf(A, "    ");
			}
		}
		fprintf(A, "\n");
    }
}

int check(float** array, int n)
{
	int* vertices;
	int i, j, k, a;
	vertices = memory2(n);
	if(vertices==0)
	{
		printf("Недостаточно памяти!");
		return 0;
	}
	vertices[0] = 0;
	for(i=1; i<n; i++)
	{
		vertices[i] = (-1);
	}
	for(i=0; ; i++)
	{
		for(j=0; j<n; j++)
		{
			a = 0;
			if(array[vertices[i]][j] > 0)
			{
				for(k=0; k<n; k++)
				{
					if(j==vertices[k])
					{
						goto aa;
					}
				}
				for(k=1; k<n; k++)
				{
					if(vertices[k]==(-1))
					{
						vertices[k] = j;
						break;
					}
				}
				for(k=0; k<n; k++)
				{
					if(vertices[k] > (-1))
					{
						a = a+1;
					}
				}
				if(a==n)
				{
					printf("\nГраф - связный!\n");
					return 1;
				}
			}
			aa:;
		}
		if(vertices[i+1]==(-1))
		{
			printf("\nГраф - несвязный!\n");
			return 0;
		}
	}
}

void min_rib(float** array, int* peaks, int* ij, int n)
{
	int i, j, min, l = 0, m = n-1, a = 0, b;
	//Количество элементов
	for(i=0; i<n; i++)
	{
		if(peaks[i] > (-1))
		{
			a = a+1;
		}
	}
	if(a!=0)
	{
		l = peaks[0];
		m = peaks[0];
		//Минимальный узел
		for(i=1; i<a; i++)
		{
			if(peaks[i] > (-1))
			{
				if(peaks[i] < l)
				{
					l = peaks[i];
				}
			}
		}
		//Максимальный узел
		for(i=1; i<a; i++)
		{
			if(peaks[i] > (-1))
			{
				if(peaks[i] > m)
				{
					m = peaks[i];
				}
			}
		}
		//Сортировка
		for(i=0; i<n; i++)
		{
			if(peaks[i] > (-1))
			{
				if(peaks[i]!=i)
				{
					do
					{
						b = peaks[i];
						peaks[i] = peaks[b];
						peaks[b] = b;
					}
					while(peaks[i]>(-1) && peaks[i]!=i);
				}
			}
		}
	}
	for(i=l; i<=m; i++)
	{
		for(j=0; j<n; j++)
		{
			if(j!=peaks[j])
			{
				if((array[i][j]!=0) && (array[i][j]!=999999999))
				{
					if(a==0)
					{
						peaks[0] = i;
						peaks[1] = j;
					}
					else b = j;
					min = array[i][j];
					ij[0] = i;
					ij[1] = j;
					goto aa;
				}
			}
		}
		if(a!=0)
		{
			if(peaks[i+1]==(-1))
			{
				i = i+1;
				for(j=i; j<m; j++)
				{
					if(peaks[i+1]!=(-1))
					{
						break;
					}
					else i = i+1;
				}
			}
		}
	}
	aa:for(i=l; i<=m; i++)
	{
		for(j=0; j<n; j++)
		{
			if(j!=peaks[j])
			{
				if((array[i][j]!=0) && (array[i][j]!=999999999))
				{
					if(array[i][j] < min)
					{
						if(a==0)
						{
							peaks[0] = i;
							peaks[1] = j;
						}
						else b = j;
						min = array[i][j];
						ij[0] = i;
						ij[1] = j;
					}
				}
			}
		}
		if(a!=0)
		{
			if(peaks[i+1]==(-1))
			{
				i = i+1;
				for(j=i; j<m; j++)
				{
					if(peaks[i+1]!=(-1))
					{
						break;
					}
					else i = i+1;
				}
			}
		}
	}
	if(a!=0)
	{
		for(i=0; i<n; i++)
		{
			if(peaks[i]==(-1))
			{
				peaks[i] = b;
				break;
			}
		}
	}
	printf("\nДлина минимального ребра: %d\nВершины, инцидентные ребру: x%d и x%d\n", min, ij[0]+1, ij[1]+1);
}

int tree(float** array1, float** array2, int n)
{
	int *peaks;
	int ij[2], i;
	peaks = memory2(n);
	if(peaks==0)
	{
		return 0;
	}
	for(i=0; i<n; i++)
	{
		peaks[i] = (-1);
	}
	for(i=1; i<n; i++)
	{
		min_rib(array1, peaks, ij, n);
		array2[ij[0]][ij[1]] = array1[ij[0]][ij[1]];
		array2[ij[1]][ij[0]] = array1[ij[1]][ij[0]];
	}
	return 1;
}

int main()
{
	setlocale(LC_ALL, "rus");
    FILE *fr;
	fr = fopen("results.txt", "w");
	float **array1, **array2;
	int n, i, j, p, f, b, temp = 0;
	float sum;

	printf("Алгоритмы на графах\n");
	do
	{
		sum = 0;
		array1 = input(&n);
		if(array1==0)
		{
		    goto end;
		}
		printf("\nМатрица весов:\n");
		output(array1, n, stdout);
		if(check(array1, n)==0)
		{
			goto end;
		}
		printf("\nВыберите, с помощью какого метода построить дерево:\nАлгоритм Прима - 1\nАлгоритм Крускала - 0\nДвумя сразу - 2\n");
		scanf("%d", &b);
		if(b==1 || b==2)
		{
			printf("\nАлгоритм Прима");

			array2 = memory1(n);
			if(array2==0)
			{
				goto end;
			}
			for(i=0; i<n; i++)
			{
				for(j=0; j<n; j++)
				{
					if(i==j)
					{
						array2[i][j] = 0;
					}
					else array2[i][j] = 999999999;
				}
			}

			tree(array1, array2, n);
			printf("\nОстовное дерево с минимальным весом:\n");
			output(array2, n, stdout);
			for(i=0; i<n; i++)
			{
				for(j=i+1; j<n; j++)
				{
					if((array2[i][j]!=0) && (array2[i][j]!=999999999))
					{
						sum+=array2[i][j];
					}
				}
			}
			fclose(A);
			printf("\nВес остовного дерева с минимальным весом: %.0f\n", sum);
		}
		if(b==0 || b==2)
		{
			printf("\nАлгоритм Крускала\n");
			A=fopen(krr,"r");
			kruskal1(A,n);
			fclose(A);
		}
		printf("\nЕсли вы хотите выполнить программу еще раз, введите 1, если нет - введите 0:\n");
		do
		{
			bb:f = scanf("%d", &p);
			if(f==0)
			{
				while(getchar()!='\n');
				printf("\nВведен символ вместо числа! Попробуйте еще раз:\n");
				goto bb;
			}
	    	if((p!=1) && (p!=0))
			{
	        	temp = temp+1;
	        	if(temp==10)
	        	{
	            	printf("\nКоличество попыток на введение истекло\n");
	            	goto end;
	        	}
	        	printf("\nНеверно! Попробуйте еще раз:\n");
			}
			else temp = 10;
		}
		while(temp<10);
	}
	while(p==1);

	end:
	fclose(fr);
	system("pause");
	return 0;
}
