//I discuss with my classmates from NCTU CS, but this time he didn't know how to give me any advice about xor linked list.
//I discuss with TA in the TA hour.
//And these below are the references:
//https://hackmd.io/@kenjin/xor_llist
//http://www.tastones.com/zh-tw/stackoverflow/data-structures/linked-list/xor_linked_list/
//https://shininglionking.blogspot.com/2020/02/c-xor-linked-list.html
//https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list
//https://blog.gtwang.org/programming/c-memory-functions-malloc-free/
//https://stackoverflow.com/questions/31505485/runtime-error-with-malloc

#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
struct Xnode{//node in the xor linked list
    int value;
    struct Xnode *ptr_near;
};
typedef struct Xnode xnode;
xnode *Node_new(int value){
    xnode *n = (xnode*)malloc(sizeof(xnode));
    n -> ptr_near = (xnode*)NULL;
    n -> value = value;
    return n;
}
xnode *xor(xnode *first, xnode *second){//xor calculation
    return (xnode*)((uintptr_t)(first)^(uintptr_t)(second));
}

struct xor_list{//xor_list
    xnode *head;
    xnode *tail;
    xnode *current;
};
typedef struct xor_list xlist;

void push_xnode(xlist *xor_list, int value){//Need to know which xlist to push
    xnode *new_node = Node_new(value);//initialize
    if(xor_list -> head != (xnode*)NULL && xor_list -> tail != (xnode*)NULL){//Already has node!
        xor_list -> tail -> ptr_near = xor(new_node, xor_list -> tail -> ptr_near);
        new_node -> ptr_near = xor_list -> tail;
        xor_list -> tail = new_node;
    }
    else{//First add!
        new_node -> value = value;
        xor_list -> head = new_node;
        xor_list -> tail = new_node;
    }
}

void pop_xnode(xlist *xor_list){//Need to know which xlist to pop
    if(xor_list -> head != (xnode*)NULL){//If not empty
        if(xor_list -> tail -> ptr_near != (xnode*)NULL){//Many nodes are in it!
            xor_list -> current = xor_list -> tail;
            xor_list -> tail = xor_list -> tail -> ptr_near;
            xor_list -> tail -> ptr_near = xor(xor_list -> tail -> ptr_near, xor_list->current);
            free(xor_list -> current);
            xor_list -> current = (xnode*)NULL;
        }
        else{//Only one node to pop!
            free(xor_list -> head);
            xor_list -> head = (xnode*)NULL;
            xor_list -> tail = (xnode*)NULL;
        }
    }
}

void print_xlist(xlist xor_list){
    xnode *last = (xnode*)NULL;
    xnode *next = (xnode*)NULL;;
    if(xor_list.head != (xnode*)NULL){//Nodes in it, print all
        xor_list.current = xor_list.head;
        xor_list.current -> ptr_near = xor_list.head -> ptr_near;
        while(xor_list.current != (xnode*)NULL){
            printf("%d%c", xor_list.current -> value, ' ');
            if(xor_list.current -> ptr_near != (xnode*)NULL){
                next = xor(last, xor_list.current -> ptr_near);
            }
            else{
                next = (xnode*)NULL;
            }
            last = xor_list.current; 
            xor_list.current = next;
        }
        printf("%c", '\n');
    }
    else{//No any node
        printf("%c", '\n');
    }
}

void free_xlist(xlist *xor_list){//free all the malloc
    while(xor_list -> head != (xnode*)NULL){
        pop_xnode(xor_list);
    }
}

int main(){
    int n=0;//The number of the order
    int k=0;//The mumber of the rail
    char order[20];
    int j;
    int l;
    int m;
    int num1=0;
    int num2=0;
    scanf("%d%d", &k, &n);
    xlist *rail;
    rail = (xlist*)malloc(sizeof(xlist)*k);
    for (m=0;m<k;m++){
        rail[m].current = (xnode*)NULL;
        rail[m].head = (xnode*)NULL;
        rail[m].tail = (xnode*)NULL;
    }
    //input
    for (j=0;j<n;j++){
        scanf("%s",order);
        if(order[0]=='l'){
            scanf("%d",&num1);
            pop_xnode(&rail[num1]);
        }
        else{
            scanf("%d%d",&num1,&num2);
            if(order[0]=='e'){
                push_xnode(&rail[num1], num2);
            }
            else if(order[0]=='m'){
                if(rail[num1].head != (xnode*)NULL){
                    rail[num1].tail -> ptr_near = xor(rail[num1].tail -> ptr_near, rail[num2].tail);
                    if (rail[num2].tail != (xnode*)NULL){//rail[num2] with nodes in it
                        rail[num2].tail -> ptr_near = xor(rail[num2].tail -> ptr_near, rail[num1].tail);
                    }
                    else{//no other nodes in the rail[num2]
                        rail[num2].head = rail[num1].tail;
                    }
                    rail[num2].tail = rail[num1].head;
                    rail[num1].head = (xnode*)NULL;
                    rail[num1].tail = (xnode*)NULL;
                }
            }
        }
        num1=0;
        num2=0;
    }
    for (l=0;l<k;l++){
        print_xlist(rail[l]);
        free_xlist(&rail[l]);//free每一個node!
    }
    free(rail);
    return 0;
}