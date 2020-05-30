#define _CRT_SECURE_NO_WARNINGS
#include "huffmantree.h"
#include <stdlib.h>
#include <string.h>

//哈弗曼树的实现     static  静态的只能在本源文件中使用
static struct Node *creatnode(int idx, int num)  //参数是头文件里面定义的  下标和出现的频率
{
    struct Node *temp = malloc(sizeof(struct Node));   
    temp->num = num;
    temp->left = NULL;
    temp->right = NULL;
    temp->idx = idx;
    temp->parent = NULL;
    return temp;
}
int huffman_isleaf(struct Node *cur)
{
    if(cur->left==NULL&&cur->right==NULL)
    return 1;
    else
    {
        return 0;
    }
}
//给出索引值找节点，是一个递归函数   
struct Node *find(struct Node *root,int idx)
{
    if(!root) return NULL;
    if(root->idx==idx) return root;    
    struct Node *left=find(root->left,idx) ;
    struct Node *right=find(root->right,idx);
    if(left) return left;
    else if(right) return right;
    return NULL;
}
//树的构建
struct huffman *huffman_create(int *num, int ct)//num是存放根节点的数组名，ct是元素个数
{
    struct huffman *huffman = malloc(sizeof(struct huffman));//分配内存
    struct Node **array=malloc(ct*sizeof(struct Node *));//创建节点指针数组，保存指针
    struct Node *temp=NULL;
    int i;
    for(i=0;i<ct;i++)
    {
        array[i]=creatnode(i,num[i]);//创建多个节点，将每个节点的指针保存在上面的指针数组里
    }
    //找出最小的和次小的节点，组装，最后形成一颗树
    int j;
    int minidx,secminidx;
    for(i=0;i<ct-1;i++)
    {
        j=0;
        while(array[j]==NULL)
        {
            j++;
        }
        minidx=j;

        for(j=0;j<ct;j++)
        {
            if(array[j]&&array[j]->num<array[minidx]->num)
            {
                minidx=j;
            }

        }

        j=0;
        while(array[j]==NULL||j==minidx)
        {
            j++;
        }
        secminidx=j;
        for(j=0;j<ct;j++)
        {
            if(array[j]&&j!=minidx&&array[j]->num<array[secminidx]->num)
            {
              secminidx=j;  
            }
        }

        temp=creatnode(-1,array[minidx]->num+array[secminidx]->num);        
        temp->left=array[minidx];
        temp->right=array[secminidx];
        temp->parent=NULL;

        array[minidx]->parent=temp;
        array[secminidx]->parent=temp;
           
        array[minidx]=temp;
        array[secminidx]=NULL;
    }
    huffman->tree=temp;
    free(array);
    array=NULL;
    return huffman;
}
void huffman_show(const struct huffman *huffman)
{
    
}
void huffman_destroy(struct huffman *huffman)
{
}
//获取编码，编码用1代表1，用2代表0
void huffman_getcode(struct huffman *huffman, int index, char *code,int *len)
{ 
    char a[20]={0};
    struct Node *temp=find(huffman->tree,index);
    if(!temp) return;
    int i=0;
    while(temp->parent)
    {
        if(temp->parent->left==temp)
        {
            a[i]=2;
        }
        else
        {
            a[i]=1;
        }
        temp=temp->parent;
        i++;
    }
    int length=i;
    char tmp=0;
    for(i=0;i<length/2;i++)
    {
        tmp=a[i];
        a[i]=a[length-i-1];
        a[length-i-1]=tmp;
    }
    strcpy(code,a);
    *len=length;
}
int huffman_getindex(struct huffman *huffman, char *code)
{
}