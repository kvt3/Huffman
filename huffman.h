
// KALYANI TARU CS610 4514 PRP

#define size(x) (sizeof(x)/sizeof((x)[0]))
#define SIZE 256
#define BUFFERSIZE 4096
#define GETBIT(x,n) ((x >> (n-1)) & 1)

long long freq[SIZE];
int lsize;
int gsize;
int pos = 7;
char *code_table[SIZE];
char file[100];
static unsigned char byte;
static unsigned char ch;
static int bsize;
int bfsize;
unsigned char wbuffer[8000];
                
struct leaf{
    unsigned char data;
    long long frq;
    struct leaf *left , *right;
} *root;


struct leafHeap{
    struct leaf *leafs;
};
 
int isLeaf(struct leaf* );
struct leaf* createNode(long long );
struct leafHeap* buildMinHeap(struct leafHeap*);
void minHeapify(struct leafHeap*, int);
void swapNode(struct leafHeap* , struct leafHeap* );
struct leaf* extMin(struct leafHeap* );
void buildHuffmanTree(struct leafHeap* );
void minHeapInsert(struct leafHeap*, struct leaf*);
void traTree(struct leaf* root, char*,int );
void CreateBinary(void);
void writeFile(struct leaf*);
void writeBits(int);
char* concat(unsigned char*, unsigned char*);
void close(FILE* , FILE* );
void writeTree(struct leaf*);
void writeByte(char );
void decodefile(void);
void printbincharpad(char c);
struct leaf* readTree(FILE*);
struct leaf* newNode(unsigned char,long long,struct leaf*, struct leaf*);
int get_bit(FILE* fpI);
char getNode(FILE* );
void treeTraves(struct leaf* , int );
void rmStr(char *s,const char *toremove);
