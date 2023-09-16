
#ifndef IP
#define IP

#include <vector>
#include <string>

using namespace std;


int a_raise_to_b(int a, int b);
vector<unsigned char> increment_ip(vector<unsigned char> ip);
void print_ip_all_subnet(vector<unsigned char> ip, int subnet_mask, int class_net);
vector<int> get_ip(string ip);
bool check_ip(vector<int> ip, int class_net);
string get_string_ip(vector<unsigned char> a, int extra);

#endif
