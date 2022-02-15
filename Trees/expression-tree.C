/*
Copyright (C) Deepali Srivastava - All Rights Reserved
This code is part of DSA course available on CourseGalaxy.com  
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	struct node *lchild;
	char info;
	struct node *rchild;
};

int isOperator(char c);
struct node *getNode(int x);
struct node *buildTree(char postfix[],struct node *root);
void prefix(struct node *root);
void preorder(struct node *p);
void postfix(struct node *root);
void postorder(struct node *p);
void parenthesizedInfix(struct node *root);
void inorder(struct node *p);
void display(struct node *root, int level);
int value(struct node *root);
int evaluate(struct node *p);

#define MAX 50
struct node* stack[MAX];
int top;

void initializeStack();
int isEmpty();
int isFull();
void push(struct node* x);
struct node* pop();

main()
{
	struct node *root=NULL;
	
	char postfixExpr[] = "54+12*3*-";
            
    root = buildTree(postfixExpr, root);
	display(root,0);
	printf("\n");

    printf("Prefix : ");
    prefix(root);

    printf("Postfix : ");
    postfix(root);

    printf("Infix : ");
    parenthesizedInfix(root);
            
    printf("Value : %d\n",value(root) );
}

int isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
		return 1;
    return 0;
}

struct node *getNode(int x)
{
	struct node *p=(struct node *) malloc(sizeof(struct node));
	p->info=x;
	p->lchild=NULL;
	p->rchild=NULL;
	return p;
}

struct node *buildTree(char postfix[], struct node *root)
{
	struct node *t;
    int i;

	initializeStack();

    for(i = 0; i < strlen(postfix); i++)
    {
		t = getNode(postfix[i]);
		if(isOperator(postfix[i]))
        {
	        t->rchild = pop();
            t->lchild = pop();
		}
		push(t);
    }
    root = pop();
	return root;
}

void prefix(struct node *root)
{
	preorder(root);
    printf("\n");
}

void preorder(struct node *p)
{
	if (p == NULL)
		return;
    printf("%c",p->info);
    preorder(p->lchild);
    preorder(p->rchild);
}

void postfix(struct node *root)
{
    postorder(root);
    printf("\n");
}

void postorder(struct node *p)
{
	if (p == NULL)
		return;
    postorder(p->lchild);
    postorder(p->rchild);
    printf("%c",p->info);
}

void parenthesizedInfix(struct node *root)
{
	inorder(root);
    printf("\n");
}

void inorder(struct node *p)
{
	if (p == NULL)
       return;

    if (isOperator(p->info))
		printf("(");

    inorder(p->lchild);
    printf("%c",p->info);
    inorder(p->rchild);

    if (isOperator(p->info))
		printf(")");
}

void display(struct node *p, int level)
{
	int i;
    if (p == NULL)
		return;

    display(p->rchild, level + 1);
    printf("\n");

    for (i = 0; i < level; i++)
		printf("    ");
    printf("%c",p->info);

    display(p->lchild, level + 1);
}

int value(struct node *root)
{
	if( root == NULL )
		return 0;
    return evaluate(root);
}

int evaluate(struct node *p)
{
	int leftValue, rightValue;
	
	if( !isOperator(p->info) ) 
		return p->info - 48;

	leftValue = evaluate(p->lchild);
    rightValue = evaluate(p->rchild);
	
	if(p->info=='+')
         return leftValue + rightValue;
    else if (p->info=='-')
	     return leftValue - rightValue;
    else if (p->info=='*')
         return leftValue * rightValue;
    else
         return leftValue / rightValue;
}

/* Function definitions for implementation of stack */

void initializeStack()
{
	top=-1; 
}

int isEmpty()
{
	if(top==-1)
		return 1;
	else
		return 0;
}

int isFull()
{
	if(top == MAX-1)
		return 1;
	else
		return 0;
}

void push(struct node* x)
{
	if(isFull())
	{
		printf("Stack Overflow\n");
		return;
	}
	top=top+1;
	stack[top]=x;
}

struct node* pop()
{
	struct node* x;
	if(isEmpty())
	{
		printf("Stack Underflow\n");
		exit(1);
	}
	x=stack[top];
	top=top-1;
	return x;
}







