#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

void* t1(void *ptr)
{
	FILE *baca, *salin;
	baca=fopen("baca.txt", "r");
	salin=fopen("salin1.txt", "w");
	char a;
	while((a=fgetc(baca))!=EOF)
	fputc(a,salin);

	fclose(baca);
	fclose(salin);
}

void* t2(void *ptr)
{
	FILE *baca, *salin;
        baca=fopen("salin1.txt", "r");
        salin=fopen("salin2.txt", "w");
        char a;
        while((a=fgetc(baca))!=EOF)
        fputc(a,salin);

        fclose(baca);
        fclose(salin);
}

int main()
{
	pthread_t tid;
	pthread_create(&tid,NULL,&t1,NULL);
	printf("Thread created\n");
	pthread_join(tid,NULL);
	pthread_create(&tid,NULL,&t2,NULL);
	printf("Thread 2 created\n");
	pthread_join(tid,NULL);
	return 0;
}
