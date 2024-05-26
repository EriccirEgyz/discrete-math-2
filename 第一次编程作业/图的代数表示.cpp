#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    //multimap<pair<int,int>,pair<int,int>> graph1;
    vector<vector<int>> graph2; //
    //接受输入
    int n,edge;
    cin>>n>>edge;
    for (int i=1;i<=edge;i++){
        int start,end,weight;
        cin>>start>>end>>weight;
        //graph1.insert(make_pair(make_pair(start,end),make_pair(weight,i)));
        graph2.push_back({i,start,end,weight});//
        //graph1[make_pair(start,end)]=weight;
        //cout<<graph1.size();
    }

    //创建邻接矩阵
    int adjacent_matrix[n][n];
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            adjacent_matrix[i][j]=0;
        }
    }

    //创建邻接表
    //vector<vector<vector<int>>> adj_list(n);
    vector<vector<vector<int>>> adj_list(n,vector<vector<int>>(edge,vector<int>(3)));

    //设置邻接矩阵
    for (int i=0; i<edge; i++){
        int start1=graph2[i][1]-1;
        int end1=graph2[i][2]-1;
        int weight1=graph2[i][3];
        int sequence_number=graph2[i][0];
        adj_list[start1].push_back({sequence_number,end1+1,weight1});
        if (adjacent_matrix[start1][end1]==0)
                adjacent_matrix[start1][end1]=weight1;
        else
            adjacent_matrix[start1][end1]=-1;
    }
    //输出邻接矩阵
    
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cout<<adjacent_matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    /*
    for (auto it=graph1.begin();it!=graph1.end();it++){
        int start1=it->first.first-1;
        int end1=it->first.second-1;
        int weight1=it->second.first;
        int sequence_number=it->second.second;
        adj_list[start1].push_back({sequence_number,end1+1,weight1});
    }
    */

   //设置邻接表
   /*
   for (int i=0; i<edge;i++){
        int start1=graph2[i][1]-1;
        int end1=graph2[i][2];
        int weight1=graph2[i][3];
        int sequence_number=graph2[i][0];
        adj_list[start1].push_back({sequence_number,end1,weight1});
    }
    */
    
    for(int i=0;i<adj_list.size();i++){
       std::sort(adj_list[i].begin(),adj_list[i].end(),[](const vector<int>& a, const vector<int>& b){
            return a[0]>b[0];
        });
    }
    
    for(int i=0; i<adj_list.size();i++){
        if (adj_list[i].size()>0){
            cout<<adj_list[i][0][0]<<endl;
        }
        else{
            cout<<0<<endl;
        }
    }

    for (int i=0;i<edge;i++){
        //cout<<graph2[i][0]<<endl;
        //int sequence=graph2[i][0];
        int start1=graph2[i][1];
        int end1=graph2[i][2];
        int weight1=graph2[i][3];
        int a=adj_list[start1-1].size();
        for (int j=0;j<a;j++){
            if (adj_list[start1-1][j][0]==(i+1)){
                if (j==a-1){
                    cout<<end1<<" "<<weight1<<" "<<0<<endl;
                }
                else{
                    cout<<end1<<" "<<weight1<<" "<<adj_list[start1-1][j+1][0]<<endl;
                }
                break;
            }
        }
    }
}