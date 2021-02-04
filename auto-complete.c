#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXCHAR 1000


typedef struct trienode{
    struct trienode * map[26];
    int status;
}TrieNode;



TrieNode* createNode(){
   TrieNode* t=(struct trienode*)malloc(sizeof(struct trienode));
   return t;
}




TrieNode* insertWord(char *word,TrieNode *node){

    TrieNode* t;
    int len=strlen(word)-1;
    if(len==0){
        node->status=1;
        return node;
    }

    int index=word[0]-97;
    if((*node).map[index]==NULL){
        (*node).map[index]=createNode();
    }
    insertWord(word+1,(*node).map[index]);
    
}




int printSuggestions(TrieNode *node,char *word,char *str){

    int len=strlen(word);
    
    if(len!=0){
        
        int index=word[0]-'a';
        if((*node).map[index]==NULL){
            return -1;
        }
        char array[strlen(str)+1];
        for(int i=0;i<strlen(str);i++){
            array[i]=str[i];
        }
        array[strlen(str)]=word[0];
        array[strlen(str)+1]=0;
        printSuggestions((*node).map[index],word+1,array);   
    }else{
        
        
        if(node->status==1){
            printf("%s\n",str);
            
        }
        if(node==NULL){
            return 0;
        }
        
        char ch;
        char array[strlen(str)+1];
        for(int i=0;i<strlen(str);i++){
            array[i]=str[i];
        }
        array[strlen(str)+1]=0;
        for(int i=0;i<26;i++){
            if((*node).map[i]==NULL){
            continue;
            }
            ch='a'+i;
            array[strlen(str)]=ch;
            printSuggestions((*node).map[i],word,array); 
        }

        return 0;
    }
    
}


int main() {
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "wordlist10000.txt";
    clock_t start_t, end_t, total_t;

    TrieNode *root=createNode();
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    start_t = clock();
    while (fgets(str, MAXCHAR, fp) != NULL){
        insertWord(str,root);
        
    }
    end_t = clock();
    total_t = end_t - start_t;
    printf("Total time taken by Method 1 to insert elements to tree: %ld\n", total_t  );
    start_t = clock();
    printSuggestions(root,"a","");
    end_t = clock();
    total_t = end_t - start_t;
    printf("Total time taken by Method 1 to print suggestions: %ld\n", total_t  );
    fclose(fp);
    return 0;
}