
// KALYANI TARU CS610 4514 PRP


#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "huffman.h"

int main(int argc, char *argv[]){
    struct leaf *leafnode;
    struct leafHeap *leafheap;
    FILE *fpI, *fpO;
    size_t s1, s2;
    unsigned char buffer[BUFFERSIZE];
    int j=0;
    char tmpfile[100];
    int count = 0;
    int i;
    int ret;

    leafheap = (struct leafHeap*) malloc(SIZE * sizeof(struct leafHeap));
    strcpy(file, argv[1]);
    strcpy(tmpfile,file);
    fpI = fopen(file,"rb");

    if (fpI == NULL)
    {
        perror("file doesn't exist.");
        return 0;
    }
    while ((s1 = fread(buffer, 1, sizeof(buffer), fpI)) > 0) {
        for ( i = 0; i < s1; ++i) {
	        if (freq[buffer[i]]==0) {
		        leafnode = (struct leaf*) malloc(SIZE * sizeof(struct leaf));
		        leafnode->data = buffer[i];
		        leafheap[j].leafs = leafnode;
		        j++;
	        }
            ++freq[buffer[i]];
        }
    }

    fclose(fpI);


    //int count = 0;
    for ( i=0; i<j; ++i) {
	    leafheap[i].leafs->frq = freq[leafheap[i].leafs->data];
	    if (leafheap[i].leafs->frq !=0)
		    ++count;
    }

    lsize = count;
    gsize = count;
    buildHuffmanTree(leafheap);
    free(leafheap);
    free(leafnode);
    ret = remove(tmpfile);
  
    if(ret == 1) {
         printf("Error: unable to delete the file");
       }
    return 0;
}



void minHeapify(struct leafHeap *leafheap, int idx){
    int smallest = idx;
    int left = 2 * idx + 1 ;
    int right = 2 * idx + 2;
    if (left < lsize && leafheap[left].leafs->frq < leafheap[smallest].leafs->frq)
      smallest = left;
 
    if (right < lsize && leafheap[right].leafs->frq < leafheap[smallest].leafs->frq)
      smallest = right;
 
    if (smallest != idx)
    {  
        swapNode(&leafheap[smallest], &leafheap[idx]);
        minHeapify(leafheap, smallest);
    }

}



struct leafHeap* buildMinHeap(struct leafHeap *leafheap)
{ 
    int n = lsize;
    int i;

    leafheap = realloc( leafheap, lsize * sizeof(struct leafHeap) );
   
	for (i = (n - 1) / 2; i >= 0; --i)
      	  minHeapify(leafheap, i);

	return leafheap;
}



void swapNode(struct leafHeap *a, struct leafHeap *b){
    struct leafHeap t = *a;
    *a = *b;
    *b = t;
}



struct leaf* extMin(struct leafHeap* leafheap)
{
   struct leaf *temp = leafheap[0].leafs;
   leafheap[0]=leafheap[lsize-1];
    --lsize;
    minHeapify(leafheap, 0);
    return temp;
}



void buildHuffmanTree(struct leafHeap* leafheap)
{
    struct leaf *left, *right;
    char code[100];
    int i = 0;
    struct leafHeap* minHeap = buildMinHeap(leafheap);

    while (lsize != 1)
    {  
        left = extMin(minHeap);
        right = extMin(minHeap);
	root = createNode(left->frq + right->frq);
        minHeapInsert(minHeap, root);
	root->left = left;
	root->right = right;
    }

	traTree(root,code,i);

}



void traTree(struct leaf* root, char* code,int i){   
    struct leaf* org;
    char* tmp;
    if(i==0){
        org = root;
    }
    if (root->left)
    {
	    code[i]='0';
        traTree(root->left,code,i+1);
    }
 
    if (root->right)
    {
        code[i]='1';
        traTree(root->right, code,i+1);
    }
 
    if (isLeaf(root))
    {   code[i]='\0';
        tmp = (char*) malloc(strlen(code) * sizeof(char));
        strcpy(tmp,code);
        code_table[root->data]=tmp;
        code =  (char*) malloc(100 * sizeof(char));
    }
    if(org == root){
      writeFile(org);
    }
}

int isLeaf(struct leaf* root){
    return(!(root->left) && !(root->right));
}



void minHeapInsert(struct leafHeap* leafheap, struct leaf* leaf){
	++lsize;
	int m = lsize-1;
	leafheap[m].leafs = leaf;
	
	while(m > 1 && leafheap[(m-1/2)].leafs->frq > leafheap[m].leafs->frq ){
		swapNode(&leafheap[(m-1/2)],&leafheap[m]);
		m = m-1/2; 
	}
}



struct leaf* createNode(long long freq){
	struct leaf* node = (struct leaf*) malloc(sizeof(struct leaf));
    node->left = node->right = NULL;
    node->data ='\0';
    node->frq = freq;
    return node;
}


char* concat(unsigned char *s1, unsigned char *s2)
{
        char *result = malloc(strlen(s1)+strlen(s2)+1);
        strcpy(result, s1);
        strcat(result, s2);
        return result; 
}


void writeFile(struct leaf* root){
    FILE *fpI,*fpO;
    size_t s1,s2;
    unsigned char buffer[BUFFERSIZE];
    unsigned char *str;
    unsigned long int size;
    int i,j;

    fpI = fopen(file,"rb");
    if (fpI == NULL){
         perror("file doesn't exist.");
     }
     fpO = fopen(strcat(file,".huf"), "wb");
     if (fpO == NULL){
         perror("file doesn't exist.");
     }
    
     writeTree(root);
                                                                           
     while ((s1 = fread(buffer, 1, sizeof(buffer), fpI)) > 0) {
        for ( i = 0; i < s1; ++i) {
            str = code_table[buffer[i]];
            size = strlen(str);
            for(j = 0 ; j<size; ++j){
                if(str[j] == '0'){
                writeBits(0);      
            }else if(str[j]== '1'){
                writeBits(1);

            }
        } 
      }
        s2 = fwrite(wbuffer, 1, bfsize, fpO);
            if (s2 < s1) {
                if (ferror(fpO))
                    printf("error while reading data");
            }
        bfsize = 0;
    }
 
  if(bsize > 0){
    //printf("%d %c",bsize,(bsize+'0'));
    byte <<= (8 - bsize);
    wbuffer[bfsize] = byte;
    bfsize++;
    wbuffer[bfsize] = bsize;
    fwrite(wbuffer, 1,2, fpO);
}
fclose(fpI);
fclose(fpO);
}

void writeBits(int bit){
    byte <<= 1;
    if(bit){
        byte |= 1;
    }
  bsize ++;
    if(bsize == 8){
        wbuffer[bfsize] = byte;
        bfsize++;
        byte = 0;
        bsize = 0;
    }
}

void writeTree(struct leaf* root){
       
    if (isLeaf(root)) {
        writeBits(1);
        writeByte(root->data);
        return;
    }
    writeBits(0);
    
    writeTree(root->left);
    writeTree(root->right);

          
}

void writeByte(char x){
    int bit,i;
    for ( i = 7; i >= 0; --i) {
        if(x & (1<<i)){
         writeBits(1);
        }else{
         writeBits(0);
        }
    }
}

void close(FILE* fpI, FILE* fpO){
  if(bsize > 0){
      byte <<= (8 - bsize);
      wbuffer[bfsize] = byte;
      fwrite(wbuffer, 1,1, fpO);
  }
 fclose(fpI);
 fclose(fpO);
}

