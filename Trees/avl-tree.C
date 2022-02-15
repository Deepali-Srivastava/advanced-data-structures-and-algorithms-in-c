/*
Copyright (C) Deepali Srivastava - All Rights Reserved
This code is part of DSA course available on CourseGalaxy.com  
*/

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

struct node
{
	struct  node *lchild;
	int info;
	struct  node *rchild;
	short int balance;
};

void display(struct node *p, int level);
void inorder(struct node *p);

struct node *rotateLeft(struct node *p);
struct node *rotateRight(struct node *p);

struct node *getNode(int x);
struct node *insertNode(struct node *p, int x);
struct node *insertionLeftSubtreeCheck(struct node *p, int *taller);
struct node *insertionRightSubtreeCheck(struct node *p, int *taller);
struct node *insertionLeftBalance(struct node *p);
struct node *insertionRightBalance(struct node *p);

struct node *deleteNode(struct node *p, int x);
struct node *deletionLeftSubtreeCheck(struct node *p, int *shorter);
struct node *deletionRightSubtreeCheck(struct node *p, int *shorter);
struct node *deletionLeftBalance(struct node *p,int *shorter);
struct node *deletionRightBalance(struct node *p,int *shorter);


main()
{
	int choice,key;
	struct node *root = NULL;

	while(1)
	{
		printf("\n");
		printf("1.Display Tree\n");
		printf("2.Insert a new node\n");
		printf("3.Delete a node\n");
		printf("4.Inorder Traversal\n");
		printf("5.Quit\n");
		
		printf("Enter your choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
		 case 1:
			display(root,0);
			break;
		 case 2:
			printf("Enter the key to be inserted : ");
			scanf("%d",&key);
			root = insertNode(root,key);
			break;
		 case 3:
			printf("Enter the key to be deleted : ");
			scanf("%d",&key);
			root = deleteNode(root,key);
			break;
		 case 4:
			inorder(root);
			break;
		 case 5:
			exit(1);
		 default:
			printf("Wrong choice\n");
		}
	}
}

void display(struct node *p, int level)
{
	int i;
	if( p == NULL )
	    return;
	
	display(p->rchild, level+1);
	printf("\n");
	
    for(i=0; i<level; i++)
	    printf("    ");
	printf("%d",p->info);
	display(p->lchild, level+1);
}

void inorder(struct node *p)
{
	if(p == NULL )
		return;
	inorder(p->lchild);
	printf("%d  ",p->info);
	inorder(p->rchild);
}

struct node *rotateLeft(struct node *p)
{
	struct node *a;
	a = p->rchild;		   
	p->rchild = a->lchild;  
	a->lchild = p;           
	return a;   
}

struct node *rotateRight(struct node *p)
{
	struct node *a;
	a = p->lchild;	
	p->lchild = a->rchild; 
	a->rchild = p;			
	return a; 
}

struct node *getNode(int x)
{
	struct node *p = (struct node *) malloc(sizeof(struct node));
	p->info = x;
	p->lchild = NULL;
	p->rchild = NULL;
	p->balance = 0;
	return p;
}

struct node *insertNode(struct node *p, int x)
{
	static int taller;
	if( p == NULL )	
	{
		p = getNode(x);
		taller = TRUE;
	}
	else if(x < p->info)	
	{
		p->lchild = insertNode(p->lchild, x);
		if( taller == TRUE )
			p = insertionLeftSubtreeCheck( p, &taller );
	}
	else if(x > p->info)	
	{
		p->rchild = insertNode(p->rchild, x);  
		if( taller == TRUE )
			p = insertionRightSubtreeCheck( p, &taller );
	}
	else  
	{
		printf("%d already present in tree\n", x);
		taller = FALSE;
	}
	return p;
}

struct node *insertionLeftSubtreeCheck( struct node *p, int *taller )
{
	switch(p->balance)
	{
	 case 0: /* Case L_1 : was balanced */  
		p->balance = 1;	/* now left heavy */
		break;
	 case -1: /* Case L_2: was right heavy */ 
		p->balance = 0;	/* now balanced */
		*taller = FALSE;
		break;
	 case 1: /* Case L_3: was left heavy */   
		p = insertionLeftBalance(p);	/* Left Balancing */
		*taller = FALSE;
	}
	return p;
}

struct node *insertionRightSubtreeCheck(struct node *p, int *taller )
{
	switch(p->balance)
	{
	 case 0: /* Case R_1 : was balanced */	
		p->balance = -1;	/* now right heavy */
		break;
	 case 1: /* Case R_2 : was left heavy */  
		p->balance = 0;	/* now balanced */ 
		*taller = FALSE;
		break;
	 case -1: /* Case R_3: Right heavy */   
		p = insertionRightBalance(p);	/* Right Balancing */
		*taller = FALSE;
	}
	return p;
}

struct node *insertionLeftBalance(struct node *p)
{
	struct node *a, *b;

	a = p->lchild;
	if(a->balance == 1)  /* Case L_3A : Insertion in AL */ 
	{
		p->balance = 0;
		a->balance = 0;
		p = rotateRight(p);
	}
	else		/* Case L_3B : Insertion in AR */
	{
		b = a->rchild;
		switch(b->balance)
		{
		case 1:					/* Case L_3B1 : Insertion in BL */
			p->balance = -1;
			a->balance = 0;
			break;
		case -1:				/* Case L_3B2 : Insertion in BR */   
			p->balance = 0;
			a->balance = 1;
			break;
		case 0:					/* Case L_3B3 : B is the newly inserted node */ 
			p->balance = 0;
			a->balance = 0;
		}
		b->balance = 0;
		p->lchild = rotateLeft(a);
		p = rotateRight(p);
	}
	return p;
}

struct node *insertionRightBalance(struct node *p)
{
	struct node *a, *b;

	a = p->rchild;
	if(a->balance == -1) /* Case R_3A : Insertion in AR */ 
	{
		p->balance = 0;
		a->balance = 0;
		p = rotateLeft(p);
	}
	else		/* Case R_3B : Insertion in AL */
	{
		b = a->lchild;
		switch(b->balance)
		{
		case -1:	/* Case R_3B1 : Insertion in BR */
			p->balance = 1;  
			a->balance = 0;
			break;
		case 1:		/* Case R_3B2 : Insertion in BL */
			p->balance = 0;
			a->balance = -1;
			break;
		case 0:		/* Case R_3B3 : B is the newly inserted node */
			p->balance = 0;
			a->balance = 0;
		}
		b->balance = 0;
		p->rchild = rotateRight(a);
		p = rotateLeft(p);
	}
	return p;
}

struct node *deleteNode(struct node *p, int x)
{
	struct node *ch, *s;
	static int shorter;

	if( p == NULL)
	{
		printf("%d not found\n",x);
		shorter = FALSE;
		return p;
	}
	if( x < p->info ) /* delete from left subtree */
	{
		p->lchild = deleteNode(p->lchild, x);
		if(shorter == TRUE)
			p = deletionLeftSubtreeCheck(p, &shorter);
	}
	else if( x > p->info ) /* delete from right subtree */
	{
		p->rchild = deleteNode(p->rchild, x);
		if(shorter==TRUE)
			p = deletionRightSubtreeCheck(p, &shorter);
	}
	else 
	{
		/* key to be deleted is found */ 
		if( p->lchild!=NULL  &&  p->rchild!=NULL )   /*2 children*/
		{
			s = p->rchild;
			while(s->lchild)
				s = s->lchild;
			p->info = s->info;
			p->rchild = deleteNode(p->rchild, s->info);
			if( shorter == TRUE )
				p = deletionRightSubtreeCheck(p, &shorter);
		}
		else	/* 1 child or no child */
		{
			if( p->lchild != NULL ) /* only left child */
				ch = p->lchild;
			else /* only right child or no child */
				ch = p->rchild;
			free(p);
			p = ch;
			shorter = TRUE;
		}						
	}
	return p; 
}

struct node *deletionLeftSubtreeCheck(struct node *p, int *shorter)
{
	switch(p->balance)
	{
		case 0: /* Case L_1 : was balanced */       
			p->balance = -1;	/* now right heavy */ 
			*shorter = FALSE;
			break;
		case 1: /* Case L_2 : was left heavy */	 
			p->balance = 0;	/* now balanced */
			break;            
		case -1: /* Case L_3 : was right heavy */   
			p = deletionRightBalance(p, shorter); /* Right Balancing */
	}
	return p;
}

struct node *deletionRightSubtreeCheck(struct node *p, int *shorter)
{
	switch(p->balance)
	{
		case 0:		/* Case R_1 : was balanced */		
			p->balance = 1;	/* now left heavy */
			*shorter = FALSE;
			break;
		case -1: /* Case R_2 : was right heavy */	
			p->balance = 0;	/* now balanced */
			break;
		case 1: /* Case R_3 : was left heavy */	
			p = deletionLeftBalance(p, shorter );  /*Left Balancing*/
	}
	return p;
}

struct node *deletionLeftBalance(struct node *p,int *shorter)
{
	struct node *a, *b;
	a = p->lchild;
	if( a->balance == 0)  /* Case R_3A */
	{
		p->balance = 1;
		a->balance = -1;
		*shorter = FALSE;
		p = rotateRight(p);
	}
	else if(a->balance == 1 ) /* Case R_3B */
	{
		p->balance = 0;
		a->balance = 0;
		p = rotateRight(p);
	}
	else						/* Case R_3C */
	{
		b = a->rchild;
		switch(b->balance)
		{
			case 0:					/* Case R_3C1 */
				p->balance = 0;
				a->balance = 0;
				break;
			case -1:				/* Case R_3C2 */
				p->balance = 0;	
				a->balance = 1;
			case 1:					/* Case R_3C3 */
				p->balance = -1;		
				a->balance = 0;
				break;
			
		}
		b->balance = 0;			
		p->lchild = rotateLeft(a);
		p = rotateRight(p);
	}
	return p;
}

struct node *deletionRightBalance(struct node *p,int *shorter)
{
	struct node *a, *b;

	a = p->rchild;
	if (a->balance == 0)	/* Case L_3A */ 
	{
		p->balance = -1;
		a->balance = 1;
		*shorter = FALSE;
		p = rotateLeft(p);			
	}
	else if(a->balance == -1 )	/* Case L_3B */ 
	{
		p->balance = 0;
		a->balance = 0;
		p = rotateLeft(p);			
	}
	else							/* Case L_3C */
	{
		b = a->lchild;
		switch(b->balance)
		{
			case 0:					/* Case L_3C1 */
				p->balance = 0;
				a->balance = 0;
				break;
			case 1:					/* Case L_3C2 */ 
				p->balance = 0;
				a->balance = -1;
				break;
			case -1:				/* Case L_3C3 */
				p->balance = 1;
				a->balance = 0;
		}
		b->balance = 0;
		p->rchild = rotateRight(a);
		p = rotateLeft(p);
	}
	return p;
}

