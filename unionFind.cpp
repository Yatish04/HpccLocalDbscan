#include<iostream>
#include <bits/stdc++.h> 
#include "types.cpp"
using namespace std;

Node newNode(int data){
	
	Node n=new struct node;
	n->data=data;
    return n;	
}

Node find(Node y){

    if(y==NULL){
            return NULL;
	 }
   return (y->parent)==NULL?y:find(y->parent);
}


// returning the root of the tree
Node unionOp(Node x,Node y)
{

  // cout<<"INSIDE "<<x->data<<"INSDIE";
  if(find(y)==y)
   {
     if(x->data>y->data){
     (x->child).push_back(y);
     y->parent=x;     
     }
     else
     {
       (y->child).push_back(x);
     x->parent=y; 
     }
     
     return find(x);
   }
  else if(find(x)==find(y)){  
        return find(x);
   }
   else
   {
       if(find(x)->data>find(y)->data){
        (find(x)->child).push_back(find(y));
        (find(y)->parent)=find(x);
	    return find(x);
	   
	   }
       else{
       	(find(y)->child).push_back(find(x));
        (find(x)->parent)=find(y);
        return find(y);
		}
       
   }


}
   
void printLevelOrderTraversal(Node root)
{
	if(root==NULL){
		return;
	}
	
	queue<Node> q;
	q.push(root);
	
	while(!q.empty())
	{   int n=q.size();
		
	while(n>0){
		
		Node x=q.front();
		q.pop();
		
		cout<< x->data<<" ";
		
		for(int i=0;i<x->child.size();i++){
			q.push(x->child[i]);
		}
		
	     n--;	
      }
       cout<<endl;
 	}
}

// int main()
// {
	
// //Test code for union find operation 	
// 	Node root=newNode(10);	
// 	Node root2=newNode(20);
	
// 	Node r1,r2;
// 	Node nodes[10];
// 	Node nodes2[10];
	
	
// 	for(int i=0;i<10;i++){
// 		nodes[i]=newNode(i*100);
// 		nodes2[i]=newNode(i*5);
// 		r1=unionOp(root,nodes[i]);
// 		r2=unionOp(root2,nodes2[i]);
// 	}
	 
// 	   printLevelOrderTraversal(r1);
// 	   cout<<"\n";
// 	   printLevelOrderTraversal(r2); 
	   
// 	   cout<<"\n";
	   
// 	   r1=unionOp(r1,r2);
// 	   printLevelOrderTraversal(r1); 
// }