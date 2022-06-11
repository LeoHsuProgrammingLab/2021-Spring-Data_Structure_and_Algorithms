#include<stdio.h>
#include<string.h>
#include <ctype.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
struct Xnode{
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
xnode *xor(xnode *first, xnode *second){
    return (xnode*)((uintptr_t)(first)^(uintptr_t)(second));
}

struct xor_list{
    xnode *head;
    xnode *tail;
    xnode *current;
};
typedef struct xor_list xlist;
//initialize to define head tail 

void push_xnode(xlist *xor_list, int value){//Need to know which node to push
    xnode *new_node = Node_new(value);
    if(xor_list -> head != (xnode*)NULL){
        xor_list->tail -> ptr_near = xor(new_node, xor_list -> tail -> ptr_near);
        //printf("line: %d \n", __LINE__);
        new_node -> ptr_near = xor_list->tail;
        xor_list->tail = new_node;
    }
    else{
        //printf("line: %d \n", __LINE__);
        new_node -> value = value;
        new_node -> ptr_near = xor((xnode*)NULL , (xnode*)NULL);
        xor_list -> head = new_node;
        xor_list -> tail = new_node;
    }
}

void pop_xnode(xlist *xor_list){//Need to know which xlist to pop
    //printf("line: %d \n", __LINE__);
    if(xor_list -> head != (xnode*)NULL){
        if(xor_list -> tail -> ptr_near != (xnode*)NULL){
            //printf("line: %d \n", __LINE__);
            xor_list -> current = xor_list -> tail;
            //printf("line: %d \n", __LINE__);
            //printf("%d\n",xor_list -> tail -> ptr_near -> value);
            xor_list -> tail = xor_list -> tail -> ptr_near;
            //printf("line: %d \n", __LINE__);
            //printf("%d\n",xor_list->current->value);
            xor_list -> tail -> ptr_near = xor(xor_list -> tail -> ptr_near, xor_list->current);
            //printf("line: %d \n", __LINE__);
            //printf("%d\n",xor_list -> tail -> ptr_near -> value);
            free(xor_list -> current);
            xor_list -> current = (xnode*)NULL;
        }
        else{
            //printf("line: %d \n", __LINE__);
            free(xor_list -> head);
            xor_list -> head = (xnode*)NULL;
            xor_list -> tail = (xnode*)NULL;
        }
    }
}

void print_xlist(xlist xor_list){
    xnode *last = (xnode*)NULL;
    xnode *next;
    if(xor_list.head != (xnode*)NULL){
        xor_list.current = xor_list.head;
        while(xor_list.current != (xnode*)NULL){
            printf("%d%c", xor_list.current -> value, ' ');
            next = xor(last, xor_list.current -> ptr_near);
            last = xor_list.current; 
            xor_list.current = next;
        }
        printf("%c", '\n');
    }
    else{
        printf("%c", '\n');
    }
}

void scan_order(char order[], xlist rail[]){
    int num1=0;//how many rails
    int num2=0;
    int i=0;
    if((isdigit(order[6])!=0 ) && (order[0]=='e')){//digit
        //Decide which rail to push or pop
        //printf("line: %d \n", __LINE__);
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
        //printf("%d%c%d\n",num1,' ',num2);
        push_xnode(&rail[num1], num2);
    }
    else if((isdigit(order[6]) != 0) && (order[0] == 'l')){
        i=6;
        while(order[i] != '\n'){
            num1 = num1*10+(order[i]-'0');
            i++;
        }
        //printf("%d\n",num1);
        //printf("line: %d \n", __LINE__);
        pop_xnode(&rail[num1]);
    }
    else{//migrate
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
        //printf("line: %d \n", __LINE__);
        //確定第一個list有東西
        if(rail[num1].head != (xnode*)NULL){
            //printf("line: %d \n", __LINE__);
            rail[num1].tail -> ptr_near = xor(rail[num1].tail -> ptr_near, rail[num2].tail);
            //printf("line: %d \n", __LINE__);
            if (rail[num2].tail != (xnode*)NULL){
                //printf("line: %d \n", __LINE__);
                rail[num2].tail -> ptr_near = xor(rail[num2].tail -> ptr_near, rail[num1].tail);
            }
            else{
                //printf("line: %d \n", __LINE__);
                rail[num2].head = rail[num1].tail;
            }
            rail[num2].tail = rail[num1].head;
            //printf("line: %d \n", __LINE__);
            rail[num1].head = (xnode*)NULL;
            rail[num1].tail = (xnode*)NULL;
        }
    }
}

int main(){
    int n=0;//The number of the order
    int k=0;//The mumber of the rail
    char order[20];
    int j;
    int l;
    int m;
    scanf("%d%d", &k, &n);
    //printf("%d%c%d",k,' ',n);
    xlist *rail;
    rail = (xlist*)malloc(sizeof(xlist)*k);
    fflush(stdin);
    for (j=0;j<n;j++){
        fgets(order, 16, stdin);
        scan_order(order, rail);
        /*printf("%c\n",'Y');
        for (l=0;l<k;l++){
            print_xlist(rail[l]);
        }
        printf("%c\n",'Y');*/
    }
    for (l=0;l<k;l++){
        print_xlist(rail[l]);
    }
    return 0;
}
/*
5 30
enter 4 2788
leave 4
migrate 4 3
enter 2 132
enter 0 2800
migrate 2 3
enter 1 3116
enter 3 8714
enter 0 267
migrate 0 1
enter 4 4055
migrate 3 0
enter 2 2567
migrate 1 4
migrate 1 2
enter 4 72
leave 1
migrate 0 4
migrate 4 1
migrate 2 0
enter 1 1230
migrate 3 2
migrate 0 4
leave 3
enter 2 8548
enter 0 4983
leave 4
migrate 3 2
enter 3 3731
enter 1 9536
*/