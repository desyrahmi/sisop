//soal nomor 3, multithreading

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
	pthread_t tid1, tid2;
	int sesuatu=0;

	(void) pthread_create(&tid1,NULL,t1,&sesuatu);
	(void) pthread_create(&tid2,NULL,t2,&sesuatu);
	printf("Thread created\n");

	(void) pthread_join(tid1,NULL);
	(void) pthread_join(tid2,NULL);
	return 0;
}
