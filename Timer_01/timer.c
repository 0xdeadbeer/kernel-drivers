#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

MODULE_LICENSE("Dual BSD/GPL"); 

static struct timer_list my_timer;  

static void callback(struct timer_list *timer) {
    pr_info("Callback called!\n");
}

static int __init hello_init(void) {

    pr_info("Loading module..\n"); 

    // timer setup code 
    int seconds = 2; 
    
    timer_setup(&my_timer, callback, 0); 
    int ret = mod_timer(&my_timer, jiffies + msecs_to_jiffies(seconds * 1000));
    if (ret) {
        pr_err("%s: Timer firing failed\n", __func__);
        return 1; 
    } 

    pr_info("Module successfully finished it's tasks!\n");
    return 0; 
}

static void hello_exit(void) {
    pr_info("Unloading module..\n");

    int ret = del_timer(&my_timer); 
    if (ret) {
        pr_err("%s: The timer is still in use...\n", __func__);
        return ;
    }
    
    pr_info("Module successfully unloaded"); 
    
}

module_init(hello_init);
module_exit(hello_exit);