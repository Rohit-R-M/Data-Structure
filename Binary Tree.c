//binary tree
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"queuelladt.h"
typedef struct tnode
{
	void* dp;
	struct tnode* lc;
	struct tnode* rc;
}TNODE;
typedef struct binary_tree
{
	TNODE* root;
	int count;
	bool (*compare)(void*,void*);
	void (*print)(void*);
}BTREE;
BTREE* createtree(bool (*cmp)(void*,void*),void (*pt)(void*))
{
	BTREE* t;
	t=(BTREE*)malloc(sizeof(BTREE));
	if(!t)
	return NULL;
	else
	t->root=NULL;
	t->count=0;
	t->compare=cmp;
	t->print=pt;
	return t;
}
bool insertion(BTREE* t,void* dpin)
{
	TNODE* nnode,*traverse,*parent;
	int ch;
	traverse = t->root;
	while(traverse)
	{
		printf("Enter the choice\n");
		printf("1 for Left subtree\n2 for Right subtree\n");
		scanf("%d",&ch);
		parent = traverse;
		if(ch==1)
		traverse = traverse->lc;
		else if(ch==2)
		traverse = traverse->rc;
		else
		printf("Invalid Choice\n");
	}
	nnode=(TNODE*)malloc(sizeof(TNODE));
	if(!nnode)
	    return false;
	else
	{
	    nnode->dp=dpin;
	    nnode->lc=NULL;
	    nnode->rc=NULL;
	}
	if(!t->root)
	    t->root=nnode;
	else if(ch==1)
	    parent->lc=nnode;
	else if(ch==2)
	    parent->rc=nnode;
    t->count++;
	return true;
}
bool find_key(BTREE* t,TNODE* root,void* pkey)
{
	if(root)
	{
		if(t->compare(root->dp,pkey))
			return true;
		if(root->lc)
			if(find_key(t,root->lc,pkey))
				return true;
		if(root->rc)
			if(find_key(t,root->rc,pkey))
				return false;
	}
	return false;
}
void find_key_freq(BTREE* t,TNODE* root,int(*freq),void* pkey)
{
	if(root)
	{
		if(t->compare(root->dp,pkey))
		(*freq)++;
		if(root->lc)
		find_key_freq(t,root->lc,freq,pkey);
		if(root->rc)
		find_key_freq(t,root->rc,freq,pkey);
		
	}
}
void preorder_traversal(BTREE* t,TNODE* root)
{
	if(root)
	{
		t->print(root->dp);
		if(root->lc)
		preorder_traversal(t,root->lc);
		if(root->rc)
		preorder_traversal(t,root->rc);
	}
}
void inorder_traversal(BTREE* t,TNODE* root)
{
	if(root)
	{
		if(root->lc)
		inorder_traversal(t,root->lc);
		t->print(root->dp);
		if(root->rc)
		inorder_traversal(t,root->rc);
	}
}
void postorder_traversal(BTREE* t,TNODE* root)
{
	if(root)
	{
		if(root->lc)
		postorder_traversal(t,root->lc);
		if(root->rc)
		postorder_traversal(t,root->rc);
		t->print(root->dp);
	}
}
void no_of_leaf(TNODE* root,int* leaf)
{
	if(root)
	{
		if(!root->lc && !root->rc)
		(*leaf)++;
		if(root->lc)
		no_of_leaf(root->lc,leaf);
		if(root->rc)
		no_of_leaf(root->rc,leaf);
	}
}
int find_height(TNODE* root)
{
	int hl,hr;
	if(root)
	{
		hl=find_height(root->lc);
		hr=find_height(root->rc);
		if(hl>hr)
		return(hl+1);
		return(hr+1);
	}
	return 0;
}
bool tree_balanced(TNODE* root)
{
	int hl,hr,bfactor;
	if(root)
	{
		hl=find_height(root->lc);
		hr=find_height(root->rc);
		bfactor=hl-hr;
		if(bfactor<=1 && bfactor>=-1)
		return true;
		return false;
    }
    return true;
}
void key_parent(BTREE* t,TNODE* root,TNODE** parent,void* pkey)
{
	if(root)
	{
		if(t->compare(root->dp,pkey))
		{
			*parent=root;
			return;
		}
		if(root->lc)
		{
			key_parent(t,root->lc,parent,pkey);
			if(root->lc==*parent && (t->compare(root->lc->dp,pkey)))
			*parent=root;
		}
		if(root->rc)
		{
			key_parent(t,root->rc,parent,pkey);
			if(root->rc==*parent && t->compare(root->rc->dp,pkey))
			*parent=root;
		}
	}
}
void breadth_first_traversal(BTREE* t)
{
	TNODE* current;
	queue* q;
	current=t->root;
	q=createqueue();
	while(current)
	{
		t->print(current->dp);
		if(current->lc)
		if(enqueue(q,current->lc))
		;
		if(current->rc)
		if(enqueue(q,current->rc))
		;
		if(!emptyqueue(q))
		current=(TNODE*)dequeue(q);
		else
		current=NULL;
	}
}
TNODE* create_new_tree(TNODE* root)
{
	TNODE* nnode;
	nnode=(TNODE*)malloc(sizeof(TNODE));
	if(nnode)
	{
		nnode->dp=root->dp;
		nnode->lc=create_new_tree(root->lc);
		nnode->rc=create_new_tree(root->rc);
		return nnode;
	}
	else
	return NULL;
}
BTREE* copy_binary_tree(BTREE* t)
{
	BTREE* ntree;
	ntree=(BTREE*)malloc(sizeof(BTREE*));
	if(ntree)
	{
		ntree->root=(t->root);
		ntree->count=t->count;
		ntree->compare=t->compare;
		ntree->print=t->print;
		return ntree;
	}
	return NULL;
}
void delete_node(TNODE* root)
{
	if(root)
	{
		delete_node(root->lc);
		delete_node(root->rc);
		free(root->dp);
		free(root);
	}
}
bool destory_tree(BTREE* t)
{
	TNODE* temp;
	if(t->root)
	{
		temp=t->root;
		delete_node(temp);
		free(t);
	}
	return true;
}
bool compare(void* d1,void* d2)
{
	if(*(int*)d1==*(int*)d2)
	return true;
	return false;
}
void print_node(void* d)
{
	printf("%d\t",*(int*)d);
}
int main()
{
	BTREE* bt,*temp;
	bt=createtree(compare,print_node);
	if(bt)
	{
		int* din,ch,leaf,*freq=0;
		TNODE* parent;
		while(1)
		{
			printf("1-Insertion\n2-search\n3-frequency\n4-no.of node\n5-tree traversal\n6-balance tree\n7-parent of key\n8-copy tree\n9-exit\n");
			printf("Enter the choice\n");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1: printf("Enter the element to be inserted\n");
				        din=(int*)malloc(sizeof(int));
				        scanf("%d",din);
			          	if(insertion(bt,din))
			         	printf("Sucessfull\n");
			         	else
			        	printf("Falied\n");
				        break;
				case 2: printf("Enter the element to be Searched\n");
				        din=(int*)malloc(sizeof(int));
				        scanf("%d",din);
				        if(find_key(bt,bt->root,din))
				        printf("Sucessfull\n");
			         	else
			        	printf("Falied\n");
				        break;
				case 3: printf("Enter Key to find the frequency\n");
				        din=(int*)malloc(sizeof(int));
				        scanf("%d",din);
				        freq=(int*)malloc(sizeof(int));
				        *freq=0;
				        find_key_freq(bt,bt->root,freq,din);
				        printf("Key Frequency=%d\n",*freq);
				        break;
				case 4: leaf=0;
				        no_of_leaf(bt->root,&leaf);
				        printf("Total no.of nodes=%d\n",bt->count);
				        printf("Total no.of leaf nodes=%d\n",leaf);
				        printf("Total no.of internal nodes=%d \n",bt->count-(leaf));
				        break;
				case 5: printf("1-Preorder\n2-inorder\n3-postorder\n4-breadth first traversal\n");
				        scanf("%d",&ch);
				        switch(ch)
				        {
				        	case 1: printf("PREORDER traversal\n");
				        	        preorder_traversal(bt,bt->root);
				        	        break;
				        	case 2: printf("INORDER traversal\n");
				        	        inorder_traversal(bt,bt->root);
				        	        break;
				            case 3: printf("POSTORDER traversal\n");
				        	        postorder_traversal(bt,bt->root);
				        	        break;
				        	case 4: printf("Breadth First traversal\n");
				        	        breadth_first_traversal(bt);
				        	        break;
				        	default:printf("Invalid choice\n");
						}
				case 6: if(tree_balanced(bt->root))
				        printf("Tree is Balanced\n");
				        else
				        printf("Tree is not Balanced\n");
				        break;
				case 7: printf("Enter the key to find its parent\n");
				        din=(int*)malloc(sizeof(int));
				        scanf("%d",din);
				        key_parent(bt,bt->root,&parent,din);
				        if(parent)
				        printf("Parents of %d is %d\n",*din,*(int*)parent->dp);
				        else
				        printf("Key is a ROOT\n");
				        break;
				case 8: temp=copy_binary_tree(bt);
				        if(temp)
				        {
				        	printf("Inorder traversal of Copy TREE is:\n");
				        	inorder_traversal(temp,temp->root);
				        	free(temp);
						}
						else
						printf("Tree is not copied\n");
						break;
				case 9: if(destory_tree(bt))
				        printf("Destoryed\n");
				        else
				        printf("Tree doesn't exists\n");
				        return 0;
				default: printf("Invalid choice\n");
			}
		}
	}
}
