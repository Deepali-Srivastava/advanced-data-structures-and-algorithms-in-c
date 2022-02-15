/*
Copyright (C) Deepali Srivastava - All Rights Reserved
This code is part of DSA course available on CourseGalaxy.com  
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INITIAL 0
#define VISITED 1

#define MAX 30

struct Vertex
{
	char name[50];
	int state;
	int predecessor;
};

struct Vertex vertexList[MAX];

int adj[MAX][MAX]; /* Adjacency Matrix */
int n=0;	/* Number of vertices in the graph */
int e=0; /* Number of edges in the graph */

void display();
int getIndex(char s[]);
int isAdjacent(char s1[], char s2[]);
void insertVertex(char s[]);
void deleteVertex(char s[]);
void insertEdge(char s1[], char s2[]);
void deleteEdge(char s1[], char s2[] );

void dfsTreeEdges();
void dfs(int v);

int stack[MAX];
int top;

void initializeStack();
int isEmpty();
int isFull();
void push(int x);
int pop();


main()
{
	insertVertex("Zero");
    insertVertex("One");
    insertVertex("Two");
    insertVertex("Three");
    insertVertex("Four");
    insertVertex("Five");
    insertVertex("Six");
    insertVertex("Seven");
    insertVertex("Eight");
    insertVertex("Nine");
    insertVertex("Ten");
    insertVertex("Eleven");

    insertEdge("Zero", "One");
    insertEdge("Zero", "Three");
    insertEdge("One", "Two");
    insertEdge("One", "Four");
    insertEdge("One", "Five");
    insertEdge("Two", "Five");
    insertEdge("Two", "Seven");
    insertEdge("Three", "Six");
    insertEdge("Four", "Three");
    insertEdge("Five", "Three");
    insertEdge("Five", "Six");
    insertEdge("Five", "Eight");
    insertEdge("Seven", "Eight");
    insertEdge("Seven", "Ten");
    insertEdge("Eight", "Eleven");
    insertEdge("Nine", "Six");
    insertEdge("Eleven", "Nine");

	dfsTreeEdges();
 
}

void dfsTreeEdges()
{
	int v,u;
	char s[50];

	printf("Enter starting vertex for Depth First Search : ");
   	scanf("%s", &s);
	u = getIndex(s);
  	if(u == -1)
		return;
	
	for(v=0; v<n; v++) 
   	{
		vertexList[v].state = INITIAL;
		vertexList[v].predecessor = -1;
	}
   	     
	dfs(u);

	for(v=0; v<n; v++)
	    if( vertexList[v].state == INITIAL )
		     dfs(v);
	
	printf("Tree Edges : \n");
	for( v = 0; v < n; v++ )
	{
	    u = vertexList[v].predecessor;
	    if ( u != -1 )
	       printf("(%s, %s)\n",vertexList[u].name,vertexList[v].name );
	}
}

void dfs(int v)
{	   
    int i;
	initializeStack();
	push(v);

	while ( !isEmpty() )
	{
	     v = pop();
		 if( vertexList[v].state == INITIAL )
		 {
		      printf("%s ", vertexList[v].name);
		      vertexList[v].state=VISITED;
		 }

		 for ( i = n-1; i >= 0; i--)
		      if ( adj[v][i]!=0 && vertexList[i].state == INITIAL )
		      {
				  push(i);
			      vertexList[i].predecessor = v;
			  }
		 
	}
   	printf("\n");
}


void display()
{
	int i,j;
	
	printf("Adjacency Matrix - \n");
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
			printf("%4d",adj[i][j]);
		printf("\n");
	}

	printf("\nVertices - ");
	for(i=0; i<n; i++)
		printf("%s  ", vertexList[i].name);

	printf("\nEdges - ");
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
		   if( adj[i][j] != 0 )
				printf("(%s, %s)  ", vertexList[i].name,vertexList[j].name);
	printf("\n\n");
}

int getIndex(char s[])
{
	int i;
    for (i = 0; i<n; i++)
       if ( strcmp(s,vertexList[i].name) == 0 )
 	       return i;
    printf("Invalid Vertex - %s \n\n", s);
	return -1;
}

void insertVertex(char s[])
{  
	int i;

    for(i = 0; i<n; i++ )
		if( strcmp(vertexList[i].name, s) == 0) 
		{
			printf("Vertex already present\n\n");
			return;
		}
	
	strcpy(vertexList[n].name, s);
	n++;
}

void deleteVertex(char s[])
{ 
	int i, x = getIndex(s), u;
	
	if(x == -1)
		return;

	u = x;
	while (u < n-1) 
	{ 
        for (i = 0; i < n; i++) /* shift rows to the left */
		    adj[i][u] = adj[i][u+1]; 
		
		for (i = 0; i < n; i++)  /* shift columns up */
			adj[u][i] = adj[u+1][i]; 
	    u++; 
	}
	
	for(i = x; i < n-1; i++)
		vertexList[i] = vertexList[i+1]; 
	n--;
}

int isAdjacent(char s1[], char s2[])
{
	int u,v;
	u = getIndex(s1);
	v = getIndex(s2);
	
	if (u == -1 || v == -1)
		return -1; 
	
	return adj[u][v];
}

/* Insert an edge (s1,s2) */
void insertEdge(char s1[], char s2[])
{
	  int u = getIndex(s1);
	  int v = getIndex(s2);
	  
	  if (u == v)
	  {    
		 printf("Not a valid edge\n\n");
		 return;
	  }
      
      if (adj[u][v] != 0 )
        printf("Edge already present\n\n");
      else  
      {
         adj[u][v] = 1;
         e++;
      }
}

/* Delete the edge (s1,s2) */
void deleteEdge(char s1[], char s2[])
{
    int u = getIndex(s1);
    int v = getIndex(s2);

	if(u==-1 || v ==-1)
		return;
   	  
    if( adj[u][v] == 0 )
        printf("Edge not present\n\n");
    else
    {
         adj[u][v] = 0;
         e--;
    }
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
	if(top==MAX-1)
		return 1;
	else
		return 0;
}

void push(int x)
{
	if(isFull())
	{
		printf("Stack Overflow\n");
		return;
	}
	top=top+1;
	stack[top]=x;
}

int pop()
{
	int x;
	if(isEmpty())
	{
		printf("Stack Underflow\n");
		exit(1);
	}
	x=stack[top];
	top=top-1;
	return x;
}
