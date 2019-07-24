#include<iostream>
#include "unionFind.cpp"
#include "distFunc.cpp"
#include<bits/stdc++.h>

using namespace std;



//M denotes the field length
//N denotes the number of records

//id in Row denotes the node data which contains parent id's
//Has to be renamed.

//visted takes care if its a member of any cluster


#define M 5

#define N 10

vector<int> visited;
vector<int> core;

Row newRow( int id){
    Row newrow=new struct row;
    newrow->id.data=id;
    return newrow;
}

vector<Row> initialise(double dataset[N][M]){
    vector<Row> data;
    visited.resize(N);
    core.resize(N);

    for(int i=0;i<N;i++){
    visited.push_back(0);
    core.push_back(0);
    }

    for(int i=0;i<N;i++){

        //initially each node is pointing to itself
        
        Row r= newRow(i);
        r->fields.resize(M);
        
        for(int j=0;j<M;j++){
            r->fields[j]=dataset[i][j];
        }
        r->actual_id=i;
        data.push_back(r);
    }
    return data;
}

vector<Row> getNeighrestNeighbours(vector<Row> dataset, Row row, double eps){
    vector<Row> neighbours;
    for(int i=0;i<dataset.size();i++){
        if(dataset[i]==row)
        continue;

        double dist = euclidean(dataset[i],row);
        if(dist<=eps){
            neighbours.push_back(dataset[i]);
        }
    }
    return neighbours;
}

vector<Row> dbscan(double dataset[N][M],int minpoints,double eps){
    vector<Row> transdataset=initialise(dataset);
    vector<Row> neighs;
    int minpts;
    Node temp;
    int temp1;
    for(int ro=0;ro<transdataset.size();ro++){
        cout<<"Processing"<<ro<<endl;
        
        neighs=getNeighrestNeighbours(transdataset,transdataset[ro],eps);
        
        if(neighs.size()>=minpoints){
            core[ro]=1;
            
            for(int neigh=0;neigh<neighs.size();neigh++){
    
                temp1=core[neighs[neigh]->actual_id];
                if(temp1)
                {
        
                    //modify parent id's
                    temp=unionOp(&transdataset[ro]->id,&neighs[neigh]->id);
                     cout<<"\nThe parent is "<<temp->data<<endl;
                }
                else
                {
                    if(!visited[neighs[neigh]->actual_id]){
                        visited[neighs[neigh]->actual_id]=1;
                        // cout<<" Trying union for "<<transdataset[ro]->id.data<<" and "<<neighs[neigh]->id.data<<endl;
                    temp=unionOp(&transdataset[ro]->id,&neighs[neigh]->id);

                    cout<<"\nThe parent is "<<temp->data<<endl;
                    }
                }
                
            }
        }
    }
    return transdataset;

}

int main()
{

    double dataset[N][M]={0};
    dataset[0][0]=0.5;
    dataset[0][1]=0.1;
    dataset[0][2]=0.2;
    dataset[0][3]=0.4;
    dataset[0][4]=0.7;
    
    dataset[1][0]=0.5;
    dataset[1][1]=0.0;
    dataset[1][2]=0.2;
    dataset[1][3]=0.4;
    dataset[1][4]=0.9;

    dataset[3][0]=2;
    dataset[3][1]=1;
    dataset[3][2]=2;
    dataset[3][3]=4;
    dataset[3][4]=7;

    dataset[9][0]=0.5;
    dataset[9][1]=0.1;
    dataset[9][2]=0.2;
    dataset[9][3]=0.4;
    dataset[9][4]=0.7;

    dataset[6][0]=2.5;
    dataset[6][1]=1.4;
    dataset[6][2]=2.2;
    dataset[6][3]=4.2;
    dataset[6][4]=7.1;
    
    vector<Row> out_data= dbscan(dataset,1,0.1);
    double out[N][M+2]={0};


    //Putting cluster number in the last column
    //is_core can be accessed from vector core
    //visited has marked for cluster
    
    for(int i=0;i<N;i++){
        int j=0;
        for(j=0;j<M;j++){
            out[i][j]=out_data[i]->fields[j];
        }
        

        Node dat=find(&out_data[i]->id);
        cout<<"cluster no is "<<j << dat->data<<endl;
        out[i][j]=(double)dat->data;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<M+1;j++)
        cout<<out[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}