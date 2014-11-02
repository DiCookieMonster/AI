#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



char Table[8][11] = {
    "Name","Language","Style","Performer","Period","Length","Theme","Like",
	"Angie","Eng","Rock","RollingStones","70","Short","Love","true",
	"HotelCalifornia","Eng","Rock","Eagles","70","Long","Place","false",
	"YouCantAlwaysGetWhatYouWant","Eng","Rock","70","Long","Life","false",
	"MyWay","Eng","Rock","RollingStones","80","Long","Life","true",
	"MyWay","Eng","Pop","FrankSinatra","60","Long","Life","true",
	"FiveMoreMinutes","Eng","Jazz","NinaHagen","80","Long","Love","false",
	"NewYorkNewYork","Eng","Jazz","FrankSinatra","70","Short","Place","true",
	"DarkBlueNigth","Heb","Pop","Rita","90","Long","Love","false",
	"DarkBlueNigth","Heb","Pop","ShlomoIdov","90","Long","Love","false",
	"Beutiful","Heb","Mizrahi","EyalGolan","90","Long","Love","false",
	"Chiquita","Eng","Pop","ABBA","70","Long","Life","true"};


float Remain[8];
float Goal;

struct TreeNode {
    int data;
    struct TreeNode *leftChildNode;
    struct TreeNode *rightChildNode;
};

typedef struct TreeNode node;
node *rootNode = NULL;

/*inserts a node to the decision tree*/
void insertNode(int i, node *n) {
    if(n == NULL) {
        n = (node*)malloc(sizeof(node));
        n->leftChildNode = NULL;
        n->rightChildNode = NULL;
        n->data = i;
    }
    else
    if(n->data == i)
        printf("\nThis value already exists in the tree!");
    else
    if(i > n->data)
        insertNode(i, n->rightChildNode);
    else
        insertNode(i, n->leftChildNode);
    }


/*print the tree */
void printTree(node *n) {
    if(n != NULL) {
        printTree(n->leftChildNode);
        printf("%d ", n->data);
        printTree(n->rightChildNode);
    }
}

/*replaces 2 rows in a table*/
void replaceRow(int i,int j)
{   int k;
    char temp[20];
    for(k=0;k<8;k++)
      {  strcpy(temp,Table[i+1]);
         strcpy(Table[i+1][k],Table[j][k]);
         strcpy(Table[j][k],temp);
      }
}
/*initialize the Remain array*/
void initRemain()
{   int i;
    for(i=0;i<8;i++)
        Remain[i]=1;
}

/*counts the amount of same element in a column of a table */
int countSameElement(int index)
{   int i,j;
    int counter=0;
    for(i=0;i<11;i++)
        for(j=1;j<11;j++)
            if(strcmp(Table[index][j],Table[index][i]))
                counter++;
    return counter;
}

/*counts the amount of same element in a column of a table */
int countDiffrenetElement(int index)
{   int i,j;
    int counter=0;
    for(i=0;i<11;i++)
        for(j=1;j<11;j++)
            if(!strcmp(Table[index][j],Table[index][i]))
                 counter++;
    return counter;
}
/*sorts the table by themes*/
int sortAtribute(int index)
{   int i,j;
    int counter=0;
    for(i=0;i<11;i++)
        for(j=1;j<11;j++)
            if(strcmp(Table[index][j],Table[index][i]))
                    replaceRow(i,j);
}
/*counts the Goal*/
void countGoal()
{
    int i;
    for(i=0;i<11;i++)
        if(strcmp(Table[8][i],"true"))
           Goal++;
    Goal=Goal/11;
    return Goal;
}

/*calculates the positive possibility*/
float positiveFactore(int index,int sameE)
{  int i;
   float positive=0;
   for(i=1;i<sameE;i++)
    if(strcmp(Table[8][i],"true"))
        positive++;
    positive=positive/sameE;
    return positive;
}

/*calculates the Remain of a property*/
float calcsRemain(int index)
{  int i;
   float Remain=0;
   for(i=0;i<8;i++)
        Remain+=countSameElement(i)/11*Goal*positiveFactore(i,countSameElement(i));
   return Remain;
}


/* calculates all Remain */
int smalestRemain(int differentE)
{   int i,in;
    float r=1;
    for(i=0;i<differentE;i++)
     { if(Remain[i]<r){
            r=Remain[i];
            in=i; }
        Remain[i]=1;
        }
    return in;
}



/*builds the tree*/
void treeParse()
{   float sRemain;
    int nodeCount=8;
    int i;
    for(i=0;i<8;i++)
       calcsRemain(i);
    for(i=0;i<8;i++)
      {
        sRemain=smalestRemain(8);
        insertNode(sRemain,rootNode);
       }

}

int main()
{   int i,j;
    printf("Name    - Language - Style-Performer    - Period - Length - Theme - Like ");
    for(i=0;i<8;i++)
        for(j=1;j<11;j++)
           printf("%s   ",Table[i][j]);
        printf("\n");
    treeParse();
    printf( "The Tree: %d\n");
    printTree(rootNode);
    return 0;
}
