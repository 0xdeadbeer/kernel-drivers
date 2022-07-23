#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h> 

MODULE_LICENSE("Dual BSD/GPL"); 

static int __init hello_init(void) {

    printk(KERN_ALERT "The module has been loaded\n"); 

    return 0; 
}

static void hello_exit(void) {
    printk(KERN_ALERT "The module has been unloaded!\n");
}

module_init(hello_init);
module_exit(hello_exit);