
//ref:https://www.geeksforgeeks.org/construct-bst-from-given-preorder-traversa/

#include<stdlib.h>
#include<string.h>
#include<stdio.h>

struct node{
    int key;
    int left_key_pos;
    int right_key_pos;
    struct node *left, *right;
};
typedef struct node t_node;

t_node *newNode(int value){
    t_node *n = (t_node*)malloc(sizeof(t_node));
    n -> key = value;
    n -> left = (t_node*)NULL;
    n -> right = (t_node*)NULL;

    return n;
}


void BST_search(t_node *root, int value, int *number){
    if(root == (t_node*)NULL){
        //printf("%d\n", __LINE__);
        *number += 0;
    }
    else if(root -> key == value){
        //printf("%d\n", __LINE__);
        *number += 1;
    }
    else if(root -> key > value){
        //printf("%d\n", __LINE__);
        BST_search(root -> left, value, number);
    }
    else if(root -> key < value){
        //printf("%d\n", __LINE__);
        BST_search(root -> right, value, number);
    }
    
}

int main(){

    t_node *node_arr[1000001];
    int n;
    scanf("%d", &n);
    int j;
    int value;

    for(j=1 ;j<n+1 ;j++){
        scanf("%d", &value);
        //input key value
        //printf("%d\n", __LINE__);
        t_node *node = newNode(value);
        //printf("%d\n", __LINE__);
        node_arr[j] = node;
        //printf("%d\n", __LINE__);
        scanf("%d", &node_arr[j] -> left_key_pos);
        scanf("%d", &node_arr[j] -> right_key_pos);
        //link the position
    }
    for(j=1 ;j<n+1 ;j++){
        if(node_arr[j] -> left_key_pos != -1){
            /*if (node_arr[left_key_pos] == (t_node*)NULL){
                node_arr[left_key_pos] = newNode(0);
            }*/
            //目前會指不到東西
            node_arr[j] -> left = node_arr[node_arr[j] -> left_key_pos];
        }
        if(node_arr[j] -> right_key_pos != -1){
            /*if (node_arr[right_key_pos] == (t_node*)NULL){
                node_arr[right_key_pos] = newNode(0);
            }*/
            node_arr[j] -> right = node_arr[node_arr[j] -> right_key_pos];
        } 
    }
    

    int num = 0;
    for(j=1 ; j<n+1 ; j++){
        BST_search(node_arr[1], node_arr[j] -> key, &num);
        //printf("%d%c\n", num,'k');
    }
    
    printf("%d", num);


    return 0;
}