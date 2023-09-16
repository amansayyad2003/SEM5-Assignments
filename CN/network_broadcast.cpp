#include "ip.h"
#include <iostream>

using namespace std;

vector<unsigned char> get_subnet_mask(int a){
    vector<unsigned char> sm;
    int num = 255;
    while(a > 0){
        if(a < 8){
            num = 0;
            for(int i = a; i >= 1; i--){
                num += a_raise_to_b(2, 8 - i);
            }
        }
       sm.push_back(num);
       a -= 8;
    }
    while(sm.size() < 4){
        sm.push_back(0);
    }

    cout << endl;
    return sm;
}

vector<unsigned char> get_network_id(vector<unsigned char> &ip, int subnet_mask){
     vector<unsigned char> Subnet_mask = get_subnet_mask(subnet_mask);
     vector<unsigned char> network_id(4);
     for(auto i = 0; i < ip.size(); i++){
         network_id[i] = ip[i] & Subnet_mask[i];
     }
     return network_id;
 }
 
 
 vector<unsigned char> get_broadcast_id(vector<unsigned char> &ip, int subnet_mask){
     vector<unsigned char> Subnet_mask = get_subnet_mask(subnet_mask);
     vector<unsigned char> broad_cast(4);
     for(auto i = 0; i < ip.size(); i++){
         broad_cast[i] = ~Subnet_mask[i];
         broad_cast[i] |= ip[i];
     }
     return broad_cast;
 }
