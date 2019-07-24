#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct node
{
	int data;
	node* parent=NULL;
    
	vector<node *> child;
};

struct row
{
    vector<double> fields;
    struct node id;
    int actual_id;
};

typedef struct node* Node;
typedef struct row* Row;


