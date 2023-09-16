#include "ip.h"
#include "subnetmask.h"

int get_no_of_subnet_mask(int subnet_mask, int class_net){
    return a_raise_to_b(2, subnet_mask - GET_SUBNET_MASK(class_net));
}

bool check_subnet_mask(int subnet_mask, int class_net){
    return subnet_mask >= GET_SUBNET_MASK(class_net) && \
                          subnet_mask <= GET_SUBNET_MASK(class_net) + 5;
}
