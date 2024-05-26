#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <string>
#include <bitset>
#include <queue>

using namespace std;
int pow_result=pow(2,14);

vector<int> harmony_not(pow_result);

int test_harmony_not(int a, int b){
    int output;
    int second_condition=0;
    int fourth_condition=0;
    int sixth_condition=0;
    if ((a+7)<=13){ //注意这里的位置是0-13
        if ((abs(a+7-b)==0)||(abs(a+7-b)==2)){
            second_condition=1;
        }
        else if (abs(a+7-b)==4){
            fourth_condition=1;
        }
        else if (abs(a+7-b)==6){
            sixth_condition=1;
        }
    }
    if ((b-7)>=0){
        if ((abs(b-7-a)==0)||(abs(b-7-a)==2)){
            second_condition=1;
        }
        else if (abs(b-7-a)==4){
            fourth_condition=1;
        }
        else if (abs(b-7-a)==6){
            sixth_condition=1;
        }
    }
    //感觉上面两个if条件的判断可以优化一下
    if (abs(a-b)==2){
        output=3;
    }
    else if(second_condition==1){
        output=4;
    }
    else if(abs(a-b)==4){
        output=5;
    }
    else if(fourth_condition==1){
        output=6;
    }
    else if(abs(a-b)==6){
        output=7;
    }
    else if(sixth_condition==1){
        output=8;
    }
    else{
        output=1000;
    }
    return output;
}

int main(){
    //输入
    unsigned long long input;
    cin>>input;
    int input2=0;
    for (int i=0; i<14; i++){
        input2+=(input%10)*(pow(2,i));
        input=input/10;
    }
    //这时input2应该是转化为的十进制了

    //开始计算每个状态之间的不和谐度
    for (int i=0; i<(pow_result); i++){
        string binary_str;
        bitset<14> binary(i);
        binary_str=binary.to_string();
        int count_1=0;
        vector<int> position;
        for (int j=0; j<binary_str.size(); j++){
            if (binary_str[j]=='1'){
                count_1++; //这里计数应该没问题
                position.push_back(j);
            } 
        }
        sort(position.begin(),position.end());
        if ((count_1==1)||(count_1==0)){
            harmony_not[i]=0;
        }
        else if(count_1==2){
            int a=position[0];
            int b=position[1];
            harmony_not[i]=test_harmony_not(a,b);
        }
        else{
            vector<int> for_xor;
            for (int j=0; j<position.size(); j++){
                for (int k=j+1; k<position.size(); k++){ //这里的排列组合应该是对的
                    int a=position[j];
                    int b=position[k];
                    for_xor.push_back(test_harmony_not(a,b));
                    //检测
                    /*
                    if (i==12824){
                        cout<<a<<" "<<b<<" "<<test_harmony_not(a,b)<<endl;
                    }
                    */
                    //上面test_harmony_not的函数应该没问题了
                }
            }
            //对所有的进行异或和
            int xor_result=0;
            for (int j=0; j<for_xor.size(); j++){
                xor_result=xor_result^for_xor[j];
            }
            harmony_not[i]=xor_result;
        }
    }
    //这里应该把所有状态的不和谐度都计算完成了
    vector<vector<pair<int, int>>> storage(pow_result);
    for (int i=0; i<(pow_result); i++){
        bitset<14> binary(i);
        /*
        if (i==8878){
            cout<<i<<" "<<binary<<endl;//检测
        }
        */
        for (int j=0; j<14; j++){
            bitset<14> binary2=binary;
            if (binary2[j]==1){
                binary2[j]=0;
            }
            else if(binary2[j]==0){//
                binary2[j]=1;
            }
            //上面遍历可以转化成为的状态
            //再将二进制转化为十进制
            int number=binary2.to_ulong();
            /*
            int number=0;
            for (int i=0; i<14; i++){
                if (binary_str2[i]=='1'){ //这里一开始没有加''号改了好久啊
                    number+=(pow(2,13-i));
                }
            }
            */
            //上面binary_str2和求number的部分应该是没问题的
            int weight=harmony_not[number];
            storage[i].push_back(make_pair(number,weight));
        }
        
    }
    /*
    for (int i=0; i<14; i++){
        cout<<storage[8878][i].first<<" "<<storage[8878][i].second<<endl;//检测
    }
    cout<<endl;
    */
    //这时图类似于邻接表的表示应该建立好了
    //cout<<storage[12809][0].first<<" "<<storage[12809][0].second<<endl;//检测
    //cout<<storage[input2].size()<<endl;//检测
    //cout<<input2<<endl;//检测
    /*
    for (int i=0; i<storage[input2].size(); i++){
        int num=storage[input2][i].first;
        bitset<14> bits(num);
        cout<<bits<<" "<<storage[input2][i].second<<endl;//检测
    }
    cout<<endl;
    */
    
    //vector<int> unused_vector(pow(2,14));
    //vector<int> used_vector;
    vector<int> visited_or_not(pow(2,14));
    //int working_vector=input2;
    vector<int> shortest_path(pow(2,14));
    int infinity=1000*(pow_result)+1;
    for (int i=0; i<pow(2,14); i++){
        //unused_vector[i]=i;
        visited_or_not[i]=0;
        shortest_path[i]=infinity;
    }
    shortest_path[input2]=0;
    vector<int> preceding_vector(pow(2,14));
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    q.push(make_pair(0,input2));

    while(q.size()!=0){
        pair<int,int> current_pair=q.top();
        int working_vector=current_pair.second;
        q.pop();
        if (visited_or_not[working_vector]==0){
            visited_or_not[working_vector]=1;
            for (int i=0; i<storage[working_vector].size(); i++){
                int next_vector=storage[working_vector][i].first;
                int next_weight=storage[working_vector][i].second;
                if (shortest_path[working_vector]+next_weight<shortest_path[next_vector]){
                    shortest_path[next_vector]=shortest_path[working_vector]+next_weight;
                    preceding_vector[next_vector]=working_vector;
                    q.push(make_pair(shortest_path[next_vector],next_vector));
                }
            }
        }
    }

    vector<int> path;
    int output=0;
    path.push_back(0);
    while(output!=input2){
        output=preceding_vector[output];
        path.push_back(output);
    }
    for (int i=path.size()-2; i>=0; i--){
        bitset<14> binary_1(path[i+1]);
        bitset<14> binary_2(path[i]);
        for (int j=0; j<14; j++){
            if (binary_1[j]!=binary_2[j]){
                if (j==13){
                    cout<<"G2"<<" ";
                }
                if (j==12){
                    cout<<"A3"<<" ";
                }
                if (j==11){
                    cout<<"B3"<<" ";
                }
                if (j==10){
                    cout<<"C3"<<" ";
                }
                if (j==9){
                    cout<<"D3"<<" ";
                }
                if (j==8){
                    cout<<"E3"<<" ";
                }
                if (j==7){
                    cout<<"F3"<<" ";
                }
                if (j==6){
                    cout<<"G3"<<" ";
                }
                if (j==5){
                    cout<<"A4"<<" ";
                }
                if (j==4){
                    cout<<"B4"<<" ";
                }
                if (j==3){
                    cout<<"C4"<<" ";
                }
                if (j==2){
                    cout<<"D4"<<" ";
                }
                if (j==1){
                    cout<<"E4"<<" ";
                }
                if (j==0){
                    cout<<"F4"<<" ";
                }
            }
        }
    }
    cout<<endl;
    cout<<shortest_path[0]<<endl;
    //cout<<input2;
}