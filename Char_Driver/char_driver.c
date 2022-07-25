#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>

dev_t dev; 
unsigned int dev_count = 10; 

static int __init hello_init(void) {

    printk(KERN_ALERT "The module has been loaded\n"); 

    if (alloc_chrdev_region(&dev, 1, dev_count, "gang_shit")) {
        printk(KERN_ALERT "BIG PROBLEMOO!!!\n");
        goto end; 
    }

    printk(KERN_ALERT "Well that worked!!\n");
    
    end:
        return 0; 
}

static void hello_exit(void) {
    printk(KERN_ALERT "The module has been unloaded!\n");

    unregister_chrdev_region(dev, dev_count);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_AUTHOR("Osamu-KJ 2022"); 
MODULE_DESCRIPTION("Simple hello world module");