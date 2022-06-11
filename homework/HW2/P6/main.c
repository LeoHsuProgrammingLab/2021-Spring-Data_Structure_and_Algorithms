//ref:https://www.geeksforgeeks.org/leftist-tree-leftist-heap/
//Sincerely, I appreciate all the TAs in the class, they really helped me a lot inlcuding debugging
//Though they didn't finish debugging for me, they indeed gave me a lot of advice, as a student from other department, 
//TAs really did me a favor for my learning.
//All I want to say: Thank you! 

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//construct a linkedlist
struct ll_node{
    int value;
    struct ll_node *next;
    struct ll_node *prev;
};
typedef struct ll_node ll_node;
ll_node *ll_node_New(int num){
    ll_node *n = (ll_node*)malloc(sizeof(ll_node));
    n -> next = (ll_node*)NULL;
    n -> prev = (ll_node*)NULL;
    n -> value = num;
    return n;
}
struct linkedlist{
    int length;
    ll_node *head;
    ll_node *tail;
};
typedef struct linkedlist llist;
//construct a leftist tree by linkedlist
struct t_node{
    int value;
    int dist;
    struct t_node *left;
    struct t_node *right;
};
typedef struct t_node t_node;
t_node *t_node_New(int num){
    t_node *n = (t_node*)malloc(sizeof(t_node));
    n -> left = (t_node*)NULL;
    n -> right = (t_node*)NULL;
    n -> value = num;
    n -> dist = 0;
    return n;
}

struct leftist_tree{//dist( i ) = 1 + dist( right( i )), dist = the distance to its child which is not equipped with both two childon left and right
    t_node *max_root;
};
typedef struct leftist_tree left_t;
left_t *left_t_New(int num){
    left_t *lt = (left_t*)malloc(sizeof(left_t));
    lt -> max_root = t_node_New(num);
    return lt;
}

void merge(int line1, int line2, llist arr_ll[], int arr_pos[], int arr_line_pos[], int arr_popped[]){
    int p;
    if(arr_ll[arr_line_pos[line1]].length <= arr_ll[arr_line_pos[line2]].length){
        arr_ll[arr_line_pos[line2]].length += arr_ll[arr_line_pos[line1]].length;
        ll_node *n = arr_ll[arr_line_pos[line1]].head;
        for(p = 0; p < arr_ll[arr_line_pos[line1]].length; p++){
            if(arr_popped[n -> value] != 0){
                arr_pos[n -> value] = arr_line_pos[line2];
            }
            n = n->next;
            if(n == (ll_node*)NULL){
                break;
            }
        }
        if(arr_ll[arr_line_pos[line2]].head != (ll_node*)NULL){
            if(arr_ll[arr_line_pos[line1]].head != (ll_node*)NULL){
                arr_ll[arr_line_pos[line1]].tail -> next = arr_ll[arr_line_pos[line2]].head;
                arr_ll[arr_line_pos[line2]].head -> prev = arr_ll[arr_line_pos[line1]].tail;
                arr_ll[arr_line_pos[line2]].head = arr_ll[arr_line_pos[line1]].head;
                //arr_ll[arr_line_pos[line1]].head = (ll_node*)NULL;
                //arr_ll[arr_line_pos[line1]].tail = (ll_node*)NULL;
            }
        }
    }
    else{//如果line2比較小
        arr_ll[arr_line_pos[line1]].length += arr_ll[arr_line_pos[line2]].length;
        ll_node *n = arr_ll[arr_line_pos[line2]].head;
        for(p = 0; p < arr_ll[arr_line_pos[line2]].length; p++){
            if(arr_popped[n -> value] != 0){
                arr_pos[n -> value] = arr_line_pos[line1];
            }
            n = n -> next;
            if(n == (ll_node*)NULL){
                break;
            }
        }
        if(arr_ll[arr_line_pos[line1]].head != (ll_node*)NULL){
            if(arr_ll[arr_line_pos[line2]].head != (ll_node*)NULL){
                arr_ll[arr_line_pos[line1]].tail -> next = arr_ll[arr_line_pos[line2]].head;
                arr_ll[arr_line_pos[line2]].head -> prev = arr_ll[arr_line_pos[line1]].tail;
                arr_ll[arr_line_pos[line1]].tail = arr_ll[arr_line_pos[line2]].tail;
                //arr_ll[arr_line_pos[line2]].head = (ll_node*)NULL;
                //arr_ll[arr_line_pos[line2]].tail = (ll_node*)NULL;
            }
        }
        arr_line_pos[line2] = arr_line_pos[line1];
    }
}

t_node *Merge1 (t_node* h1, t_node* h2, int arr_popped[]);
void swapChildren(t_node* max_root2){
    t_node *no;
    no = max_root2 -> left;
    max_root2 -> left = max_root2 -> right;
    max_root2 -> right = no;
}

t_node *Merge(t_node * h1, t_node * h2, int arr_popped[]){
    if (h1 == (t_node*)NULL){
        if(h2 != (t_node*)NULL){
            if(arr_popped[h2 -> value] == 0){
                h2 = Merge(h2 -> left, h2 -> right, arr_popped);
            }
        }
        return h2;
    }
    if (h2 == (t_node*)NULL){
        if(h1 != (t_node*)NULL){
            if(arr_popped[h1 -> value] == 0){
                h1 = Merge(h1 -> left, h1 -> right, arr_popped);
            }
        }
        return h1;
    }
    if(arr_popped[h1 -> value] == 0){//If already popped
        h1 = Merge(h1 -> left, h1 -> right, arr_popped);
    }
    if(arr_popped[h2 -> value] == 0){//If already popped
        h2 = Merge(h2 -> left, h2 -> right, arr_popped);
    }
    if(h1 == (t_node*)NULL){
        return h2;
    }
    if (h2 == (t_node*)NULL)
        return h1;
    if (h1->value >= h2->value)
        return Merge1(h1, h2, arr_popped);
    else
        return Merge1(h2, h1, arr_popped);
}
  
t_node *Merge1(t_node * h1, t_node * h2, int arr_popped[]){
    if (h1->left == (t_node*)NULL)
        h1->left = h2;
    else
    {
        h1->right = Merge(h1->right, h2, arr_popped);
        if(h1 -> right != (t_node*)NULL){
            if (h1->left->dist < h1->right->dist)
                swapChildren(h1);
            h1->dist = h1->right->dist + 1;
        }
    }
    return h1;
}

void find_head(llist *ls, int arr_popped[], int jump){
    ll_node *ls1 = ls -> head -> next;
    while(arr_popped[ls1 -> value] == 0){
        ls1 = ls1 -> next;
        jump ++;
    }
    ls -> head = ls1;
}
void find_tail(llist *ls, int arr_popped[], int jump){
    ll_node *ls1 = ls -> tail -> prev;
    while(arr_popped[ls1 -> value] == 0 ){
        ls1 = ls1 -> prev;
        jump ++;
    }
    ls -> tail = ls1;
}
void insert(int num, int line, llist arr_ll[], int arr_pos[], int arr_line_pos[]){//When push
    if(arr_ll[arr_line_pos[line]].head != (ll_node*)NULL){
        ll_node *new_node = ll_node_New(num);
        new_node -> next = arr_ll[arr_line_pos[line]].head;
        arr_ll[arr_line_pos[line]].head -> prev = new_node;
        arr_ll[arr_line_pos[line]].head = new_node;
    }
    else{
        ll_node *new_node = ll_node_New(num);
        arr_ll[arr_line_pos[line]].head = new_node;
        arr_ll[arr_line_pos[line]].tail = new_node;
    }
    arr_ll[arr_line_pos[line]].length++;
    arr_pos[num] = arr_line_pos[line];
}
void insert_tree(int num, int line, left_t arr_lines[], int most_index, int arr_popped[], int arr_line_pos[]){//When push
    left_t *lt = left_t_New(num);
    arr_lines[most_index] = *lt;
    arr_lines[arr_line_pos[line]].max_root = Merge(arr_lines[arr_line_pos[line]].max_root, arr_lines[most_index].max_root, arr_popped);
}
void deleteMax(left_t *lt, int arr_popped[]){//adjust your array(popped or not)
    lt -> max_root = Merge(lt -> max_root -> left, lt -> max_root -> right, arr_popped);
}
void pop_head(int num, int arr_popped[], llist *ls, int arr_pos[]){//adjust your llist
    int jump = 1;
    if(ls -> head != ls -> tail){
        find_head(ls, arr_popped, jump);
        ls -> length -= jump;
    }
    else{
        ls -> head = (ll_node*)NULL;
        ls -> tail = (ll_node*)NULL;
        ls -> length = 0;
    }
    arr_popped[num] = 0;
    //arr_pos[num] = -1;
}
void pop_tail(int num, int arr_popped[], llist *ls, int arr_pos[]){
    int jump = 1;
    find_tail(ls, arr_popped, jump);
    arr_popped[num] = 0;
    ls -> length -= jump;
}

int main(){
    int t;//t means the number of the testcases
    scanf("%d", &t);
    while(t--){
        int n, o, l;
        scanf("%d", &n);//N indicates the number of packages.
        scanf("%d", &o);//O indicates the total number of “push” and “merge” operations.
        scanf("%d", &l);//L indicates the number of production lines.
        int arr_popped[n+1];
        int h;
        for(h = 0; h < n+1; h++){
            arr_popped[h] = 1;
        }
        int arr_pos[n+1];//store the package's lines
        int arr_line_pos[l];
        int k;
        for(k = 0; k < l; k++){
            arr_line_pos[k] = k;
        }
        for(k = 0; k < n+1; k++){
            arr_pos[k] = -1;//-1 means that it hasn't been traced yet
        }
        int i;
        int arr_op[o][3];//construct an array to store all the operations 
        for(i = 0; i < o; i++){//o operation
            char arr[7];//read the option string
            scanf("%s", arr);
            if(arr[0] == 'p'){
                arr_op[i][0] = 0;
            }
            else if(arr[0] == 'm'){
                arr_op[i][0] = 1;
            }
            scanf("%d", &arr_op[i][1]);
            scanf("%d", &arr_op[i][2]);
        }
        int arr_pair[n];//store the diary record
        for(i = 0; i<n; i++){
            scanf("%d", &arr_pair[i]);
        }
        left_t arr_lines[l+1];
        for(i = 0; i < l+1; i++){//initialize lines
            arr_lines[i] = *left_t_New(0);
        }
        llist arr_ll[l];
        for(i = 0; i < l; i++){//initailize llist
            arr_ll[i].length = 0;
            arr_ll[i].head = (ll_node*)NULL;
            arr_ll[i].tail = (ll_node*)NULL;
        }
        int id_op = 0;//op's index
        int j = 0;
        bool t_or_f[n];
        for (i = 0; i < n; i++){
            t_or_f[i] = false;
        }
        bool result = true;
        while(j < n){
            bool through = true;
            while(through == true && j < n){
                if(arr_pair[j] == arr_op[id_op][1] && arr_op[id_op][0] == 0){//檢查是否為operation = package record
                    t_or_f[j] = true;
                    j++;
                    if(id_op < o-1){
                        id_op++;
                    }
                    continue;
                }
                if(arr_pos[arr_pair[j]] != -1){//已經存進去了
                    if(arr_pair[j] == arr_ll[arr_pos[arr_pair[j]]].head -> value){//head
                        if(arr_ll[arr_pos[arr_pair[j]]].head -> value == arr_lines[arr_pos[arr_pair[j]]].max_root -> value){
                            deleteMax(&arr_lines[arr_pos[arr_pair[j]]], arr_popped);
                        }
                        pop_head(arr_pair[j], arr_popped, &arr_ll[arr_pos[arr_pair[j]]], arr_pos);
                        t_or_f[j] = true;
                        j++;
                    }
                    else if(arr_pair[j] == arr_ll[arr_pos[arr_pair[j]]].tail -> value){// tail
                        if(arr_ll[arr_pos[arr_pair[j]]].tail -> value == arr_lines[arr_pos[arr_pair[j]]].max_root -> value){
                            deleteMax(&arr_lines[arr_pos[arr_pair[j]]], arr_popped);
                        }
                        pop_tail(arr_pair[j], arr_popped, &arr_ll[arr_pos[arr_pair[j]]], arr_pos);
                        t_or_f[j] = true;
                        j++;
                    }
                    else if(arr_pair[j] == arr_lines[arr_pos[arr_pair[j]]].max_root -> value){// max
                        deleteMax(&arr_lines[arr_pos[arr_pair[j]]], arr_popped);
                        arr_popped[arr_pair[j]] = 0;//記錄已經popped
                        t_or_f[j] = true;
                        j++;
                    }
                    else{
                        through = false;
                    }
                }
                else{//還沒存進去
                    if(arr_op[id_op][0] == 0){//push
                        insert(arr_op[id_op][1], arr_op[id_op][2], arr_ll, arr_pos, arr_line_pos);
                        insert_tree(arr_op[id_op][1], arr_op[id_op][2], arr_lines, l, arr_popped, arr_line_pos);
                    }
                    else{//merge
                        if(arr_ll[arr_line_pos[arr_op[id_op][1]]].length <= arr_ll[arr_line_pos[arr_op[id_op][2]]].length){//跟著linkedlist的位置去存
                            arr_lines[arr_line_pos[arr_op[id_op][2]]].max_root = Merge(arr_lines[arr_line_pos[arr_op[id_op][1]]].max_root, arr_lines[arr_line_pos[arr_op[id_op][2]]].max_root, arr_popped);
                        }
                        else{
                            arr_lines[arr_line_pos[arr_op[id_op][1]]].max_root = Merge(arr_lines[arr_line_pos[arr_op[id_op][1]]].max_root, arr_lines[arr_line_pos[arr_op[id_op][2]]].max_root, arr_popped);
                        }
                        merge(arr_op[id_op][1], arr_op[id_op][2], arr_ll, arr_pos, arr_line_pos, arr_popped);
                        }
                    if(id_op < o-1){
                        id_op++;
                    }
                }       
            }
            if(j < n){
                if(t_or_f[j] == false){
                    result = false;
                    break;
                }
            }
        }
        if(result == false){//有false
            printf("%s\n", "impossible");
        }
        else{//全部都是true
            printf("%s\n", "possible");
        }
    }
    return 0;
}