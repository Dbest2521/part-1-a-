#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "inverted.h"
#include "Tree.h"
#include "readData.h"
#include "List.h"

//for each url in list-of-urls, read <url>.txt file, and update inverted index            Tree tree = newTree(InsertAtLeaf);

Tree GetInvertedList(){
    char** urls
    GetCollection(**urls);
    int num = numURLs();

    //creating a new tree
    Tree tree = newTree(InsertAtLeaf);
    
    int buffer[100];
    for(int i0; i < num; i++){
        
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
                Link curr = TreeInsert(tree, buffer);
                DLListAfter(list, url[i]);
            }
        }
    }
    //*treeNode = words;
    //urlListNode = list of urls
    return *treeNode;
}

void printTree(Link tree){
    if (tree == NULL){
        return;
    }
    
    printTree(tree->left);
    printf("%s", tree);
    printTree(tree->right);
}
