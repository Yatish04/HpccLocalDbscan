#include<iostream>
#include<bits/stdc++.h>
#include<math.h>
// #include "types.cpp"

/*This file includes various distance metrics that can be used to 
find neighrest neighbours. Current dist metric - euclidean only. 
Can be extended to metrics like haversine etc..
 */


double euclidean(Row row1,Row row2){
    double ans=0;
    int M=row1->fields.size();
    
    for(int i=0;i<M;i++)
    ans=ans+(pow((row1->fields[i])-(row2->fields[i]),2));

    return ans;
}

