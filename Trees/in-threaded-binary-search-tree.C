/*
Copyright (C) Deepali Srivastava - All Rights Reserved
This code is part of DSA course available on CourseGalaxy.com  
*/


/* Fully in-threaded Binary Search Tree */

#include <stdio.h>
#include <stdlib.h>

typedef enum {False,True} boolean;

struct node
{
	struct node *left;
	boolean leftThread;
	int info;
	boolean rightThread;
	struct node *right;
};

struct node *inorderPredecessor(struct node *p);
struct node *inorderSuccessor(struct node *p);
struct node *getNode(int x);
struct node *insertNode(struct node *root, int x);
struct node *deleteNode(struct node *root, int x);
void inorder(struct node *root);


main( )
{
	int choice,x;
	struct node *root=NULL;
	
	while(1)
	{
		printf("1.Insert a new node\n");
		printf("2.Delete a node\n");
		printf("3.Inorder Traversal\n");
		printf("4.Exit\n");
		
		printf("Enter your choice : ");
		scanf("%d",&choice);

		switch(choice)
		{
		 case 1:
			printf("Enter the key to be inserted : ");
			scanf("%d",&x);
			root = insertNode(root,x);
			break;
		 case 2:
			printf("Enter the key to be deleted : ");
			scanf("%d",&x);
			root = deleteNode(root,x);
			break;
		 case 3:
			inorder(root);
			break;
		 case 4:
			exit(1);
		 default:
			printf("Wrong choice\n");
		}
	}
}

struct node *inorderPredecessor(struct node *p)
{
	if( p->leftThread == True )
		return p->left;
	
	p = p->left;
	while( p->rightThread == False )
		p = p->right;
	return p;
}

struct node *inorderSuccessor(struct node *p)
{
	if( p->rightThread == True )
		return p->right; 

	p = p->right;
	while( p->leftThread == False )
		p = p->left;
	return p;
}

void inorder( struct node *root)
{
	struct node *p;
	if(root == NULL )
	{
		printf("Tree is empty\n");
		return;
	}

	/* Find the leftmost node of the tree */
	p = root;
	while( p->leftThread == False )
		p = p->left;
	
	while( p!=NULL )
	{
		printf("%d ",p->info);	
		if( p->rightThread == True)
            p = p->right;
        else
        {
             p = p->right;
             while( p->leftThread == False )
                p = p->left;
        }
	} 
	printf("\n\n");
}

struct node *getNode(int x)
{
	struct node *p = (struct node *) malloc(sizeof(struct node));
	p->info = x;
	p->left = NULL;
	p->right = NULL;
	p->leftThread = True;
	p->rightThread = True;
	return p;
}

struct node *insertNode(struct node *root, int x)
{       
	struct node *temp,*par,*p;

	p = root;
	par = NULL;

	while( p!=NULL )
	{
		par = p;
		if(x < p->info)
		{
			if(p->leftThread == False)
				p = p->left;	
			else 
				break;
		}
		else if (x > p->info)
		{
			if(p->rightThread == False)
				p = p->right;
			else 
				break;
		}
		else
        {
             printf("%d already present in the tree\n",x);
             return;
        }
	}
	 
	temp = getNode(x);
	
	if( par == NULL )
		root = temp;
	else if( x < par->info ) /* inserted as left child */
	{
		temp->left = par->left;
		temp->right = par;
		par->leftThread = False;
		par->left = temp;
	}
	else /* inserted as right child */
	{
		temp->left = par;
		temp->right = par->right;
		par->rightThread = False;
		par->right = temp;
	}	
	return root;
}

struct node *deleteNode(struct node *root, int x)
{
	struct node *par,*p, *ps, *s, *ch, *pred, *succ;
	
	p = root;
	par = NULL;
	
	while( p!=NULL)
	{
		if(x == p->info)
			break;
		
		par = p;
		if(x < p->info)
		{
			if(p->leftThread == False)
				p = p->left;	
			else 
				break;
		}
		else 
		{
			if(p->rightThread == False)
				p = p->right;
			else 
				break;
		}
	}

	if(p == NULL || p->info != x)
	{
		printf("%d not found\n",x);
		return root;
	}
	
	if(p->leftThread==False && p->rightThread==False )/*Case C : 2 children*/
	{
		/*Find inorder successor and its parent*/
	    ps = p;
	    s = p->right;
	    
		while(s->leftThread == False)
	    {
		   ps = s;
		   s = s->left;
	    }
	   	p->info = s->info;
		p = s;
		par = ps;
   	}

	/*Case A : No child*/
    if(p->leftThread == True && p->rightThread == True)
    {
         if(par == NULL)
             root = NULL;
         else if(p == par->left)
         {
             par->leftThread = True;
             par->left = p->left;
         }
         else
         {
              par->rightThread = True;
              par->right = p->right;
         }
		 free(p);
         return root;
     }
	 /*Case B : 1 child*/
     if(p->leftThread == False) /*node to be deleted has left child */
         ch = p->left;
     else                /*node to be deleted has right child */
         ch = p->right;

     if (par == NULL)   /*node to be deleted is root node*/
         root = ch;
     else if (p == par->left)  /* node is left child of its parent */
         par->left = ch;
     else        /*node is right child of its parent*/
         par->right = ch;

     pred = inorderPredecessor(p);
     succ = inorderSuccessor(p);

     if(p->leftThread == False) /*if p has left child, right is a thread */
          pred->right = succ;
     else  /*p has right child,left is a thread*/
          succ->left = pred;
	 
	 free(p);
	 return root;
}

