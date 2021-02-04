#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXCHAR 1000


typedef struct trienode{
    char c;
    struct trienode * next;
    struct trienode * child;;
    int status;
}TrieNode;



TrieNode* createNode(){
   TrieNode* t=(struct trienode*)malloc(sizeof(struct trienode));
   t->c='\0';
   t->next=NULL;
   t->child=NULL;
   return t;
}




TrieNode* insertWord(char *word,TrieNode *node){
    
    TrieNode* t;
    int len=strlen(word)-1;
    if(len==0){
        node->status=1;
        return node;
    }
    int found=0;
    while(node!=NULL){
       
       if(node->c==word[0]){
            found=1;
            break;
        }else if(node->c=='\0'){
            node->c=word[0];
            node->child=createNode();
            found=1;
            break;
        }
        t=node;
        node=node->next;
    }

    if(!found){
        node=t;
        node->next=createNode();
        node=node->next;
        node->c=word[0];
        node->child=createNode();
    }

    
    insertWord(word+1,node->child);
    
}




int printSuggestions(TrieNode *node,char *word,char *str){

    int len=strlen(word);
    
    if(len!=0){
        while(node!=NULL){
            if(node->c==word[0]){
                break;
            }
            node=node->next;
        }
        // int index=word[0]-'a';
        if(node==NULL){
            return -1;
        }
        char array[strlen(str)+1];
        for(int i=0;i<strlen(str);i++){
            array[i]=str[i];
        }
        array[strlen(str)]=word[0];
        array[strlen(str)+1]=0;
        printSuggestions(node->child,word+1,array);   
    }else{

        if(node->status==1){
            printf("%s\n",str);        
        }
        
        if(node->child==NULL){
            return 0;
        }
        
        char ch;
        char array[strlen(str)+1];
        for(int i=0;i<strlen(str);i++){
            array[i]=str[i];
        }
        array[strlen(str)+1]=0;
        
        while(node!=NULL){
            // if(node->child==NULL){
            //     continue;
            // }
            array[strlen(str)]=node->c;
            printSuggestions(node->child,word,array); 
            node=node->next;
        }

        return 0;
    }
    
}


int main() {
    clock_t start_t, end_t, total_t;
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "wordlist10000.txt";

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
    printf("Total time taken by Method 2 to insert elements to tree: %ld\n", total_t  );
    start_t = clock();
    printSuggestions(root,"a","");
    end_t = clock();
    total_t = end_t - start_t;
    printf("Total time taken by Method 2 to print suggestions: %ld\n", total_t  );
    printf("%ld",sizeof(*root));
    fclose(fp);
    return 0;
}