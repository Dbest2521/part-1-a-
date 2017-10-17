#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int numURLs(){
    FILE *f = fopen("collection.txt", "r");
    char buff[1000];
    
    int nums = 0;
    while (fscanf(f, "%s", buff) == 1){
        nums++;
    }
    fclose(f);
    return nums;

}


char** ReadURLs(int nums){
    
    FILE *f = fopen("collection.txt", "r");
    
    char buff[1000];//stores urls into array
    char** urls = malloc(nums * sizeof(char*));// allocating a memory space for the total number of urls
    
    //copying the list of url into new array
    int i = 0;
    while (i<nums){
        fscanf(f, "%s", buff);
        urls[i] = strdup(buff);//creates a copy of buff into urls[i]
        i++;
    }
    
    fclose(f);
    return urls;
}

//finding index of the url in the list of urls
int URLindex(char** urls, int nums, char* url){

    int i = 0;
    while (i<nums){
        if (strcmp(urls[i], url)==0){
            return i;
        }
        i++;
    }
    return -1;
}

int** AdjMatrix (int N){

    int** m = malloc (N * sizeof (int*));
    int i = 0;
    while (i<N){
        m[i] = calloc (N, sizeof(int));
        i++;
    }
    return m;
}

int main(void){
    int nums = numURLs();
    char** urls = ReadURLs(nums);
    return 0;
}    
    
//strstr - finding string within another string -> returns a pointer -- return NULL if haven't found, else return a pointer at the first letter 
//skip the new line/and the next string by doing fscanf("%s")
//space needed before fscanf(" %s");




