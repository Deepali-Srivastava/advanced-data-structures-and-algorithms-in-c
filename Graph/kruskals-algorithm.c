/*
Copyright (C) Deepali Srivastava - All Rights Reserved
This code is part of DSA course available on CourseGalaxy.com  
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 30
#define NIL -1

struct Vertex
{
	char name[50];
	int father;
};
struct Vertex vertexList[MAX];  

struct Edge
{
	int u;
	int v;
	int weight;
};

struct QueueNode
{
    struct Edge edge;  
    struct QueueNode *link;
};   

struct QueueNode *front = NULL;

int adj[MAX][MAX]; /* Adjacency Matrix */
int n=0; /* Number of vertices in the graph */
int e=0; /* Number of edges in the graph */

void display();
int getIndex(char s[]);
void insertVertex(char s[]);
void deleteVertex(char s[]);
void insertEdge(char s1[], char s2[], int wt);
void deleteEdge(char s1[], char s2[] );

void kruskals();

void insert(struct Edge e);
struct Edge Delete();
int isEmpty();

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

    insertEdge("Zero", "One", 19);
    insertEdge("Zero", "Three", 14);
    insertEdge("Zero", "Four", 12);
    insertEdge("One", "Two", 20);
    insertEdge("One", "Four", 18);
    insertEdge("Two", "Four", 17);
    insertEdge("Two", "Five", 15);
    insertEdge("Two", "Nine", 29);
    insertEdge("Three", "Four", 13);
    insertEdge("Three", "Six", 28);
    insertEdge("Four", "Five", 16);
    insertEdge("Four", "Six", 21);
    insertEdge("Four", "Seven", 22);
    insertEdge("Four", "Eight", 24);
    insertEdge("Five", "Eight", 26);
    insertEdge("Five", "Nine", 27);
    insertEdge("Six", "Seven", 23);
    insertEdge("Seven", "Eight", 30);
    insertEdge("Eight", "Nine", 35);

    kruskals();
}

void kruskals()
{
 	struct QueueNode *front = NULL; 
	struct Edge e;

	int  u, v, v1, v2, r1 ,r2, edgesInTree,wtTree;
	
 	for(u = 0; u < n; u++)
 	    for (v = 0; v < u; v++)
 		   if( adj[u][v] != 0 )
 		   {
				 e.u = u;
				 e.v = v;
				 e.weight = adj[u][v];
			     insert(e);
		   }
 	   
 	for (v = 0; v < n; v++)
 	   vertexList[v].father = NIL;
 	   
	r1 = NIL; /* root of the tree to which vertex v1 belongs */
	r2 = NIL; /* root of the tree to which vertex v2 belongs */
	edgesInTree = 0;  
	wtTree = 0;
	   
 	while( !isEmpty() && edgesInTree < n-1 )
 	{
 	     e = Delete();
		 v1 = e.u;
 	     v2 = e.v;

 	     v = v1;
 	     while(vertexList[v].father!=NIL)
 		    v = vertexList[v].father;
 	     r1 = v;
 		 
		 v = v2;
 		 while(vertexList[v].father!=NIL)
 		     v = vertexList[v].father;
 		 r2 = v;

 	   	 if(r1!=r2)  /*Edge (v1,v2) is included*/
 	   	 {
 	   	    edgesInTree++;
 	   	    printf("(%s, %s) \n",vertexList[v1].name,vertexList[v2].name); 
 	   	    wtTree += e.weight;
 	   	    vertexList[r2].father = r1;
 	   	 }
    }
 	  
 	if(edgesInTree < n-1)
 	      printf("Graph is not connected, no spanning tree possible\n");
 	else
	      printf("Weight of Minimum Spanning Tree is %d\n",wtTree);
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
		for(j=0; j<i; j++)
		   if( adj[i][j] != 0 )
				printf("(%s, %s, %d )  ", vertexList[i].name,vertexList[j].name, adj[i][j]);
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

void insertEdge(char s1[], char s2[], int wt)
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
         adj[u][v] = wt;
		 adj[v][u] = wt;
         e++;
      }
}

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
		 adj[v][u] = 0;
         e--;
    }
}

/* Insert an edge in the linked priority queue */
void insert(struct Edge e)
{
	struct QueueNode *temp,*p;

	temp = (struct QueueNode *)malloc(sizeof(struct QueueNode));
	temp->edge = e;
	
	/*Queue is empty or edge to be added has weight less than first edge*/
	if( front == NULL || temp->edge.weight < front->edge.weight )
	{
		temp->link = front;
		front = temp;
	}
	else
	{
		p = front;
		while( p->link != NULL && p->link->edge.weight <= temp->edge.weight )
			p = p->link;
		temp->link = p->link;
		p->link = temp;
	}
}

/*Delete an edge from the linked priority queue*/
struct Edge Delete()
{
	struct QueueNode *temp;
	struct Edge e;
	if(isEmpty())
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	temp = front;
	front = front->link;
	e = temp->edge;
	free(temp);
	return e;
}

int isEmpty()
{
	if(front==NULL)
		return 1;
	else
		return 0;
}


