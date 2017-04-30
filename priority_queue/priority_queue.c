#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct __binary_heap* binary_heap;
struct __binary_heap {
    unsigned int capacity;
    unsigned int size;
    unsigned int *heap;
};

binary_heap CreateBinaryQueue(unsigned int* a,unsigned int N);
void PrintHeap(binary_heap bi_heap);



binary_heap CreateBinaryQueue(unsigned int* a,unsigned int N)
{
    unsigned int index=0,temp_index=0;
    
    binary_heap bi_heap = (binary_heap)malloc(sizeof(struct __binary_heap));
    assert(bi_heap != NULL);
    bi_heap->heap = (unsigned int*)malloc(sizeof(unsigned int)*(N+1)); // add a sentinal element
    bi_heap->capacity = N+1;
    bi_heap->size=1;
    // copy the data from array to heap
    for (index=0;index<N;index++){
        *(bi_heap->heap) = *(a+index);
        for (temp_index=index+1;temp_index>1 && *(bi_heap->heap+temp_index/2) > *(bi_heap->heap);temp_index/=2){
            *(bi_heap->heap+temp_index) = *(bi_heap->heap+temp_index/2);
        }
        *(bi_heap->heap+temp_index) = *(bi_heap->heap);
        bi_heap->size ++;
        bi_heap->capacity ++;
        PrintHeap(bi_heap);
    }
    printf("size:%d\n",bi_heap->size);    
    return bi_heap;
}
unsigned int ExtractMax(binary_heap bi_heap)
{
    unsigned int index=0;
    *(bi_heap->heap)=*(bi_heap->heap+1);
    // *(bi_heap->heap+1) = *(bi_heap->heap+bi_heap->size);
    for (index=2;index<bi_heap->size-1;index*=2){
        // printf("index=%d,left=%d,right=%d,tail=%d\n",index,*(bi_heap->heap+index),*(bi_heap->heap+index+1),*(bi_heap->heap+bi_heap->size-1));
        if ((*(bi_heap->heap+index) < *(bi_heap->heap+index+1)) && (*(bi_heap->heap+bi_heap->size-1) > *(bi_heap->heap+index))){
            *(bi_heap->heap+index/2) = *(bi_heap->heap+index);
        } else if ((*(bi_heap->heap+index) > *(bi_heap->heap+index+1)) && (*(bi_heap->heap+bi_heap->size-1) > *(bi_heap->heap+index+1))){
            *(bi_heap->heap+index/2) = *(bi_heap->heap+index+1);
            index++;
        } else {
            break;
        }
    }
    *(bi_heap->heap+index/2) = *(bi_heap->heap+bi_heap->size-1);
    bi_heap->size --;
    // printf("size:%d, pop:%d ----",bi_heap->size,*(bi_heap->heap));
    PrintHeap(bi_heap);
    return *(bi_heap->heap);
}

void PrintHeap(binary_heap bi_heap)
{
    unsigned int index=0;
    while(index++ < bi_heap->size-1){
        printf("(%d)%d->",index,*(bi_heap->heap+index));
    }
    printf("end\n");
}
void main(void)
{
    unsigned int a[] = {31,26,65,68,19,32,24,16,21,13};
    unsigned int result=0;
    binary_heap bi_heap = CreateBinaryQueue(a,sizeof(a)/sizeof(a[0]));
    PrintHeap(bi_heap);
    while (bi_heap->size>1){
        result=ExtractMax(bi_heap);
        printf("pop %d \n",result);
    }
    printf("Hello World !!\n");
    
}