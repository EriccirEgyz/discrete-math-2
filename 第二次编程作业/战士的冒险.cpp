#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    int number;
    cin >> number;
    vector<vector<int>> round_number(number, vector<int>(number));
    for (int i=0; i<number; i++){
        for (int j=0; j<number; j++){
            cin >> round_number[i][j];
        }
    }
    vector<int> optimal_path(number);
    vector<int> path(number);
    for (int i=0; i<number; i++){
        optimal_path[i] = i+1;
        path[i]=i+1;
    }
    int optimal_path_length=10000000;
    while (next_permutation(path.begin(),path.end())){
        int accumulated_path_length=0;
        int last_step;
        int continue_or_not=1;
        for (int i=0; (i<number&&continue_or_not==1); i++){
            if (i==0){
                last_step=path[i];
            }
            else{
                int vector_number=path[i];
                accumulated_path_length+=round_number[last_step-1][vector_number-1];
                last_step=vector_number;
                if (accumulated_path_length>=optimal_path_length){
                    continue_or_not=0;
                    break;
                }
            }
        }
        if (accumulated_path_length<optimal_path_length){
            optimal_path_length=accumulated_path_length;
            optimal_path=path;
        }
    }
    

    cout<<optimal_path_length<<endl;
    for (int i=0; i<number; i++){
        cout<<optimal_path[i]<<" ";
    }

}