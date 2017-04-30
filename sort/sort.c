#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// 顺序打印数组
// 输入：
//      a:将要打印的数组
//      N:数组的长度
// 输出：
//      无
void PrintArray(unsigned int a[], unsigned int N)
{
    unsigned int index=0;
    printf("%d",a[0]);
    for (index=1;index<N;index++){
        printf("->%d",a[index]);
    }
    printf(" end \n");
}

// 插入排序
// 输入：
//      a:将要被排序的数组
//      N:数组的长度
// 输出：
//      无
void InsertionSort(unsigned int* a, unsigned int N)
{
    unsigned int pos_sorted=0; //表示在[0,pos_sorted]之间的数据都已经被排好序了
    signed int index_sorted=0; //指示在排好序的序列中寻找新元素的插入点
    unsigned int temp= *a; //index_sorted位置的元素
    for (pos_sorted=1; pos_sorted<N; pos_sorted++){
        temp = *(a+pos_sorted);
        for (index_sorted=pos_sorted; index_sorted>0 && *(a+index_sorted-1) > temp;index_sorted--){
            *(a+index_sorted) = *(a+index_sorted-1); 
        }
        *(a+index_sorted) = temp;
    }
}
// 希尔排序
// 输入：
//      a:将要被排序的数组
//      N:数组的长度
// 输出：
//      无
void ShellSort(unsigned int* a, unsigned int N)
{
    unsigned int increasement=0;
    unsigned int i=0,j=0,k=0;
    unsigned int temp=0;
    for (increasement=N/2; increasement>0; increasement/=2){
        for (i=0;i<increasement;i++){
            temp = *(a+i);
            for (j=i;(j+increasement)<N;j+=increasement){
                if (temp > *(a+j+increasement)){
                    *(a+j) = *(a+j+increasement);
                }else{
                    *(a+j) = temp;
                    temp = *(a+j+increasement);
                }
            }
            *(a+j) = temp;
            printf("The array after %dth sorting is:",k++);
            PrintArray(a,N);
        }
        printf("\n");
    }
}
// 归并排序
// 输入：
//      a:将要被排序的数组
//      N:数组的长度
// 输出：
//      无
unsigned int* MergeSortRecursive(unsigned int* a, unsigned int N)
{
    unsigned int left_index=0,right_index=0,main_index=0;
    unsigned int center_pos = N/2;
    unsigned int left_length = N/2;
    unsigned int* temp_result = (unsigned int *)malloc(sizeof(unsigned int)*N);
    unsigned int* left_result;
    unsigned int* right_result;
    assert(N!=0);
    
    printf ("left len:%d, N:%d\n",left_length,N);
    if (left_length > 1){
        left_result = MergeSortRecursive(a,left_length);
        right_result = MergeSortRecursive(a+left_length,N-left_length);
    } else {
        left_result = a;
        right_result = a+1;
    }
    
    while ((left_index<left_length) && (right_index<(N-left_length))){
        if (*(left_result+left_index) <= *(right_result+right_index)){
            *(temp_result+main_index++) = *(left_result+left_index++);
        } else {
            *(temp_result+main_index++) = *(right_result+right_index++);
        }
        printf ("left:right = %d:%d,temp_result:%d\n",*(left_result+left_index),*(right_result+right_index),*(temp_result+main_index-1));
    }
    
    if ((left_index == left_length) && (right_index < (N-left_length))){
        while(right_index < (N-left_length)){
            *(temp_result+main_index++) = *(right_result+right_index++);
            printf("temp_result:%d\n",*(temp_result+main_index-1));
        }
    } else {
        while(left_index < left_length){
            *(temp_result+main_index++) = *(left_result+left_index++);
            printf("temp_result:%d\n",*(temp_result+main_index-1));
        }
    }
    
    return temp_result;
}

// 快速排序
// 输入：
//      a:将要被排序的数组
//      N:数组的长度
// 输出：
//      无
void QuickSort(unsigned int* a,unsigned int N)
{
    unsigned int temp=0;
    unsigned int center=0;
    unsigned int center_index=N/2, left_index=0, right_index=N-1;
    if (N > 2){
        // Firstly, adjust the order among a[left_index] a[center_index] and a[right_index].
        // Attention: The order of comparation must be AB,AC,BC. Why ? 
        if (*a > *(a+center_index)){
            temp = *a;
            *a = *(a+center_index);
            *(a+center_index) = temp;
        } 
        if (*a > *(a+right_index)){
            temp = *a;
            *a = *(a+right_index);
            *(a+right_index) = temp;
        }
        // printf("left=%d, center=%d, right=%d.\n",*a,*(a+center_index),*(a+right_index));
        
        if (*(a+center_index) > (*(a+right_index))){
            temp = *(a+center_index);
            *(a+center_index) = *(a+right_index);
            *(a+right_index) = temp;
        }
        // Secondly, swap the a[center_index] and a[right_index] to make sure the last element of this array is a[center_index].
        temp = *(a+right_index);
        *(a+right_index) = *(a+center_index);
        *(a+center_index) = temp;
        // printf("left=%d, center=%d, right=%d.\n",*a,*(a+center_index),*(a+right_index));
        left_index=0;right_index=N-2;
        while(left_index < right_index){
            // printf("left_index=%d, right_index=%d.\n",left_index,right_index);
            // printf("\t a[left]=%d, a[right]=%d, a[center]=%d \n",*(a+left_index),*(a+right_index),*(a+N-1));
            if (*(a+left_index) < *(a+N-1)) {
                left_index ++;
            } else {
                if (*(a+right_index) > *(a+N-1)) {
                    right_index --;
                } else {
                    temp = *(a+right_index);
                    *(a+right_index) = *(a+left_index);
                    *(a+left_index) = temp;
                    left_index++;
                    right_index--;
                }
            }
        }
        QuickSort(a,left_index);
        QuickSort(a+left_index,N-left_index);
    } else if (N == 2){
        if (*a > *(a+1)){
            temp = *(a+1);
            *(a+1) = *a;
            *a = temp;
        }
    }
}

void main(void)
{
    unsigned int a[] = {8,64,51,32,21,15,37,53,72};
    unsigned int* merge_sort_result=NULL;
    printf("The initial array is:"); PrintArray(a,sizeof(a)/sizeof(a[0]));
    //InsertionSort(a,sizeof(a)/sizeof(a[0]));
    //printf("The InsertionSorted array is:"); PrintArray(a,sizeof(a)/sizeof(a[0]));
    //ShellSort(a,sizeof(a)/sizeof(a[0]));
    // merge_sort_result = MergeSortRecursive(a,sizeof(a)/sizeof(a[0]));
    // PrintArray(merge_sort_result,sizeof(a)/sizeof(a[0]));
    QuickSort(a,sizeof(a)/sizeof(a[0]));PrintArray(a,sizeof(a)/sizeof(a[0]));
    printf("Hello World !!! \n");
    
}