/*
Copyright (C) Deepali Srivastava - All Rights Reserved
This code is part of DSA course available on CourseGalaxy.com  
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 30
#define TEMPORARY 1
#define PERMANENT 2
#define NIL -1
#define INFINITY 99999

struct Vertex
{
	char name[50];
	int status;
    int predecessor;
    int length;
};
struct Vertex vertexList[MAX];  

int adj[MAX][MAX]; /* Adjacency Matrix */
int n=0; /* Number of vertices in the graph */
int e=0; /* Number of edges in the graph */

void display();
int getIndex(char s[]);
void insertVertex(char s[]);
void deleteVertex(char s[]);
void insertEdge(char s1[], char s2[], int wt);
void deleteEdge(char s1[], char s2[]);

void prims();
int tempVertexMinL();

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

    prims();
}

void prims()
{	
	  int c,v;
	    
	  int edgesInTree = 0;
	  int wtTree = 0;
	  int root;
   			    
   	  for(v=0; v<n; v++)
   	  {
   	     vertexList[v].status = TEMPORARY;
   		 vertexList[v].length = INFINITY;
   		 vertexList[v].predecessor = NIL;
   	  }

   	  root = 0;
   	  vertexList[root].length = 0;
   		
      while(1)
      {
         c = tempVertexMinL();
   	     if(c == NIL) 
   		 {
   		    if(edgesInTree == n-1) 
   		        printf("Weight of minimum spanning tree is %d\n", wtTree);
   			else 		
   			    printf("Graph is not connected, Spanning tree not possible");
			return;
   	      }
   		  vertexList[c].status = PERMANENT;
   			
          /* Include edge ( vertexList[c].predecessor,c ) in the tree*/ 
   		  if(c != root)
   		  {
   			   edgesInTree++;
   			   printf("(%s, %s)\n", vertexList[vertexList[c].predecessor].name,vertexList[c].name);
   			   wtTree = wtTree + adj[vertexList[c].predecessor][c];
   		  }
   		     
   		  for(v = 0; v < n; v++)
   		     if(adj[c][v]!=0 && vertexList[v].status == TEMPORARY)
   				 if (adj[c][v] < vertexList[v].length)
   				 {
   				    vertexList[v].length = adj[c][v];
   				    vertexList[v].predecessor = c;
   				 }
     }
}

int tempVertexMinL()
{
     int min = INFINITY;
     int v, x = NIL;
 	
     for (v = 0; v < n; v++)
     {
         if(vertexList[v].status == TEMPORARY && vertexList[v].length < min)
         {
 	        min = vertexList[v].length;
 	        x = v;
         }
     }
     return x;
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
		 adj[v][u] = 0;
         e--;
    }
}


   


