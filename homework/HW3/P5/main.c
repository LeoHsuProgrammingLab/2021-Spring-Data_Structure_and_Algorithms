//I heard the method of treap from the TA and I discussed the concept of treap with my classmate 沈家睿 on discord.
//Especially I have difficulties with the "while loop" of last operation, TA told me that I can write in the "while(true)" instead of "while A or B".
//These below are all the references of this homework I read:
//1.http://yp155136codingarea.blogspot.com/2016/03/treap-lazy-tag.html
//2.https://codertw.com/%E7%A8%8B%E5%BC%8F%E8%AA%9E%E8%A8%80/494973/#outline__1
//3.http://memphis.is-programmer.com/posts/46317.html
//4.http://sunmoon-template.blogspot.com/2015/01/split-merge-randomized-binary-search.html

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node{
    int priority;
    int fix;
    int size;
    int max;
    int tag_reve;
    int tag_plus;
    struct node *left;
    struct node *right;
}node;

node *New_n(int priority){
    node *n = malloc(sizeof(node));
    int ran = rand();
    n -> fix = ran;
    n -> priority = priority;
    n -> max  = priority;
    n -> tag_reve = 0;
    n -> tag_plus = 0;
    n -> left = (node*)NULL;
    n -> right = (node*)NULL;
    n->size = 1;
    return n;
}

int bigger(int a, int b){
    if(a>b)
        return a;
    else
        return b;
}

void down(node **n){//lazy tag
    if(*n){
        if((*n) -> tag_plus != 0){
            (*n)->priority += (*n)->tag_plus;
            (*n)->max += (*n)->tag_plus;
            if((*n)->left)
                (*n)->left->tag_plus += (*n)->tag_plus;
            if((*n)->right)
                (*n)->right->tag_plus += (*n)->tag_plus; 
            (*n)->tag_plus = 0;
        }
        if((*n)->tag_reve == 1){
            if((*n)->left || (*n)->right){
                node *store = (*n)->left;
                (*n) -> left = (*n)->right;
                (*n) -> right = store;
                if((*n)->left)
                    (*n)->left -> tag_reve = (*n)->left->tag_reve ^ (*n)->tag_reve;
                if((*n)->right)
                    (*n)->right -> tag_reve = (*n)->right->tag_reve ^ (*n)->tag_reve;
            }
            (*n)->tag_reve = 0;
        }
    }
}

void upd(node **n){
    if((*n)!=(node*)NULL){
        (*n) -> size = ((*n)->left ? (*n)->left->size : 0) + ((*n)->right ? (*n)->right->size : 0)+1;
        if((*n)->left){
            down(&((*n)->left));
            (*n) -> max = bigger((*n)->left->max, (*n)->priority);
            if((*n)->right){
                down(&((*n)->right));
                (*n) -> max = bigger((*n)->right->max, (*n)->max);
            } 
        }
        else{
            if((*n)->right){
                down(&((*n)->right));
                (*n) -> max = bigger((*n)->right->max, (*n)->priority);
            }
            else{
                down(n);
                (*n)->max = (*n)-> priority;
            }
        }
    }
}

int size(node *a){
    return a?a->size:0;
}

node *merge(node **a, node **b){
    if(!(*a))
        return *b;
    if(!(*b))
        return *a;
    if((*a)->fix < (*b)->fix){
        down(a);
        (*a)->right = merge(&(*a)->right, b);
        upd(a);
        return *a;
    }
    else{
        down(b);
        (*b)->left = merge(a, &(*b)->left);
        upd(b);
        return *b;
    }
}

void split(node **rt, node **a, node **b, int pos){
    //down(rt);
    //upd(rt);
    if((*rt) == (node*)NULL){
        *a = (node*)NULL;
        *b = (node*)NULL;
    }
    else{
        down(rt);
        if(pos <= size((*rt)->left)){
            *b = (*rt);
            split(&(*rt)->left, a, &((*b)->left), pos);
            down(a);
            upd(a);
            down(b);
            upd(b);
        }
        else{
            *a = (*rt);
            split(&(*rt)->right, &((*a)->right), b, pos-size((*rt)->left)-1);
            down(a);
            upd(a);
            down(b);
            upd(b);
        }
        upd(rt);
    } 
}

void insert(node **rt, int priority, int pos){
    node *a, *b, *now_n;
    split(rt, &a, &b, pos);
    now_n = New_n(priority);
    a = merge(&a, &now_n);
    *rt = merge(&a, &b);
}

void delete_pos(node **rt, int pos){
    node *a1, *b1, *a2, *b2;
    split(rt, &a1, &b1, pos-1);
    split(&b1, &a2, &b2, 1);
    *rt = merge(&a1, &b2);
}

void increase(node **rt, int pos1, int pos2, int plus){
    node *a1, *b1, *a2, *b2;
    split(rt, &a1, &b1, pos1-1);//a1 is the left part
    split(&b1, &a2, &b2, pos2-pos1+1);//a2 is the middle object, b2 is the right part
    a2 -> tag_plus += plus;
    node *c = merge(&a1, &a2);
    *rt = merge(&c, &b2);
}

int query_max(node **rt, int pos1, int pos2){//if pos1 = 1, pos2 = n?
    node *a1, *b1, *a2, *b2;
    split(rt, &a1, &b1, pos1-1);
    split(&b1, &a2, &b2, pos2-pos1+1);
    int max = a2 -> max;
    node *c = merge(&a1, &a2);
    *rt = merge(&c, &b2);
    return max;
}

void reverse(node **rt, int pos1, int pos2){
    node *a1, *b1, *a2, *b2;
    split(rt, &a1, &b1, pos1-1);
    split(&b1, &a2, &b2, pos2-pos1+1); 
    a2 -> tag_reve = 1;
    node *c = merge(&a1, &a2);
    *rt = merge(&c, &b2);
}

void remove_max(node **rt){
    down(rt);
    int max = (*rt)->max;
    int pos = 0;
    node *now = *rt;
    while(true){
        down(&(now->left));
        down(&(now->right));
        if(now->left){//If left exist
            if(max == now->left->max){
                now = now->left;
            }
            else{
                if(max == now->priority){
                    break;
                }
                if(max == now->right->max){
                    pos += now->left->size + 1;
                    now = now->right;
                }
            }
        }
        else{
            if(max == now->priority){
                break;
            }
            if(max == now->right->max){
                pos += 1;
                now = now->right;
            }
        }
    }
    pos += ((now->left)? now->left->size : 0) + 1;
    delete_pos(rt, pos);
}

node *root = (node*)NULL;

int main(){
    srand(19981003);
    int no_num, op_num;
    scanf("%d %d", &no_num, &op_num);
    int i;
    int store;
    for(i = 0; i<no_num; i++){
        scanf("%d", &store);
        insert(&root, store, i);
    }
    int type, pos1, pos2, pos, priority, plus;
    for(i = 0; i<op_num; i++){
        scanf("%d", &type);
        if(type == 1){
            scanf("%d %d", &priority, &pos);
            insert(&root, priority, pos);
        }
        else if(type == 2){
            scanf("%d", &pos);
            delete_pos(&root, pos);
        }
        else if(type == 3){
            scanf("%d %d %d", &pos1, &pos2, &plus);
            increase(&root, pos1, pos2, plus);
        }
        else if(type == 4){
            scanf("%d %d", &pos1, &pos2);
            printf("%d\n", query_max(&root, pos1, pos2));
        }
        else if(type == 5){
            scanf("%d %d", &pos1, &pos2);
            reverse(&root, pos1, pos2);
        }
        else if(type == 6){
            remove_max(&root);
        }
    }
    return 0;
}

