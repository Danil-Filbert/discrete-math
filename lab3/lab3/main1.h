#include <math.h>
#include <inttypes.h>
int i,j;
typedef struct {
    int n1;       // первый узел
    int n2;         // второй узел
    float w;          // вес ребра
} edge;             //структура для ребра

typedef struct set {
    struct set *p;      // адрес ребра, с которым связан набор данного узла
} set;                  // структура для набора узлов


int ns,ne,m;      // число наборов, ребер и узлов
set *sets; // имя массива наборов
edge *E, *E1;   // имя массива ребер

//Выделение памяти для массива ребер
edge *mem_edge(int n)
{
	E = (edge*) malloc(n*sizeof(edge));
	if(E == NULL)
		return(0);
	return(E);
}

edge *mem_edge_1(int n)
{
	E1 = (edge*) malloc(n*sizeof(edge));
	if(E1 == NULL)
		return(0);
	return(E1);
}

//Выделение памяти для массива наборов
set *mem_set(int n)
{
	sets = (set*)malloc(n*sizeof(set));
	if(sets == NULL)
		return(0);
	return(sets);
}

int input1(edge *E, FILE *f, int nv)
{
    int k,b;

    b = 0;

    for(i = 0; i < nv; i++)
    {
        for(j = 0; j < nv; j++)
        {
            E[nv*i+j].n1 = i;
            E[nv*i+j].n2 = j;
            k = fscanf(f,"%f", &E[nv*i+j].w);
            if (k == 0)
                return (-1);
            if (feof(f)!=0)
                return (-1);
        }
    }
    for (i = 0; i < nv; i++)
    {
        for (j = i+1; j < nv; j++)
        {
            if (E[nv*i+j].w > 0)
                b++;
        }
    }

    /*fprintf(stdout, "Матрица смежности заданного взвешенного графа\n");
    for (i = 0; i < nv; i++)
    {
        for (j = 0; j < nv; j++)
        {
            if(E[nv*i+j].w != INFINITY)
        	{
                fprintf(stdout, " ");
			}
            fprintf(stdout, "%.0f  ", E[nv*i+j].w);
            if(E[nv*i+j].w != INFINITY)
        	{
                fprintf(stdout, " ");
			}
        }
        fprintf(stdout, "\n");
    }*/
    return(b);
}

int connect(edge *E, int nv)
{
    int vertex[nv];
    int a = 0;
    int b = 0;
    int k = 0;
    for (i = 0; i < nv; i++)
        vertex[i] = 1;  //присваиваем всем вершинам параметр 1 - нерассмотренные
    vertex[0] = 2;      //отмечаем первую вершину как необработанную//
    do
    {
        a = 1;
        for (i = 0; i < nv; i++)
        {
            if (vertex[i] == 2)
            {
                vertex[i] = 3; //помечаем вершину как обработанную
                k = i;
                break;
            }
        }
        for (i = 0; i < nv; i++)
        {
            if ((E[nv*k+i].w > 0 && E[nv*k+i].w != INFINITY) && vertex[i] == 1)
                vertex[i] = 2;
        }
        for (i = 0; i < nv; i++)
        {
            if (vertex[i] == 2)
                a = 0;
        }
    }while(a == 0);
    for (i = 0; i < nv; i++)
        if (vertex[i] == 1)
            b = 1;
    return b;
}

// фунция сравнения двух ребер по весу для qsort`a
int cmp(edge *a, edge *b)
{
    if(a->w > b->w ) return 1;
    if(a->w < b->w ) return -1;
    return(0);
}

// функция создания начальных наборов узлов
int init_set(set *sets,int ns)
{
    for(i = 0; i < ns ; i++)
        sets[i].p = &sets[i];
    return(0);
}

//Функция получения адреса набора, с которым связан данный набор
set* get_set_id(set* s)
{
    if(s == s->p )
        return s;
    else {
        set *p = get_set_id(s->p);
        s->p = p;
        return p;
    }
}
//Связь двух ранее не связанных наборов
void group_sets(set *a, set *b)
{
    a->p = b;
}

int kruskal(int ns, int m, set *sets, edge *E1, edge *E, int nv)
{
    int W = 0;
    for(i = 0; ns > 1 && i < m; i++)
    {   // определение принадлежности вершин ребра одному набору вершин
        if (get_set_id (&sets[E1[i].n1]) != get_set_id (&sets[E1[i].n2]))
        {
            group_sets (get_set_id (&sets[E1[i].n1]),  get_set_id (&sets[E1[i].n2]));
            ns--;
            E[nv*(E1[i].n1)+(E1[i].n2)].w = E1[i].w;
            E[nv*(E1[i].n2)+(E1[i].n1)].w = E[nv*(E1[i].n1)+(E1[i].n2)].w;
            printf("Вес минимального ребра: %.0f\n",E1[i].w);
            printf("Ребра, инцендентные ему: x%d и x%d\n",E1[i].n1+1, E1[i].n2+1);
            printf("\n");
            W += E1[i].w;
        }
    }
    return (W);
}

int kruskal1(FILE*f, int nv)
{
    int d,W;
    //char finame[300];
    //FILE*f;

        /*do
        {
            printf ("Введите имя файла с матрицей смежности взвешенного связаного графа:\n");
            scanf ("%s", finame);
            f = fopen(finame, "r");
            if (!f)
            {
                printf ("Файла с данным именем не существует. Введите имя файла еще раз\n");
                a = 0;
            }
            else
                a = 1;
        } while (a == 0);*/

        /*printf ("Введите число узлов графа:\n");
        scanf ("%d", &nv);
        int e = 0;
        do{
            if (nv <= 0)
            {
                printf("Введено неверное число узлов. Введите значение еще раз:\n");
                fscanf (f, "%d", &nv);
                e++;
            }
            else
                break;
        }while(e < 10);
        if (e == 10)
            return (1);*/

        ne = nv*nv;

    E = mem_edge(ne);
    if (E == 0)
    {
        printf("Не удалось выделить память\n");
        system("pause");
        return(1);
    }

    sets = mem_set(nv);
    if (sets == 0)
    {
        printf("Не удалось выделить память\n");
        system("pause");
        return(1);
    }

    m = input1(E, f, nv);

    if (m == -1)
    {
        printf("Некоректные данные в файле\n");
        system("pause");
        return(1);
    }

    /*g = connect(E, nv);
    if (g == 0)
        printf ("Граф в файле связаный\n");
    else
    {
        printf ("Граф в файле несвязаный\n");
        system("pause");
        return(1);
    }
    printf("\n");*/

    E1 = mem_edge_1(m);
    if (E1 == 0)
    {
        printf("Не удалось выделить память\n");
        system("pause");
        return(1);
    }

    d = 0;
    for (i = 0; i < nv; i++)
    {
        for (j = i+1; j < nv; j++)
        {
            if (E[nv*i+j].w > 0)
            {
                E1[d].n1 = E[nv*i+j].n1;
                E1[d].n2 = E[nv*i+j].n2;
                E1[d].w = E[nv*i+j].w;
                E[nv*i+j].w = INFINITY;
                E[nv*j+i].w = E[nv*i+j].w;
                d++;
            }
        }
    }

    // быстрая сортировка ребер по весу
    qsort(E1, m, sizeof(edge), (int (*)(const void*, const void*)) cmp);

    ns = nv;
    init_set(sets, ns);

    W = kruskal (ns, m, sets, E1, E, nv);

    fprintf(stdout, "Матрица смежности остовного дерева с минимальным весом\n");
    for (i = 0; i < nv; i++)
    {
        for (j = 0; j < nv; j++)
        {
            if(E[nv*i+j].w != INFINITY)
        	{
                fprintf(stdout, " ");
			}
            fprintf(stdout, " %.0f  ", E[nv*i+j].w);
            if(E[nv*i+j].w != INFINITY)
        	{
                fprintf(stdout, " ");
			}
        }
        fprintf(stdout, "\n");
    }
    printf("Минимальный вес = %d\n", W);
    free(E);
    free(E1);
    free(sets);
	return (0);
}
