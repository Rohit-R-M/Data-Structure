//Binary search Tree
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct tnode
{
	void*dp;
	struct tnode*rc;
	struct tnode*lc;
}tnode;
typedef struct btree
{
	tnode*root;
	int count;
	int(*compare)(void*,void*);
	void(*print)(void*);
}btree;
btree*createtree(int(*cmp)(void*,void*),void(*pd)(void*))
{
	btree*t=(btree*)malloc(sizeof(btree));
	if(t)
	{
		t->root=NULL;
		t->count=0;
		t->compare=cmp;
		t->print=pd;
	}
	return t;
}
bool insert(btree*t,void*din)
{
	tnode*newnode,*root,*parent=NULL;
	int res;
	newnode=(tnode*)malloc(sizeof(tnode));
	if(!newnode)
	return false;
	newnode->dp=din;
	newnode->lc=NULL;
	newnode->rc=NULL;
	if(!t->root)     //t->root==0
	{
		t->root=newnode;
		t->count++;
		return true;
	}
	root=t->root;
	while(root)
	{
		parent=root;
		res=t->compare(root->dp,din);
		if(res>=0)
		root=root->rc;
		else
		root=root->lc;
	}
	if(res>=0)
	{
		  parent->rc=newnode;
    }
	else
	{
		  parent->lc=newnode;	  
	}
	t->count++;
	return true;
}
tnode*largenode(tnode*root)
{
	if(root->rc)
	   return(largenode(root->rc));
	return root;
}
tnode*smallnode(tnode*root)
{
	if(root->lc)
	  return(smallnode(root->lc));
	return root;
}
bool findkey(btree*t,tnode*root,void*pkey)
{
	int res;
	res=t->compare(root->dp,pkey);
	if(res==0)
	return true;
	if(res>=0)
	{
		if(root->rc)
		return(findkey(t,root->rc,pkey));
	}
	else
	{
		if(root->lc)
		return(findkey(t,root->lc,pkey));
	}
	return false;
}
bool deletenode(btree*t,void*pkey)
{
	tnode *curnode,*parent=NULL;
	int res;
	curnode=t->root;
	while(curnode)
	{
		res=t->compare(curnode->dp,pkey);
		if(res==0)
		break;
		else if(res>=0)
		{
			parent=curnode;
			curnode=curnode->rc;
		}
		else
		{
			parent=curnode;
			curnode=curnode->lc;
		}
	}
	if(!curnode)
	return false;
	if(curnode->rc==NULL&&curnode->lc==NULL)
	{
		if(parent->lc==curnode)
		parent->lc=NULL;
		else
		parent->rc=NULL;
	}
	else if(curnode->lc==NULL)
	{
		if(parent->lc==curnode)
		parent->lc=curnode->rc;
		else
		parent->rc=curnode->rc;
	}
	else if(curnode->rc==NULL)
	{
		if(parent->lc==curnode)
		parent->lc=curnode->lc;
		else
		parent->rc=curnode->lc;
	}
	t->count--;
	return true;
}
void preorder(btree*t,tnode*root)
{
	if(root)
	{
		t->print(root->dp);
		if(root->lc)
		preorder(t,root->lc);
		if(root->rc)
		preorder(t,root->rc);
	}
}
void inorder(btree*t,tnode*root)
{
	if(root)
	{
		
		if(root->lc)
		inorder(t,root->lc);
		t->print(root->dp);
		if(root->rc)
		inorder(t,root->rc);
	}
}
void postorder(btree*t,tnode*root)
{
	if(root)
	{
		
		if(root->lc)
		postorder(t,root->lc);
		if(root->rc)
		postorder(t,root->rc);
		t->print(root->dp);
	}
}
void no_of_leaf(tnode* root,int* leaf)
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
void key_parent(btree* t,tnode* root,tnode** parent,void* pkey)
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
int find_height(tnode* root)
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
bool tree_balanced(tnode* root)
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
void descending_order(btree* t,tnode* root)
{
	if(root)
	{
		if(root->rc)
		descending_order(t,root->rc);
		t->print(root->dp);
		if(root->lc)
		descending_order(t,root->lc);
	}
}
int compare(void*dp1, void*dp2)
{
	
  if(*(int*)dp1==*(int*)dp2)
  {
	return 0;
  }
  else if(*(int*)dp1<*(int*)dp2)
  {
	  return 1;
  }
  else
  {
	  return -1;
  }
}

void print(void *dp)
{
  printf("%d\t", *(int *)dp);
}

int main()
{
  btree *t = createtree(compare, print);

  if(!t)
    return 1;
  int *din,*pkey,*freq,leaf;
  int ch;
  tnode *p;
  while(1)
    {
      printf("Enter you choice :\n 1-insert \n2-search \n3-largenode\n4-smallnode\n5-delete\n6-tree traversal\n7-No.of nodes\n8-tree balance\n9-Descending order\n10-Height of tree\n11-tree is balanced or not\n12-Parent of an element\n13-exit\n");
      scanf("%d", &ch);
      switch(ch)
        {
          case 1:
            din = (int *)malloc(sizeof(int));
            if(!din)
              break;
            printf("Enter the data to be inserted: ");
            scanf("%d", din);
            if(insert(t, din))
              printf("Inserted\n");
            else
              printf("Not inserted\n");
            break;
          case 2:pkey=(int*)malloc(sizeof(int));
            printf("Enter the data to be delete: ");
            scanf("%d",pkey);
            if(findkey(t,t->root,pkey))
            {
              printf("Found\n");
		    }
            else
            {
              printf("Not found\n");
		    }
            break;
          case 3:p=largenode(t->root);
            print(p->dp);
            break;
          case 4:p=smallnode(t->root);
            print(p->dp);
            break;
            
          case 5:pkey=(int*)malloc(sizeof(int));
            printf("Enter the data to be searched: ");
            scanf("%d",pkey);
            if(deletenode(t,pkey))
            printf("delete");
            else
            printf("not delete");
            break;
         case 6:if(t->count == 0)
            {
              printf( "Tree is empty\n");
              break;
            }
            printf("Enter your choice :\n 1-preorder \n2-inorder \n3-postorder\n");
            scanf("%d", &ch);
            switch(ch)
              {
                case 1:
                  preorder(t, t->root);
                  break;
                case 2:
                  inorder(t, t->root);
                  break;
                case 3:
                  postorder(t, t->root);
                  break;
                default:
                  printf("Invalid choice\n");
              }
            break;
			case 7: leaf=0;
				        no_of_leaf(t->root,&leaf);
				        printf("Total no.of nodes=%d\n",t->count);
				        printf("Total no.of leaf nodes=%d\n",leaf);
				        printf("Total no.of internal nodes=%d \n",t->count-(leaf));
				        break;
			case 8:if(tree_balanced(t->root))
				        printf("Tree is Balanced\n");
				        else
				        printf("Tree is not Balanced\n");
				        break;
			case 9: printf("Descending order:\n");
				    descending_order(t,t->root);
					break;
			case 10:printf("Height of the tree is:");
			        printf("%d\n",find_height(t->root));   
			        break;
		    case 11:if(tree_balanced(t->root))
		            printf("Tree is Balance\n");
		            else
		            printf("Tree is not Balance\n");
		    	    break;
		    case 12:printf("Enter the key to find its parent\n");
				        din=(int*)malloc(sizeof(int));
				        scanf("%d",din);
				        key_parent(t,t->root,&p,din);
				        if(p)
				        printf("Parents of %d is %d\n",*din,*(int*)p->dp);
				        else
				        printf("Key is a ROOT\n");
				        break;
			case 13:return 0;       
			default:printf("Invalid Choice\n");
		}
	}
}
