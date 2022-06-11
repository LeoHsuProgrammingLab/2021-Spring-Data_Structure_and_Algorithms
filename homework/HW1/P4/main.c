//I discussed with my senior high school classmate, Nien Chieh, who studied in NCTU.
//I referenced the link: http://www2.lssh.tp.edu.tw/~hlf/class-1/lang-c/stack2.htm in order to know the ''stack'' better.
#include<stdio.h>
#include<string.h>
#include <ctype.h>
char opt[5]={'(','*','/','+','-'};
int prior[5]={3,2,2,1,1};
char stack_op[1000005];
double stack_num[1000005];
int top_op=-1;
int top_num=-1;

//function!
int priority(char op){
    int j=0;
    for (j=0;j<5;j++){
        if(op==opt[j]){
           return prior[j]; 
        }
    }
    return -1;
}
void push_op(char sign){
    stack_op[++top_op]=sign;
}
void push_num(double sign){
    stack_num[++top_num]=sign;
}
char pop_op(){
    return stack_op[top_op--];
}
double pop_num(){
    return stack_num[top_num--];
}
void calculate(char c){
    double second=pop_num();
    double first=pop_num();
    if(c=='+'){
        push_num(first+second);
    }
    else if(c=='-'){
        push_num(first-second);
    }
    else if(c=='*'){
        push_num(first*second);
    }
    else if(c=='/'){
        push_num(first/second);
    }
}
void operator_flow(char c){
    if(c=='+' || c=='-'){
        if(top_op==-1){
            push_op(c);
        }
        else if (priority(c)>priority(stack_op[top_op])){
            push_op(c);
        }
        else{
            while((top_op>-1) && (stack_op[top_op]!='(')){
                calculate(pop_op());
            }
            push_op(c);
        }
    }
    else if(c=='*' || c=='/'){
        if(top_op==-1){
            push_op(c);
        }
        else if(priority(c)>priority(stack_op[top_op])){
            push_op(c);
        }
        else{
            while((top_op>-1) && (stack_op[top_op]=='*'|| stack_op[top_op]=='/')){
                calculate(pop_op());
            }
            push_op(c);
        }
    }
    else if(c=='('){
        push_op(c);
    }
    else if(c==')'){
        while((top_op>-1) && stack_op[top_op]!='('){
            calculate(pop_op());
        }
        pop_op();
    }
    else if(c=='\0'){
        while(top_op>-1){
            calculate(pop_op());
        }
    }
}

double scan_infix(char infix[]){
    double num=0;
    int i;
    int len = strlen(infix);
    for (i=0;i<=len;i++){
        if(isdigit(infix[i])!=0){
            num=num*10+(infix[i]-'0');
        }
        else{
			if (i!=0){
				if(isdigit(infix[i-1])!=0){
                	push_num(num);
                	num=0;
            	}
			}
            operator_flow(infix[i]);
        }
    }
    return stack_num[top_num];
}

int main(){
    char infix[1000005];
    while(scanf("%s",infix)!=EOF){
        printf("%0.15f\n",scan_infix(infix));
    }
	return 0;
}


