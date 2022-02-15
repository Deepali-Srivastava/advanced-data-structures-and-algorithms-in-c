/*
Copyright (C) Deepali Srivastava - All Rights Reserved
This code is part of DSA course available on CourseGalaxy.com  
*/

#include<stdio.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1

#define M 5	/*order of B tree*/
#define MAX (M-1)	/*Maximum number of keys allowed in a node*/

#if M%2==0
#define CEIL_MDIV2 (M/2)
#else
#define CEIL_MDIV2 ((M+1)/2)
#endif

#define MIN (CEIL_MDIV2-1)	/*Minimum number of keys allowed in a node except root*/

struct node
{
	int numKeys;
	int key[M];
	struct node *child[M];
};

void inorder(struct node *p);
void display(struct node *p,int blanks);

struct node *search(int x,struct node *p);
int searchNode(int x,struct node *p,int *n);

struct node *insert(int x,struct node *root);
int recInsert(int x, struct node *p, int *iKey, struct node **iKeyRchild);

void insertByShift( struct node *p, int n, int iKey, struct node *iKeyRchild );
void split(struct node *p, int n, int *iKey, struct node **iKeyRchild);

struct node *Delete(int x,struct node *root);
void recDelete(int x,struct node *p);
void deleteByShift(struct node *p,int n);
void restore(struct node *p,int n);
void borrowLeft(struct node *p,int n);
void borrowRight(struct node *p,int n);
void combine(struct node *p,int m);

int main()
{
	struct node *root = NULL, *ptr;
	int x,choice,n;
	while(1)
	{
		printf("1.Search\n");
		printf("2.Insert\n");
		printf("3.Delete\n");
		printf("4.Display tree\n");
		printf("5.Inorder traversal\n");
		printf("6.Quit\n");
		printf("Enter your choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				printf("Enter the key to be searched : ");
				scanf("%d",&x);
				if( (ptr=search(x, root)) == NULL )
					printf("Key not present in the tree\n");
				else
					printf("Key present in node %p \n",ptr);
				break;
			case 2:
				printf("Enter the key to be inserted : ");
				scanf("%d",&x);
				root = insert(x, root);
				break;
			case 3:
				printf("Enter the key to be deleted : ");
				scanf("%d",&x);
				root = Delete(x, root);
				break;
			case 4:
				printf("\n\n");
				display( root, 0 );
				printf("\n\n");
				break;
			case 5:
				inorder(root);
				printf("\n\n");
				break;
			case 6:
				exit(1);
			default:
				printf("Wrong choice\n");
				break;
		}
	}
}

void inorder(struct node *p)
{
	int i;
	if( p == NULL )
		return;

	for(i=0; i<p->numKeys; i++)
	{
		inorder(p->child[i]);
		printf("%d\t",p->key[i+1] );
	}
	inorder(p->child[i]);
}

void display(struct node *p, int blanks)
{
	int i;
	if( p == NULL )
		return;

	for(i=1; i<=blanks; i++)
		printf(" ");

	for(i=1; i<=p->numKeys; i++)
		printf("%d ",p->key[i]);

	printf("\n");
	
	for(i=0; i<=p->numKeys; i++)
		display(p->child[i], blanks+10);
}

struct node *search(int x, struct node *p)
{
	int n;
	
	if( p == NULL )  /* Key x not present in the tree */
		return NULL;
	n=0;
	if( searchNode(x, p, &n ) ) /* Key x found in node p  */ 
		return p;
	        
	return search( x, p->child[n]); /* Search in node p->child[n] */
}

int searchNode(int x, struct node *p, int *n)
{
	if( x < p->key[1] )
	{
		*n = 0;
		return FALSE;
	}

	*n = p->numKeys;
	while( ( x < p->key[*n] ) && *n>1 )
		(*n)--;

	if( x == p->key[*n] )
		return TRUE;
	else
		return FALSE;
}

struct node *insert(int x, struct node *root)
{
	int iKey=0, taller;
	struct node *iKeyRchild=NULL, *temp;
	
	taller = recInsert(x, root, &iKey, &iKeyRchild);
	
	if( taller )  /* Height increased by one, new root node has to be created */
	{
		temp = (struct node *)malloc( sizeof(struct node) );
		temp->numKeys = 1;
		temp->child[0] = root;	
		temp->key[1] = iKey;
		temp->child[1] = iKeyRchild;
		root = temp;
	}
	return root;
}

int recInsert(int x, struct node *p, int *iKey, struct node **iKeyRchild)
{
	int n,flag;

	if( p == NULL )  /* First Base case : key not found */
	{
		*iKey = x;
		*iKeyRchild = NULL;
		return TRUE;   
	}
	
	n = 0;
	if( searchNode( x, p, &n) ) /* Second Base Case : key found */
	{
		printf("Duplicate keys are not allowed\n");
		return FALSE;  /* No need to insert the key */
	}

	flag = recInsert( x, p->child[n], iKey, iKeyRchild );

	if( flag )
	{
		if( p->numKeys < MAX )
		{
			insertByShift(p, n, *iKey, *iKeyRchild);
			return FALSE; /* Insertion over */
		}
		else
		{
			split(p, n, iKey, iKeyRchild );
			return TRUE;  /* Insertion not over : Median key yet to be inserted */
		}
	}
	return FALSE;
}

void insertByShift( struct node *p, int n, int iKey, struct node *iKeyRchild )
{
	int i;
	
	for( i = p->numKeys; i > n; i-- )
	{
		p->key[i+1] = p->key[i];
		p->child[i+1] = p->child[i];
	}
	p->key[n+1] = iKey;
	p->child[n+1] = iKeyRchild;
	p->numKeys++;
}

void split(struct node *p, int n, int *iKey, struct node **iKeyRchild)
{
	int i,j,medianKey, lastKey, d;
	struct node *lastChild, *newNode;
	
	if( n == MAX )
	{
		lastKey = *iKey;
		lastChild = *iKeyRchild;
	}
	else
	{
		lastKey = p->key[MAX];
		lastChild = p->child[MAX];
		for( i = p->numKeys-1; i > n; i-- )
		{
			p->key[i+1] = p->key[i];
			p->child[i+1] = p->child[i];
		}
		p->key[i+1] = *iKey;
		p->child[i+1] = *iKeyRchild;
	}
	
	
	d = CEIL_MDIV2;
	medianKey = p->key[d];

	newNode = (struct node *)malloc(sizeof(struct node) );
	newNode->numKeys = M - d; 

	newNode->child[0] = p->child[d];
	for( i=1, j=d+1; j<=MAX; i++,j++ )
	{
		newNode->key[i] = p->key[j];
		newNode->child[i] = p->child[j];
	}
	
	newNode->key[i] = lastKey;
    newNode->child[i] = lastChild;

	p->numKeys = d-1;
	 
	*iKey = medianKey;
	*iKeyRchild = newNode;
}

struct node *Delete(int x, struct node *root)
{
	struct node *temp;

	if ( root == NULL )
    {
		printf("Tree is empty");
        return;
    }

	recDelete(x, root);
	
	if( root!=NULL && root->numKeys == 0 )/*Height of tree decreased by 1*/
	{
		temp = root;
		root = root->child[0];
		free(temp);
	}
	return root;
}

void recDelete(int x, struct node *p)
{
	int n=0;
	struct node *s;

	if( searchNode(x, p, &n) )  /* Key x found in node p */
	{
		if( p->child[n]==NULL )/*node p is a leaf node */
		{
			deleteByShift( p, n);
		    return;
		}
		else /*node p is a non leaf node */
		{	
			s = p->child[n]; /*point to the right subtree*/
			while( s->child[0]!=NULL )   /*move down till leaf node arrives*/
				s = s->child[0];
			p->key[n] = s->key[1];
			recDelete(s->key[1], p->child[n]);
		}
	}
	else	/*key x not found in node p */
	{
		if( p->child[n] == NULL )/*if p is a leaf node*/ 
		{
             printf("Value %d not present in the tree\n", x);
             return;
        }	
		 /*p is a non-leaf node*/
		recDelete(x, p->child[n]); 
	}
	if( p->child[n]->numKeys < MIN ) /*check underflow in p->child[n]*/
		restore( p, n);
}


void deleteByShift( struct node *p, int n)
{
	int i;
	for( i = n+1; i <= p->numKeys; i++ )
	{
		p->key[i-1] = p->key[i];
		p->child[i-1] = p->child[i];
	}
	p->numKeys--;
}


 /* Called when p->child[n] becomes underflow */
void restore(struct node *p, int n)
{
	if( n!=0  &&  p->child[n-1]->numKeys > MIN )      
		borrowLeft(p, n);
	else if( n!=p->numKeys && p->child[n+1]->numKeys > MIN )
		borrowRight(p, n);   
	else
	{	
		if(n!=0)  /*if there is a left sibling*/
			combine(p, n);	 /*combine with left sibling*/
		else 
			combine(p, n+1);  /*combine with right sibling*/
	}
}

void borrowLeft(struct node *p, int n)
{	
	int i;
	struct node *underflowNode = p->child[n];		
	struct node *leftSibling = p->child[n-1];	/* left sibling of underflowNode */

	underflowNode->numKeys++;

	/*Shift all the keys and children in underflowNode one position right*/
	for(i = underflowNode->numKeys; i>0; i--)
	{
		underflowNode->key[i+1] = underflowNode->key[i];
		underflowNode->child[i+1] = underflowNode->child[i];
	}
	underflowNode->child[1] = underflowNode->child[0];

	/* Move the separator key from parent node p to underflowNode */
	underflowNode->key[1] = p->key[n];
	
	/* Move the rightmost key of leftSibling to the parent node p */
	p->key[n] = leftSibling->key[leftSibling->numKeys];

	/*Rightmost child of leftSibling becomes leftmost child of underflowNode */
	underflowNode->child[0] = leftSibling->child[leftSibling->numKeys];
	
	leftSibling->numKeys--;
}

void borrowRight(struct node *p,int n)
{
	int i;
	struct node *underflowNode = p->child[n];		
	struct node *rightSibling = p->child[n+1];	/* right sibling of underflowNode */

	/* Move the separator key from parent node p to underflowNode */
	underflowNode->numKeys++;
	underflowNode->key[underflowNode->numKeys] = p->key[n+1];
	
	/* Leftmost child of node rightSibling becomes the rightmost child of underflowNode*/
	underflowNode->child[underflowNode->numKeys] = rightSibling->child[0];

	/*Move the leftmost key from node rightSibling to parent node p */
	p->key[n+1] = rightSibling->key[1];
	rightSibling->numKeys--;
	
	/*Shift all the keys and children of node rightSibling one position left*/
	rightSibling->child[0] = rightSibling->child[1];
	for(i=1; i<=rightSibling->numKeys; i++)
	{
		rightSibling->key[i] = rightSibling->key[i+1];
		rightSibling->child[i] = rightSibling->child[i+1];
	}
}

void combine(struct node *p, int m)
{
	int i;    
	struct node *nodeA = p->child[m-1];        
	struct node *nodeB = p->child[m];	
	
	nodeA->numKeys++;

	/* Move the key from the parent node p to nodeA */
	nodeA->key[nodeA->numKeys] = p->key[m];
	
	/* Shift the keys and children that are after separator key in node p one position left */
	for(i=m; i<p->numKeys; i++)   
	{
		p->key[i] = p->key[i+1];
		p->child[i] = p->child[i+1];
	}
	p->numKeys--;

	/*Leftmost child of nodeB becomes rightmost child of nodeA */
	nodeA->child[nodeA->numKeys] = nodeB->child[0];

	/*Insert all the keys and children of nodeB at the end of nodeA */
	for( i = 1; i<=nodeB->numKeys; i++)
	{
		nodeA->numKeys++;
		nodeA->key[nodeA->numKeys] = nodeB->key[i];
		nodeA->child[nodeA->numKeys] = nodeB->child[i];
	}
	free(nodeB);
}
