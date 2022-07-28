#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

const int major_number = 200; 
const int minor_number = 0; 

const char *module_name = "Chamu-r"; 
const char *module_code_name = "chamur";

dev_t dev = MKDEV(major_number, minor_number); 
unsigned int dev_count = 10; 

struct class *device_class; 

static int __init hello_init(void) {

    printk("Loading the %s module\n", module_name); 

    if (register_chrdev_region(dev, dev_count, module_code_name)) {
        printk(KERN_WARNING "[!!] Problem encountered while registring '%s' with the following numbers: (%d, %d) \n", module_code_name, major_number, minor_number);
        goto end; 
    }

    device_class = class_create(THIS_MODULE, module_code_name);

    printk(KERN_ALERT "[+] Successfully loaded '%s'\n", module_code_name);

    end:
        return 0; 
}

static void hello_exit(void) {
    printk("Unloading the %s module\n", module_name);

    class_destroy(device_class); 
    unregister_chrdev_region(dev, dev_count);

    printk(KERN_ALERT "[+] Successfully unloaded '%s'\n", module_code_name);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_AUTHOR("Osamu-KJ 2022"); 
MODULE_DESCRIPTION("Simple hello world module");
MODULE_LICENSE("GPL");