//ref:https://www.geeksforgeeks.org/construct-bst-from-given-preorder-traversa/
//https://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/
//http://alrightchiu.github.io/SecondRound/binary-tree-traversalxun-fang.html
//https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
//I asked the question on the forum and the classmate&TA gave me some helpful advice on my work.

#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<stdbool.h>

struct node{
    int key;
    int left_key_pos;
    int right_key_pos;
    struct node *left, *right, *parent;
};
typedef struct node t_node;

t_node *newNode(int value){
    t_node *n = (t_node*)malloc(sizeof(t_node));
    n -> key = value;
    n -> left = (t_node*)NULL;
    n -> right = (t_node*)NULL;
    n -> parent = (t_node*)NULL;

    return n;
}
int max_key(int a, int b){
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}
int min_key(int a, int b){
    if(a < b){
        return a;
    }
    else{
        return b;
    }
}

void BST_search(t_node *root, int *number, int min, int max){
    if(root  == (t_node*)NULL){//node is null, stop
        *number += 0;
    }
    else{//node isn't null
        if(root -> key >= min && root -> key <= max){//Healthy fruit
            *number += 1;
            BST_search(root -> left, number, min, root -> key-1);
            BST_search(root -> right, number, root -> key+1, max);
        }
        else{
            BST_search(root -> left, number, min, min_key(max, root -> key));//Fruit of the poisonous tree, I need to update the max-value of the node
            BST_search(root -> right, number, max_key(min, root -> key ), max);//Fruit of the poisonous tree, I need to update the min-value of the node
        }
    }

}

int main(){

    t_node *node_arr[1000001];
    int n;
    scanf("%d", &n);
    int j;
    int value;
    int left_key_pos;
    int right_key_pos;

    for(j=1 ;j<n+1 ;j++){
        scanf("%d", &value);
        t_node *node = newNode(value);
        node_arr[j] = node;
        scanf("%d", &left_key_pos);
        node_arr[j] -> left_key_pos = left_key_pos;
        scanf("%d", &right_key_pos);
        node_arr[j] -> right_key_pos = right_key_pos;
    }
    for(j=1 ;j<n+1 ;j++){
        if(node_arr[j] -> left_key_pos != -1){
            node_arr[j] -> left = node_arr[node_arr[j] -> left_key_pos];
            node_arr[j] -> left -> parent = node_arr[j];
        }
        if(node_arr[j] -> right_key_pos != -1){
            node_arr[j] -> right = node_arr[node_arr[j] -> right_key_pos];
            node_arr[j] -> right -> parent = node_arr[j];
        } 
    }
    
    int num = 0;
    BST_search(node_arr[1], &num, 1, 1000000000);
    printf("%d", num);
    return 0;
}
//printf("%d\n", __LINE__);