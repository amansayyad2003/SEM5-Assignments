#include <iostream>
#include "ip.h"
#include "subnetmask.h"
#include "network_broadcast.h"

using namespace std;

vector<int> START_SUBNET_MASKA = {10, 0, 0, 0};
vector<int> END_SUBNET_MASKA = {10, 255, 255, 255};

vector<int> START_SUBNET_MASKB = {172, 16, 0, 0};
vector<int> END_SUBNET_MASKB = {172, 31, 255, 255};

vector<int> START_SUBNET_MASKC = {192, 168, 0, 0};
vector<int> END_SUBNET_MASKC = {192, 168, 255, 255};


string get_string_ip(vector<unsigned char> a, int extra = 0){
    a[a.size()-1] += extra;
    string result;
    for(auto i : a){
        result += to_string(i);
        result += '.';
    }
    result.pop_back();
    return result;
}

int a_raise_to_b(int a, int b){
    int ans = 1;
    for(int i = 0; i < b; i++){
        ans *= a;
    }
    return ans;
}

vector<unsigned char> increment_ip(vector<unsigned char> ip){
    vector<unsigned char> result = ip;
    for(int i = ip.size()-1; i >= 0 ; i--){
        if(ip[i] < 255){
            result[i]++;
            for(int j = i+1; j < 4; j++){
                result[j] = 0;
            }
            return result;
        }
    }
    return result;
}

void print_ip_all_subnet(vector<unsigned char> ip, int subnet_mask, int class_net){
    int subnets = get_no_of_subnet_mask(subnet_mask, class_net);
    /* int no_of_host = a_raise_to_b(2, 32 - subnet_mask); */
    vector<unsigned char> broadcast_id, network_id;
    network_id = get_network_id(ip, GET_SUBNET_MASK(class_net));
    broadcast_id = get_broadcast_id(network_id, subnet_mask);
    for(int i = 1; i <= subnets; i++){
        cout << "Subnet " << i << endl;
        cout << "Network id: " << get_string_ip(network_id) << endl;
        cout << "Broadcast id: " << get_string_ip(broadcast_id) << endl;
        cout << "Range of valid ip addresses are: " << "[" << \
            get_string_ip(network_id, 1) << ", " << get_string_ip(broadcast_id, -1) 
            << "]" << endl;
        network_id = increment_ip(broadcast_id);
        broadcast_id = get_broadcast_id(network_id, subnet_mask);
        cout << endl;
    }
}

vector<int> get_ip(string ip){
    vector<int> ip_address;
    int count = 0, sum = 0, num;
    for(auto i: ip){
        if(i == '.'){
            count++;
            if(count > 3){
                ip_address.clear();
                return ip_address;
            }
            ip_address.push_back(sum);
            sum = 0;
        }
        else if((num = i - '0') >= 0 && num <= 9){
            sum *= 10;
            sum += num;
        }
        else{
            ip_address.clear();
            return ip_address;
        }
        /* cout << sum << "\t" << count << endl; */
    }
    ip_address.push_back(sum);
    /* cout << count << endl; */
    if(count < 3){
        ip_address.clear();
    }
    /* cout << ip_address.size() << endl; */
    return ip_address;
}

bool check_ip(vector<int> ip, int class_net){
    vector<int> start, end;
    if(class_net == 1){
        start = START_SUBNET_MASKA;
        end = END_SUBNET_MASKA;
    }
    else if(class_net == 2){
        start = START_SUBNET_MASKB;
        end = END_SUBNET_MASKB;
    }
    else{
        start = START_SUBNET_MASKC;
        end = END_SUBNET_MASKC;
    }
    for(int i = 0; i < 4; i++){
        /* cout << ip[i] << "\t" << start[i] << "\t" << end[i] << endl; */
        if(ip[i] < start[i] || ip[i] > end[i]){
            return false;
        }
    }
    return true;
}
