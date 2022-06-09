#ifndef SORT_H__
#define SORT_H__

#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

#include "metrics.h"


// Use essa função para movimentar dados 
template <typename T>
void swap(T* a, T *b)
{

    T* tmp = a;
    a      = b;
    b      = tmp;
}


template <typename T>
void bubble_sort_internal(T* array, int size, bool (*compare)(T&, T&), PerformanceMetrics *p)  
{
    // bubble sort
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            p->n_comp++;   // incrementa o número de comparações
            if (compare(array[j], array[j + 1]))
            {
                p->n_mov+=3; // swap realiza tres movimentacao de dados
                swap(&array[j], &array[j + 1]);
            }
        }
    }
}



template <typename T>
void insertion_sort_internal(T* array, int size,  bool (*compare)(T&, T&), PerformanceMetrics *p)
{
    // insertion sort
    for (int i = 1; i < size; i++)
    {
        T tmp = array[i];   
        int j = i - 1;
        while (j >= 0 && compare(tmp, array[j]))
        {
            p->n_comp++;   // incrementa o número de comparações
            p->n_mov++;   // incrementa o número de movimentações
            array[j + 1] = array[j];
            j--;
        }   
        array[j + 1] = tmp;
        p->n_comp++;
        p->n_mov++;
    }
}


template <typename T>
void selection_sort_internal(T* array, int size, bool (*compare)(T&, T&), PerformanceMetrics *p)
{
    for (int i = 0; i < size; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            p->n_comp++;
            if (compare(array[j], array[min]))
                min = j;
        }
        swap(&array[i],&array[min]);
        p->n_mov+=3;
    }
}


template<typename T>
void merge(T* arr, int start, int end, bool (*compare)(T&, T&), PerformanceMetrics* p)
{

    // left_start: start index of first half [start, mid]
    // right_start: start index of second half [mid+1, end]
    // tmp_start: start index of temp
    // temp: temporary vector to store the merged array
    int left_start, right_start, tmp_start, mid;

    vector<T> temp(end -start + 1);

    mid = (start + end) / 2;
    tmp_start   = 0;
    left_start  = start;
    right_start = mid + 1;

    while (left_start <= mid && right_start < end)
    {
        p->n_comp++;
        if (compare(arr[left_start], arr[right_start]))
        {
            p->n_mov++;
            temp[tmp_start] = arr[left_start];
            ++left_start;
            ++tmp_start;
        }
        else
        {
            p->n_mov++;
            temp[tmp_start] = arr[right_start];
            ++right_start;
            ++tmp_start;
        }
    }

    while (left_start <= mid)
    {
        p->n_mov++;
        temp[tmp_start] = arr[left_start];
        ++left_start;
        ++tmp_start;
    }

    while (right_start < end)
    {
        p->n_mov++;
        temp[tmp_start] = arr[right_start];
        ++right_start;
        ++tmp_start;
    }

    // write the merged sequence back to the original array
    for (int i = start; i < end; ++i)
    {
        p->n_mov++;
        arr[i] = temp[i - start];
    }

}


template <typename T>
void mergesort_internal(T* array, int start, int end, bool (*compare)(T&, T&), PerformanceMetrics *p)
{
    if( start < end )
    {
        int mid = (start + end) / 2;
        mergesort_internal(array, start, mid, compare, p);
        mergesort_internal(array, mid + 1, end, compare, p);
        merge(array, start, end, compare, p);
    }

}

template <typename T>
int partition(T* arr, int lo, int hi, bool (*compare)(T&, T&),PerformanceMetrics *p){
	
	T pivot = arr[hi];
	int i     = lo-1;
	for (int j = lo; j <= hi - 1; j++){
        p->n_comp++;
        if(compare(arr[j], pivot))
        {
            p->n_mov+=3;
            i++;
			swap(&arr[i],&arr[j]);
		}
	}
    p->n_mov+=3;
	swap(&arr[i+1],&arr[hi]);
	return i+1;
}

template <typename T>
void quicksort_internal(T* array, int lo, int hi, bool (*compare)(T&, T&), PerformanceMetrics *p)
{
	if(lo<hi)
    {
		int pi = partition(array,lo,hi,compare,p);
		quicksort_internal(array,lo,pi-1,compare,p);
		quicksort_internal(array,pi+1,hi,compare,p);
	}
}


template <typename T>
void bubble_sort(T* array, int size, bool (*compare)(T&, T&))  
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p,"bubble_sort");
    auto t1 = Clock::now();
    bubble_sort_internal(array, size, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    PerformanceMetricsPrint(&p);
}

template <typename T>
void selection_sort(T* array, int size, bool (*compare)(T&, T&))  
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p, "selection_sort");
    auto t1 = Clock::now();
    selection_sort_internal(array, size, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    PerformanceMetricsPrint(&p);
}

template <typename T>
void insertion_sort(T* array, int size, bool (*compare)(T&, T&))  
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p, "insertion_sort");
    auto t1 = Clock::now();
    insertion_sort_internal(array, size, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    PerformanceMetricsPrint(&p);
}


template <typename T>
void merge_sort(T* array, int size, bool (*compare)(T&, T&))  
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p, "merge_sort");
    auto t1 = Clock::now();
    mergesort_internal(array, 0, size, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    PerformanceMetricsPrint(&p);
}


template <typename T>
void quick_sort(T* array, int size, bool (*compare)(T&, T&))  
{
    PerformanceMetrics p;
    SetUpPerformanceMetrics(&p, "quick_sort");
    auto t1 = Clock::now();
    quicksort_internal<T>(array, 0, size, compare, &p);
    auto t2 = Clock::now();
    std::chrono::duration<double> diff = t2 - t1;
    PerformanceMetricsCPUTime(&p, diff.count());
    PerformanceMetricsPrint(&p);
}

#endif
