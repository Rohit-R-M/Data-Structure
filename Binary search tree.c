/*Binary Sreach tree*/ ////delete function missing
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"queuelladt.h"
typedef struct node
{
	void* dp;
	struct node* lc;
	struct node* rc;
}TNODE;
typedef struct binary_search_tree
{
	int count;
	TNODE* root;
	bool (*compare)(void*,void*);
	void (*print)(void*);
}BST;
BST* createbst(bool (*cmp)(void*,void*),void (*pt)(void*))
{
	BST* bt;
	bt=(BST*)malloc(sizeof(BST));
	if(!bt)
	return NULL;
	else
	bt->count=0;
	bt->root=NULL;
	bt->compare=cmp;
	bt->print=pt;
	return bt;
}
bool insert_node(BST* bt,void* dpin)
{
	TNODE* nnode,*root,*parent;
	int result=0;
	nnode=(TNODE*)malloc(sizeof(TNODE));
	if(!nnode)
	return false;
	else
	{
		nnode->dp=dpin;
		nnode->lc=NULL;
		nnode->rc=NULL;
	}
	if(!bt->root)                //when empty
	{
		bt->root=nnode;
		bt->count++;
		return true;
	}
	root=bt->root;
	parent=NULL;
	while(root)
	{
		parent=root;
		result=bt->compare(root->dp,dpin);
		if(result==1)
		root=root->lc;
		else
		root=root->rc;
	}
	if(result==0)
	parent->lc=nnode;
	else
	parent->rc=nnode;
	bt->count++;
	return true;
}
TNODE* largest_node(TNODE* root)
{
	if(root->rc)
	return(largest_node(root->rc));
	else
	return root;
}
TNODE* smallest_node(TNODE* root)
{
	if(root->lc)
	return(largest_node(root->lc));
	else
	return root;
}
bool find_key(BST* bt,TNODE* root,void* pkey)
{
	int result;
	result=(bt->compare(root->dp,pkey));
	if(result==0)
	return true;
	if(result>0)
	{
	    if(root->rc)
	    {
	        return(find_key(bt,root->rc,pkey));
        }
    }
	else
	{
      	if(root->lc)
      	{
	        return(find_key(bt,root->lc,pkey));
		}
	}
	return false;
}
void preorder_traversal(BST* bt,TNODE* root)
{
	if(root)
	{
		bt->print(root->dp);
		if(root->lc)
		preorder_traversal(bt,root->lc);
		if(root->rc)
		preorder_traversal(bt,root->rc);
	}
}
void inorder_traversal(BST* bt,TNODE* root)
{
	if(root)
	{
		if(root->lc)
		inorder_traversal(bt,root->lc);
		bt->print(root->dp);
		if(root->rc)
		inorder_traversal(bt,root->rc);
	}
}
void postorder_traversal(BST* bt,TNODE* root)
{
	if(root)
	{
		if(root->lc)
		postorder_traversal(bt,root->lc);
		if(root->rc)
		postorder_traversal(bt,root->rc);
		bt->print(root->dp);
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
void key_parent(BST* bt,TNODE* root,TNODE** parent,void* pkey)
{
	if(root)
	{
		if(bt->compare(root->dp,pkey))
		{
			*parent=root;
			return;
		}
		if(root->lc)
		{
			key_parent(bt,root->lc,parent,pkey);
			if(root->lc==*parent && (bt->compare(root->lc->dp,pkey)))
			*parent=root;
		}
		if(root->rc)
		{
			key_parent(bt,root->rc,parent,pkey);
			if(root->rc==*parent && bt->compare(root->rc->dp,pkey))
			*parent=root;
		}
	}
}
void breadth_first_traversal(BST* bt)
{
	TNODE* current;
	queue* q;
	current=bt->root;
	q=createqueue();
	while(current)
	{
		bt->print(current->dp);
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
BST* copy_binary_tree(BST* bt)
{
	BST* ntree;
	ntree=(BST*)malloc(sizeof(BST*));
	if(ntree)
	{
		ntree->root=(bt->root);
		ntree->count=bt->count;
		ntree->compare=bt->compare;
		ntree->print=bt->print;
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
bool destory_tree(BST* bt)
{
	TNODE* temp;
	if(bt->root)
	{
		temp=bt->root;
		delete_node(temp);
		free(bt);
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
	BST* bt,*temp;
	bt=createbst(compare,print_node);
	if(bt)
	{
		int* din,ch,leaf,*freq=0;
		TNODE* parent;
		while(1)
		{
			printf("1-Insertion\n2-search\n3-frequency\n4-no.of node\n5-tree traversal\n6-balance tree\n7-parent of key\n8-copy tree\n9-Largest node\n10-Smallest node\n11-exit\n");
			printf("Enter the choice\n");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1: printf("Enter the element to be inserted\n");
				        din=(int*)malloc(sizeof(int));
				        scanf("%d",din);
			          	if(insert_node(bt,din))
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
				        find_key(bt,bt->root,din);
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
			    case 9:if(!largest_node)
			            printf("No elements\n");
			            else
			            printf("largest element is %d\n",*(int*)largest_node);
			            break;
			    case 10:if(!smallest_node)
			            printf("No elements\n");
			            else
			            printf("Smallest element is %d\n",*(int*)smallest_node);
			            break;
				case 11: if(destory_tree(bt))
				        printf("Destoryed\n");
				        else
				        printf("Tree doesn't exists\n");
				        return 0;
				default: printf("Invalid choice\n");
			}
		}
	}
}
