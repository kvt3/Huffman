
// KALYANI TARU CS610 4514 PRP

#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "huffman.h"


int main(int argc, char *argv[]){
    FILE *fpI,*fpO;
    unsigned char c;
    int flag = 0;
    unsigned char buffer[BUFFERSIZE];
    unsigned long int j;
    char tmpfile[100];
    int fsize;
    struct leaf* node;
    struct leaf* rootnode;
    int ffsize,i;

    strcpy(file, argv[1]);
    strcpy(tmpfile, file);
    
    fpI = fopen(file,"rb");
    if (fpI == NULL){
        perror("file doesn't exist.");
    }
    rmStr(file,".huf");
    fpO = fopen(file, "w");
    if (fpO == NULL){
        perror("file doesn't exist.");
    }

    fseek(fpI,-1,SEEK_END);
    fsize = ftell(fpI);
    c = fgetc(fpI);
    
    rewind(fpI);
    ch = fgetc(fpI);
    
    node = readTree(fpI);
    rootnode = node;
    treeTraves(node,0);
    
    while(!feof(fpI)){
         
        if(feof(fpI) || flag == 1){
            free(node);
            fclose(fpI);
            break;
        }

        j = 0;
        while(j < BUFFERSIZE && !feof(fpI)){
            
            if(feof(fpI) || flag == 1){
                break;
            }

        for ( i= 7; i >= 0; --i){
            if (!isLeaf(node)){
                if(get_bit(fpI)){
                    node = node->right;
                }
                else{
                    node = node->left;
                }
            }else{
                 ffsize =  ftell(fpI);
            //   printf("size: %d\n",ffsize);
                i++;                
                buffer[j]=node->data;
                j++;
                node = rootnode;
                if((ffsize == fsize) && (pos == (7-(c+0)))){
              //      printf("%d %d %d\n",ffsize,pos,j);
                    flag = 1;
                     break;
               }
            }
        }
        }

         fwrite(buffer, 1, j, fpO);

}
    
    fclose(fpO);

    int ret = remove(tmpfile);

       if(ret == 1){
         printf("Error: unable to delete the file");
        }
   
}

int isLeaf(struct leaf* root){
    return(!(root->left) && !(root->right));
}

struct leaf* newNode(unsigned char data,long long freq,struct leaf* left, struct leaf* right){
          struct leaf* node = (struct leaf*) malloc(sizeof(struct leaf));
          node->left = right; 
          node->right = left;
          node->data = data;
          node->frq = freq;
         return node;
    }

struct leaf* readTree(FILE* fpI) {
           int p = get_bit(fpI);
   if (p) {
            return newNode(getNode(fpI), -1, NULL, NULL);
       }else {
        
        return newNode('\0', -1, readTree(fpI), readTree(fpI));
       }
}

void printbincharpad(char c)
{   int i;
    for ( i = 7; i >= 0; --i) {
        putchar( (c & (1 << i)) ? '1' : '0' );
    }
    putchar('\n');
}

 int get_bit(FILE* fpI)
{          
        if(pos < 0){
            pos = 7;
            ch = fgetc(fpI);
            exit;
        }
        if (ch & (1 << pos)){
            pos--;
            return 1;
        }else{ 
            pos--;
            return 0;
        }
}

char getNode(FILE* fpI){
    unsigned char t;
    int j;
    for( j=0; j<8; j++){
        t <<= 1;
        if(get_bit(fpI)){
            t |= 1;
        }
    }
    return t;
}


void treeTraves(struct leaf* root,int i){
    if(isLeaf(root)){
    //    printf("data: %c\n",root->data);
        return;
    }
    
    treeTraves(root->left,0);
    treeTraves(root->right,1);
}

void rmStr(char *s,const char *toremove)
{
      while( s=strstr(s,toremove) )
              memmove(s,s+strlen(toremove),1+strlen(s+strlen(toremove)));
}
