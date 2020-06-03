//Working : Correct ;)
#include<stdio.h>

#define SIZE 10

void matrix_chain_order(int a[], int n)
{	
	int  m[n+1][n+1], s[n+1][n+1];
	int i,j,k,l;
	int q;
	for(i=1; i<=n; i++)
		m[i][i] = 0;

	for(l =2; l<=n ; l++)
	{	for(i= 1; i<=n-l+1; i++)
		{	j = i+l-1;
			m[i][j] = 999999;
			for(k= i; k<=j-1; k++)
			{	q = (m[i][k] +m[k+1][j] + a[i-1]*a[k]*a[j]);
				if(q < m[i][j])
				{	m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	printf("\nminimum number of operations to be done : %d \n",m[1][n]);	
}

main()
{	int n;
	int i;	
	int matrix_order[SIZE];

	printf("\nEnter the number of Matrices : ");
	scanf("%d", &n);

	printf("\nEnter the order of the matrix : ");
	for(i=0; i<=n; i++)
		scanf("%d", &matrix_order[i]);

	matrix_chain_order(matrix_order, n);
}
