typedef struct pst_node{
    int val;
    struct pst_node* left, *right;
}pst_node;

typedef struct per_stack {
    int top, capacity;
    int* array;
}per_stack;

typedef struct per_queue
{
    int front, rear, size, capacity;
    int* arr;
}per_queue;

typedef struct ver_node{
    int ver;
    struct ver_node *next;
}ver_node;

typedef struct DoubleLLNode {  
    int data;
    struct DoubleLLNode* next;
    struct DoubleLLNode* prev;
    ver_node *vers;
}DoubleLLNode;

typedef struct CircularLLNode {
    int data;
    struct CircularLLNode* next;
    ver_node *vers;
}CircularLLNode;

typedef struct LinkedListNode {
    int data;
    struct LinkedListNode* next;
    ver_node *vers;
}LinkedListNode;

typedef struct pbst{
    struct pbst *left, *right;
    int data, present;
}pbst;

typedef struct RB_Node{
    struct RB_Node *left, *right, *parent;
    int val, color;
}RB_Node;

typedef struct RB_Tree_Node{
    RB_Node *root;
}RB_Tree_Node;

typedef struct Het_Vec_Node {
    void* pointer_data;
    struct Het_Vec_Node* next;
    ver_node *vers;
}Het_Vec_Node;

typedef struct Het_Map_Node {
    void* pointer_data, *pointer_key;
    struct Het_Map_Node* next;
    ver_node *vers;
}Het_Map_Node;

typedef struct per_stack_ll_node{
    int data, ver;
    struct per_stack_ll_node *next;
}per_stack_ll_node;

typedef struct per_stack_ll {
    struct per_stack_ll_node *head;
}per_stack_ll;

//  Persistent Segment Tree

pst_node* pst_node_init();

void pst_build(pst_node* n,int low,int high);

pst_node* pst_update(pst_node* prev, int low, int high, int idx, int value);

int pst_query(pst_node* n, int low, int high, int l, int r);

void set_arr();

//  Persistent Stack

per_stack* per_stack_create(int capacity);

int per_stack_isEmpty(per_stack* per_stack);

per_stack* per_stack_push(per_stack* per_stack, int item);

per_stack* per_stack_pop(per_stack* per_stack);

int per_stack_peek(per_stack* per_stack);

//  Persistent Double Ended Circular Queue

per_queue* per_queue_create(int capacity);

int per_queue_isFull(per_queue* queue);

int per_queue_isEmpty(per_queue* queue);

per_queue* per_queue_insert_front(per_queue* queue, int key);

per_queue* per_queue_insert_rear(per_queue* queue, int key);

per_queue* per_queue_delete_front(per_queue* queue);

per_queue* per_queue_delete_rear(per_queue* queue);

int per_queue_front(per_queue* queue);

int per_queue_rear(per_queue* queue);


//	Persistent Doubly Linked List

DoubleLLNode* per_DoublyLL_insert(DoubleLLNode* head_ref, int new_data, int pos, int ver, int new_ver);

DoubleLLNode* per_DoublyLL_delete(DoubleLLNode* head_ref, int pos, int ver, int new_ver);

void per_DoublyLL_print(DoubleLLNode* head_ref, int pos, int ver);


//  Persistent Circular Linked List

CircularLLNode* per_CircularLL_insert(CircularLLNode* head_ref, int new_data, int pos, int ver, int new_ver);

CircularLLNode* per_CircularLL_delete(CircularLLNode* head_ref, int pos, int ver, int new_ver);

void per_CircularLL_print(CircularLLNode* head_ref, int pos, int ver);


//  Persistent Linked List

LinkedListNode* per_LinkedList_insert(LinkedListNode* head_ref, int new_data, int pos, int ver, int new_ver);

LinkedListNode* per_LinkedList_delete(LinkedListNode* head_ref, int pos, int ver, int new_ver);

void per_LinkedList_print(LinkedListNode* head_ref, int pos, int ver);


//  Persistent Binary Search Tree

pbst* per_bst_insert(pbst *root, int val);

pbst* per_bst_delete(pbst *root, int val);

void per_bst_search(pbst *root, int val);

//  Persistent Red-Black Tree

RB_Tree_Node* per_RBTree_insert(RB_Tree_Node *tree, int n);

RB_Tree_Node* per_RBTree_get_deleted_Tree(RB_Tree_Node *tree, int n);

void per_RBTree_get_search_result(RB_Tree_Node *tree, int n);

void per_RBTree_printInOrder(RB_Tree_Node *tree);

//  Persistent Heterogenous Vector

Het_Vec_Node* per_Het_Vec_insert(Het_Vec_Node* head_ref, void* new_pointer_data, int pos, int ver, int new_ver);

void per_Het_Vec_print(Het_Vec_Node* head_ref, int pos, int ver);

Het_Vec_Node* per_Het_Vec_delete(Het_Vec_Node* head_ref, int pos, int ver, int new_ver);

//  Persistent Heterogeneous Map

void per_Het_Map_print(Het_Map_Node* head_ref, void* key, int ver);

Het_Map_Node* per_Het_Map_delete(Het_Map_Node* head_ref, void* key, int ver, int new_ver);

Het_Map_Node* per_Het_Map_insert(Het_Map_Node* head_ref, void* new_key, void* new_pointer_data, int ver, int new_ver);

//  Persistent Stack using Linked List

per_stack_ll* per_stack_ll_push(per_stack_ll* per_st_ver, int val, int ver);

per_stack_ll* per_stack_ll_pop(per_stack_ll* per_st, int ver);

void per_stack_ll_peek(per_stack_ll* per_st, int ver);