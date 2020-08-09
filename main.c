#include <stdio.h>
#include "header.h"

pst_node* pst_ver[100];
per_stack* per_stack_ver[100];
per_queue* per_queue_ver[100];
DoubleLLNode* per_DoublyLL_ver[100];
CircularLLNode* per_CircularLL_ver[100];
LinkedListNode* per_LinkedList_ver[100];
pbst* per_bst_ver[100];
RB_Tree_Node* per_RBTree_ver[100];
Het_Vec_Node* per_Het_Vec_ver[100];
Het_Map_Node* per_Het_Map_ver[100];
per_stack_ll* per_stack_ll_ver[100];
extern int arr[];
int persistence = -1;
void pst(){
	int i,j,k=1,p,u,ind,val,l,r,res,n;
	printf("Enter size of Array: ");
	scanf("%d", &n);
    printf("Enter elements in the Array\n");
    for (int i=0; i<n; i++)
        scanf("%d", &arr[i]);
    pst_node* root = pst_node_init();
    pst_build(root, 0, n-1);
    pst_ver[0] = root;
	while(1){
		printf("1. Update\n2. pst_query\n3. Exit\n");
		scanf("%d",&p);
		if(p ==1){
		    if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
		    else
		        u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
			printf("Enter Update Index: ");
			scanf("%d", &ind);
            if(ind > n || ind<1){
                printf("Invalid Update Index\n");
                continue;
            }
			printf("Enter Update Value: \n");
			scanf("%d", &val);
			pst_ver[k++] = pst_update(pst_ver[u], 0, n-1, ind-1, val);
			printf("Update %d done\n", k-1);
		}
        else if(p ==2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Left Index: ");
            scanf("%d", &l);
            if(l > n || l<1){
                printf("Invalid Left Index\n");
                continue;
            }
            printf("Enter Right Index: ");
            scanf("%d", &r);
            if(r > n || r<1 || l>r){
                printf("Invalid Right Index\n");
                continue;
            }
            res = pst_query(pst_ver[u], 0, n-1, l-1, r-1);
            printf("Result of Minimum in Update %d Range %d , %d : %d\n", u, l, r, res);
        }
		else if(p==3)
			break;
		else
		    printf("Invalid Option\n");
	}
}

void persistent_stack(){
    int i,j,k=1,p,u,ind,val,l,r,res,n;
    printf("Enter size of Array: ");
    scanf("%d", &n);
    per_stack* root = per_stack_create(n);
    per_stack_ver[0] = root;
    while(1){
        printf("1. Push\n2. Pop\n3. Peek\n4. Print\n5. Exit\n");
        scanf("%d",&p);
        if(p == 1){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            per_stack_ver[k++] = per_stack_push(per_stack_ver[u], val);
            printf("Update %d done\n", k-1);
        }
        else if(p == 2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            per_stack_ver[k++] = per_stack_pop(per_stack_ver[u]);
            printf("Update %d done\n", k-1);
        }
        else if(p == 3){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            res = per_stack_peek(per_stack_ver[u]);
            printf("Update %d has Top value: %d\n", k-1, res);
        }
        else if(p == 4){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            for(i=0;i<=per_stack_ver[u]->top;i++){
                printf("%d\t", per_stack_ver[u]->array[i]);
            }
            printf("\n");
        }
        else if(p == 5)
            break;
        else
            printf("Invalid Option\n");
    }
}

void persistent_circular_double_ended_queue(){
    int i,j,k=1,p,u,ind,val,l,r,res,n;
    printf("Enter size of Array: ");
    scanf("%d", &n);
    per_queue* root = per_queue_create(n);
    per_queue_ver[0] = root;
    while(1){
        printf("1. Insert in Front\n2. Insert in Rear\n3. Delete from Front\n4. Delete from Rear\n5. Get Value at Front\n6. Get Value at Rear\n7. Print\n8. Exit\n");
        scanf("%d",&p);
        if(p == 1){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            per_queue_ver[k++] = per_queue_insert_front(per_queue_ver[u], val);
            printf("Update %d done\n", k-1);
        }
        else if(p == 2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            per_queue_ver[k++] = per_queue_insert_rear(per_queue_ver[u], val);
            printf("Update %d done\n", k-1);
        }
        else if(p == 3){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            per_queue_ver[k++] = per_queue_delete_front(per_queue_ver[u]);
            printf("Update %d done\n", k-1);
        }
        else if(p == 4){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            per_queue_ver[k++] = per_queue_delete_rear(per_queue_ver[u]);
            printf("Update %d done\n", k-1);
        }
        else if(p == 5){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            res = per_queue_front(per_queue_ver[u]);
            printf("Update %d has Front value: %d\n", k-1, res);
        }
        else if(p == 6){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            res = per_queue_rear(per_queue_ver[u]);
            printf("Update %d has Rear value: %d\n", k-1, res);
        }
        else if(p == 7){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            if(!per_queue_isEmpty(per_queue_ver[u]))
                for(int i=per_queue_ver[u]->front;i!=(per_queue_ver[u]->rear+1)%per_queue_ver[u]->size;i=(i+1)%per_queue_ver[u]->size){
                    printf("%d\t", per_queue_ver[u]->arr[i]);
                }
            else
                printf("Queue Empty!!!");
            printf("\n");
        }
        else if(p == 8)
            break;
        else
            printf("Invalid Option\n");
    }
}

void DLL(){
    int i,j,k=1,p,u,ind,val,l,r,res,n, pos;
	per_DoublyLL_ver[0] = NULL;
    DoubleLLNode* head;
	while(1){
        printf("1. Insert\n2. Delete\n3. Print Value\n4. Exit\n");
        scanf("%d",&p);
        if(p == 1){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            printf("Enter Position: ");
            scanf("%d", &pos);
            head = per_DoublyLL_insert(per_DoublyLL_ver[u], val, pos, u, k);
            if(head != NULL)
                per_DoublyLL_ver[k] = head;
            else
                per_DoublyLL_ver[k] = per_DoublyLL_ver[u];
            k++;
            printf("Update %d done\n", k-1);
        }
        else if(p == 2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Position: ");
            scanf("%d", &pos);
            head = per_DoublyLL_delete(per_DoublyLL_ver[u], pos, u, k);
            if(pos == 1 && head != NULL)
                per_DoublyLL_ver[k] = head;
            else
                per_DoublyLL_ver[k] = per_DoublyLL_ver[u];
            k++;
        }
        else if(p == 3){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Position: ");
            scanf("%d", &pos);
            per_DoublyLL_print(per_DoublyLL_ver[u], pos, u);
        }
        else if(p == 4)
            break;
        else
            printf("Invalid Option\n");
    }
}

void CLL(){
    int i,j,k=1,p,u,ind,val,l,r,res,n, pos;
    per_CircularLL_ver[0] = NULL;
    CircularLLNode* head;
    while(1){
        printf("1. Insert\n2. Delete\n3. Print Value\n4. Exit\n");
        scanf("%d",&p);
        if(p == 1){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            printf("Enter Position: ");
            scanf("%d", &pos);
            head = per_CircularLL_insert(per_CircularLL_ver[u], val, pos, u, k);
            if(head != NULL)
                per_CircularLL_ver[k] = head;
            else
                per_CircularLL_ver[k] = per_CircularLL_ver[u];
            k++;
            printf("Update %d done\n", k-1);
        }
        else if(p == 2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Position: ");
            scanf("%d", &pos);
            head = per_CircularLL_delete(per_CircularLL_ver[u], pos, u, k);
            if(pos == 1 && head != NULL)
                per_CircularLL_ver[k] = head;
            else
                per_CircularLL_ver[k] = per_CircularLL_ver[u];
            k++;
        }
        else if(p == 3){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Position: ");
            scanf("%d", &pos);
            per_CircularLL_print(per_CircularLL_ver[u], pos, u);
        }
        else if(p == 4)
            break;
        else
            printf("Invalid Option\n");
    }
}

void LinkedList(){
    int i,j,k=1,p,u,ind,val,l,r,res,n, pos;
    per_LinkedList_ver[0] = NULL;
    LinkedListNode* head;
    while(1){
        printf("1. Insert\n2. Delete\n3. Print Value\n4. Exit\n");
        scanf("%d",&p);
        if(p == 1){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            printf("Enter Position: ");
            scanf("%d", &pos);
            head = per_LinkedList_insert(per_LinkedList_ver[u], val, pos, u, k);
            if(head != NULL)
                per_LinkedList_ver[k] = head;
            else
                per_LinkedList_ver[k] = per_LinkedList_ver[u];
            k++;
            printf("Update %d done\n", k-1);
        }
        else if(p == 2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Position: ");
            scanf("%d", &pos);
            head = per_LinkedList_delete(per_LinkedList_ver[u], pos, u, k);
            if(pos == 1 && head != NULL)
                per_LinkedList_ver[k] = head;
            else
                per_LinkedList_ver[k] = per_LinkedList_ver[u];
            k++;
        }
        else if(p == 3){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Position: ");
            scanf("%d", &pos);
            per_LinkedList_print(per_LinkedList_ver[u], pos, u);
        }
        else if(p == 4)
            break;
        else
            printf("Invalid Option\n");
    }
}

void persistent_bst(){
    int i,j,k=1,p,u,ind,val,l,r,res,n;
    per_bst_ver[0] = NULL;
    while(1){
        printf("1. Insert\n2. Delete\n3. Search\n4. Exit\n");
        scanf("%d",&p);
        if(p == 1){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            per_bst_ver[k++] = per_bst_insert(per_bst_ver[u], val);
            printf("Update %d done\n", k-1);
        }
        else if(p == 2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            per_bst_ver[k++] = per_bst_delete(per_bst_ver[u], val);
            printf("Update %d done\n", k-1);
        }
        else if(p == 3){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            per_bst_search(per_bst_ver[u], val);
        }
        else if(p == 4)
            break;
        else
            printf("Invalid Option\n");
    }
}

void persistent_RB_Tree(){
    int i,j,k=1,p,u,ind,val,l,r,res,n;
    per_RBTree_ver[0] = NULL;
    while(1){
        printf("1. Insert\n2. Delete\n3. Search\n4. Print Tree Inorder\n5. Exit\n");
        scanf("%d",&p);
        if(p == 1){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            per_RBTree_ver[k++] = per_RBTree_insert(per_RBTree_ver[u], val);
            printf("Update %d done\n", k-1);
        }
        else if(p == 2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            per_RBTree_ver[k++] = per_RBTree_get_deleted_Tree(per_RBTree_ver[u], val);
            printf("Update %d done\n", k-1);
        }
        else if(p == 3){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            per_RBTree_get_search_result(per_RBTree_ver[u], val);
        }
        else if(p == 4){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            per_RBTree_printInOrder(per_RBTree_ver[u]);
        }
        else if(p == 5)
            break;
        else
            printf("Invalid Option\n");
    }
}

void persistent_Heterogeneous_Vector(){
    int i,j,k=1,p,u,ind,l,r,res,n, pos;
    void *val;
    per_Het_Vec_ver[0] = NULL;
    Het_Vec_Node* head;
    while(1){
        printf("1. Insert\n2. Delete\n3. Print Value\n4. Exit\n");
        scanf("%d",&p);
        if(p == 1){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%p", &val);
            printf("Enter Position: ");
            scanf("%d", &pos);
            head = per_Het_Vec_insert(per_Het_Vec_ver[u], val, pos, u, k);
            if(head != NULL)
                per_Het_Vec_ver[k] = head;
            else
                per_Het_Vec_ver[k] = per_Het_Vec_ver[u];
            k++;
            printf("Update %d done\n", k-1);
        }
        else if(p == 2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Position: ");
            scanf("%d", &pos);
            head = per_Het_Vec_delete(per_Het_Vec_ver[u], pos, u, k);
            if(pos == 1 && head != NULL)
                per_Het_Vec_ver[k] = head;
            else
                per_Het_Vec_ver[k] = per_Het_Vec_ver[u];
            k++;
        }
        else if(p == 3){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Position: ");
            scanf("%d", &pos);
            per_Het_Vec_print(per_Het_Vec_ver[u], pos, u);
        }
        else if(p == 4)
            break;
        else
            printf("Invalid Option\n");
    }
}

void persistent_Heterogeneous_Map(){
    int i,j,k=1,p,u,ind,l,r,res,n, pos;
    void *val, *key;
    per_Het_Map_ver[0] = NULL;
    Het_Map_Node* head;
    while(1){
        printf("1. Insert\n2. Delete\n3. Print Value\n4. Exit\n");
        scanf("%d",&p);
        if(p == 1){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Key: ");
            scanf("%p", &key);
            printf("Enter Value: ");
            scanf("%p", &val);
            head = per_Het_Map_insert(per_Het_Map_ver[u], key, val, u, k);
            if(head != NULL)
                per_Het_Map_ver[k] = head;
            else
                per_Het_Map_ver[k] = per_Het_Map_ver[u];
            k++;
            printf("Update %d done\n", k-1);
        }
        else if(p == 2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Key: ");
            scanf("%p", &val);
            head = per_Het_Map_delete(per_Het_Map_ver[u], val, u, k);
            if(pos == 1 && head != NULL)
                per_Het_Map_ver[k] = head;
            else
                per_Het_Map_ver[k] = per_Het_Map_ver[u];
            k++;
        }
        else if(p == 3){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Key: ");
            scanf("%p", &val);
            per_Het_Map_print(per_Het_Map_ver[u], val, u);
        }
        else if(p == 4)
            break;
        else
            printf("Invalid Option\n");
    }
}

void persistent_stack_ll(){
    int i,j,k=1,p,u,ind,val,l,r,res,n;
    per_stack_ll_ver[0] = NULL;
    while(1){
        printf("1. Push\n2. Pop\n3. Peek\n4. Exit\n");
        scanf("%d",&p);
        if(p == 1){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            printf("Enter Value: ");
            scanf("%d", &val);
            per_stack_ll_ver[k] = per_stack_ll_push(per_stack_ll_ver[u], val, k);
            k++;
            printf("Update %d done\n", k-1);
        }
        else if(p == 2){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            per_stack_ll_ver[k++] = per_stack_ll_pop(per_stack_ll_ver[u], u);
            printf("Update %d done\n", k-1);
        }
        else if(p == 3){
            if(persistence == 2) {
                printf("Enter Update Number: ");
                scanf("%d", &u);
            }
            else
                u = k-1;
            if(u >= k || u<0){
                printf("Invalid Update Number\n");
                continue;
            }
            per_stack_ll_peek(per_stack_ll_ver[u], u);
        }
        else if(p == 4)
            break;
        else
            printf("Invalid Option\n");
    }
}

int main(){
    int option;
    //pst();
    //persistent_stack();
    //persistent_circular_double_ended_queue();
    //DLL();
    //CLL();
    //LinkedList();
    //persistent_bst();
    //persistent_RB_Tree();
    //persistent_Heterogeneous_Vector();
    //persistent_Heterogeneous_Map();
    printf("1. Persistent Segment Tree\n2. Persistent Stack (using Array)\n3. Persistent Double Ended Circular Queue\n");
    printf("4. Persistent Doubly Linked List\n5. Persistent Circular Linked List\n6. Persistent Linked List\n");
    printf("7. Persistent Binary Search Tree\n8. Persistent Red-Black Tree\n9. Persistent Heterogenous Vector\n");
    printf("10. Persistent Heterogeneous Map\n11. Persistent Stack (using Linked List)\nEnter an Option : ");
    scanf("%d", &option);
    while(persistence != 1 && persistence!= 2){
        printf("\n1. Partially Persistent\n2. Completely Persistent\nEnter Option : ");
        scanf("%d", &persistence);
        if(persistence != 1 && persistence!= 2)
            printf("Enter valid option");
    }
    switch(option){
        case 1: pst();break;
        case 2: persistent_stack();break;
        case 3: persistent_circular_double_ended_queue();break;
        case 4: DLL();break;
        case 5: CLL();break;
        case 6: LinkedList();break;
        case 7: persistent_bst();break;
        case 8: persistent_RB_Tree();break;
        case 9: persistent_Heterogeneous_Vector();break;
        case 10: persistent_Heterogeneous_Map();break;
        case 11: persistent_stack_ll();break;
        default: printf("Invalid Option");
    }
    return 0;
} 