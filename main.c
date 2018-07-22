#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
#include<malloc.h>
#define DONE
#include"structs.h"

char *cbook[257];
FNODE *root = NULL;
int sym_range;
struct queue q1;

int main(void)
{
	if(!getSym()){
        printf("Error accepting symbols\n");
        getch();
        return 0;
	}

	printf("fr is %f rear is %f\n",q1.front->fnptr->prob,q1.rear->fnptr->prob);

	codebook(root,q1.front,q1.rear,1);

#ifdef DONE

	if(encInput())
        decoded();


    param();
    clrmem();
#endif

    getch();
	return 0;
}

