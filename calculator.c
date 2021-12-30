#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 50

typedef struct {//数字栈结构体
	double data[MAXSIZE];
	int top;
} opstack;

typedef struct {//符号栈结构体
	char data[MAXSIZE];
	int top;
} stack;

//初始化栈
void InitStack(stack *s) {
	s->top=0;
}

//取栈头
int GetTop(stack s, char *e) {
	if(s.top<=0)
		return 0;
	else {
		*e=s.data[s.top-1];
		return 1;
	}
}

//出栈操作
void Pop(stack *s, char *e) {
	if(s->top<=0)
		printf("栈空!");
	else
		*e=s->data[--s->top];
}

//入栈操作
void Push(stack *s, char e) {
	if(s->top>=MAXSIZE)
		printf("栈满!");
	else
		s->data[s->top++]=e;
}

//判断栈空
int StackEmpty(stack s) {
	if(s.top==0)
		return 1;
	else return 0;
}

//计算表达式值
double ComputeExpress(char a[]) {
	opstack s;
	int i=0, value;
	float x1, x2, result;
	s.top=-1;
	while (a[i]!='\0') {
		if(a[i]!=' '&&a[i]>='0'&&a[i]<='9') {
			value=0;
			while (a[i]!=' ') {
				value=10*value+a[i]-'0';
				i++;
			}
			s.top++;
			s.data[s.top]=value;
		} else {
			switch(a[i]) {
				case '+':
					x1=s.data[s.top--];
					x2=s.data[s.top--];
					result=x1+x2;
					s.data[++s.top]=result;
					break;
				case '-':
					x1=s.data[s.top--];
					x2=s.data[s.top--];
					result=x2-x1;
					s.data[++s.top]=result;
					break;
				case '*':
					x1=s.data[s.top--];
					x2=s.data[s.top--];
					result=x1*x2;
					s.data[++s.top]=result;
					break;
				case '/':
					x1=s.data[s.top--];
					x2=s.data[s.top--];
					result=x2/x1;
					s.data[++s.top]=result;
					break;
				case '^':
					x1=s.data[s.top--];
					x2=s.data[s.top--];
					result=pow(x2,x1);
					s.data[++s.top]=result;
					break;
			}
			i++;
		}
	}
	if(!s.top!=-1) {
		result=s.data[s.top];
		s.top--;
		if(s.top==-1)
			return result;
		else {
			printf("表达式错误!");
			//exit(-1);
		}
	}
}

//中缀表达式转后缀表达式
void TranslateExpress(char str[], char exp[]) {
	stack s;
	char ch, e;
	int i=0, j=0;
	InitStack(&s);
	ch=str[i++];
	while(ch!='\0') {
		switch(ch) {
			case '(':
				Push(&s,ch);
				break;
			case ')':
				while (GetTop(s,&e)&&e!='(') {
					Pop(&s,&e);
					exp[j++]=e;
				}
				Pop(&s,&e);
				break;
			case '+':
			case '-':
				while (!StackEmpty(s)&&GetTop(s,&e)&&e!='(') {
					Pop(&s,&e);
					exp[j++]=e;
				}
				Push(&s,ch);
				break;
			case '*':
			case '/':
				while(!StackEmpty(s)&&GetTop(s,&e)&&e=='/'||e=='*'||e=='^') {
					Pop(&s,&e);
					exp[j++]=e;
				}
				Push(&s,ch);
				break;
			case '^':
				while(!StackEmpty(s)&&GetTop(s,&e)&&e=='^') {
					Pop(&s,&e);
					exp[j++]=e;
				}
				Push(&s,ch);
				break;
			case ' ':
				break;
			default:
				while(ch>='0'&&ch<='9') {
					exp[j++]=ch;
					ch=str[i++];
				}
				i--;
				exp[j++]=' ';
		}
		ch=str[i++];
	}
	while(!StackEmpty(s)) {
		Pop(&s,&e);
		exp[j++]=e;
	}
	exp[j]='\0';
}

//判断中缀表达式是否合理
bool judge_infix(char str[]){
	int temp=0;
 	if(str[0]=='/'||str[0]=='*')
		return false;
	if(str[strlen(str)-1]<'0'&&str[strlen(str)-1]>'9')
		return false;
	for(int i=0; i<strlen(str); i++) {
		if(str[i]=='(') {
			if(i==0&&(str[i+1]=='*'||str[i+1]=='/'))
				return false;
			else if(str[i-1]>='0'&&str[i-1]<='9')
				return false;
			temp++;
		} else if(str[i]==')') {
			if(i==0)
				return false;
			else if(str[i-1]=='+'||str[i-1]=='*'||str[i-1]=='-'||str[i-1]=='/')
				return false;
			else if(str[i+1]>='0'&&str[i+1]<='9')
				return false;
			temp--;
		}
	}
	if(temp==0)
		return true;
	return false;
}

int main() {
	char a[MAXSIZE],b[MAXSIZE];
	double f;
	int flag=0;
	printf("请输入一个算术表达式:");
	gets(a);
	printf("中缀表达式为: %s\n",a);
	bool judge = judge_infix(a);
	if(judge == false){
        printf("表达式有误！\n");
        system("pause");
		exit(-1);
	}else
		TranslateExpress(a,b);
		printf("后缀表达式为: %s\n",b);
		f=ComputeExpress(b);
		printf("计算结果为: %f\n",f);
	system("pause");
	return 0;
}
