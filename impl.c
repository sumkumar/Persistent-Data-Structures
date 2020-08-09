#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "header.h"
  
#define MAXN 10000
#define min(a,b) a>b?b:a

pst_node* pst_node_init(){ 
	pst_node* head = (pst_node *)malloc(sizeof(pst_node));
	head->left = NULL; 
	head->right = NULL; 
	head->val = INT_MAX; 
	return head;
}

int arr[MAXN];

RB_Node *balance_RB_node;

void pst_build(pst_node* n, int low,int high){
    if (low==high) 
    { 
        n->val = arr[low]; 
        return; 
    } 
    int mid = (low+high) / 2; 
	n->left = pst_node_init();
	n->right = pst_node_init();
    pst_build(n->left, low, mid); 
    pst_build(n->right, mid+1, high);
    n->val = min(n->left->val, n->right->val);
}

pst_node* pst_update(pst_node* prev, int low, int high, int idx, int value){
    if (idx > high || idx < low || low > high)
        return NULL;
	pst_node* cur = pst_node_init();
    if (low == high){
        cur->val = value;
        return cur;
    }
    int mid = (low+high) / 2;
    if (idx <= mid){
        cur->right = prev->right;
		cur->left = pst_update(prev->left, low, mid, idx, value);
    }
    else{
        cur->left = prev->left;
		cur->right = pst_update(prev->right, mid+1, high, idx, value); 
    }
    cur->val = min(cur->left->val, cur->right->val); 
	return cur;
}

int pst_query(pst_node* n, int low, int high, int l, int r){ 
    if (l > high || r < low || low > high)
       return INT_MAX;
    if (l <= low && high <= r)
       return n->val;
    int mid = (low+high) / 2;
    int p1 = pst_query(n->left,low,mid,l,r);
    int p2 = pst_query(n->right,mid+1,high,l,r);
    return min(p1, p2);
}

per_stack* per_stack_create(int capacity){
    per_stack* per_st = (per_stack*)malloc(sizeof(per_stack));
    per_st->capacity = capacity;
    per_st->top = -1;
    per_st->array = (int*)malloc(per_st->capacity * sizeof(int));
    return per_st;
}

int per_stack_isFull(per_stack* per_st){
    return per_st->top == per_st->capacity - 1;
}

int per_stack_isEmpty(per_stack* per_st){
    return per_st->top == -1;
}

per_stack* per_stack_push(per_stack* per_st, int item){
    per_stack* per_stack_new = per_stack_create(per_st->capacity);
    for(int i=0;i<=per_st->top;i++){
        per_stack_new->array[i] = per_st->array[i];
    }
    per_stack_new->top = per_st->top;
    if (per_stack_isFull(per_stack_new)){
        printf("Stack Full!!!\n");
        return NULL;
    }
    per_stack_new->array[++per_stack_new->top] = item;
    return per_stack_new;
}

per_stack* per_stack_pop(per_stack* per_st){
    per_stack* per_stack_new = per_stack_create(per_st->capacity);
    for(int i=0;i<=per_st->top;i++){
        per_stack_new->array[i] = per_st->array[i];
    }
    per_stack_new->top = per_st->top;
    if (per_stack_isEmpty(per_stack_new)){
        printf("Stack Empty!!!\n");
        return NULL;
    }
    per_stack_new->top--;
    return per_stack_new;
}

int per_stack_peek(per_stack* per_st){
    if (per_stack_isEmpty(per_st)){
        printf("Stack Empty!!!\n");
        return -1;
    }
    return per_st->array[per_st->top];
}

per_queue* per_queue_create(int capacity){
    per_queue* queue = (per_queue*) malloc(sizeof(per_queue));
    queue->capacity = capacity;
    queue->front = -1;
    queue->size = capacity;
    queue->rear = 0;
    queue->arr = (int*) malloc(queue->capacity * sizeof(int));
    return queue;
}

int per_queue_isFull(per_queue* queue){
    return ((queue->front == 0 && queue->rear == queue->size-1) || (queue->front == queue->rear+1));
}

int per_queue_isEmpty(per_queue* queue){
    return (queue->front == -1);
}

per_queue* per_queue_insert_front(per_queue* queue, int key){
    if (per_queue_isFull(queue)){
        printf("Queue Full!!!\n");
        return NULL;
    }
    per_queue* queue_new = per_queue_create(queue->capacity);
    if(queue->front != -1)
    for(int i=queue->front;i!=(queue->rear+1)%queue->size;i=(i+1)%queue->size){
        queue_new->arr[i] = queue->arr[i];
    }
    queue_new->front = queue->front;
    queue_new->rear = queue->rear;

    if(queue_new->front == -1){
        queue_new->front = 0;
        queue_new->rear = 0;
    }
    else if (queue_new->front == 0)
        queue_new->front = queue_new->size - 1;
    else
        queue_new->front = queue_new->front-1;
    queue_new->arr[queue_new->front] = key ;
    return queue_new;
}

per_queue* per_queue_insert_rear(per_queue* queue, int key){
    if (per_queue_isFull(queue)){
        printf("Queue Full!!!\n");
        return NULL;
    }
    per_queue* queue_new = per_queue_create(queue->capacity);
    if (queue->front != -1)
        for(int i=queue->front;i!=(queue->rear+1)%queue->size;i=(i+1)%queue->size){
            queue_new->arr[i] = queue->arr[i];
        }

    queue_new->front = queue->front;
    queue_new->rear = queue->rear;

    if (queue_new->front == -1){
        queue_new->front = 0;
        queue_new->rear = 0;
    }
    else if (queue_new->rear == queue_new->size-1)
        queue_new->rear = 0;
    else
        queue_new->rear = queue_new->rear+1;
    printf("front: %d rear: %d\n", queue_new->front, queue_new->rear);
    queue_new->arr[queue_new->rear] = key ;
    return queue_new;
}

per_queue* per_queue_delete_front(per_queue* queue){
    if (per_queue_isEmpty(queue)){
        printf("Queue Empty!!!\n");
        return NULL;
    }

    per_queue* queue_new = per_queue_create(queue->capacity);
    if (queue->front != -1)
        for(int i=queue->front;i!=(queue->rear+1)%queue->size;i=(i+1)%queue->size){
            queue_new->arr[i] = queue->arr[i];
        }
    queue_new->front = queue->front;
    queue_new->rear = queue->rear;

    if (queue_new->front == queue_new->rear){
        queue_new->front = -1;
        queue_new->rear = -1;
    }
    else if (queue_new->front == queue_new->size -1)
        queue_new->front = 0;
    else
        queue_new->front = queue_new->front+1;
    return queue_new;
}

per_queue* per_queue_delete_rear(per_queue* queue){
    if (per_queue_isEmpty(queue)){
        printf("Queue Empty!!!\n");
        return NULL;
    }

    per_queue* queue_new = per_queue_create(queue->capacity);
    if (queue->front != -1)
        for(int i=queue->front;i!=(queue->rear+1)%queue->size;i=(i+1)%queue->size){
            queue_new->arr[i] = queue->arr[i];
        }
    queue_new->front = queue->front;
    queue_new->rear = queue->rear;

    if (queue_new->front == queue_new->rear)
    {
        queue_new->front = -1;
        queue_new->rear = -1;
    }
    else if (queue_new->rear == 0)
        queue_new->rear = queue_new->size-1;

    else
        queue_new->rear = queue_new->rear-1;
    return queue_new;
}

int per_queue_front(per_queue* queue){
    if (per_queue_isEmpty(queue)){
        printf("Queue Empty!!!\n");
        return INT_MIN;
    }
    return queue->arr[queue->front];
}

int per_queue_rear(per_queue* queue){
    if (per_queue_isEmpty(queue)){
        printf("Queue Empty!!!\n");
        return INT_MIN;
    }
    return queue->arr[queue->rear];
}


DoubleLLNode* per_DoublyLL_insert(DoubleLLNode* head_ref, int new_data, int pos, int ver, int new_ver){
    DoubleLLNode *new_node = (DoubleLLNode*)malloc(sizeof(DoubleLLNode)), *dummy_head, *prev_node = NULL;
	dummy_head = head_ref;
	new_node->data = new_data;
	new_node->vers = (ver_node*)malloc(sizeof(ver_node));
	new_node->vers->ver = new_ver;
	new_node->vers->next = NULL;
	int k=0,present, added = 0;
	if(dummy_head == NULL){
        new_node->next = NULL;
        new_node->prev = NULL;
        return new_node;
	}
    while(dummy_head != NULL){
        //printf("DB\t%d\n", dummy_head->data);
        ver_node *dummy_ver_head = dummy_head->vers;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
                ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
                new_ver_node->ver = new_ver;
                new_ver_node->next = dummy_head->vers;
                dummy_head->vers = new_ver_node;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        if(k==pos-1 && present == 1){
            new_node->next = dummy_head->next;
            new_node->prev = dummy_head;
            dummy_head->next = new_node;
            if(new_node->next != NULL){
                new_node->next->prev = new_node;
            }
            added = 1;
            k++;
        }
        prev_node = dummy_head;
        dummy_head = dummy_head->next;
    }
    if(pos == 1){
        new_node->next = head_ref;
        head_ref->prev = new_node;
        new_node->prev = NULL;
        return new_node;
    }
    if(added == 0){
        printf("Linked List too small!\n");
        free(new_node);
        return NULL;
    }
    return NULL;
}

DoubleLLNode* per_DoublyLL_delete(DoubleLLNode* head_ref, int pos, int ver, int new_ver){
    DoubleLLNode* dummy_head = head_ref;
    int k=0, present;
    while(dummy_head != NULL){
        //printf("DB\t%d\n", dummy_head->data);
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL, *curr_ver_node, *prev=NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        dummy_head = dummy_head->next;
    }
    //printf("k: %d pos: %d\n",k , pos);
    if(k<pos){
        printf("Linked List too small!\n");
        return NULL;
    }
    k=0;dummy_head = head_ref;
    while(dummy_head != NULL){
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL, *curr_ver_node, *prev=NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            if(dummy_ver_head->ver == ver && k!=pos-1){
                present = 1;
                ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
                new_ver_node->ver = new_ver;
                new_ver_node->next = dummy_head->vers;
                dummy_head->vers = new_ver_node;
                break;
            }
            else if(dummy_ver_head->ver == ver && k==pos-1){
                present = 1;
            }
            prev_ver_node = dummy_ver_head;
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        dummy_head = dummy_head->next;
    }
    printf("Update %d done\n", new_ver);
    return NULL;
}

void per_DoublyLL_print(DoubleLLNode* head_ref, int pos, int ver){
    DoubleLLNode* dummy_head = head_ref;
    int k=0, present;
    while(dummy_head != NULL){
        //printf("DB\t%d\n", dummy_head->data);
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        if(k==pos){
            printf("%d is present here\n", dummy_head->data);
            break;
        }
        dummy_head = dummy_head->next;
    }
    //printf("k: %d pos: %d\n",k , pos);
    if(k<pos){
        printf("Linked List too small!\n");
        return ;
    }
}


CircularLLNode* per_CircularLL_insert(CircularLLNode* head_ref, int new_data, int pos, int ver, int new_ver){
    CircularLLNode *new_node = (CircularLLNode*)malloc(sizeof(CircularLLNode)), *dummy_head, *prev_node = NULL;
    dummy_head = head_ref;
    new_node->data = new_data;
    new_node->vers = (ver_node*)malloc(sizeof(ver_node));
    new_node->vers->ver = new_ver;
    new_node->vers->next = NULL;
    int k=0,present, added = 0;
    if(dummy_head == NULL){
        new_node->next = new_node;
        return new_node;
    }
    ver_node *dummy_ver_head = dummy_head->vers;
    present = 0;
    while(dummy_ver_head != NULL){
        //printf("vers %d\n", dummy_ver_head->ver);
        if(dummy_ver_head->ver == ver){
            present = 1;
            ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
            new_ver_node->ver = new_ver;
            new_ver_node->next = dummy_head->vers;
            dummy_head->vers = new_ver_node;
            break;
        }
        dummy_ver_head = dummy_ver_head->next;
    }
    if(present == 1)
        k++;
    if(k==pos-1 && present == 1){
        new_node->next = dummy_head->next;
        dummy_head->next = new_node;
        added = 1;
        k++;
    }
    dummy_head = dummy_head->next;
    while(dummy_head != head_ref){
        //printf("DB\t%d\n", dummy_head->data);
        dummy_ver_head = dummy_head->vers;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
                ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
                new_ver_node->ver = new_ver;
                new_ver_node->next = dummy_head->vers;
                dummy_head->vers = new_ver_node;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        if(k==pos-1 && present == 1){
            new_node->next = dummy_head->next;
            dummy_head->next = new_node;
            added = 1;
            k++;
        }
        prev_node = dummy_head;
        dummy_head = dummy_head->next;
    }
    if(pos == 1){
        new_node->next = head_ref;
        while(head_ref->next != new_node->next){
            head_ref = head_ref->next;
        }
        head_ref->next = new_node;
        return new_node;
    }
    if(added == 0){
        printf("Linked List too small!\n");
        free(new_node);
        return NULL;
    }
    return NULL;
}

CircularLLNode* per_CircularLL_delete(CircularLLNode* head_ref, int pos, int ver, int new_ver){
    CircularLLNode* dummy_head = head_ref;
    int k=0, present;
    ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL, *curr_ver_node, *prev=NULL;
    present = 0;
    while(dummy_ver_head != NULL){
        //printf("vers %d\n", dummy_ver_head->ver);
        if(dummy_ver_head->ver == ver){
            present = 1;
        }
        dummy_ver_head = dummy_ver_head->next;
    }
    if(present == 1)
        k++;
    dummy_head = dummy_head->next;
    while(dummy_head != head_ref){
        //printf("DB\t%d\n", dummy_head->data);
        dummy_ver_head = dummy_head->vers;
        prev_ver_node = NULL;prev=NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        dummy_head = dummy_head->next;
    }
    //printf("k: %d pos: %d\n",k , pos);
    if(k<pos){
        printf("Linked List too small!\n");
        return NULL;
    }
    k=0;dummy_head = head_ref;
    dummy_ver_head = dummy_head->vers;
    prev_ver_node = NULL;prev=NULL;
    present = 0;
    while(dummy_ver_head != NULL){
        if(dummy_ver_head->ver == ver && k!=pos-1){
            present = 1;
            ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
            new_ver_node->ver = new_ver;
            new_ver_node->next = dummy_head->vers;
            dummy_head->vers = new_ver_node;
            break;
        }
        else if(dummy_ver_head->ver == ver && k==pos-1){
            present = 1;
        }
        prev_ver_node = dummy_ver_head;
        dummy_ver_head = dummy_ver_head->next;
    }
    if(present == 1)
        k++;
    dummy_head = dummy_head->next;
    while(dummy_head != head_ref){
        dummy_ver_head = dummy_head->vers;
        prev_ver_node = NULL;prev=NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            if(dummy_ver_head->ver == ver && k!=pos-1){
                present = 1;
                ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
                new_ver_node->ver = new_ver;
                new_ver_node->next = dummy_head->vers;
                dummy_head->vers = new_ver_node;
                break;
            }
            else if(dummy_ver_head->ver == ver && k==pos-1){
                present = 1;
            }
            prev_ver_node = dummy_ver_head;
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        dummy_head = dummy_head->next;
    }
    printf("Update %d done\n", new_ver);
    return NULL;
}

void per_CircularLL_print(CircularLLNode* head_ref, int pos, int ver){
    CircularLLNode* dummy_head = head_ref;
    int k=0, present;
    ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL;
    present = 0;
    while(dummy_ver_head != NULL){
        //printf("vers %d\n", dummy_ver_head->ver);
        if(dummy_ver_head->ver == ver){
            present = 1;
            break;
        }
        dummy_ver_head = dummy_ver_head->next;
    }
    if(present == 1)
        k++;
    if(k==pos){
        printf("%d is present here\n", dummy_head->data);
        return ;
    }
    dummy_head = dummy_head->next;
    while(dummy_head != head_ref){
        //printf("DB\t%d\n", dummy_head->data);
        dummy_ver_head = dummy_head->vers;
        prev_ver_node = NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        if(k==pos){
            printf("%d is present here\n", dummy_head->data);
            break;
        }
        dummy_head = dummy_head->next;
    }
    //printf("k: %d pos: %d\n",k , pos);
    if(k<pos){
        printf("Linked List too small!\n");
        return ;
    }
}

LinkedListNode* per_LinkedList_insert(LinkedListNode* head_ref, int new_data, int pos, int ver, int new_ver){
    LinkedListNode *new_node = (LinkedListNode*)malloc(sizeof(LinkedListNode)), *dummy_head, *prev_node = NULL;
    dummy_head = head_ref;
    new_node->data = new_data;
    new_node->vers = (ver_node*)malloc(sizeof(ver_node));
    new_node->vers->ver = new_ver;
    new_node->vers->next = NULL;
    int k=0,present, added = 0;
    if(dummy_head == NULL){
        new_node->next = NULL;
        return new_node;
    }
    while(dummy_head != NULL){
        //printf("DB\t%d\n", dummy_head->data);
        ver_node *dummy_ver_head = dummy_head->vers;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
                ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
                new_ver_node->ver = new_ver;
                new_ver_node->next = dummy_head->vers;
                dummy_head->vers = new_ver_node;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        if(k==pos-1 && present == 1){
            new_node->next = dummy_head->next;
            dummy_head->next = new_node;
            added = 1;
            k++;
        }
        prev_node = dummy_head;
        dummy_head = dummy_head->next;
    }
    if(pos == 1){
        new_node->next = head_ref;
        return new_node;
    }
    if(added == 0){
        printf("Linked List too small!\n");
        free(new_node);
        return NULL;
    }
    return NULL;
}

LinkedListNode* per_LinkedList_delete(LinkedListNode* head_ref, int pos, int ver, int new_ver){
    LinkedListNode* dummy_head = head_ref;
    int k=0, present;
    while(dummy_head != NULL){
        //printf("DB\t%d\n", dummy_head->data);
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL, *curr_ver_node, *prev=NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        dummy_head = dummy_head->next;
    }
    //printf("k: %d pos: %d\n",k , pos);
    if(k<pos){
        printf("Linked List too small!\n");
        return NULL;
    }
    k=0;dummy_head = head_ref;
    while(dummy_head != NULL){
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL, *curr_ver_node, *prev=NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            if(dummy_ver_head->ver == ver && k!=pos-1){
                present = 1;
                ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
                new_ver_node->ver = new_ver;
                new_ver_node->next = dummy_head->vers;
                dummy_head->vers = new_ver_node;
                break;
            }
            else if(dummy_ver_head->ver == ver && k==pos-1){
                present = 1;
            }
            prev_ver_node = dummy_ver_head;
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        dummy_head = dummy_head->next;
    }
    printf("Update %d done\n", new_ver);
    return NULL;
}

void per_LinkedList_print(LinkedListNode* head_ref, int pos, int ver){
    LinkedListNode* dummy_head = head_ref;
    int k=0, present;
    while(dummy_head != NULL){
        //printf("DB\t%d\n", dummy_head->data);
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        if(k==pos){
            printf("%d is present here\n", dummy_head->data);
            break;
        }
        dummy_head = dummy_head->next;
    }
    //printf("k: %d pos: %d\n",k , pos);
    if(k<pos){
        printf("Linked List too small!\n");
        return ;
    }
}




pbst* per_bst_insert(pbst *root, int val){
    pbst* new_node = (pbst*)malloc(sizeof(pbst));
    new_node->left = NULL;
    new_node->right = NULL;
    if(root == NULL){
        new_node->data = val;
        new_node->present = 1;
        return new_node;
    }
    if(root->data > val){
        new_node->data = root->data;
        new_node->right = root->right;
        new_node->present = root->present;
        if(root->left == NULL){
            pbst* new_leaf = (pbst*)malloc(sizeof(pbst));
            new_leaf->data = val;
            new_leaf->right = NULL;
            new_leaf->left = NULL;
            new_node->left = new_leaf;
            new_leaf->present = 1;
        }
        else{
            new_node->left = per_bst_insert(root->left, val);
            if(new_node->left == NULL){
                free(new_node);
                return NULL;
            }
        }
    }
    else if(root->data < val){
        new_node->data = root->data;
        new_node->left = root->left;
        new_node->present = root->present;
        if(root->right == NULL){
            pbst* new_leaf = (pbst*)malloc(sizeof(pbst));
            new_leaf->data = val;
            new_leaf->right = NULL;
            new_leaf->left = NULL;
            new_node->right = new_leaf;
            new_leaf->present = 1;
        }
        else{
            new_node->right = per_bst_insert(root->right, val);
            if(new_node->right == NULL){
                free(new_node);
                return NULL;
            }
        }
    }
    else{
        printf("Already Present\n");
        free(new_node);
        return NULL;
    }
    return new_node;
}

pbst* per_bst_delete(pbst *root, int val){
    pbst* new_node = (pbst*)malloc(sizeof(pbst));
    new_node->left = NULL;
    new_node->right = NULL;
    if(root == NULL){
        printf("Value not present in Tree\n");
        free(new_node);
        return NULL;
    }
    if(root->data > val){
        new_node->data = root->data;
        new_node->right = root->right;
        new_node->present = root->present;
        if(root->left == NULL){
            printf("Value not present in Tree\n");
            free(new_node);
            return NULL;
        }
        else{
            new_node->left = per_bst_delete(root->left, val);
            if(new_node->left == NULL){
                free(new_node);
                return NULL;
            }
        }
    }
    else if(root->data < val){
        new_node->data = root->data;
        new_node->left = root->left;
        new_node->present = root->present;
        if(root->right == NULL){
            printf("Value not present in Tree\n");
            free(new_node);
            return NULL;
        }
        else{
            new_node->right = per_bst_delete(root->right, val);
            if(new_node->right == NULL){
                free(new_node);
                return NULL;
            }
        }
    }
    else{
        new_node->left = root->left;
        new_node->right = root->right;
        new_node->data = root->data;
        new_node->present = 0;
    }
    return new_node;
}

void per_bst_search(pbst *root, int val){
    if(root == NULL){
        printf("Value not present in Tree\n");
        return ;
    }
    if(root->data > val){
        per_bst_search(root->left, val);
    }
    else if(root->data < val){
        per_bst_search(root->right, val);
    }
    else if(root->present == 1){
        printf("Value is Present\n");
    }
    else{
        printf("Value not present in Tree\n");
    }
    return ;
}

void set_RB_Node(RB_Node *node, int val){
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->color = 0;
    node->val = val;
}

int RB_isOnLeft(RB_Node *node){
    return node == node->parent->left;
}

RB_Node* RB_get_uncle(RB_Node *node){
    if (node->parent == NULL || node->parent->parent == NULL)
        return NULL;

    if (RB_isOnLeft(node->parent))
        return node->parent->parent->right;
    else
        return node->parent->parent->left;
}

RB_Node* RB_get_sibling(RB_Node *node) {
    if (node->parent == NULL)
        return NULL;
    if (RB_isOnLeft(node))
        return node->parent->right;
    return node->parent->left;
}

void RB_moveDown(RB_Node *node, RB_Node *nParent) {
    if (node->parent != NULL) {
        if (RB_isOnLeft(node)) {
            node->parent->left = nParent;
        } else {
            node->parent->right = nParent;
        }
    }
    nParent->parent = node->parent;
    node->parent = nParent;
}

int RB_hasRedChild(RB_Node *node) {
    return (node->left != NULL && node->left->color == 0) ||
           (node->right != NULL && node->right->color == 0);
}

void reset_RBTree(RB_Tree_Node *tree){
    tree->root = NULL;
}

void per_RBTree_leftRotate(RB_Tree_Node *tree, RB_Node *x) {
    RB_Node *nParent = x->right;
    if (x == tree->root)
        tree->root = nParent;
    RB_moveDown(x, nParent);
    x->right = nParent->left;
    if (nParent->left != NULL)
        nParent->left->parent = x;
    nParent->left = x;
}

void per_RBTree_rightRotate(RB_Tree_Node *tree, RB_Node *x) {
    RB_Node *nParent = x->left;
    if (x == tree->root)
        tree->root = nParent;
    RB_moveDown(x, nParent);
    x->left = nParent->right;
    if (nParent->right != NULL)
        nParent->right->parent = x;
    nParent->right = x;
}

void RB_swapColors(RB_Node *x1, RB_Node *x2){
    int temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
}

void RB_swapValues(RB_Node *x1, RB_Node *x2){
    int temp;
    temp = x1->val;
    x1->val = x2->val;
    x2->val = temp;
}

void per_RBTree_fixRedRed(RB_Tree_Node *tree, RB_Node *x) {
    if (x == tree->root) {
        x->color = 1;
        return;
    }
    RB_Node *parent = x->parent, *grandparent = parent->parent, *uncle_x = RB_get_uncle(x);
    if (parent->color != 1) {
        if(uncle_x != NULL && uncle_x->color == 0){
            parent->color = 1;
            uncle_x->color = 1;
            grandparent->color = 0;
            per_RBTree_fixRedRed(tree, grandparent);
        }
        else{
            if(RB_isOnLeft(parent)){
                if (RB_isOnLeft(x))
                    RB_swapColors(parent, grandparent);
                else{
                    per_RBTree_leftRotate(tree, parent);
                    RB_swapColors(x, grandparent);
                }
                per_RBTree_rightRotate(tree, grandparent);
            }
            else{
                if (RB_isOnLeft(x)){
                    per_RBTree_rightRotate(tree, parent);
                    RB_swapColors(x, grandparent);
                }
                else
                    RB_swapColors(parent, grandparent);
                per_RBTree_leftRotate(tree, grandparent);
            }
        }
    }
}

RB_Node *RB_get_successor(RB_Node *x){
    RB_Node *temp = x;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}

RB_Node* BSTreplace(RB_Node *x){
    if (x->left != NULL && x->right != NULL)
        return RB_get_successor(x->right);
    if (x->left == NULL && x->right == NULL)
        return NULL;
    if (x->left != NULL)
        return x->left;
    else
        return x->right;
}

void per_RBTree_fixDoubleBlack(RB_Tree_Node *tree, RB_Node *x){
    if (x == tree->root)
        return;
    RB_Node *sibling_x = RB_get_sibling(x), *parent = x->parent;
    if (sibling_x == NULL){
        per_RBTree_fixDoubleBlack(tree, parent);
    } else {
        if (sibling_x->color == 0) {
            parent->color = 0;
            sibling_x->color = 1;
            if (RB_isOnLeft(sibling_x)) {
                per_RBTree_rightRotate(tree, parent);
            } else {
                per_RBTree_leftRotate(tree, parent);
            }
            per_RBTree_fixDoubleBlack(tree, x);
        } else {
            if (RB_hasRedChild(sibling_x)) {
                if (sibling_x->left != NULL && sibling_x->left->color == 0) {
                    if (RB_isOnLeft(sibling_x)) {
                        sibling_x->left->color = sibling_x->color;
                        sibling_x->color = parent->color;
                        per_RBTree_rightRotate(tree, parent);
                    } else {
                        sibling_x->left->color = parent->color;
                        per_RBTree_rightRotate(tree, sibling_x);
                        per_RBTree_leftRotate(tree, parent);
                    }
                } else {
                    if (RB_isOnLeft(sibling_x)) {
                        sibling_x->right->color = parent->color;
                        per_RBTree_leftRotate(tree, sibling_x);
                        per_RBTree_rightRotate(tree, parent);
                    } else {
                        sibling_x->right->color = sibling_x->color;
                        sibling_x->color = parent->color;
                        per_RBTree_leftRotate(tree, parent);
                    }
                }
                parent->color = 1;
            } else {
                sibling_x->color = 0;
                if (parent->color == 1)
                    per_RBTree_fixDoubleBlack(tree, parent);
                else
                    parent->color = 1;
            }
        }
    }
}

void per_RBTree_deleteNode(RB_Tree_Node *tree, RB_Node *v){
    RB_Node *u = BSTreplace(v);
    int uvBlack = ((u == NULL || u->color == 1) && (v->color == 1));
    RB_Node *parent = v->parent;
    if (u == NULL){
        if (v == tree->root){
            tree->root = NULL;
        } else {
            if (uvBlack) {
                per_RBTree_fixDoubleBlack(tree, v);
            }
            else{
                if(RB_get_sibling(v) != NULL)
                    RB_get_sibling(v)->color = 0;
            }
            if (RB_isOnLeft(v)) {
                parent->left = NULL;
            }
            else{
                parent->right = NULL;
            }
        }
        free(v);
        return;
    }
    if (v->left == NULL || v->right == NULL){
        if (v == tree->root){
            v->val = u->val;
            v->left = v->right = NULL;
            free(u);
        } else {
            if (RB_isOnLeft(v)) {
                parent->left = u;
            } else {
                parent->right = u;
            }
            free(v);
            u->parent = parent;
            if (uvBlack){
                per_RBTree_fixDoubleBlack(tree, u);
            } else{
                u->color = 1;
            }
        }
        return;
    }
    RB_swapValues(u, v);
    per_RBTree_deleteNode(tree, u);
}

void RB_get_inorder(RB_Node *x){
    if (x == NULL)
        return;
    RB_get_inorder(x->left);
    printf("%d\n", x->val);
    RB_get_inorder(x->right);
}

RB_Node* per_RBTree_search(RB_Tree_Node *tree, int n){
    RB_Node *temp = tree->root;
    while (temp != NULL) {
        if (n < temp->val) {
            if (temp->left == NULL)
                break;
            else
                temp = temp->left;
        } else if (n == temp->val) {
            break;
        } else {
            if (temp->right == NULL)
                break;
            else
                temp = temp->right;
        }
    }
    return temp;
}

void per_RBTree_get_search_result(RB_Tree_Node *tree, int n){
    RB_Node* result = per_RBTree_search(tree, n);
    if(result->val == n){
        printf("Value Found!\n");
    }
    else{
        printf("Value Not Found!\n");
    }
}

void per_RBTree_delete(RB_Tree_Node *tree, int n) {
    if (tree->root == NULL)
        return;
    RB_Node *v = per_RBTree_search(tree, n), *u;

    if (v->val != n) {
        printf("No node found to delete with value: %d\n", n);
        return;
    }
    per_RBTree_deleteNode(tree, v);
}

void per_RBTree_printInOrder(RB_Tree_Node *tree){
    printf("Inorder: \n");
    if (tree->root == NULL)
        printf("Tree is empty\n");
    else
        RB_get_inorder(tree->root);
    printf("\n");
}

RB_Node* RB_get_clone(RB_Node* node){
    if(node == NULL)
        return NULL;
    RB_Node *new_node = (RB_Node*)malloc(sizeof(RB_Node));
    set_RB_Node(new_node, node->val);
    new_node->val = node->val;
    new_node->color = node->color;
    new_node->left = RB_get_clone(node->left);
    new_node->right = RB_get_clone(node->right);
    if(new_node->left != NULL)
        new_node->left->parent = new_node;
    if(new_node->right != NULL)
        new_node->right->parent = new_node;
    return new_node;
}

RB_Tree_Node* perRBTree_get_clone(RB_Tree_Node* tree){
    if(tree == NULL)
        return NULL;
    RB_Tree_Node *newRBTree = (RB_Tree_Node*)malloc(sizeof(RB_Tree_Node));
    reset_RBTree(newRBTree);
    if(tree->root == NULL){
        newRBTree->root = NULL;
        return newRBTree;
    }
    newRBTree->root = RB_get_clone(tree->root);
    //newRBTree->root->parent = NULL;
    return newRBTree;
}

RB_Tree_Node* per_RBTree_get_deleted_Tree(RB_Tree_Node *tree, int n){
    RB_Tree_Node *newRBTree = perRBTree_get_clone(tree);
    per_RBTree_delete(newRBTree, n);
    return newRBTree;
}

RB_Node* per_RB_Node_insert(RB_Node *root, int val){
    RB_Node* new_node = (RB_Node*)malloc(sizeof(RB_Node));
    set_RB_Node(new_node, 0);
    if(root == NULL){
        new_node->val = val;
        new_node->color = 1;
        return new_node;
    }
    if(root->val > val){
        new_node->val = root->val;
        new_node->right = root->right;
        new_node->color = root->color;
        if(root->left == NULL){
            RB_Node* new_leaf = (RB_Node*)malloc(sizeof(RB_Node));
            set_RB_Node(new_leaf, val);
            new_leaf->val = val;
            new_leaf->right = NULL;
            new_leaf->left = NULL;
            new_leaf->parent = new_node;
            new_node->left = new_leaf;
            balance_RB_node = new_leaf;
        }
        else{
            new_node->left = per_RB_Node_insert(root->left, val);
            if(new_node->left == NULL){
                free(new_node);
                return NULL;
            }
        }
        if(new_node->left != NULL)
            new_node->left->parent = new_node;
        if(new_node->right != NULL)
            new_node->right->parent = new_node;
    }
    else if(root->val < val){
        new_node->val = root->val;
        new_node->left = root->left;
        if(root->right == NULL){
            RB_Node* new_leaf = (RB_Node*)malloc(sizeof(RB_Node));
            set_RB_Node(new_leaf, val);
            new_leaf->val = val;
            new_leaf->right = NULL;
            new_leaf->left = NULL;
            new_node->right = new_leaf;
            new_leaf->parent = new_node;
            balance_RB_node = new_leaf;
        }
        else{
            new_node->right = per_RB_Node_insert(root->right, val);
            if(new_node->right == NULL){
                free(new_node);
                return NULL;
            }
        }
        if(new_node->left != NULL)
            new_node->left->parent = new_node;
        if(new_node->right != NULL)
            new_node->right->parent = new_node;
    }
    else{
        printf("Already Present\n");
        free(new_node);
        return NULL;
    }
    return new_node;
}

RB_Tree_Node* per_RBTree_insert(RB_Tree_Node *tree, int n){
    RB_Tree_Node *newRBTree = (RB_Tree_Node*)malloc(sizeof(RB_Tree_Node));
    reset_RBTree(newRBTree);
    balance_RB_node = NULL;
    if(tree != NULL)
        newRBTree->root = per_RB_Node_insert(tree->root, n);
    else
        newRBTree->root = per_RB_Node_insert(NULL, n);
    if(balance_RB_node != NULL){
        //per_RBTree_fixRedRed(newRBTree, balance_RB_node);
    }
    return newRBTree;
}


Het_Vec_Node* per_Het_Vec_insert(Het_Vec_Node* head_ref, void* new_pointer_data, int pos, int ver, int new_ver){
    Het_Vec_Node *new_node = (Het_Vec_Node*)malloc(sizeof(Het_Vec_Node)), *dummy_head, *prev_node = NULL;
    dummy_head = head_ref;
    new_node->pointer_data = new_pointer_data;
    new_node->vers = (ver_node*)malloc(sizeof(ver_node));
    new_node->vers->ver = new_ver;
    new_node->vers->next = NULL;
    int k=0,present, added = 0;
    if(dummy_head == NULL){
        new_node->next = NULL;
        return new_node;
    }
    while(dummy_head != NULL){
        //printf("DB\t%d\n", dummy_head->pointer_data);
        ver_node *dummy_ver_head = dummy_head->vers;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
                ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
                new_ver_node->ver = new_ver;
                new_ver_node->next = dummy_head->vers;
                dummy_head->vers = new_ver_node;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        if(k==pos-1 && present == 1){
            new_node->next = dummy_head->next;
            dummy_head->next = new_node;
            added = 1;
            k++;
        }
        prev_node = dummy_head;
        dummy_head = dummy_head->next;
    }
    if(pos == 1){
        new_node->next = head_ref;
        return new_node;
    }
    if(added == 0){
        printf("Linked List too small!\n");
        free(new_node);
        return NULL;
    }
    return NULL;
}

Het_Vec_Node* per_Het_Vec_delete(Het_Vec_Node* head_ref, int pos, int ver, int new_ver){
    Het_Vec_Node* dummy_head = head_ref;
    int k=0, present;
    while(dummy_head != NULL){
        //printf("DB\t%d\n", dummy_head->pointer_data);
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL, *curr_ver_node, *prev=NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        dummy_head = dummy_head->next;
    }
    //printf("k: %d pos: %d\n",k , pos);
    if(k<pos){
        printf("Linked List too small!\n");
        return NULL;
    }
    k=0;dummy_head = head_ref;
    while(dummy_head != NULL){
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL, *curr_ver_node, *prev=NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            if(dummy_ver_head->ver == ver && k!=pos-1){
                present = 1;
                ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
                new_ver_node->ver = new_ver;
                new_ver_node->next = dummy_head->vers;
                dummy_head->vers = new_ver_node;
                break;
            }
            else if(dummy_ver_head->ver == ver && k==pos-1){
                present = 1;
            }
            prev_ver_node = dummy_ver_head;
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        dummy_head = dummy_head->next;
    }
    printf("Update %d done\n", new_ver);
    return NULL;
}

void per_Het_Vec_print(Het_Vec_Node* head_ref, int pos, int ver){
    Het_Vec_Node* dummy_head = head_ref;
    int k=0, present;
    while(dummy_head != NULL){
        //printf("DB\t%d\n", dummy_head->pointer_data);
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL;
        present = 0;
        while(dummy_ver_head != NULL){
            //printf("vers %d\n", dummy_ver_head->ver);
            if(dummy_ver_head->ver == ver){
                present = 1;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(present == 1)
            k++;
        if(k==pos){
            printf("%p is present here\n", dummy_head->pointer_data);
            break;
        }
        dummy_head = dummy_head->next;
    }
    //printf("k: %d pos: %d\n",k , pos);
    if(k<pos){
        printf("Linked List too small!\n");
        return ;
    }
}

Het_Map_Node* per_Het_Map_insert(Het_Map_Node* head_ref, void* new_key, void* new_pointer_data, int ver, int new_ver){
    Het_Map_Node *new_node = (Het_Map_Node*)malloc(sizeof(Het_Map_Node)), *dummy_head, *node = NULL, *last_node = NULL;
    dummy_head = head_ref;
    new_node->pointer_data = new_pointer_data;
    new_node->pointer_key = new_key;
    new_node->next = NULL;
    new_node->vers = (ver_node*)malloc(sizeof(ver_node));
    new_node->vers->ver = new_ver;
    new_node->vers->next = NULL;
    int k=0,present, added = 0;
    if(dummy_head == NULL){
        new_node->next = NULL;
        return new_node;
    }
    node = NULL;
    last_node = NULL;
    while(dummy_head != NULL){
        //printf("DB\t%p\n", dummy_head->pointer_data);
        ver_node *dummy_ver_head = dummy_head->vers;
        present = 0;
        while(dummy_ver_head != NULL) {
            //printf("vers %d\n", dummy_ver_head->ver);
            if (dummy_ver_head->ver == ver && dummy_head->pointer_key != new_key) {
                ver_node *new_ver_node = (ver_node *) malloc(sizeof(ver_node));
                new_ver_node->ver = new_ver;
                new_ver_node->next = dummy_head->vers;
                dummy_head->vers = new_ver_node;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        if(dummy_head->next == NULL)
            last_node = dummy_head;
        dummy_head = dummy_head->next;
    }
    if(last_node != NULL){
        last_node->next = new_node;
    }
    return NULL;
}

Het_Map_Node* per_Het_Map_delete(Het_Map_Node* head_ref, void* key, int ver, int new_ver){
    Het_Map_Node* dummy_head = head_ref;
    int present = 0;
    while(dummy_head != NULL){
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL, *curr_ver_node, *prev=NULL;

        while(dummy_ver_head != NULL){
            if(dummy_ver_head->ver == ver && dummy_head->pointer_key == key){
                present = 1;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        dummy_head = dummy_head->next;
    }
    if(present == 0){
        printf("Key Not found!\n");
        return NULL;
    }
    present = 0;
    while(dummy_head != NULL){
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL, *curr_ver_node, *prev=NULL;

        while(dummy_ver_head != NULL){
            if(dummy_ver_head->ver == ver && dummy_head->pointer_key != key){
                present = 1;
                ver_node *new_ver_node = (ver_node*)malloc(sizeof(ver_node));
                new_ver_node->ver = new_ver;
                new_ver_node->next = dummy_head->vers;
                dummy_head->vers = new_ver_node;
                break;
            }
            dummy_ver_head = dummy_ver_head->next;
        }
        dummy_head = dummy_head->next;
    }
    printf("Update %d done\n", new_ver);
    return NULL;
}

void per_Het_Map_print(Het_Map_Node* head_ref, void* key, int ver){
    Het_Map_Node* dummy_head = head_ref;
    int k=0, present=0;
    while(dummy_head != NULL){
        //printf("DB\t%d\n", dummy_head->pointer_data);
        ver_node *dummy_ver_head = dummy_head->vers, *prev_ver_node = NULL;
        if(dummy_head->pointer_key == key)
            while(dummy_ver_head != NULL){
                //printf("vers %d\n", dummy_ver_head->ver);
                if(dummy_ver_head->ver == ver){
                    printf("%p is present here\n", dummy_head->pointer_data);
                    present = 1;
                    break;
                }
                dummy_ver_head = dummy_ver_head->next;
            }
        dummy_head = dummy_head->next;
    }
    if(present == 0)
        printf("Key Not found!\n");
}

int per_stack_ll_isEmpty(per_stack_ll* per_st){
    return per_st == NULL;
}

per_stack_ll* per_stack_ll_push(per_stack_ll* per_st_ver, int val, int ver){
    per_stack_ll* per_st = (per_stack_ll*)malloc(sizeof(per_stack_ll));
    per_stack_ll_node* per_st_node = (per_stack_ll_node*)malloc(sizeof(per_stack_ll_node));
    per_st_node->data = val;
    per_st_node->ver = ver;
    per_st_node->next = NULL;
    per_st->head = per_st_node;
    if(per_st_ver == NULL){
        return per_st;
    }
    per_st_node->next = per_st_ver->head;
    return per_st;
}

per_stack_ll_node* per_st_node_clone(per_stack_ll_node* node){
    if(node == NULL)
        return NULL;
    per_stack_ll_node* new_node = (per_stack_ll_node*)malloc(sizeof(per_stack_ll_node));
    new_node->data = node->data;
    new_node->ver = node->ver;
    new_node->next = per_st_node_clone(node->next);
    return new_node;
}

per_stack_ll* per_stack_ll_pop(per_stack_ll* per_st, int ver){
    if (per_stack_ll_isEmpty(per_st)){
        printf("Stack Empty!!!\n");
        return NULL;
    }
    per_stack_ll_node *node = per_st->head;
    per_stack_ll_node *new_node = NULL;
    int flag=0;

    while(node != NULL){
        if(flag ==1){
            //printf("DB\t%d\tver: %d\n", node->data, node->ver);
            new_node = per_st_node_clone(node);
            break;
        }
        if(node->ver == ver)
            flag = 1;
        node = node->next;
    }
    if(new_node == NULL){
        printf("Stack Empty!!!\n");
        return NULL;
    }
    per_stack_ll* per_st_new = (per_stack_ll*)malloc(sizeof(per_stack_ll));
    per_st_new->head = node;
    return per_st_new;
}

void per_stack_ll_peek(per_stack_ll* per_st, int ver){
    if (per_stack_ll_isEmpty(per_st)){
        printf("Stack Empty!!!\n");
        return ;
    }
    per_stack_ll_node *node = per_st->head;
    int flag=0;
    while(node != NULL){
        //printf("DB\t%d\tver: %d\n", node->data, node->ver);
        if(node->ver <= ver)
            break;
        node = node->next;
    }
    if(node == NULL){
        printf("Stack Empty!!!\n");
        return ;
    }
    printf("Update %d has Top value: %d\n", ver, node->data);
}