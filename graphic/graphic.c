#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_VERTEX_NUM 100

typedef struct __edge_node{
    struct __edge_node* next;
    unsigned int next_vertex_pos; //当前顶点所构成的一条边的权重
} list_node;
typedef list_node* p_list_node;

typedef struct __vertex{
    struct __vertex* next_vertex; //pointer to the next vertex
    unsigned char cur_ver_index; // index of current vertex
    unsigned int weight;
} vertex;

typedef struct __graph{
    vertex vertex_table[MAX_VERTEX_NUM];
    unsigned int vertex_size;
} digraph;

/**
    _________
    |_________| -> |_________| -> |_________|
    |_________| -> |_________| -> |_________|
    |next=NULL| -> invalid index in table
    |weight=0 |
    |_________| -> |_________| -> |_________|
    |_________|
    |_________|
    |_________| -> |_________| -> |_________|
    |_________|
    |_________| -> |_________| -> |_________|
    |_________| -> |_________| -> |_________|
**/

unsigned char IsVertexExist(digraph* g, unsigned char vertex_checked)
{
    unsigned int index = vertex_checked - 'A';
    assert(index <= MAX_VERTEX_NUM);
    return (g->vertex_table[index].weight != 0);
}

// create a digraph with two vertexes and edge.
// if the weight is 0, we think this edge is invalid.
void CreatGraphic(digraph* g, unsigned char start_vertex,unsigned char end_vertex,unsigned int weight)
{
    unsigned int index=0;
    assert(weight > 0);
    assert((start_vertex != 0)&&(end_vertex != 0));
    vertex* temp_start_vertex;
    vertex* temp_end_vertex;
    while(index++ < MAX_VERTEX_NUM){
        g->vertex_table[index].weight = 0;
        g->vertex_table[index].cur_ver_index = 0;
        g->vertex_table[index].next_vertex = NULL;
    }
    g->vertex_size = 0;
    // check the input.
    assert(start_vertex - 'A' < MAX_VERTEX_NUM);
    assert(end_vertex - 'A' < MAX_VERTEX_NUM);
    
    temp_end_vertex = (vertex*)malloc(sizeof(vertex));
    temp_end_vertex->next_vertex = NULL;
    temp_end_vertex->cur_ver_index = end_vertex - 'A';
    temp_end_vertex->weight = weight;
    g->vertex_table[start_vertex-'A'].next_vertex = temp_end_vertex; 
    g->vertex_table[start_vertex-'A'].weight = 1; //use it as the valid-flag of this vertex in table.
    g->vertex_size ++;
    g->vertex_table[end_vertex-'A'].weight = 1;
    g->vertex_size ++;
}

// add an edge to the digraphic
// start_vertex: the start vertex of the added edge.
// end_vertex: the end vertex of the added edge.
// weight: the weight of the added edge.
void AddEdge(digraph* g, unsigned char start_vertex,unsigned char end_vertex,unsigned int weight)
{
    vertex* temp_start_vertex;
    vertex* temp_end_vertex;
    assert(weight > 0);
    assert((start_vertex != 0)&&(end_vertex != 0));
    // if the start vertex is not in the digraph, the we think the edge to be added is invalid; 
    if (!IsVertexExist(g,start_vertex)){
        printf ("Invalid edge, please check the input vertexes \n");
    } else {
        // if either of the two vertexes is in the digraph , then we must add the new edge.
        // first ,consider the situation that only one vertex is in the digraph.
        if (!IsVertexExist(g,end_vertex)){
            // insert the vertex into the list from its header.
            temp_end_vertex = (vertex*)malloc(sizeof(vertex));
            assert(temp_end_vertex != NULL);
            temp_end_vertex->cur_ver_index = end_vertex - 'A';
            temp_end_vertex->next_vertex = g->vertex_table[start_vertex - 'A'].next_vertex;
            temp_end_vertex->weight = weight;
            g->vertex_table[start_vertex - 'A'].next_vertex = temp_end_vertex;
            g->vertex_table[end_vertex - 'A'].weight = 1;
            g->vertex_size ++;
        } else {
            // insert the vertex into the list from its header.
            temp_end_vertex = (vertex*)malloc(sizeof(vertex));
            assert(temp_end_vertex != NULL);
            temp_end_vertex->cur_ver_index = end_vertex - 'A';
            temp_end_vertex->next_vertex = g->vertex_table[start_vertex - 'A'].next_vertex;
            temp_end_vertex->weight = weight;
            g->vertex_table[start_vertex - 'A'].next_vertex = temp_end_vertex;            
        }        
    }
    
}

TopologySort(digraph* G, vertex* start_vertex, vertex* end_vertex)
{
    
}

void PrintGraphic(digraph* g)
{
    unsigned int index_in_table=0;
    vertex* temp_vertex = NULL;
    while(index_in_table < MAX_VERTEX_NUM){
        if (g->vertex_table[index_in_table].weight != 0){
            printf("%c", index_in_table + 'A');
            temp_vertex = g->vertex_table[index_in_table].next_vertex;
            while(temp_vertex != NULL){
                printf("->%c", temp_vertex-> cur_ver_index + 'A');
                temp_vertex = temp_vertex->next_vertex;
            }
            printf("\n");
        }
        index_in_table++;
    }
}

void CreateTestGraphic(void)
{
    digraph* G=(digraph*)malloc(sizeof(digraph));
    printf("The Initial Graphic is : \n");
    CreatGraphic(G,'A','B',1);
    PrintGraphic(G);
    AddEdge(G,'A','D',1);
    AddEdge(G,'A','C',1);
    AddEdge(G,'B','E',1);
    AddEdge(G,'B','D',1);
    AddEdge(G,'C','F',1);
    AddEdge(G,'D','F',1);
    AddEdge(G,'D','G',1);
    AddEdge(G,'E','D',1);
    AddEdge(G,'E','G',1);
    AddEdge(G,'G','F',1);    
    printf("The New Graphic is : \n");
    PrintGraphic(G);
}

void main(void)
{
    digraph* G=(digraph*)malloc(sizeof(digraph));
    printf("The Initial Graphic is : \n");
    CreateTestGraphic();
    PrintGraphic(G);
    printf("Hello World !!! \n");
}

