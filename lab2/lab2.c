#include <locale.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

int* memory(int n)
{
	int *x = (int*)malloc(n*sizeof(int));
	if (x==NULL) 
	{
		printf("\nНедостаточно памяти!\n");
		return 0;
	}
    return x;
}

int* input(int v, int* n)
{
	FILE *A;
    int i, y, u, temp;
	u = 1;
    if(v==0)
    {
    	char k[256];
		temp = 0;
		printf("\nВведите название файла, из которого будут взяты значения логической функции:\n");
		aa:scanf("%s", &k);
		A = fopen(k, "r");
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
	}
	else
	{
		temp = 0;
		A = stdin;
	}
	printf("\nВведите количество переменных:\n");
	bb:u = scanf("%d", n);
	if(u==EOF)
    {
    	printf("\nЗначений в файле недостаточно!\n");
        return 0;
    }
    if(u==0)
    {
		while(getchar()!='\n');
    	printf("\nВведен символ вместо числа!\n");
        return 0;
    }
	if((*n)<=0)
	{
		if(v==1)
		{
	    	temp = temp+1;
	    	if(temp==10)
	    	{
	    		printf("\nКоличество попыток на введение истекло!\n");
	        	return 0;
	    	}
	    	printf("\nНеверно! Попробуйте еще раз:\n");
	    	goto bb;
		}
		else
		{
			printf("\nДанные файла некорректны!\n");
            return 0;
		}
	}
	int *array;
	y = 1;
	for (i=0; i<(*n); i++)
    {
        y = y*2;
    }
	array = memory(y);
	if (array==0)
    {
    	printf("\nНедостаточно памяти для ввода логической функции!\n");
        return 0;
    }
    if(v==1)
    {
		printf("\nВведите значения логической функции:\n");
	}
	for(i=0; i<y; i++)
	{
		temp = 0;
	    cc:u = fscanf(A, "%d", &array[i]);
	    if(u==EOF)
	    {
	        printf ("\nЗначений в файле недостаточно!\n");
            return 0;
		}
		if (u==0)
        {
        	while(getchar()!='\n');
        	printf("\nВведен символ вместо числа!\n");
            return 0;
        }
	    if((array[i]!=1) && (array[i]!=0))
		{
		    if(v==1)
		    {
		        temp = temp+1;
		        if (temp==10)
		        {
		        	printf("\nКоличество попыток на введение истекло!\n");
		            return 0;
		        }
		        printf("\nВведен неверный элемент! Попробуйте еще раз:\n");
			    goto cc;
		    }
		    else
		    {
		    	printf("\nДанные файла некорректны!\n");
                return 0;
            }
		}
	}
    return array;
}

int* grey_code(int n)
{
	int* x;
	int i, u = 1;
	for(i=0; i<n; i++)
    {
        u = u*2;
    }
    x = memory(u);
    if(x==0)
    {
        printf("Не достаточно памяти\n");
        return 0;
    }
    for(i=0; i<u; i++)
    {
		x[i] = (i>>1) ^ i;
    }
    return x;
}

int* conversion(int x, int n)
{
	int* array;
    int i;
    array = memory(n);
    if(array==0)
    {
        printf ("Не достаточно памяти\n");
        return 0;
    }
    for(i=n-1; i>=0; i--)
    {
        if((x%2)==1)
		{
			array[i] = 1;
		}
        else array[i] = 0;
        x = x/2;
    }
    return array;
}

void gap(int n, FILE *A)
{
	int i;
    for (i=0; i<n; i++)
    {
        fprintf(A, " ");
    }
}

int carnot_map(int* y, int n, FILE *A)
{
	int* array, * x;
	int a, b, i, j, k, p, g1, g2, u = 1, a1 = 1, b1 = 1;
	a = n/2;
	b = n-a;
	g2 = b/2;
	g1 = b-g2;
	gap(b+1, A);
	x = grey_code(n);
	if(x==0)
    {
    	return 0;
	}
	//a1-количество строчек, b1-количество столбцов, u-количество ячеек
	for(i=0; i<a; i++)
    {
        a1 = a1*2;
    }
    for(i=0; i<b; i++)
    {
        b1 = b1*2;
    }
	for(i=0; i<n; i++)
    {
        u = u*2;
    }
    //Цикл для вывода строчки значений переменных
	for(i=0; i<b1; i++)
	{
		array = memory(b);
    	if(array==0)
    	{
        	return 0;
    	}
		array = conversion(x[i], b);
		for(j=0; j<b; j++)
		{
			fprintf(A, "%d", array[j]);
		}
		fprintf(A, " ");
	}
	fprintf(A, "\n");
	for(i=0; i<a1; i++)
    {
    	array = memory(a);
    	if(array==0)
    	{
        	return 0;
    	}
        array = conversion(x[i], a);
        //Цикл для вывода столбца значений переменных
        for(j=0; j<a; j++)
        {
            fprintf(A, "%d", array[j]);
        }
        if(b!=a)
        {
            gap(1, A);
        }
        for(j=0; j<b1; j++)
        {
            gap(g1, A);
            if((i%2)==1)
            {
                for(k=0; k<u; k++)
                {
                    if(x[i*b1+b1-j-1]==k)
                    {
                        p = k;
                        break;
                    }
                }
                fprintf(A, "%d", y[p]);
            }
            else
            {
                for(k=0; k<u; k++)
                {
                    if(x[i*b1+j]==k)
                    {
                        p = k;
                        break;
                    }
                }
                fprintf(A, "%d", y[p]);
            }
            gap(g2, A);
        }
        fprintf(A, "\n");
        free(array);
    }
    return 1;
}

int truth_table(int* y, int n, FILE *A)
{
	int* array;
	int i, j, u = 1;
	for(i=0; i<n; i++)
    {
        u = u*2;
    }
    for(i=0; i<n; i++)
    {
    	fprintf(A, "x%d ", i+1);
	}
	fprintf(A, "f(x)\n");
    for(i=0; i<u; i++)
    {
    	array = memory(n);
    	if(array==0)
        {
            return 0;
        }
    	array = conversion(i, n);
        for(j=0; j<n; j++)
        {
        	fprintf(A, " %d ", array[j]);
		}
		fprintf(A, " %d\n", y[i]);
		free(array);
	}
	return 1;
}

int snf(int* y, int n, int m, FILE *A)
{
	int* array;
	int i, j, u = 1, temp = 0;
	char k1, k2;
	if(m==1)
	{
		k1 = 'v';
		k2 = '&';
	}
	else
	{
		k1 = '&';
		k2 = 'v';
	}
	for(i=0; i<n; i++)
    {
        u = u*2;
    }
    for(i=0; i<u; i++)
    {
    	array = memory(n);
	    if(array==0)
	    {
	        return 0;
	    }
        array = conversion(i, n);
    	if(y[i]==m)
    	{
    		if(temp==1)
			{
				fprintf(A, " %c ", k1);
			}
			temp = 1;
    		fprintf(A, "(");
    		for(j=0; j<n; j++)
    		{
    			if(array[j]==m)
    			{
    				fprintf(A, "(x%d)", j+1);
				}
				else
				{
					fprintf(A, "(~x%d)", j+1);
				}
				if(j!=(n-1))
				{
					fprintf(A, "%c", k2);
				}
			}
			fprintf(A, ")");
		}
		free(array);
	}
	return 1;
}

main()
{
	setlocale(LC_ALL, "rus");
    FILE *A;
	A = fopen("results.txt", "w");
	int p, n, v, temp, f;
	printf("Функции алгебры логики\n");
	
	do
	{
		printf("Если вы хотите ввести данные с клавиатуры, введите 1, получить данные из файла - 0:\n");
		temp = 0;
		do
		{
			aa:f = scanf("%d", &v);
			if(f==0)
			{
			    while(getchar()!='\n');	
				printf("\nВведен символ вместо числа! Попробуйте еще раз:\n");
				goto aa;
			}
	    	if((v!=1) && (v!=0)) 
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
	    
	    int* y;
	    y = input(v, &n);
	    if(y==0)
	    {
	    	goto end;
		}
		
		printf("\nТаблица истинности:\n");
		if(truth_table(y, n, stdout)==0)
		{
			goto end;
		}
		
		printf("\nКарта Карно:\n");
		if(carnot_map(y, n, stdout)==0)
		{
			goto end;
		}
		
		printf("\nСДНФ:\n");
		if(snf(y, n, 1, stdout)==0)
		{
			goto end;
		}
		
		printf("\n\nСКНФ:\n");
		if(snf(y, n, 0, stdout)==0)
		{
			goto end;
		}
		
		temp = 0;
		printf("\n\nЕсли вы хотите выполнить программу еще раз, введите 1, если нет - введите 0:\n");
		do
		{
			bb:f = scanf("%d", &p);
			if(f==0)
			{
				getchar();
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
    fclose(A);
	system("pause");
	return 0;
}
