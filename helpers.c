#include"structs.h"
#include<stdio.h>

FNODE *makefnode(float pr,char ch)
{
    FNODE *t = (FNODE *)malloc(sizeof(FNODE));
    t->prob = pr;
    t->symbol = ch;
    t->father = NULL;
    t->left = NULL;
    t->right = NULL;

    return t;
}

QNODE *findMin(QNODE *l,QNODE *r)
{
    QNODE *mid = NULL;
    QNODE *t = l;
    float s1=0,s2=0;
    s1 = l->fnptr->prob;
    t = l->next;
    while(t != r->next)
    {
        s1 -= t->fnptr->prob;
        t = t->next;
    }

    mid = l;
    t = l->next;
    while(t != r)
    {
        s2 = s1 + 2*(t->fnptr->prob);
        if(mod(s2) <= mod(s1)) mid = t;
        //else return mid;

        s1 = s2;
        t = t->next;
    }
    return mid;

}

void saveWord(int pre,FNODE *rt)
{
    if(pre == 1)
    {
        cbook[(int)rt->symbol] = (char *)malloc(2*sizeof(char));
        cbook[(int)rt->symbol][0] = '0';
        cbook[(int)rt->symbol][1] = '\0';
        return;
    }

    char tem[MAX_CODE_LENGTH] = "";
    sprintf(tem,"%d",pre);
    cbook[(int)rt->symbol] = (char *)malloc(sizeof(char)*(strlen(tem)+1));
    int i;
    for(i = 1;i < strlen(tem);i++) cbook[(int)rt->symbol][i-1] = tem[i];
    cbook[(int)rt->symbol][i-1] = '\0';
    printf("sym is %c with code %s\n",rt->symbol,cbook[(int)rt->symbol]);
    return;
}

float mod(float n)
{
    if(n >= 0) return n;
    else return -1*n;
}

float sqr(float n)
{
    return n*n;
}

void clrmem()
{
    int i;
    for(i = 0;i < 257;i++)
        if(cbook[i] != NULL)
            free(cbook[i]);

    clrTree(root);
    QNODEPTR t = q1.front;

    clrqueue(t);

    return;
}

void clrqueue(QNODEPTR t)
{
    //QNODEPTR t = q.front;

    if(t) return;

    clrqueue(t->next);

    free(t);
}

void clrTree(FNODEPTR r)
{

    if(r == NULL)
        return;
    else if(r->left != NULL){
        clrTree(r->left);
        r->left = NULL;
    }
    else if(root->right != NULL){
        clrTree(r->right);
        r->right = NULL;
    }
    else{
        free(r);
        return;
    }
}

