#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <stack>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<double> producing_efficiency(n-1);
    for (int i=0; i<n-1; i++){
        double m;
        scanf("%lf",&m);
        producing_efficiency[i] = m;
    }
    vector<double> production_line_building(n-1);
    for (int i=0; i<n-1; i++){
        double m;
        scanf("%lf",&m);
        production_line_building[i]=m;
    }

    vector<pair<int,vector<pair<int,pair<double,double>>>>> storage(n);

    for (int i=0; i<n; i++){
        int numbers;
        scanf("%d",&numbers);
        storage[i].first=numbers;
        for (int j=0; j<numbers; j++){
            int technology_type;
            double production_amount;
            scanf("%d %lf",&technology_type,&production_amount);
            storage[technology_type-1].second.push_back(make_pair(i+1,make_pair(production_amount,0)));//这个production_amount设置得可以小心一些
        }
    }

    //cout<<"到这里成功了"<<endl;

    for (int i=0; i<n; i++){
        for (int j=0; j<storage[i].second.size(); j++){
            //int technology_type=storage[i].second[j].first;
            double target_amount=storage[i].second[j].second.first;
            double actual_amount=0;
            double actual_producing_efficiency=producing_efficiency[i];
            double time1=production_line_building[i];
            double total_time=0;
            while (actual_amount<target_amount){
                if (actual_amount+(actual_producing_efficiency*time1)>=target_amount){
                    total_time+=(target_amount-actual_amount)/actual_producing_efficiency;
                    break;
                }
                else{
                    total_time+=time1;
                    actual_amount+=actual_producing_efficiency*time1;
                    //actual_producing_efficiency+=producing_efficiency[technology_type-1];
                    actual_producing_efficiency+=producing_efficiency[i];
                }
            }
            storage[i].second[j].second.second=total_time;
        }
    }

    //cout<<"到这里成功了"<<endl;
    //cout<<storage[0].second[0].second.first<<endl;
    //cout<<storage[0].second[0].second.second<<endl;

    stack<int> waiting_list;
    vector<double> fastest_time(n);

    for (int i=0; i<n; i++){
        if (storage[i].first==0){
            waiting_list.push(i+1);
        }
        fastest_time[i]=0; //先全部初始化为0
    }

    for ( int i=1; i<n; i++){
        int working_vector=waiting_list.top();
        waiting_list.pop();

        for (int j=0; j<storage[working_vector-1].second.size();j++){
            int update_vector=storage[working_vector-1].second[j].first;
            double update_time=storage[working_vector-1].second[j].second.second+fastest_time[working_vector-1];
            if (update_time>fastest_time[update_vector-1]){
                fastest_time[update_vector-1]=update_time;
            }
            storage[update_vector-1].first--;
            if (storage[update_vector-1].first==0){
                waiting_list.push(update_vector);
            }
        }
    }

    //cout<<"到这里成功了"<<endl;

    cout<<fixed<<setprecision(2)<<fastest_time[n-1];

}