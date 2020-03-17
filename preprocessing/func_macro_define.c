//
// Created by guangsujiqiang on 3/17/20.
//

#define device_init_wakeup(dev,val) device_can_wakeup(dev) = !!(val); device_set_wakeup_enable(dev,val);
if (n > 0)
device_init_wakeup(d, v);