#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/timer.h>

static struct timer_list my_timer;  

static void callback(struct timer_list *timer) {
    pr_info("Callback called!\n");
}

static int __init init(void) {

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

static void __exit exit(void) {
    pr_info("Unloading module..\n");

    int ret = del_timer(&my_timer); 

    while (ret) {
        pr_err("%s: The timer is still in use...\n", __func__);
        int ret = del_timer(&my_timer); 
    }
     
    pr_info("Module successfully unloaded\n"); 
    
}

module_init(init);
module_exit(exit);
MODULE_AUTHOR("Osamu-KJ 2022");
MODULE_DESCRIPTION("Simple timer that will wait x seconds and then call a callback function"); 