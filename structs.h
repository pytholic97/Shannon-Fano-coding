#include<stdbool.h>

#define MAX_CODE_LENGTH 50

typedef struct fnode
{
    char symbol;
    float prob;
    struct fnode *father;
    struct fnode *left;
    struct fnode *right;
}FNODE;
typedef struct fnode *FNODEPTR;

typedef struct qnode
{
    struct fnode *fnptr;
    struct qnode *next;
}QNODE;
typedef struct qnode *QNODEPTR;

typedef struct queue
{
    struct qnode *front;
    struct qnode *rear;
}QUEUE;

extern char *cbook[257];
extern FNODE *root;
extern int sym_range;
extern struct queue q1;

//Essential functions
void codebook(FNODE *fath,QNODE *l,QNODE *r,int pre);
bool getSym();
bool encInput();
bool decoded();

//Helper Functions
float mod(float );
float sqr(float );
FNODE *makefnode(float pr,char ch);
QNODE *findMin(QNODE *l,QNODE *r);
void saveWord(int pre,FNODE *rt);
void clrmem();
void clrqueue(QNODEPTR t);
void clrTree(FNODEPTR r);
