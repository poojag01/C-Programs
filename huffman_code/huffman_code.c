#include<stdio.h>
#include<stdlib.h>
#define SIZE 10

typedef struct Node
{	char data;
	int freq;
	struct Node *left, *right;
}node;


void display( node *p, int n);
void swap(node * a, node *b);
void preorder(node *root);
void min_heapify( node *a, int i, int n);
void build_heap( node *a, int n);
node extract_min(node *a , int n)
void insert(node *a, node *add, int n);
void huffmann_decode(node *root, char s[]);
node * huffmann_coding(node *p, int n);

void display(node *p, int n)
{	int i;
	printf("\nData   Frequency\n");
	for(i=1; i<=n; i++)
		printf("%3c %9d\n",p[i].data, p[i].freq);
}

void swap(node * a, node *b)
{
	node temp = *a;
	*a = *b;
	*b = temp;

//	printf("\nswap a : %p b : %p values : %d %d",a,b, (a)->freq,b->freq);
}

void preorder(node *root)
{	if(root == NULL)
		return ;	
	else
	{
		printf("\n   %c    %d   ",root->data, root->freq);
		preorder(root->left);
		preorder(root->right);
	}

}

void min_heapify( node *a, int i, int n)
{	int l = 2*i;
	int r = 2*i +1;
	int min = i;
	//printf(" \n i : %d a : %p", i, a);
	if(l<=n && a[l].freq < a[i].freq)
		min = l;
	if(r<= n && a[r].freq < a[min].freq)
		min = r;

	if( min != i)
	{//	printf("\nheapify swap %d and %d",min, i);	
		swap(&a[i], &a[min]);
		min_heapify(a, min, n);
	}
}

void build_heap( node *a, int n)
{	int i;
	for(i =n/2; i>0; i--)
		min_heapify(a, i, n);
}

node extract_min(node *a , int n)
{	swap(&a[1], &a[n]);
	n--;
	min_heapify(a, 1, n);
//	printf("\n n : %d The value after deletion :\n",n);
//	display(a,n);
	return a[n+1];
}

void insert(node *a, node *add, int n)
{	int i;

	a[++n] = *add;
	i = n;

	while(i>1 && a[i].freq < a[i/2].freq)
	{	swap(&a[i], &a[i/2]);
		i /= 2;
	}
//	printf("\nAfter insertion of freq : %d\n",add->freq);
//	display(a, n);

}

void huffmann_decode(node *root, char s[])
{	
	if(root == NULL || root->left == NULL || root->right == NULL)
		printf("\nCant decode the string\n");
	else
	{	
		node * temp = root;
		
		printf("\nThe characters transferred for the string (\" %s \") are : \n", s);
	//	preorder(temp);
		for(int i=0; s[i]; i++ )
		{	printf("%c",s[i]);
			if(s[i] == '0')
				temp = temp->left;
			
			if(s[i] == '1')
				temp = temp->right;

			if(temp->left == NULL && temp->right == NULL)
			{	printf("  %c\n",temp->data);
				temp = root;
			}
		}
		printf("\n\n");
	}
	
}

node * huffmann_coding(node *p, int n)
{
	node * add= (node *)malloc(sizeof(node));
	node x[n], y[n];
	node *root;
	int j=0;
	int ch;

	build_heap(p, n);

	for(int i=0; i<n; i++)
		x[i].left = x[i].right = y[i].left = y[i].right = NULL;

	while(n >1)
	{
		x[j] = extract_min(p, n);
		n--;
		y[j] = extract_min(p, n);
		n--;
		add->freq= x[j].freq + y[j].freq;
		add->left = &x[j];
		add->right = &y[j];
		insert(p, add, n);
		n++;
		j++;
	}
	root = p+1;
	preorder(root);
	printf("\nThe total number of characters to be transferred :  %d\n",root->freq);
	
	printf("\nThe total number of characters to be transferred :  %d\n",(p+1)->freq);

	
	printf("\nDo you want to test a string for the huffmann code? (1 for yes) : ");
	scanf("%d", &ch);

	if(ch==1)
	{
		char str[3*SIZE];	
		printf("\nEnter the binary string to decode : ");	
		scanf("%s", str);
		printf("%s", str);

		huffmann_decode(p+1, str);	//huffmann decoding 
	}		

	return p;
}

main()
{	int n;
	int i;
	
	int ch=0;	//choice for huffmann decoding want to perform or not

	node *p = (node *)malloc(SIZE*sizeof(node));
	//node p[SIZE];

	node * root;
	printf("\nEnter the number of distinct data : ");
	scanf("%d", &n);

	printf("\nEnter the character and it's frequency : \n");
	for(i=1; i<=n; i++)
	{	printf("%d. ",i);
		scanf(" %c %d", &(p+i)->data, &(p+i)->freq);
		p->left = p->right = NULL;

	}
	for(i=0; i<=n; i++)
		printf("\nnode + %d : %p %p\n", i, p+i, &(p+i)->data);

	p = huffmann_coding(p, n);
}
