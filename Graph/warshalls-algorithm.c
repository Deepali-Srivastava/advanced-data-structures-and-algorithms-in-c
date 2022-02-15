/*
Copyright (C) Deepali Srivastava - All Rights Reserved
This code is part of DSA course available on CourseGalaxy.com  

*/

/* Path matrix by Warshall's algorithm */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 30

struct Vertex
{
	char name[50];
};

struct Vertex vertexList[MAX];

int adj[MAX][MAX]; /* Adjacency Matrix */
int n=0; /* Number of vertices in the graph */
int e=0; /* Number of edges in the graph */

int getIndex(char s[]);
void insertVertex(char s[]);
void deleteVertex(char s[]);
void insertEdge(char s1[], char s2[]);
void deleteEdge(char s1[], char s2[] );
void warshalls();

main()
{
	insertVertex("Zero");
  	insertVertex("One");
	insertVertex("Two");
	insertVertex("Three");

	insertEdge("Zero", "One");
    insertEdge("Zero", "Three");
    insertEdge("One", "Two");
    insertEdge("Two", "One");
    insertEdge("Three", "Zero");
    insertEdge("Three", "Two");

	warshalls();
}

void warshalls()
{
    int i,j,k,p[MAX][MAX];
	 
	for(i=0; i<n; i++)
	    for(j = 0; j < n; j++)
	          p[i][j] = adj[i][j];
	      
	for(k=0; k<n; k++)
	{
		for(i=0; i<n; i++)
	       for(j=0; j<n; j++)
	            p[i][j] = ( p[i][j]  || ( p[i][k] && p[k][j] ) );
	}
	   
	for(i=0; i<n; i++)
	{
	   for(j=0; j<n; j++)
	      printf("%d ", p[i][j]);
	   printf("\n");
	}
	printf("\n");  
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


