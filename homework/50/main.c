/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct DisjointSet{
    // TODO: Determine fields to use by your method
    int parent;
    int rank;
} disjoint_set;

disjoint_set ds[1 << 24];
bool set[1 << 24] = {};

int c2i(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}

int hash(const char* s) {
    int ret = 0;
    for (int i = 0; i < 4; ++i)
        ret = (ret << 6) | c2i(s[i]);
    return ret;
}

void makeset(const char* s){
    int i = hash(s);
    ds[i].parent = i;
    ds[i].rank = 1;
    // TODO: Initialize a set
}

inline void static init(const char* s) {
    int i = hash(s);
    if (!set[i]) {//set[i] doesn't exist
        makeset(s);
        set[i] = 1;
    }
}

int find_set(const char* s) {
    init(s);
    int i = hash(s);
    // TODO: Implement your find algorithm here
    int root = i;
    while (root != ds[root].parent){
        root = ds[root].parent;
    }
    int next;
    while (i != root){
        next = ds[i].parent;
        ds[i].parent = root;
        ds[i].rank = 2;
        i = next;
    }
    return  root something ;
}

void link(const char *ra, const char *rb) {
    int a = find_set(ra), b = find_set(rb);
    ds[a].parent = b;
    if(ds[a].rank > ds[b].rank){
        ds[b].parent = a;
    }
    else if(ds[a].parent == b){
        if(ds[a].rank == ds[b].rank){
            ds[b].rank = ds[b].rank +1;
        }
    }
    // TODO: Implement your union algorithm here
}

bool same_set(const char *a, const char *b) {
    return (find_set(a) == find_set(b));
}

bool stringcompare(const char *a, const char *b) {
    // implement your string compare
    int j;
    if(strlen(a) == strlen(b)){
        for (j = 0; j< strlen(a); j++){
            int sa = hash(a + (j * 4)), sb = hash(b + (j * 4));
            if (sa != sb){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }

}

int main() {
    int n;
    scanf("%d", &n);
    char cmd[16], a[512], b[512];
    for (int i = 0; i < n; ++i) {
        scanf("%s %s %s", cmd, a, b);
        if (!strcmp(cmd, "union")) {
            init(a);
            init(b);
            link(a, b);
        } else {
            bool same = stringcompare(a, b);
            if(same) puts("True");
            else puts("False");
        }
    }
}*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct DisjointSet{
    // TODO: Determine fields to use by your method
    int parent;
    int rank;
} disjoint_set;

disjoint_set ds[1 << 24];
bool set[1 << 24] = {};

int c2i(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}

int hash(const char* s) {
    int ret = 0;
    for (int i = 0; i < 4; ++i)
        ret = (ret << 6) | c2i(s[i]);
    return ret;
}

void makeset(const char* s){
    int i = hash(s);
    ds[i].parent = i;
    ds[i].rank = 1;
    // TODO: Initialize a set
}

inline void static init(const char* s) {
    int i = hash(s);
    if (!set[i]) {//set[i] doesn't exist
        makeset(s);
        set[i] = 1;
    }
}

int find_set(const char* s) {
    init(s);
    int i = hash(s);
    // TODO: Implement your find algorithm here
    int root = i;
    while (root != ds[root].parent){
        root = ds[root].parent;
    }
    int next;
    while (i != root){
        next = ds[i].parent;
        ds[i].parent = root;
        ds[i].rank = 2;
        i = next;
    }
    return  root/* something */;
}

void link(const char *ra, const char *rb) {
    int a = find_set(ra), b = find_set(rb);
    ds[a].parent = b;
    // TODO: Implement your union algorithm here
}

bool same_set(const char *a, const char *b) {
    return (find_set(a) == find_set(b));
}

bool stringcompare(const char *a, const char *b) {
    // implement your string compare
    int i;
    if(strlen(a) == strlen(b)){
        int len = strlen(a);
        for(int i = 0; i < len / 4; i++){
            if(!same_set(a + i * 4, b + i * 4))
                return false;
        }
        return true;
    }else{
        return false;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char cmd[16], a[512], b[512];
    for (int i = 0; i < n; ++i) {
        scanf("%s %s %s", cmd, a, b);
        if (!strcmp(cmd, "union")) {
            init(a);
            init(b);
            link(a, b);
        } else {
            bool same = stringcompare(a, b);
            if(same) puts("True");
            else puts("False");
        }
    }
}