
#ifndef NETWORK_BROADCAST
#define NETWORK_BROADCAST

#include <vector>

using namespace std;

vector<unsigned char> get_subnet_mask(int a);
vector<unsigned char> get_network_id(vector<unsigned char> &ip, int subnet_mask);
vector<unsigned char> get_broadcast_id(vector<unsigned char> &ip, int subnet_mask);

#endif
