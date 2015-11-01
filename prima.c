//coba prima biasa
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int main()
{
	int input;
	int i,j,k=0, jum=0, total=0;
	printf("Masukkan bilangan prima sampai ke = ");
	scanf("%d", &input);
	printf("Deret bilangan prima adalah \n");
	for(i=1; i<=input; i++)
	{
		for(j=1; j<=i; j++)
		{
			if(i%j==0)
			{
				k++;
			}
		}
		if(k==2)
		{
			printf("%d\t", i);
			jum+=1;
			total+=i;
		}
		k=0;
	}
	printf("\nTerdapat %d bilangan dengan total %d\n", jum, total);
}
