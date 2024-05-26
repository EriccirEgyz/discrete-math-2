#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

int n, edge, start;

void DFS_function(int working_vector,stack<int>& DFS, vector<int>& visited2, const vector<vector<int>>& graph){
    int whether_pop=0;
    int next_working_vector;
    if (visited2[working_vector-1]==0){
        cout<<working_vector<<" ";
        visited2[working_vector-1]=1;
    }
    if (graph[working_vector-1].size()!=0){
        for(int i=0; i<graph[working_vector-1].size(); i++){
            if(visited2[(graph[working_vector-1][i])-1]==0){
                whether_pop=1;
                next_working_vector=graph[working_vector-1][i];
                //cout<<next_working_vector<<" ";
                break;
            }
        }
    }
    if (whether_pop==0){
        /*
        int visited_all=0;
        for(int i = 0; i < n; i++){
            if(visited2[i]==0){
                visited_all=1;
                break;
            }
        }
        */
        if (!DFS.empty()){
        //if (visited_all==1){
            next_working_vector=DFS.top();
            DFS.pop();
            DFS_function(next_working_vector,DFS,visited2,graph);
        }
        
    }
    else{
        DFS.push(working_vector);
        //visited2[working_vector-1]=1;
        DFS_function(next_working_vector,DFS,visited2,graph);
    }  
}

void BFS_function(int start,const vector<vector<int>>& graph){
    queue<int> BFS;
    vector<int> visited(n);
    for (int i = 0; i < n; i++){
        visited[i]=0;
    }
    //cout<<start<<" ";
    visited[start-1]=1;
    BFS.push(start);
    while(!BFS.empty()){
        int working_vector2 = BFS.front();
        cout<<working_vector2<<" ";
        BFS.pop();
        if (graph[working_vector2-1].size()!=0){
            for(int i = 0; i < graph[working_vector2-1].size(); i++){
                if(visited[graph[working_vector2-1][i]-1]==0){
                    //cout<<graph[working_vector2-1][i]<<" "; 
                    visited[graph[working_vector2-1][i]-1]=1;
                    BFS.push(graph[working_vector2-1][i]);
                }
            }
        }
            
    }
}

int main(){
    std::cin>>n>>edge>>start;
    //vector<vector<int>>graph(n,vector<int>(edge));//
    vector<vector<int>>graph(n);
    graph.resize(n);//

    for(int i = 0; i < edge; i++){
        int start1, end1;
        std::cin>>start1>>end1;
        graph[start1-1].push_back(end1);
    }

    for (int i=0; i<n; i++){
        if (graph[i].size()!=0){
            reverse(graph[i].begin(),graph[i].end());
        }
    }

    BFS_function(start,graph);
    cout<<endl;
    
    stack<int> DFS;
    vector<int> visited2(n);
    for (int i = 0; i < n; i++){
        visited2[i]=0;
    }
    //visited2[start-1]=1;
    //cout<<start<<" ";
    DFS_function(start,DFS,visited2,graph);

}