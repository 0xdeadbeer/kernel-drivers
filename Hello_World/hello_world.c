#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void) {

    printk(KERN_ALERT "The module has been loaded\n"); 

    return 0; 
}

static void hello_exit(void) {
    printk(KERN_ALERT "The module has been unloaded!\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_AUTHOR("Osamu-KJ 2022"); 
MODULE_DESCRIPTION("Simple hello world module");