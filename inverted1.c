#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
//#include "inverted.h"
//#include "Tree.h"
//#include "readData.h"
//#include "List.h"


#define key(it) (it)
#define cmp(k1,k2) (strcmp(k1, k2))
#define less(k1,k2) (cmp(k1,k2) < 0)
#define eq(k1,k2) (cmp(k1,k2) == 0)


//creating a List

typedef struct DLListRep *DLList;

// data structures representing DLList

typedef struct DLListNode {
	char   *value;  // value of this list item (string)
	struct DLListNode *prev;
	               // pointer previous node in list
	struct DLListNode *next;
	               // pointer to next node in list
} DLListNode;

typedef struct DLListRep {
	int  nitems;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *curr;  // current node in list
	DLListNode *last;  // last node in list
} DLListRep;


//creating a Tree

// client view of a Tree
typedef struct TreeRep *Tree;

// Representation of Trees and Nodes
typedef struct Node *Link;

typedef struct Node {
	char value[100];
	DLList LOU;//a list of urls
	Link left, right;
} Node;

typedef struct TreeRep {
	Link  root;
	int   nwords;//number of words inside each node
} TreeRep;

// Items and operations on Items
typedef char *Key;
typedef Key Item; // item is just a key



// create a new DLListNode (private function)
DLListNode *newDLListNode(char *it)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	new->value = strdup(it);
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLList
DLList newDLList()
{
	struct DLListRep *L;

	L = malloc(sizeof (struct DLListRep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;
	L->curr = NULL;
	return L;
}

// Interface: create a new empty Tree
Tree newTree()
{
	TreeRep *new = malloc(sizeof(TreeRep));
	assert(new!=NULL); 
    new->root = NULL;
    new->nwords = 0;
    return new;
}	

//making a new node containing a value 
Link newNode(char value[100]){
    Link new = malloc(sizeof(Node));
    assert(new != NULL);
    new->left = new->right = NULL;
    strcpy(new->value, value);
	new->LOU = newDLList();
	return new;
}

// Helpers: various styles of insert
Link insert(Link t, Item it)
{
	if (t == NULL) return newNode(it);
	int diff = cmp(key(it),key(t->value));
	if (diff == 0)
		strcpy(t->value,it);
	else if (diff < 0){
		t->left = insert(t->left, it);
	} else if (diff > 0){
		t->right = insert(t->right, it);
	}
	return t;
}
// insert an item after current item
// new item becomes current item
void DLListAfter(DLList L, char *it)
{
	assert(L != NULL); 
	struct DLListNode *p = newDLListNode(it);
	struct DLListNode *temp = L->first;
	
	while(temp!=NULL){
	    if (strcmp(temp->value, it)==0){
	        return;
	    }
	    else {
	        temp = temp->next;
	    }
	}
	
    if (L->first == NULL)
	    L->first = L->last = L->curr = p;
	
    else if (L->curr->next!=NULL){
        p->next = L->curr->next;
        L->curr->next->prev = p;
        L->curr->next = p;
        p->prev = L->curr;
    }
    else {
        L->curr->next = p;
        p->prev = L->curr;
        L->last = p;
    }
    L->curr = p;
    L->nitems++;	
	
}

//number of urls
int numURLs(){
        printf("AAAA");
    FILE *f = fopen("collection.txt", "r");
    char buff[1000];

    int nums = 0;

    while (fscanf(f, " %s", buff)){
        nums++;

    }

    fclose(f);
    return nums;

}
//reading in urls
char** ReadURLs(int nums, char** urls){
    
    FILE *f = fopen("collection.txt", "r");
    
    char buff[1000];//stores urls into array
    urls = malloc(nums * sizeof(char*));// allocating a memory space for the total number of urls
    
    //copying the list of url into new array
    int i = 0;
    while (i<nums){
        fscanf(f, " %s", buff);
        urls[i] = strdup(buff);//creates a copy of buff into urls[i]
        i++;
    }
    
    fclose(f);
    return urls;
}

//geting a collection of urls
void GetCollection(char **urls){
    int nums = numURLs();
    printf("4444\n");
    ReadURLs(nums,urls);
    //return urls;
}    


//for each url in list-of-urls, read <url>.txt file, and update inverted index            Tree tree = newTree(InsertAtLeaf);

Tree GetInvertedList(){
    char** urls = NULL;
    printf("5555\n");
    GetCollection(urls);    
    printf("3333\n");
    int num = numURLs();

    //creating a new tree
    Tree tree = newTree();
    
    char buffer[100];
    int i;

    for(i = 0; i < num; i++){
        
        sprintf(buffer,"%s.txt", urls[i]);//prints .txt to the end of each urlnumber
        FILE *f = fopen(buffer, "r");    
        while (!feof(f)){
            fscanf(f, " %s", buffer);
            if (strcmp(buffer, "#start") == 0){
                fscanf(f, " %s", buffer);
                if (strcmp(buffer, "Section - 2") == 0){
                    break;
                }
            }
    
            while (!feof(f)){   
                fscanf(f, " %s", buffer);
                if (strcmp(buffer, "#end") == 0) break;
                Link curr = insert(tree->root, buffer);
                DLListAfter(curr->LOU, urls[i]);
            }
        }
    }
    //*treeNode = words;
    //urlListNode = list of urls
    return tree;
}

void printTree(Link tree){
    if (tree == NULL){
        return;
    }
    
    printTree(tree->left);
    printf("%s", tree->value);
    printTree(tree->right);
}


int main (){
    printf("1111\n");
    Tree tree = GetInvertedList();
        printf("22222\n");
    printTree(tree->root);
    return 0;

}
