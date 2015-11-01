#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int jum=0, total=0, k=0, prime[1000];

void* t1(void *ptr)
{
	int *i, j;
	i=(int*)ptr;
	for(j=1; j<=*i; j++)
	{
		if(*i%j==0)
		{
			k++;
		}
	}
	if(k==2)
	{
		jum+=1;
		total+=*i;
		prime[jum]=*i;
	}
	k=0;
}

int main()
{
	pthread_t tid;
	int i, input;
	printf("Masukkan bilangan prima sampai ke : ");
	scanf("%d", &input);
	for(i=1; i<input; i++)
	{
		pthread_create(&tid,NULL,t1,(void*)&i);
		pthread_join(tid, NULL);
	}
	for (i=1; i<=jum; i++) printf("%d ", prime[i]);
	printf("\nTerdapat %d bilangan dengan total %d\n", jum, total);
	return 0;
}
