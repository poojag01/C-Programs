
//Working fine :)
//time Complexity : O(ElgV) 

#include<stdio.h>
#include<stdlib.h>

#define SIZE 30

/*
int internal_name[SIZE];
char external_name[SIZE];		

*/
typedef struct Edges
{	int weight;
	int src;
	int dest;

}Edge;

typedef struct Graph
{	int v;	//no. of vertices
	int e;	//no.of edges;

	Edge *edge;
}Graph;

typedef struct Vertex
{
	int key;	//parent of i-th vertex
	int rank;	//no. of directly reachable vertices
	//char reachable[SIZE];
}Vertices;


void display(Vertices V[], int v)	//(vertex V)	//(int node[], int key[], int reachable[],int n)
{
	int i;
	printf("\nVertex \t   Parent  \t  Rank\n");
	for(i=0; i<v; i++)
		printf("%5d %11d %12d\n", i, V[i].key, V[i].rank);
}

void display_edges(Edge E[], int e)
{
	printf("\nSno.    Source \t\t Destination \t Weight\n");
	for(int i=0; i<e; i++)
		printf("%3d %10d %16d %12d \n",i+1, E[i].src, E[i].dest, E[i].weight);
}

Graph create_graph(int v, int e)
{	Graph g;
	g.v = v;
	g.e = e;

	g.edge = (Edge *)malloc(e*sizeof(Edge));

	return g;
}

void max_heapify(Edge G[], int i, int nv)
{	int l = 2*i+1;
	int r = 2*i +2;

	int max = i;
	

	if(l < nv && G[l].weight > G[max].weight)
		max = l;
	if(r < nv && G[r].weight > G[max].weight)
		max = r;

	if(max != i)
	{
		Edge temp;
			
		temp = G[max];
		G[max] = G[i];
		G[i] = temp;	
	
		max_heapify(G, max, nv);
	}
}


void build_heap(Edge G[], int nv)
{
	int i;

	for(i=nv/2-1; i>=0; i--)
		max_heapify(G, i, nv);


}

void heap_sort(Edge G[], int nv)
{	
	build_heap(G, nv);
		display_edges(G, nv);

	for(int i= nv-1; i>0; i--)
	{	Edge temp;
		
		temp = G[0];
		G[0] = G[i];
		G[i] = temp;
		
		display_edges(G, nv);
		max_heapify(G,0, i);

	}

}


int find_set(Vertices V[],int i)
{
	if(V[i].key != i)
		V[i].key = find_set(V, V[i].key);

	return V[i].key;	
}

void union_set(Vertices V[], int a, int b)
{	

	int a_key = find_set(V, a);
	int b_key = find_set(V, b);

	
	if(V[a_key].rank > V[b_key].rank)
	{	V[b].key = a;
//		V[a].rank++;
	}
	if(V[a_key].rank < V[b_key].rank)
	{	V[a].key = b;
//		V[b].rank++;
	}
	else	//(V[a_key].rank == V[b_key].rank)
	{	V[b].key = a;
		V[a].rank++;
	}
}

void kruskal(Graph G)
{
	int nv = G.v;		
	int i;
	int n= G.e;

	Vertices V[nv];
	Edge result[nv];
	

	int ee=0;	//edges in V[]

	for(i=0; i<nv; i++)	//initializing the parent/key value and rank of the V[]
	{	V[i].key = i;
		V[i].rank = 0;

	}

	heap_sort(G.edge, n);	//sorting edge[] of the graph G on the basis of the weight of the edges

	printf("\n\n");

	for(i=0; i<n && ee < nv-1 ; i++)
	{	Edge next_edge = G.edge[i];

		int x = find_set(V, next_edge.src);
		int y = find_set(V, next_edge.dest);	
		
		if(x != y)
		{
			result[ee++] = next_edge;
			union_set(V, x, y);
		}
	}
	printf("\n---------Vertices telling parent and rank--------- ");
	display(V, nv);

	printf("\n\n------------Selected Edges for Minimum Spanning Tree--------------- ");
	display_edges(result, ee);
	printf("\n\n");
}

main()
{
//	node vertex[SIZE];



	int ne;	//number of edges
	int nv;	//number of vertices
	int i;

	Graph g;

	printf("\nEnter the total number of vertices(or nodes) and edges : ");
	scanf("%d %d", &nv, &ne);
	
	g = create_graph(nv, ne);

	printf("\nPlease refer to vertices name\n");
	for(i=0; i<5; i++)
		printf( "%c  as  %d\n",97+i, i);
	printf("ans so on....\n");
	
/*	
	printf("\nEnter the vertices one by one : ");
	for(i=1; i<=g.v; i++)	//assigning the internal and external names to the vertices
	{	printf( "%d. ",i);
		internal_name[i] = i;
		scanf( " %c", &external_name[i]);
	}	
*/

	printf("\nEnter SOURCE  DESTINATION   WEIGHT: \n");
	for(i=0; i<ne; i++)
	{	printf("%d. ",i+1);
		scanf( " %d %d %d", &(g.edge[i].src), &(g.edge[i].dest), &(g.edge[i].weight));
	}
	
	kruskal(g);
	
}
