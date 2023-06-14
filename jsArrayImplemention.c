#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vector
{
    int *arr;
    int size;
    int capacity;
} Vector;

void init(Vector *v)
{
    v->arr = NULL;
    v->size = 0;
    v->capacity = 0;
}

void reserve(Vector *v, int addSize)
{
    int newSize = v->capacity + addSize;
    int *tmp = (int *)calloc(newSize, sizeof(int));
    for (size_t i = 0; i < v->size; i++)
    {
        tmp[i] = v->arr[i];
    }
    free(v->arr);
    v->arr = tmp;
    v->capacity = newSize;
}

void pushBack(Vector *v, int e)
{
    if (v->size == v->capacity)
    {
        reserve(v, v->capacity ? v->capacity : 1);
    }
    v->arr[v->size++] = e;
}

void insert(Vector *v, int index, int e)
{
    if (index > v->size)
    {
        if (index > v->capacity)
        {
            reserve(v, index - v->capacity);
        }
        v->size = index;
    }
    v->arr[index] = e;
}

int at(Vector *v, int index)
{
    if (index < 0 || index > v->size)
    {
        printf("Index not found");
        return -1;
    }
    return v->arr[index];
}

void concat(Vector *v1, Vector *v2)
{
    for (int i = 0; i < v2->size; i++)
    {
        pushBack(v1, v2->arr[i]);
    }
}

void copyWithin(Vector *v, int soursIndex, int copyStartINdex, int copyEndINdex)
{
    for (int i = 0; i < copyEndINdex - copyStartINdex; i++)
    {
        v->arr[soursIndex++] = v->arr[i];
    }
}

Vector *every(Vector *v, bool (*predicat)(int element))
{
    Vector *tmp = (Vector *)calloc(sizeof(Vector), 1);
    init(v);
    for (int i = 0, j = 0; i < v->size; i++)
    {
        if (predicat(v->arr[i]))
        {
            tmp->arr[j++] = v->arr[i];
        }
    }
    return tmp;
}

void filter(Vector *v, bool (*predicat)(int element))
{
    int *arr = (int *)calloc(sizeof(int), v->capacity);
    for (int i = 0, j = 0; i < v->size; i++)
    {
        if (predicat(v->arr[i]))
        {
            arr[j++] = v->arr[i];
        }
    }
    free(v->arr);
    v->arr = arr;
    arr = NULL;
}

void flatMap(Vector *v, int (*UnaryOperator)(int element))
{
    for (int i = 0; i < v->size; i++)
    {
        v->arr[i] = UnaryOperator(v->arr[i]);
    }
}

Vector *map(Vector *v, int (*UnaryOperator)(int element))
{
    Vector *tmp = (Vector *)calloc(sizeof(Vector), 1);
    init(v);
    for (int i = 0, j = 0; i < v->size; i++)
    {
        tmp->arr[i] = UnaryOperator(v->arr[i]);
    }
    return tmp;
}

void forEach(Vector *v, void (*BinaryOperator)(int element, int index, Vector *v))
{
    for (int i = 0; i < v->size; i++)
    {
        BinaryOperator(v->arr[i], i, v);
    }
}

int indexOf(Vector *v, int e)
{
    for (int i = 0; i < v->size; i++)
    {
        if (v->arr[i] == e)
        {
            return i;
        }
    }
    return -1;
}

int lastIndexOf(Vector *v, int e)
{
    for (int i = v->size - 1; i >= 0; --i)
    {
        if (v->arr[i] == e)
        {
            return i;
        }
    }
    return -1;
}

void reduce(Vector *v, int (*BinaryOperator)(int accumulator, int current), int defaultValueAccumulator)
{
    int accumulator = defaultValueAccumulator;
    for (int i = 0; i < v->size; i++)
    {
        accumulator = BinaryOperator(accumulator, v->arr[i]);
    }
}

void reduceRight(Vector *v, int (*BinaryOperator)(int accumulator, int current), int defaultValueAccumulator)
{
    int accumulator = defaultValueAccumulator;
    for (int i = v->size - 1; i >= 0; --i)
    {
        accumulator += BinaryOperator(accumulator, v->arr[i]);
    }
}

void reverse(Vector *v)
{
    int tmp = 0;
    for (int i = 0, j = v->size - 1; i < j; --i, --j)
    {
        tmp = v->arr[i];
        v->arr[i] = v->arr[j];
        v->arr[j] = tmp;
    }
}

Vector *slice(Vector *v, int startIndex, int EndIndex)
{
    Vector *tmp = (Vector *)calloc(sizeof(Vector), 1);
    init(v);
    for (int i = startIndex, j = 0; i <= EndIndex; ++i, ++j)
    {
        tmp->arr[j] = v->arr[i];
    }
    return tmp;
}

int compareIntegers(const void *a1, const void *b1)
{
    const int *a = (const int *)a1;
    const int *b = (const int *)b1;
    if (a < b)
    {
        return -1;
    }
    else if (a > b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void sort(Vector *v)
{
    qsort(v->arr, v->size, sizeof(int), compareIntegers);
}

bool some(Vector *v, bool (*predicat)(int element))
{
    int i = 0;
    while (!predicat(v->arr[i++]))
        ;
    if (i == v->size)
    {
        return false;
    }
    return true;
}

void fill(Vector *v, int startIndex, int value, int endIndex)
{
    for (int i = startIndex; i < endIndex; i++)
    {
        v->arr[i] = value;
    }
}

int findIndex(Vector *v, bool (*predicat)(int element))
{
    for (int i = 0; i < v->size; i++)
    {
        if (predicat(v->arr[i]))
        {
            return i;
        }
    }
    return -1;
}

int find(Vector *v, bool (*predicat)(int element))
{
    int index = findIndex(v, predicat);
    if (index != -1)
    {
        return v->arr[index];
    }
    return -1;
}

int findLastIndex(Vector *v, bool (*predicat)(int element))
{
    for (int i = v->size - 1; i > 0; --i)
    {
        if (predicat(v->arr[i]))
        {
            return i;
        }
    }
    return -1;
}

bool with(Vector *v, int e)
{
    if (indexOf(v, e))
        return true;
    return false;
}

bool predicat(int e)
{
    return e > 1;
}

int UnaryOperator(int e)
{
    return e * 2;
}

void BinaryOperator1(int element, int index, Vector *v)
{
    printf("Element : %d", element);
}

int BinaryOperator(int accumulator, int current)
{
    return accumulator + current;
}

int main()
{
    Vector v1;
    init(&v1);
    pushBack(&v1, 31);
    insert(&v1, 1, 20);
    insert(&v1, 3, 18);

    Vector v2;
    init(&v2);
    pushBack(&v2, 12);
    insert(&v2, 13, 10);
    insert(&v2, 14, 13);

    concat(&v1, &v2);
    copyWithin(&v1, 0, 1, 3);
    every(&v1, predicat);
    filter(&v1, predicat);
    flatMap(&v1, UnaryOperator);
    map(&v1, UnaryOperator);
    forEach(&v1, BinaryOperator1);
    indexOf(&v1, 1);
    lastIndexOf(&v1, 1);
    reduce(&v1, BinaryOperator, 0);
    reduceRight(&v1, BinaryOperator, 0);
    reverse(&v1);
    slice(&v1, 1, 3);
    sort(&v1);
    fill(&v1, 0, 124, 3);
    find(&v1, predicat);
    findIndex(&v1, predicat);
    findLastIndex(&v1, predicat);
    with(&v1, 1);
}
