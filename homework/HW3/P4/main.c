//ref:DSA TA Hour, and the pdf made by the Professor(Chapter: hashing).
//I also discussed the concept of hash and terminal execution with my classmates 邱譯.
//Really appreciated the TA's advice.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <math.h>
int ascii(char a){
    if(a >= 'a'){
        return a-'a'+26;
    }
    else{
        return a-'A';
    }
}

int find_head(char email[], int alpha[], int count[], int len_e, int *goal, int head){
    int i;
    for(i = head+1; i < len_e; i++){
        count[ascii(email[i])]--;
        if(count[ascii(email[i])] == alpha[ascii(email[i])]-1){
            *goal = *goal - 1;
            break;
        }
    }
    return i;
}

int find_tail(char email[], int alpha[], int count[], int max, int len_e, int *goal, int tail, bool *first){
    int i;
    for(i = tail+1; i < len_e; i++){
        count[ascii(email[i])]++;
        if(count[ascii(email[i])] == alpha[ascii(email[i])]){
            *goal = *goal + 1;
            if(*goal == max){
                *first = false;
                return i;
            }
        }
    }
    return -1;
}

int min(int a, int b){
    if (a <= b){return a;}
    else{return b;}
}

bool compare(char a[], int i, int id, int pos){//
    int j;
    bool tf = true;
    for(j = id+1; j <= i; j++){
        if(a[j] != a[(pos - i) + (j-id)-1]){
            tf =false;
            break;
        }
    }
    return tf;
}

void printMail(char email[], int posRec[], int len_e){
    int i;
    if(len_e == 0){
        printf("\n");
    }
    else{
        for(i = 0; i< len_e; i++){
            if(i == len_e -1)
                printf("%c\n", email[i]);
            else
                printf("%c", email[i]);
            if(posRec[i] == 1){
                printf("|");
            }
        }
    }
}

void con_table(int hash_table[], int base_table[], char email[], int len_e){
    int i;
    for(i = 0; i < len_e; i++){
        if(i!=0){
            hash_table[i] = hash_table[i-1]*31%10007+ascii(email[i]);
            base_table[i] = base_table[i-1]*31%10007;
        }
        else{
            hash_table[i] = ascii(email[i]);
            base_table[i] = 1;
        }
    }
}

void tag_bar(int hash_table[], int base_table[], char email[], int len_e, int posRec[], int *id){
    int i;
    for(i = 0; i < len_e/2; i++){
        if(*id!= -1){
            if((hash_table[i] - hash_table[*id]*base_table[i - *id]%10007+10007)%10007 == (hash_table[(len_e-1) - (*id+1)] - hash_table[(len_e-1) - (i+1)]*base_table[i-*id]%10007+10007)%10007){
                if(compare(email, i, *id, (len_e-1))){
                    posRec[i] = 1;
                    posRec[(len_e-1) - (i+1)] = 1;
                    *id = i;
                }
            }
        }
        else{
            if(hash_table[i] == (hash_table[len_e-1] - hash_table[(len_e-1) - (i+1)]*base_table[i+1]%10007+10007)%10007){
                if(compare(email, i, *id, (len_e-1))){
                    posRec[i] = 1;
                    posRec[(len_e-1) - (i+1)] = 1;
                    *id = i;
                }
            }
        }
    }
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        char email[100001] = {0};
        char garble[100001] = {0};
        scanf("%s%s", email, garble);
        int len_e = strlen(email);
        int len_g = strlen(garble);
        int i = 0, j = 0;
        int alpha[52] = {0};
        int garble_table[52] = {0};
        for(i = 0; i< len_g; i++){//construct the garble
            alpha[ascii(garble[i])]++;
        }
        int len_table = 0;
        for (i = 0; i<52; i++){//garbel kinds: in order to compare to the email more easily
            if(alpha[i] != 0){
                garble_table[j] = i;
                j++;
                len_table = j;
            }
        }
        int count[52]= {0};
        int h_t_len[2][100001];
        int head = -1;
        int tail = -1;
        int smallest = len_e;
        int goal = 0;
        bool find = true;
        bool first = true;
        while(tail < len_e){
            tail = find_tail(email, alpha, count, len_table, len_e, &goal, tail, &first);
            if(tail == -1){
                if(first == true){
                    find = false;
                }
                break;
            }
            head = find_head(email, alpha, count, len_e, &goal, head);
            int pre_small = smallest;
            smallest = min(smallest, tail - head);
            if(pre_small != smallest){
                h_t_len[0][smallest] = head;
                h_t_len[1][smallest] = tail;
                if (smallest + 1 == len_g){//find the shortest garbledtext
                    break;
                }
            }
        }
        int hash_table[100001] = {0};
        int base_table[100001] = {0};
        int posRec[100001] = {0};
        int id = -1;
        if(find == true){//Build a new email
            char fixed_email[100001] = {0};
            for (i = 0; i<len_e; i++){
                if (i >= h_t_len[0][smallest]){
                    if(i > h_t_len[1][smallest]){
                        fixed_email[i-(smallest+1)] = email[i];
                    }
                }
                else{
                    fixed_email[i] = email[i];
                }   
            }
            
            int len_f_e = strlen(fixed_email);
            con_table(hash_table, base_table, fixed_email, len_f_e);
            tag_bar(hash_table, base_table, fixed_email, len_f_e, posRec, &id);
            printMail(fixed_email, posRec, len_f_e);
        }
        else{//the same email
            con_table(hash_table, base_table, email, len_e);
            tag_bar(hash_table, base_table, email, len_e, posRec, &id);
            printMail(email, posRec, len_e);
        }
    }
    return 0;
}