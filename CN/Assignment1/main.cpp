#include <iostream>
#include "ip.h"
#include "subnetmask.h"
#include "network_broadcast.h"

using namespace std;

int main(){
    int class_net;
    string ip_address;
    int subnet_mask;
    vector<int> ip;
    vector<unsigned char> ip1(4);
    while(1){
        cout << "\n-----------------------------------------------------\n";
        while(1){
            cout << "Choose the class\n";
            cout << "\t1. A\n\t2. B\n\t3. C\n";
            cin >> class_net;
            if(class_net != 1 && class_net != 2 && class_net != 3){
                cout << "\n!! Select valid option.\n";
            }
            else{
                break;
            }
            /* print_range_subnet_mask(class_net); */
        }
        cout << "-----------------------------------------------------\n";
        cout << "Enter the ip address in range: ";
        if(class_net == 1){
            cout << "[10.0.0.0, 10.255.255.255]" << endl;
        }
        else if(class_net == 2){
            cout << "[172.16.0.0, 172.31.255.255]" << endl;
        }
        else{
            cout << "[192.168.0.0, 192.168.255.255]" << endl;
        }
        while(1){
            cout << "\nEnter the ip address: ";
            cin >> ip_address;
            ip = get_ip(ip_address);
            if(ip.size() == 4){
                int i;
                for(i = 0; i < ip.size(); i++){
                    if(ip[i] > 255){
                        break;
                    }
                }
                if(i == ip.size()){
                    if(check_ip(ip, class_net)){
                        for(auto i = 0; i < ip.size(); i++){
                            ip1[i] = ip[i];
                        }
                        break;
                    }
                }
            }
            cout << "\n!! Enter valid ip address" << endl;
        }
        cout << "-----------------------------------------------------\n";
        while(1){
            cout << "Enter subnet mask number in the range: ";
            cout << "[" << GET_SUBNET_MASK(class_net) << ", " << \
                GET_SUBNET_MASK(class_net) + 5 << "]" << endl;
            cout << "\nEnter the subnet mask number: ";
            cin >> subnet_mask;
            if(check_subnet_mask(subnet_mask, class_net)){
                break;
            }
            cout << "\n!! Enter valid subnet mask\n" << endl;
        }

        cout << "\nNumber of subnets: " << get_no_of_subnet_mask(subnet_mask, class_net) \
            << endl;

        cout << "-----------------------------------------------------\n";
        print_ip_all_subnet(ip1, subnet_mask, class_net);
        cout << "-----------------------------------------------------\n";
        cout << "Do you want to continue\n\t1. Yes\n\t2. No" << endl;
        cin >> class_net;
        if(class_net != 1){
            break;
        }
    }
    return 0;
}
