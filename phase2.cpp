#include<iostream>
#include "unionFind.cpp"
// #include "distFunc.cpp"
#include<bits/stdc++.h>

using namespace std;

double euclidean(Row row1,Row row2){
    double ans=0;
    int M=row1->fields.size();
    
    for(int i=0;i<M;i++)
    ans=ans+(pow((row1->fields[i])-(row2->fields[i]),2));

    return ans;
}

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
    
    for(int ro=0;ro<transdataset.size();ro++){
        
        neighs=getNeighrestNeighbours(transdataset,transdataset[ro],eps);
        if(neighs.size()>=minpoints){
            core[ro]=1;

            for(int neigh=0;neigh<neighs.size();neigh++){
                if(core[neighs[neigh]->actual_id])
                
                {
                    cout << typeid(&(transdataset[ro]->id)).name() << '\n';
                    //modify parent id's
                    // temp=unionOp(transdataset[ro]->id,neighs[neigh]->id);
                    
                }
                else
                {
                    if(!visited[neighs[neigh]->actual_id]){
                        visited[neighs[neigh]->actual_id]=1;
                    }
                    //temp=unionOp(&transdataset[ro]->id,&neighs[neigh]->id);
                }
                
            }
        }
    }
    return transdataset;

}

int main()
{
    double dataset[N][M]={0};
    vector<Row> out_data= dbscan(dataset,1,0);
    double out[N][M+2]={0};
    for(int i=0;i<N;i++){
        int j=0;
        for(j=0;j<M;j++){
            out[i][j]=out_data[i]->fields[j];
        }
        Node dat=find(&out_data[i]->id);
        out[i][j+1]=dat->data;
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<M+1;j++)
        cout<<out[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}