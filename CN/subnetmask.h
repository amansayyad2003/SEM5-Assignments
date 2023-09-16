
#ifndef SUBNETMASK 
#define SUBNETMASK

#include <vector>

using namespace std;

#define CLASS_A_SUBNET_MASK     8
#define CLASS_B_SUBNET_MASK     16
#define CLASS_C_SUBNET_MASK     24

#define GET_SUBNET_MASK(CLASS)  ((CLASS == 1)? CLASS_A_SUBNET_MASK : \
                                (CLASS == 2)? CLASS_B_SUBNET_MASK : \
                                CLASS_C_SUBNET_MASK)

#define GET_NO_OF_BYTES(CLASS)     (CLASS == 1)? 1 : (CLASS == 2) ? 2 : 3


bool check_subnet_mask(int subnet_mask, int class_net);
int get_no_of_subnet_mask(int subnet_mask, int class_net);

#endif
