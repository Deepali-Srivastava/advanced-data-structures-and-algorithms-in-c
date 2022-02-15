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
    int pathLength;
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
void deleteEdge(char s1[], char s2[] );

void findPaths(char s[]);
void findPath(int s, int v);
void dijkstra(int s);
int tempVertexMinPL();

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

    insertEdge("Zero", "Three", 2);
    insertEdge("Zero", "One", 5);
    insertEdge("Zero", "Four", 8);
    insertEdge("One", "Four", 2);
    insertEdge("Two", "One", 3);
    insertEdge("Two", "Five", 4);
    insertEdge("Three", "Four", 7);
    insertEdge("Three", "Six", 8);
    insertEdge("Four", "Five", 9);
    insertEdge("Four", "Seven", 4);
    insertEdge("Five", "One", 6);
    insertEdge("Six", "Seven", 9);
    insertEdge("Seven", "Three", 5);
    insertEdge("Seven", "Five", 3);
    insertEdge("Seven", "Eight", 5);
    insertEdge("Eight", "Five", 3);

    findPaths("Zero");
}

void findPaths(char source[])
{
     int s,v;
	 s = getIndex(source);
     
	 if(s == -1)
		 return;

	 dijkstra(s);
	   
	 printf("Source Vertex : %s\n\n",source);
	        
     for(v = 0; v < n; v++)
	 {
		 printf("Destination Vertex : %s \n", vertexList[v].name);
		 if ( vertexList[v].pathLength == INFINITY )
	        printf("There is no path from %s to %s\n\n", source, vertexList[v].name );
		 else
		    findPath(s,v);
	 }
}

void dijkstra(int s)
{
     int v, c;

     for(v = 0; v < n; v++)
     {
        vertexList[v].status = TEMPORARY;
        vertexList[v].pathLength = INFINITY;
        vertexList[v].predecessor = NIL;
     }

     vertexList[s].pathLength = 0;

     while(1)
     {
         c = tempVertexMinPL();

         if(c == NIL)
              return;

         vertexList[c].status = PERMANENT;

         for(v=0; v<n; v++)
         {
            if( adj[c][v]!=0 && vertexList[v].status == TEMPORARY )
                if( vertexList[c].pathLength + adj[c][v] < vertexList[v].pathLength)
                 {
                    vertexList[v].predecessor = c;
                    vertexList[v].pathLength = vertexList[c].pathLength + adj[c][v];
                 }
         }
      }
 }

 int tempVertexMinPL()
 {
     int min = INFINITY;
     int v, x = NIL;
   
	 for (v = 0; v < n; v++)
     {
          if (vertexList[v].status == TEMPORARY && vertexList[v].pathLength < min)
          {
               min = vertexList[v].pathLength;
               x = v;
          }
      }
      return x;
}
 
void findPath(int s, int v)
{
	int i, u;
	int path[MAX]; 
   	int sd = 0;	     
   	int count = 0;		    
   	   	
   	while (v != s)
   	{
   	   count++;
   	   path[count] = v;
   	   u = vertexList[v].predecessor;
   	   sd += adj[u][v];
   	   v=u;	
   	}
   	count++;
   	path[count] = s;

   	printf("Shortest Path is : ");
   	for(i = count; i>=1; i--)	
   	      printf("%s ", vertexList[path[i]].name );
   	printf("\n Shortest distance is : %d\n\n",sd );
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
				printf("(%s, %s, %d)  ", vertexList[i].name,vertexList[j].name, adj[i][j]);
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



