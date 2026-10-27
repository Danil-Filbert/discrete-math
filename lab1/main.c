#include <locale.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int** memory(int n)
{
	int i;
	int **x = (int**)malloc(n*sizeof(int*));
	if (x==NULL) 
	{
		printf("Недостаточно памяти\n");
		return 0;
	}
    for (i=0; i<n; i++)
	{
		x[i] = (int*)malloc(n*sizeof(int));
		if (x[i]==NULL) 
		{
			printf("Недостаточно памяти\n");
			return 0;
		}
	}
    return x;
}

int** input(int v, int* n)
{
	FILE *A;
    int i, j, u, temp;
	u = 5;
    if(v==0)
    {
    	char k[256];
		temp = 0;
		printf("\nВведите название файла, из которого будут взяты значения для бинарной матрицы:\n");
		aa:scanf("%s", &k);
		A = fopen(k, "r");
		if(A==NULL)
	    {
	        temp = temp+1;
	    	if(temp==10)
	    	{
	        	return 0;
	    	}
	    	printf("Не удалось открыть файл или файл не найден! Попробуйте еще раз:\n");
	    	goto aa;
	   	}
	}
	else
	{
		temp = 0;
		A = stdin;
		printf("\nВведите количество элементов множества:\n");
	}
	bb:u = fscanf(A, "%d", n);
	if(u==EOF)
    {
        return 2;
    }
    if(u==0)
    {
        return 3;
    }
	if(n<=0)
	{
		if(v==1)
		{
	    	temp = temp+1;
	    	if(temp==10)
	    	{
	        	return 4;
	    	}
	    	printf("Неверно! Попробуйте еще раз:\n");
	    	goto bb;
		}
		else
		{
            return 5;
		}
	}
	int **array;
	array = memory(*n);
	if (array==0)
    {
        return 6;
    }
    if(v==1)
    {
		printf("\nВведите элементы бинарной матрицы:\n");
	}
	for(i=0; i<(*n); i++)
	{
	    for(j=0; j<(*n); j++)
	    {
		    temp = 0;
	        cc:fscanf(A, "%d", &array[i][j]);
	        if(u==EOF)
	        {
	        	printf ("Значений в файле недостаточно\n");
                return 2;
			}
			if (u==0)
            {
                return 3;
            }
	        if((array[i][j]!=1) && (array[i][j]!=0))
		    {
		    	if(v==1)
		    	{
		            temp = temp+1;
		            if (temp==10)
		            {
		                return 4;
		            }
		            printf("Введен неверный элемент! Попробуйте еще раз:\n");
			        goto cc;
		    	}
		    	else
		    	{
                    return 5;
                }
		    }
	    } 
	}
    return array;
}

void output(int** array, int n, FILE *A)
{
    int i, j;
	for(i=0; i<n; i++)
    { 
		for (j=0; j<n; j++)
        {
		    fprintf(A, "%d   ", array[i][j]);
		}
		fprintf(A, "\n");
    }
}

int reflex(int** array, int n)
{
	int i;
	for(i=0; i<n; i++)
	{
		if(array[i][i]!=1)
		{
			return 0;
		}
	}
	return 1;
}

int antireflex(int** array, int n)
{
	int i;
	for(i=0; i<n; i++)
	{
		if(array[i][i]!=0)
		{
			return 0;
		}
	}
	return 1;
}

int symm(int** array, int n)
{
	int i, j;
	for(i=0; i<n; i++)
	{
		for(j=i+1; j<n; j++)
		{
			if(array[i][j]!=array[j][i])
			{
				return 0;
			}
		}
	}
	return 1;
}

int antisymm(int** array, int n)
{
	int i, j;
	for(i=0; i<n; i++)
	{
		for(j=i+1; j<n; j++)
		{
			if((array[i][j]==1) && (array[j][i]==1))
			{
				return 0;
			}
		}
	}
	return 1;
}

int tranz(int** array, int n)
{
	int i, j, k;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(array[i][j]==1)
			{
				for(k=0; k<n; k++)
				{
					if((array[j][k]==1) && (array[i][k]==0))
					{
						return 0;
					}
				}
			}
		}
	}
	return 1;
}

void reverse(int** array1, int** array2, int n)
{
	int i, j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			array2[i][j] = array1[j][i];
		}
	}
}

void compos(int** array1, int** array2, int** array3, int n)
{
	int i, j, k;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(array1[i][j]==1)
			{
				for(k=0; k<n; k++)
				{
					if(array2[j][k]==1)
					{
						array3[i][k] = 1;
					}
					else array3[i][k] = 0;
				}
			}
		}
	}
}

int check(int** array)
{
	if(array==0)
	{
		printf("\nНе удалось связаться с файлом!\n");
		return 0;
	}
	else if(array==2)
	{
		printf("\nЗначений в файле недостаточно!\n");
		return 0;
	}
	else if(array==3)
	{
		printf("\nВведен символ вместо числа!\n");
		return 0;
	}
	else if(array==4)
	{
		printf("\nКоличество попыток на введение истекло!\n");
		return 0;
	}
	else if(array==5)
	{
		printf("\nЭлемент отношения отличен от нуля или единицы!\n");
		return 0;
	}
	else if(array==6)
	{
		printf("\nНедостаточно памяти для ввода множества!\n");
		return 0;
	}
	else return 1;
}

main ()
{
	setlocale(LC_ALL, "rus");
    FILE *A;
	A = fopen("results.txt", "w");
	int p, n, v, temp, i, z, a, b, c, d, f;
	printf("Анализ свойств бинарных отношений\n");
	
	do
	{
		printf("Если вы хотите ввести данные матрицы с клавиатуры, введите 1, получить данные из файла - 0:\n");
		temp = 0;
		do
		{
			f = scanf("%d", &v);
			if(f==0)
			{
				printf("\nВведен символ вместо числа!\n");
				goto end;
			}
	    	if((v!=1) && (v!=0)) 
			{
	        	temp = temp+1;
	        	if(temp==10)
	        	{
	            	printf("Количество попыток на введение истекло\n");
	            	goto end;
	        	}
	        	printf("Неверно! Попробуйте еще раз:\n");
			}
			else temp = 10;
		}
		while(temp<10);
	    
	    int** array1, ** array2, ** array3;
	    array1 = input(v, &n);
	    if(check(array1)==0)
	    {
	    	goto end;
		}

		array2 = memory(n);
		if(array2==0)
		{
			printf("Памяти для множества недостаточно\n");
			goto end;
	    }
	    
		array3 = memory(n);
		if(array3==0)
		{
			printf("Памяти для множества недостаточно\n");
			goto end;
	    }
		
		printf("\nВывод матрицы:\n");
		output(array1, n, stdout);
		output(array1, n, A);
		
		printf("\nОбратная матрица:\n");
		reverse(array1, array2, n);
		output(array2, n, stdout);
		output(array2, n, A);
		
		printf("\nКомпозиция:\n");
		compos(array1, array2, array3, n);
		output(array3, n, stdout);
		output(array3, n, A);
		
		printf("\nСвойства композиции:\n");
		a = reflex(array3, n);
		b = antireflex(array3, n);
		c = symm(array3, n);
		d = antisymm(array3, n);
		
		if(a==1)
		{
			printf("Композиция рефлексивна\n");
		}
		else if(b==1)
		{
			printf("Композиция антирефлексивна\n");
		}
		else printf("Композиция ни рефлексивна, ни антирефлексивна\n");
		
		if((b==1) && (c==1) && (d==1))
		{
			printf("Композиция и симметрична, и асимметрична, и антисимметрична\n");
		}
		else if((b==1) && (d==1))
		{
			printf("Композиция и асимметрична, и антисимметрична\n");
		}
		else if((c==1) && (d==1))
		{
			printf("Композиция и симметрична, и антисимметрична\n");
		}
		else if(c==1)
		{
			printf("Композиция симметрична\n");
		}
		else if(d==1)
		{
			printf("Композиция антисимметрична\n");
		}
		else printf("Композиция ни симметрична, ни антисимметрична, ни асимметрична\n");
		
		if(tranz(array3, n)==1)
		{
			printf("Композиция транзитивна\n");
		}
		else printf("Композиция не транзитивна\n");
		
		temp = 0;
		printf("\nЕсли вы хотите выполнить программу еще раз, введите 1, если нет - введите 0:\n");
		do
		{
			f = scanf("%d", &p);
			if(f==0)
			{
				printf("\nВведен символ вместо числа!\n");
				goto end;
			}
	    	if((p!=1) && (p!=0)) 
			{
	        	temp = temp+1;
	        	if(temp==10)
	        	{
	            	printf("Количество попыток на введение истекло\n");
	            	goto end;
	        	}
	        	printf("Неверно! Попробуйте еще раз:\n");
			}
			else temp = 10;
		}
		while(temp<10);
	}
	while(p==1);
	
    end:
    fclose(A);
	system("pause");
	return 0;
}
