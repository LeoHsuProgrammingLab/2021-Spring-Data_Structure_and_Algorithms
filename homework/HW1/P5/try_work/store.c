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
        //new_node -> ptr_near = xor((xnode*)NULL , (xnode*)NULL);
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
            //xor_list -> head -> ptr_near = (xnode*)NULL;
            xor_list -> tail = (xnode*)NULL;
            //xor_list -> tail -> ptr_near = (xnode*)NULL;
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

void scan_order(char order[], xlist rail[]){
    int num1=0;//how many rails
    int num2=0;
    int i=0;
    if((isdigit(order[6])!=0 ) && (order[0]=='e')){//order:enter
        i=6;
        while(order[i]!=' '){
            num1=num1*10+(order[i]-'0');
            i++;
        }
        i++;
        while(order[i]!='\n'){
            num2=num2*10+(order[i]-'0');
            i++;
        }
        push_xnode(&rail[num1], num2);
    }
    else if((isdigit(order[6]) != 0) && (order[0] == 'l')){//order:leave
        i=6;
        while(order[i] != '\n'){
            num1 = num1*10+(order[i]-'0');
            i++;
        }
        pop_xnode(&rail[num1]);
    }
    else{//order:migrate
        i=8;
        while(order[i] != ' '){
            num1 = num1*10+(order[i]-'0');
            i++;
        }
        i++;
        while(order[i] != '\n'){
            num2 = num2*10+(order[i]-'0');
            i++;
        }
        //確定第一個list有東西
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

void free_xlist(xlist *xor_list){//free all the malloc
    while(xor_list -> head != (xnode*)NULL){
        pop_xnode(xor_list);
    }
}