#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned int ns[] = {1000, 10000, 25000, 50000, 75000, 100000, 250000, 500000, 750000, 1000000};


void fill_increasing(int *t, unsigned int n) {
    int i;
    for (i = 0; i < n; i++) {
        t[i] = i;
    }
}
 
void fill_decreasing(int *t, unsigned int n) {
    int i;
    for (i = 0; i < n; i++) {
        t[i] = -i;
    }
}
 
void fill_vshape(int *t, unsigned int n) {
            int *begin;
            int *end;
			begin = t;
            end = t + n - 1;
            int k = n;
            while (end - begin > 1)
            {
                *begin = k;
                k--;
                *end = k;
                k--;
                begin++;
                end--;
            }
}
 
void fill_random(int *t, unsigned int n) {
    int i;
    for (i = 0; i < n; i++) {
        t[i] = rand();
    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
	*yp = temp;
}

void selection_sort(int *t, unsigned int n) 
{ 
    int i, j, min_idx; 
   
    for (i = 0; i < n-1; i++) 
    { 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (t[j] < t[min_idx]) 
            min_idx = j; 
        swap(&t[min_idx], &t[i]); 
    } 
} 

 
void printArray(int *t, int n)
{
    int i;
    for (i=0; i < n; i++)
        printf("%d ", t[i]);
    printf("\n");
}
 
void insertion_sort(int *t, unsigned int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = t[i];
        j = i - 1;
 
        while (j >= 0 && t[j] > key) {
            t[j + 1] = t[j];
            j = j - 1;
        }
        t[j + 1] = key;
    }
}

int partition(int *t, int low, int high) 
{ 
    int pivot = t[high];
    int i = (low - 1); 
  	int j;
    for (j = low; j <= high- 1; j++) 
    {  
        if (t[j] <= pivot) 
        { 
            i++;    
            swap(&t[i], &t[j]); 
        } 
    } 
    swap(&t[i + 1], &t[high]); 
    return (i + 1); 
} 

int random_partition(int *t, int low, int high)
{
	int pivot = low + rand()%high;
	swap(&t[pivot], &t[high]);
	return partition(t, low, high);
}


void quick__sort(int *t, int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(t, low, high); 
        quick__sort(t, low, pi - 1); 
        quick__sort(t, pi + 1, high); 
    } 
} 

void quick_sort(int *t, unsigned int n)
{
	quick__sort(t, 0, n-1);
}


int heap_d(int *t, int index, int *psize){
	int size = *psize;
	int l = index * 2 + 1;
	int r = index * 2 + 2;
	int argmin;
	if(l>=size){
		if((r >= size) || (t[l] < t[r]))
		return argmin = l;
		 else 
		 return r;
		if(t[argmin] < t[index]){
			swap(&t[index], &t[argmin]);
			heap_d(t, argmin, size);
		}
	}
}

void heap_up(int *t, int index){
	if(index > 0){
		int parent = (index -1)/2;
		if(t[index] < t[parent]){
			swap(&t[index], &t[parent]);
			heap_up(t, parent);
		}
	}
}

int heap_poll(int *t, int *psize){
	int size = *psize;
	int v = t[0];
	size -= 1;
	t[0] = t[size];
	heap_d(t, 0, size);
	return v;
}

void heap_add(int *t, int *psize, int *v){
	int size = *psize;
	t[size] = &v;
	heap_up(t, size);
	size += 1;
}

 
void heap_sort(int *t, unsigned int n) {
    int size = 0;
    int i;
    for(i = 0; i < n; i++){
    	heap_add(t, size, &t[i]);
	}
	for(i = 0; i < n; i ++){
		t[i] = heap_poll(t, size);
	}
}
 
void is_random(int *t, unsigned int n) {
    return;
}
 
void is_increasing(int *t, unsigned int n) {
    int i;
    for (i = 1; i < n; i++) {
        assert(t[i] > t[i - 1]);
    }
}
 
void is_decreasing(int *t, unsigned int n) {
    int i;
    for (i = 1; i < n; i++) {
        assert(t[i] < t[i - 1]);
    }
}
 
void is_vshape(int *t, unsigned int n) {
    int *begin = t;
    int *end = t + n - 1;
 
    while (end - begin > 1) {
        assert(*begin > *end);
        begin++;
        assert(*end > *begin);
        end--;
    }
}
 
void is_sorted(int *t, unsigned int n) {
    int i;
    for (i = 1; i < n; i++) {
        assert(t[i] >= t[i - 1]);
    }
}

//


 
void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, /*fill_vshape*/ };
void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, /*is_vshape */};
void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, /*heap_sort*/ };
 
char *fill_names[] = { "Random", "Increasing", "Decreasing", "V_shape" };
char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };
 
int main() {
	FILE *fp=fopen("dane.txt", "w");
    int i,j,k;
    for (i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions) ; i++) {
    void(*sort)(int *, unsigned int) = sort_functions[i];
 
        for (j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
            void (*fill)(int *, unsigned int) = fill_functions[j];
            void (*check)(int *, unsigned int) = check_functions[j];
 
	            for (k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
	            	
	                unsigned int n = ns[k];
	                int *t = malloc(n * sizeof(*t));
	 				
	                fill(t, n);
	                check(t, n);
	                clock_t begin = clock();
	                sort(t, n);
	                clock_t end = clock();
	                is_sorted(t, n);
	                printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double)CLOCKS_PER_SEC);
	                fprintf(fp, "%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double)CLOCKS_PER_SEC);
	       
	                free(t);
	            }
        }
   }
//   int z,x;
//   for(z = 0; z < 16; z++){
//   	x = rand()%50+20;
//   	printf("X = %d\n",x);
//   }
   fclose(fp);
    return 0;
}
