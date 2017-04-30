#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

////////////////////////////////////////////////////////////////////////////
// binary search tree definition
typedef struct __binary_search_tree bst_node;
typedef bst_node* my_bst;
struct __binary_search_tree{
    bst_node* left_child;
    bst_node* right_child;
    int data;
};
// doubly-linked list definition
typedef struct __doubly_list_node doubly_list_node;
typedef doubly_list_node* dlist;
typedef doubly_list_node* p_dlist_node;
struct __doubly_list_node {
    p_dlist_node prev_node;
    p_dlist_node next_node;
    int data;
};
// single-linked list definition
typedef struct __single_list_node single_list_node;
typedef single_list_node* slist;
typedef single_list_node* slist_node;
struct __single_list_node {
    slist_node next_node;
    int data;
};
// flag definition
typedef enum __flag{
    find_max = 0,
    find_min
} find_max_min;

typedef enum __left_right_flag{
    left = 0,
    right
} left_right_flag;
///////////////////////////////////////////////////////////////////////////////

//create a new empty binary search tree.
my_bst CreateBst(int x)
{
    my_bst root = (my_bst) malloc(sizeof(bst_node));
    assert(root != NULL);
    root->data = x;
    root->left_child = NULL;
    root->right_child = NULL;
    return root;
}
//make tree empty

////////////////////////////////////////////////////////////////////////
//find x in a tree, we don't handle the root node here. if the x is found
// then return the its node. otherwise return null.
bst_node* FindNode(my_bst root, int x)
{
    if (root != NULL){
        if (x < root->data)
            return FindNode(root->left_child,x);
        else if(x > root->data)
            return FindNode(root->right_child,x);
        else
            return root;
    }
    else
        return NULL;
}
//find minimum and maximum value.
int FindMaxMin(my_bst root,find_max_min flag)
{
    assert(root != NULL);
    assert(flag==find_max || flag==find_min);
    
    if (flag == find_max){
        if (root->right_child != NULL)
            return FindMaxMin(root->right_child,flag);
        else
            return root->data;
    } else {
        if (root->left_child != NULL)
            return FindMaxMin(root->left_child,flag);
        else
            return root->data;
    }
}
//insert node
my_bst InsertNode(my_bst root,int x)
{
    bst_node* index_node = root;
    bst_node* temp_node;
    if (x < root->data){
        if (root->left_child != NULL){
            InsertNode(root->left_child,x);
        } else {
            temp_node = (bst_node*) malloc(sizeof(bst_node));
            assert(temp_node != NULL);
            temp_node->data = x;
            temp_node->left_child = NULL;
            temp_node->right_child = NULL;  
            root->left_child = temp_node;
        }
    } else if (x > root->data){
        if (root->right_child != NULL){
            InsertNode(root->right_child,x);
        } else {
            temp_node = (bst_node*) malloc(sizeof(bst_node));
            assert(temp_node != NULL);
            temp_node->data = x;
            temp_node->left_child = NULL;
            temp_node->right_child = NULL;  
            root->right_child = temp_node;
        }
    }

    return root;
}
//delete node
my_bst DeleteNode(my_bst root, int x)
{
    if (x == root->data){
        // for the root node of the tree.
        if ((root->left_child == NULL) && (root->right_child != NULL)){
            root = root->right_child;
        }else if ((root->left_child != NULL) && (root->right_child == NULL)){
            root = root->left_child;
        }else if ((root->left_child == NULL) && (root->right_child == NULL)){
            return NULL;
        }else{
            root->right_child->left_child->left_child = root->left_child;
            root = root->right_child;
        }
    }else if (x > root->data){
        if (root->right_child != NULL){
            if (x == root->right_child->data){
                if ((root->right_child->right_child != NULL) && (root->right_child->left_child == NULL)){
                    root->right_child = root->right_child->right_child;
                }else if ((root->right_child->left_child != NULL) && (root->right_child->right_child == NULL)){
                    root->right_child = root->right_child->left_child;
                }else if ((root->right_child->left_child != NULL) && (root->right_child->right_child != NULL)){
                    root->right_child->left_child->right_child = root->right_child->right_child;
                    root->right_child = root->right_child->left_child;
                }else{
                    free(root->right_child);
                    root->right_child = NULL;
                }
            }
            else
                root->right_child = DeleteNode(root->right_child,x);
        }    
    }else if (x < root->data){
        if (root->left_child != NULL){
            if (x == root->left_child->data){
                if ((root->left_child->right_child != NULL) && (root->left_child->left_child == NULL)){
                    root->left_child = root->left_child->right_child;
                }else if ((root->left_child->left_child != NULL) && (root->left_child->right_child == NULL)){
                    root->left_child = root->left_child->left_child;
                }else if ((root->left_child->left_child != NULL) && (root->left_child->right_child != NULL)){
                    root->left_child->right_child->left_child = root->left_child->left_child;
                    root->left_child = root->left_child->right_child;
                }else{
                    free(root->left_child);
                    root->left_child = NULL;
                }
            }
            else
                root->left_child = DeleteNode(root->left_child,x);
        }
    }
    return root;
}
////////////////////////////////////////////////////////////////////
//translate the bst to a ordered single-end list.


////////////////////////////////////////////////////////////////////
//translate the bst to a ordered single-end list.
slist_node TranBst2SList(my_bst root,slist header,left_right_flag flag)
{
    printf("root=%XH,root->data=%d,header=%XH\n",root,root->data,header);
    if ((root->left_child != NULL)&&(root->right_child != NULL)){
        slist_node cur_node = (slist_node)malloc(sizeof(single_list_node));//current node
        slist_node pre_node ; // previous node
        
        cur_node->data = root->data;
        pre_node = TranBst2SList(root->left_child,header,left);
        pre_node->data = root->left_child->data;
        pre_node->next_node = cur_node;        
        cur_node->next_node = TranBst2SList(root->right_child,NULL,right);
        if (flag == left){
            return cur_node->next_node;
        }else{
            return pre_node;
        }
    }else if ((root->left_child == NULL)&&(root->right_child != NULL)){
        slist_node cur_node = (slist_node)malloc(sizeof(single_list_node));
        
        cur_node->data = root->data;
        cur_node->next_node = TranBst2SList(root->right_child,NULL,right);  
        if (flag == left){
            if (header != NULL){
                header = cur_node;
            }                
            return cur_node->next_node;
        }else{
            return cur_node;
        }
    }else if ((root->left_child != NULL)&&(root->right_child == NULL)){
        slist_node cur_node = (slist_node)malloc(sizeof(single_list_node));//current node
        slist_node pre_node; // previous node
        
        cur_node->data = root->data;
        cur_node->next_node = NULL;
        pre_node = TranBst2SList(root->left_child,header,left);
        pre_node->data = root->left_child->data;
        pre_node->next_node = cur_node;        
        if (flag == left){
            return cur_node;
        }else{
            return pre_node;
        }
    }else{
        slist_node cur_node = (slist_node)malloc(sizeof(single_list_node));
        
        cur_node->data = root->data;
        cur_node->next_node = NULL;
        if (header != NULL)
            header = cur_node;
        return cur_node;
    }
}


///////////////////////////////////////////////////////////////////
//check weather two trees has the same structure, ignoring the data.



///////////////////////////////////////////////////////////////////
//get the number of nodes in kth level.

///////////////////////////////////////////////////////////////////
//get the mirred bst of a specified bst.


///////////////////////////////////////////////////////////////////
//check weather two trees has the same structure, ignoring the data.


////////////////////////////////////////////////////////////////////
// print a bst as follow.
//      6
//    4    8
//   2 5  7  9
// we print it like:
//6
//  4
//    2
//    5
//  8
//    7
//    9
void PrintBst(my_bst root,int index)
{
    unsigned int cnt=0;
    if (root != NULL){
        for (cnt=0;cnt<index;cnt++){
            printf("\t");
        }
        printf("%d\n",root->data);
        index++;
        if (root->left_child != NULL){
            PrintBst(root->left_child,index);
        }
        if (root->right_child != NULL){
            PrintBst(root->right_child,index);
        }   
    }   
}
////////////////////////////////////////////////////////////////////
// print a list
//  1->2->3->4->5
// we print it like:
//  1->2->3->4->5
void PrintList(slist list)
{
	slist index_list = list;
	while(index_list->next_node != NULL){
		printf ("%d -> ",index_list->data);
		index_list = index_list->next_node;
	}
	printf ("%d end \n",index_list->data);
}

void main(void)
{
    int a[] = {7,3,11,1,5,9,13,0,2,4,6,8,10,12,14};
    int index=0;
    my_bst bst_1 = CreateBst(a[0]);
    slist sl_1 = (slist)malloc(sizeof(single_list_node));
    sl_1->next_node=NULL;
    for (index=1;index<(sizeof(a)/sizeof(a[0]));index++)
        bst_1 = InsertNode(bst_1,a[index]);
    PrintBst(bst_1,0);
    {
        //bst_1 = DeleteNode(bst_1,0);
        //PrintBst(bst_1,0);
    }
    
    TranBst2SList(bst_1,sl_1,left);
    PrintList(sl_1);
    
    printf("Hello World\n");    
}