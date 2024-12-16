#include "actions.h"
float var1 = 0;

void action_var1plus(lv_event_t * e) {
    set_var_dht_var1();
    if(var1>5)loadScreen(2);
}

void set_var_dht_var1() {
    var1 = var1 + 1;
    printf("%f\n", var1);
}

float get_var_dht_var1() {
    return var1;
}
