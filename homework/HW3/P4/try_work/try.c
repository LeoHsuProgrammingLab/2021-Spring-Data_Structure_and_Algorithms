#include<stdio.h>

int main(){

    int i;
    char garble[4] = "AADF";
    char email[8] = "ABCADBFG";
    int alpha[52] = {0};
    int table[8] = {2, 0, 0, 1, 0, 1, 0};
    int max = 3;
    int now = 0;
    int tail = 0;
    for (i = 0; i<8; i++){
        alpha[email[i]-'A']++;
        if(alpha[email[i]-'A'] == table[email[i]-'A']){
            now++;
        }
        printf("%d", now);
    }
    puts("");
    int head = 0;
    for (i = 0; i<8; i++){
        alpha[email[i]-'A']--;
        if(alpha[email[i]-'A'] == table[email[i]-'A']-1){
            now--;
        }
        printf("%d", now);
    }
    int a = 10007*10006;
    printf("%d\n", a);
    return 0;
}