//Creating an array for storing the symbols their pros and an array of chars or ints for storing code
//for each symbol. Then recursion.
//Left is highest pro
//Assign memory to oort in main;

#include "structs.h"
#include <stdio.h>

bool getSym()
{
    char *ch = (char *)malloc(sizeof(char)*100);
	float sum=0.0,*p = (float *)malloc(sizeof(float)*100);
	int i = 0,j=0,k=0;
	for(;j < 257;j++) cbook[j] = NULL;
	while(1){
        //printf("Enter again\n");
        scanf(" %c%f",&ch[i],&p[i]);
        for(j = 0;j < i;j++)
        {

            if(ch[i] == ch[j])
            {
                printf("\nSymbol already exists. Please enter again");
                j = -1;
                break;
            }
        }
        if(j == -1) continue;
        sum += p[i];
        //printf("SUM IS %f prob is %d\n",sum,(sum==1.00));
        i++;
        //if(sum == 1.00f) break;
        if(mod(sum-1.0000) <= (float)0.0001) break;
        else if(sum > 1.00){
            printf("Invalid symbols\n");
            free(ch);
            free(p);
            return false;
        }

        if(i == 99){
            printf("Overflow!\n Exiting\n");
            free(ch);
            free(p);
            return false;
        }
	}

	printf("i is %d\n",i);
	sym_range = i;
	for(j = i-2;j >= 0;j--)
        for(k = 0;k <= j;k++)
        if(p[k] > p[k+1]){
            char sw = ch[k];
            sum = p[k];
            ch[k] = ch[k+1];
            p[k]= p[k+1];
            ch[k+1] = sw;
            p[k+1] = sum;
        }
printf("B$\n");
    for(j = i-1;j >= 0;j--) printf("Sorted sym %c  pro %f\n",ch[j],p[j]);
    printf("then\n");

    QNODEPTR qn = (QNODEPTR)malloc(sizeof(struct qnode));
    qn->fnptr = makefnode(p[i-1],ch[i-1]); //q1.front is the largest element
    qn->next = NULL;
    QNODEPTR t = qn;
    q1.front = qn;
    q1.rear = NULL;

    for(j = i-2;j >= 0;j--)
    {
        QNODEPTR qn = (QNODEPTR)malloc(sizeof(struct qnode));
        qn->fnptr = makefnode(p[j],ch[j]);
        qn->next = NULL;
        t->next = qn;
        t = qn;
    }
    q1.rear = t;
    #ifdef DBUG  //To display created symbol tree;
    QNODEPTR rar = q1.front;
    while(rar != NULL)
    {
        printf("%c   %f\n",rar->fnptr->symbol,rar->fnptr->prob);
        rar = rar->next;
    }
    #endif

    free(ch);
    free(p);
    return true;
}



void codebook(FNODE *fath,QNODE *l,QNODE *r,int pre) //Works!!!!
{
    QNODE *mid;
    FNODE *t = root;
    if(r == l)
    {
        if(fath && fath->left != NULL){
            r->fnptr->father = fath;
            fath->right = r->fnptr;
        }
        else if(fath){
            l->fnptr->father = fath;
            fath->left = l->fnptr;
        }
        saveWord(pre,l->fnptr);
        return;
    }
    mid = findMin(l,r);
    t = makefnode(-1,'-');
    if(fath && fath->left)
    {
        fath->right = t;
        t->father = fath;
    }
    else if(fath)
    {
        fath->left = t;
        t->father = fath;
    }

    if(pre == 1) root = t;
    pre *= 10;
    codebook(t,l,mid,pre);
    pre += 1;
    codebook(t,mid->next,r,pre);
    pre -= 1;
    pre /= 10;

}

bool encInput()
{
    FILE *fin = fopen("input.txt","r");
    if(!fin)
    {
        printf("failure 1\n");
        return false;
    }
    FILE *fop = fopen("output.txt","w+");
    if(!fop)
    {
        printf("failure 2\n");
        return false;
    }

    char c;
    while(fscanf(fin,"%c",&c) != EOF)
    {
        fprintf(fop,"%s",cbook[(int)c]);
    }

    fclose(fin);
    fclose(fop);
    return true;
}

bool decoded()
{
    FILE *fin = fopen("output.txt","r");
    if(!fin)
    {
        printf("failure 1\n");
        return false;
    }
    FILE *fop = fopen("results.txt","w+");
    if(!fop)
    {
        printf("failure 2\n");
        return false;
    }

    char c;
    if(!root->left && !root->right)
        while(fscanf(fin,"%c",&c) != EOF)
            if(c == '0') fprintf(fop,"%c",root->symbol);
    FNODEPTR tm = root;
    //printf("root l = %f r = %f\n",root->prob);
printf("\n");
    while(fscanf(fin,"%c",&c) != EOF)
    {
        if(c == '0')
            tm = tm->left;
        else
            tm = tm->right;

         if(tm->left == NULL || tm->right == NULL)
        {
            fprintf(fop,"%c",tm->symbol);
            printf("%c",tm->symbol);
            tm = root;
            continue;
        }
    }

    fclose(fin);
    fclose(fop);

    return true;
}


void param()
{
    float r=0,var=0,eff=0,hx=0;

    QNODEPTR t = q1.front;

    while(t)
    {
        r += strlen(cbook[(int)t->fnptr->symbol])*t->fnptr->prob;
        hx += -(t->fnptr->prob)*log2(t->fnptr->prob);
        t = t->next;
    }
    t = q1.front;
    while(t)
    {
        var += (t->fnptr->prob)*sqr(strlen(cbook[(int)t->fnptr->symbol]) - r);
        t = t->next;
    }
    printf("Average code length %f\nCode eff is %f\nVariance is %f\n",r,hx/r,var);

}


/************ Version 1.0 Obselete
void codebook(FNODE *fath,QNODE *l,QNODE *r,int pre)
{
    QNODE *mid;
    FNODE *t = root;
    if(r == l->next)
    {
        //TODO: add 1 extra bit in codeword and a 1 and a zero for right and left
        fath->left = l->fnptr;
        fath->right = r->fnptr;
        l->fnptr->father = fath;
        r->fnptr->father = fath;
        if(l == q1.front){
            root->left = fath;
            fath->father = root;
        }
        cbook[]
        return;
    }
    else if(r == l)
    {
        if(fath->left != NULL){
            r->fnptr->father = fath;
            fath->right = r->fnptr;
        }
        else{
            l->fnptr->father = fath;
            fath->left = l->fnptr;
        }
        if(l == q1.front){
            root->left = l->fnptr;
            l->fnptr->father = root;
            //root = fath;  //Uncomment this and comment above 2.
        }
        //Save the word corresponding to respective symbol; Remember to remove the leading 1
        return;
    }
    mid = findMin(l,r);
    pre *= 10;
    t = makefnode();

    //if(!fath) root = t;
    codebook(t,l,mid,pre);
    if(root == t)
    //TODO
    pre += 1;


    codebook(t,mid->next,r,pre);
    //TODO
    root->right = t;
    t->father = root;
    pre -= 1;
    pre /= 10;
}********/
