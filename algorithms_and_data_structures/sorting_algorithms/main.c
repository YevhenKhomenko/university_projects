

#include <stdio.h>
#include <stdlib.h>
#define N 1000 // 10000, 100000
#define R 100
#define RAND(R) rand()%R
#define CNT_PRN printf("\n cnt_cmp = %lld cnt_cpy = %lld\n\n",cnt_cmp,cnt_cpy);

long cnt_cmp, cnt_cpy;

int printf_array(int a[],int n);
int best_array(int a[],int n);
int worst_array(int a[],int n);
int avg_array(int a[],int n,int k);
int counting_sort(int a[], int n, int max);
int bubble_sort(int a[],int n);
int heap_sort(int a[], int n);
int build_max_heap(int a[],int n);
int max_heapify(int a[], int i,int n);



int main() {
    
    int array[N];
    
    best_array(array,N);
    
    avg_array(array, N, 3);
    
    worst_array(array,N);
  
    
    return 0;
}
int printf_array(int a[], int n){
    int i;
    for(i = 0; i < n; i++) printf("%d\t",a[i]);
    printf("\n\n");
    return i;
}

int best_array(int a[],int n){
    int i, max;
    max = a[0];
    for(i = 0; i < n; i++){
        a[i]=i;
        if(max < a[i]) max = a[i];
    }
    printf("Best array: \n");
    //printf_array(a, n);
    //bubble_sort(a,N);
    // counting_sort(a, N, max);             //call sorting method here!
    //heap_sort(a, N);
    
    return i;
}

int worst_array(int a[],int n){
    int i, max;
    max = a[0];
    for(i = 0; i < n; i++){
       a[i]=n - 1 - i;
        if(max < a[i]) max = a[i];
    }
    printf("Worst array: \n");
    //printf_array(a, n);
    //bubble_sort(a,N);
    //counting_sort(a, N, max);           // call sorting method here!
    //heap_sort(a, N);
    return i;
}

int avg_array(int a[],int n, int k){
    int i,j, max;
    max = a[0];
    for(j = 1; j <= k; j++){
        srand(j);
        for(i = 0; i < n; i++){
            a[i] = RAND(R);
            if(max < a[i]) max = a[i];
        }
        printf("Average array: \n");
        //printf_array(a, n);
        //bubble_sort(a,N);
        //counting_sort(a, N, max);         // call sorting method here!
        //heap_sort(a, N);
        }
    
    return j;
}

int bubble_sort(int a[], int n){
    int temp,i,j;
    
    for( i = 0; i < n - 1; i++){
        for(j = 0; j < n - 1 - i ; j++){
            cnt_cmp++;
                if(a[j] > a[j+1]){
                temp = a[j+1];
                a[j+1]= a[j];
                a[j] = temp;
                    cnt_cpy += 3;
            }
        }
        
    }
    printf("Bubble sort:\n");
   // printf_array(a, n);
    CNT_PRN;
    cnt_cmp = 0;
    cnt_cpy = 0;
    
    
    return 0;
}

int counting_sort(int a[], int n,int max){
    int  count[max + 1];
    int res[n];
    int j;
    for(j = 0; j <= max ; j++){
        count[j] = 0;
       
    }
    for(j = 0;j < n; j++){
        count[a[j]]=count[a[j]]+1;
        cnt_cpy++;
    }
    for(j = 1; j <= max; j++) {
        count[j] = count[j - 1] + count[j];
     
    }
    for(j = 0; j < n; j++){
        res[count[a[j]] - 1] = a[j];
        cnt_cpy++;
        count[a[j]] = count[a[j]] - 1;
        cnt_cpy++;
    }
    printf("Counting sort:\n");
    //printf_array(res, N);
    CNT_PRN;
    cnt_cmp = 0;
    cnt_cpy = 0;
    printf("\n\n");
    return 0;
}

int heap_sort(int a[],int n){
    build_max_heap(a,n);
    int heapsize,i, temp;
    heapsize = n;
    for(i = n - 1;i > 0; i--){
        temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        cnt_cpy += 3;
        heapsize--;
        max_heapify(a, 0, heapsize);
    }
    printf("Heap sort:\n");
    //printf_array(a, N);
    CNT_PRN;
    cnt_cmp = 0;
    cnt_cpy = 0;
    return 0;
}

int build_max_heap(int a[],int n){
    int i;
    for(i = n/2; i >= 0; i--){
        max_heapify(a, i, n);
    }
    return 0;
}

int max_heapify(int a[], int i, int n){
    int left, right;
    int largest, temp;
    
    left = 2 * (i + 1) - 1;
    right = 2 * (i + 1);
    
    if((left < n) && (a[left] > a[i])){
        largest = left;
        cnt_cmp++;
    }else {
        largest = i;
    }
    
    if((right < n) && (a[right] > a[largest])){
        largest = right;
        cnt_cmp++;
    }
    if(largest != i){
        temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        cnt_cpy += 3;
        max_heapify(a, largest, n);
    }
    return 0;
}
 


