//ref: Graph pdf from the DSA class. I also learn some topological sorting from the DSA TA. Really appreciate!

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int vertex;
    struct node *next;
}node;
node *New_n(int vertex){
    node *n = malloc(sizeof(node));
    n -> vertex = vertex;
    n -> next = NULL;
    return n;
}

typedef struct linkedlist{
    node *head;
    node *tail;
}llist;

int bigger(int a, int b){
    if(a>b)
        return a;
    else
        return b;
}
int smaller(int a, int b){
    if(a<b)
        return a;
    else
        return b;
}

int main(){
    int n;
    scanf("%d", &n);
    int i, j;
    int len = 0;
    int edge = 0;
    int total = 0;
    llist arr[n+1];
    for(i = 1; i<n+1; i++){//construct an adjacent list
        arr[i].head = (node*)NULL;
        arr[i].tail = (node*)NULL;
        scanf("%d", &len);
        total += len;
        for(j = 0; j<len; j++){
            scanf("%d", &edge);
            if(arr[i].tail == (node*)NULL){
                arr[i].head = New_n(edge);
                arr[i].tail = arr[i].head;
            }
            else{
                arr[i].tail -> next = New_n(edge);
                arr[i].tail = arr[i].tail -> next; 
            }
        }
    }
    total /= 2;
    int arr_q[2][400001] = {0};
    int id_en = 0;
    for(i = 1; i< n+1; i++){
        if(arr[i].head != (node*)NULL){
            if(i == arr[arr[i].head -> vertex].head -> vertex && i<arr[i].head -> vertex){
                arr_q[0][id_en] = smaller(i, arr[i].head -> vertex);
                arr_q[1][id_en] = bigger(i, arr[i].head -> vertex);
                id_en++;
            }
        }
    }
    int id_de = 0;
    while(id_en < total){
        if(id_en == id_de){
            printf("No\n");
            return 0;
        }
        arr[arr_q[0][id_de]].head = arr[arr_q[0][id_de]].head -> next;
        arr[arr_q[1][id_de]].head = arr[arr_q[1][id_de]].head -> next;
        if(arr[arr_q[0][id_de]].head != (node*)NULL){
            if(arr_q[0][id_de] == arr[arr[arr_q[0][id_de]].head -> vertex].head -> vertex){
                arr_q[0][id_en] = smaller(arr[arr_q[0][id_de]].head -> vertex, arr[arr[arr_q[0][id_de]].head -> vertex].head -> vertex);
                arr_q[1][id_en] = bigger(arr[arr_q[0][id_de]].head -> vertex, arr[arr[arr_q[0][id_de]].head -> vertex].head -> vertex);
                id_en ++;
            }
        }
        if(arr[arr_q[1][id_de]].head != (node*)NULL){
            if(arr_q[1][id_de] == arr[arr[arr_q[1][id_de]].head -> vertex].head -> vertex){
                arr_q[0][id_en] = smaller(arr[arr_q[1][id_de]].head -> vertex, arr[arr[arr_q[1][id_de]].head -> vertex].head -> vertex);
                arr_q[1][id_en] = bigger(arr[arr_q[1][id_de]].head -> vertex, arr[arr[arr_q[1][id_de]].head -> vertex].head -> vertex);
                id_en ++;
            }
        }
        id_de ++;
    }    
    printf("Yes\n");
    for(i = 0; i<total; i++){
        printf("%d %d\n", arr_q[0][i], arr_q[1][i]);
    }
    
    return 0;
}