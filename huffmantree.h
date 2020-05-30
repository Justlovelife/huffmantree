//树的节点定义
struct Node{
    struct Node *parent;    //父亲节点
    struct Node *left;      //左孩子
    struct Node *right;     //右孩子
    int num;  //保存的字母或者其他的频率  
    int idx;   //是一个索引，通常是传进来的构建树的数组的下标，通过下标可以找到字符
};
//一棵树的结构
struct huffman{
    struct Node *tree; //树根
    int ct_treenode;   //树里有多少个叶子节点
};
struct huffman *huffman_create(int *num,int ct);//创建一棵树，参数是int数组的名字，还要数组的元素个数
void huffman_destroy(struct huffman *huffman);//销毁一棵树
void huffman_getcode(struct huffman *huffman, int index, char *code,int *len);//根据索引得到某个字符的编码和编码长度
int huffman_getindex(struct huffman *huffman,char *code);  //得到一个字符的编码
int huffman_isleaf(struct Node *cur);//判断是否是左子树



