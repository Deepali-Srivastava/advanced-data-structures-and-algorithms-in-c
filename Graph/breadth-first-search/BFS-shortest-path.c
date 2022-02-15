/*
Copyright (C) Deepali Srivastava - All Rights Reserved
This code is part of DSA course available on CourseGalaxy.com  
*/

/* Shortest distance and shortest path of a vertex from start vertex using BFS*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define INITIAL 0
#define WAITING 1
#define VISITED 2

#define INFINITY 99999

#define MAX 30

struct Vertex
{
	char name[50];
	int state;
	int distance;
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

void findShortestPath(char s[]);
void bfs(int v);

int queue[MAX];
int front,rear;
void initializeQueue();
int isFull();
int isEmpty();
void enqueue(int x);
int dequeue();

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

    insertEdge("Zero", "One");
    insertEdge("Zero", "Three");
    insertEdge("One", "Two");
    insertEdge("One", "Four");
    insertEdge("One", "Five");
    insertEdge("Two", "Three");
    insertEdge("Two", "Five");
    insertEdge("Three", "Six");
    insertEdge("Four", "Five");
    insertEdge("Four", "Seven");
    insertEdge("Five", "Six");
    insertEdge("Five", "Eight");
    insertEdge("Six", "Eight");
    insertEdge("Six", "Nine");
    insertEdge("Seven", "Eight");
    insertEdge("Eight", "Nine");

    findShortestPath("Two");
}

void findShortestPath(char s[])
{
   int i,u,v,x,y,count,path[MAX];
   
   u = getIndex(s);
   if(u == -1)
		return;

   for(v = 0; v < n; v++) 
   {	
	  vertexList[v].state = INITIAL;
	  vertexList[v].predecessor = -1;
	  vertexList[v].distance = INFINITY;
   }
		   
   bfs(u);
		   
   for(v = 0; v < n; v++)
   {
	   if(vertexList[v].distance == INFINITY )
		  printf("No path from vertex %s to vertex %s\n",s,vertexList[v].name);
	   else	
	   {
		  printf("Shortest distance from vertex %s to vertex %s is %d\n", s,vertexList[v].name,vertexList[v].distance); 
		    			                                             
		  /*Store the full path in array path*/
		  count = 0;
		  y=v;
		  while ( y != -1 )
		  {
		     count++;
		     path[count] = y;
		     x = vertexList[y].predecessor;
		     y = x;	
		  }
		  printf("Shortest Path is : ");
		  for(i = count; i > 1; i-- )	
		   	   printf("%s ->", vertexList[path[i]].name);
		  printf(vertexList[path[i]].name );
		  printf("\n");
		}
	}
}

void bfs(int v)
{	   
    int i;
    initializeQueue();
	enqueue(v);
    vertexList[v].state = WAITING;
	vertexList[v].distance = 0;
	vertexList[v].predecessor = -1;
	   	   
    while( !isEmpty() )
    {
	    v = dequeue();
	  	vertexList[v].state = VISITED;
	   		
	   	for (i = 0; i<n; i++)
	   	    if( adj[v][i] !=0 && vertexList[i].state == INITIAL) 
	   	    {
	   		    enqueue(i);
	   		    vertexList[i].state = WAITING;
				vertexList[i].predecessor = v;
	   			vertexList[i].distance = vertexList[v].distance + 1;
	   	    }
	 }
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

/* Function definitions for implementation of queue */

void initializeQueue()
{
	rear=-1;
	front=-1;
}

int isEmpty()
{
	if(front==-1 || front==rear+1)
		return 1;
	else
		return 0;
}

int isFull()
{
	if(rear==MAX-1)
		return 1;
	else
		return 0;
}

void enqueue(int x)
{
	if(isFull())
	{
		printf("Queue Overflow\n");
		return;
	}
	if(front==-1)  
		front=0;
	rear=rear+1;
	queue[rear]=x;
}

int dequeue()
{
	int x;
	if(isEmpty())
	{
		printf("Queue Underflow\n");
		exit(1);
	}
	x=queue[front];
	front=front+1;
	return x;
}

