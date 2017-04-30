#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //提供bool类型的变量定义 


/**
单向链表的各种操作 
**/ 
typedef struct _node node;
typedef node* mList;
struct _node{
	node* next;
	int data;	
};


mList CreateList()
{
	mList header = (mList)malloc(sizeof(node));
	header->next = NULL;
	header->data = 0;
	return header;
} 

/*
Find the node whose next node->data is data. We don't handle the header node here.
*/
node* FindNode(mList list,int data)
{
	node* index_node = list;

    if (index_node->data == data)
        return NULL;
    
	while(index_node->next->next != NULL){
		if (index_node->next->data == data)
			return index_node;
		else
			index_node = index_node->next;
	}
    return index_node;
}

/*
Insert data at the position specified by position. insert-back
*/
mList InsertNode(mList list,int pos, int data){

	node* position = FindNode(list,pos);
	node* new_node = (node*)malloc(sizeof(node));
	
	if (new_node == NULL){
		printf ("Out of Resources !!!\n");
	}
	
    // the data is going to be inserted at the header of the list. 
	if (position == NULL){
		new_node->next = NULL;
		list->next = new_node;
		new_node->data = data; 
    }
    else{
		new_node->data = data;
        new_node->next = position->next->next;
		position->next->next = new_node;
	}
	return list;
}
/*
Delete the node behind the node specified by pos
*/
mList DeleteNode(mList list, int pos)
{
    node* position=FindNode(list,pos);
    // if the header is about to be deleted.
    if (position == NULL)
        return list->next;
    else{
        position->next = position->next->next;
        return list;
    }
}

//Check if the list has a loop, if it has then get the entry of the loop.
node* FindLoop(mList list)
{
    node* fast_node = list;
    node* slow_node = list;
    while ((fast_node->next != NULL) && (fast_node->next->next != NULL)){
        printf("fast_node: %d, slow_node: %d\n",fast_node->data,slow_node->data);
        fast_node = fast_node->next->next;
        slow_node = slow_node->next;
        if  (fast_node == slow_node){
            // find the loop, continue to find the entrance.
            fast_node = list;
            while(fast_node != slow_node){
                fast_node = fast_node->next;
                slow_node = slow_node->next;
            }
            return fast_node;
        }
    }
    return NULL;
}

//Check if the two lists has interface. assume that the list has a loop and not and
//then handle these two situationa relatively.


// get the Kth node from the back of the list.
node* GetKth(mList list, unsigned int k)
{
    unsigned int index = 1;
    node* node_index = list;
    node* result_node = list;
    while(index++ < k)
        node_index = node_index->next;
    while(node_index->next != NULL){
        result_node = result_node->next;
        node_index = node_index->next;
    }
    return result_node;    
}
/////////////////////////////////////////////////////////////////////
// merge two ordered list.


// reverse the list.( do not use the head-insert) 
mList Reverse(mList list)
{
    mList result = (mList)malloc(sizeof(node));
    node* node_index_l = list;// node index in list
    result->next = NULL;
    result->data = node_index_l->data;
    while(node_index_l != NULL){
        node* temp_node = (node*)malloc(sizeof(node));
        temp_node = 
    
}

void PrintList(mList list)
{
	mList index_list = list;
	while(index_list->next != NULL){
		printf ("%d -> ",index_list->data);
		index_list = index_list->next;
	}
	printf ("%d end \n",index_list->data);
}
//////////////////////////////////////////////////////////////////////////////////
// find the last node form the list
node* FindLastNode(mList list)
{
    mList temp_list = list;
    while (temp_list->next != NULL)
        temp_list = temp_list->next;
    return temp_list;
}

int main(int argc, char *argv[]) {
	int a[]={1,2,3,4,5,6,7,8,9};
    int loop[]={100,101,102,103};
	char i=0;
    node* loop_entrance = NULL;
    unsigned int k=1;
    node* kth_node = NULL;// the Kth node from the back of the list.
    // create a loop list.
    mList loop_list = CreateList();
    mList header = loop_list;
    loop_list->data = loop[0];
    for (i=1; i<(sizeof(loop)/sizeof(loop[0])); i++)
    {
        node* temp_node = (node*) malloc(sizeof(node));
        temp_node->data = loop[i];
        loop_list->next = temp_node;
        loop_list = loop_list->next;
    }
    loop_list->next = header;
    
	mList list = CreateList();
	list->data = a[0];
	for (i=0; i<(sizeof(a)/sizeof(a[0]))-1; i++)
		list = InsertNode(list,a[i],a[i+1]);
    node* last_node = FindLastNode(list);
    //last_node->next = header;
	
    
    // handle the list.
    PrintList(list);
    printf("\n");
    list = DeleteNode(list,a[8]);
    
    if ((loop_entrance = FindLoop(list)) == NULL)
        printf("there is no loop in this list \n");
    else
        printf("find a loop in this list, its entrance is %d \n",loop_entrance->data);
    
    k=3;
    kth_node = GetKth(list,k);
    printf("the %dth node from the back of the list is:%d \n",k,kth_node->data);
    PrintList(list);
	return 0;
}
