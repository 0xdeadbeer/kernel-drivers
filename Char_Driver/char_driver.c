#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

const int major_number = 200; 
const int minor_number = 0; 

const char *module_name = "Chamu-r"; 
const char *module_code_name = "chamur";

dev_t dev = MKDEV(major_number, minor_number); 
unsigned int dev_count = 2;
struct file_operations fop; 
struct cdev *cdevice;
struct device *devicefs; 
struct class *device_class; 

// driver data
#define limit 1024
char user_data[limit];

static ssize_t chamur_read(struct file* file, char *buff, size_t len, loff_t *off) {
    
    if (len > limit*sizeof(char)) return 0; 

    copy_to_user(buff, user_data, len);
    
    printk("TRYING TO READ YK");

    return len; 
}

static ssize_t chamur_write(struct file* file, const char *buff, size_t len, loff_t *off) {

    if (len > limit) return 0; // big problem 

    copy_from_user(&user_data, buff, len);

    return len; 
}

static int chamur_open(struct inode* inode, struct file *file) {
    printk("AYO IM OPENING BRO~\n");
    return 0; 
}

static int chamur_release(struct inode* inode, struct file *file) {
    printk("AYO IM CLOSING BRO~\n");
    return 0; 
}

static int __init chamur_init(void) {

    int ret; 

    printk("Loading the %s module\n", module_name); 

    // setup the fop struct 
    fop.owner = THIS_MODULE; 
    fop.read = &chamur_read; 
    fop.write = &chamur_write; 
    fop.open = &chamur_open; 
    fop.release = &chamur_release; 

    ret = register_chrdev_region(dev, dev_count, module_code_name);

    if (IS_ERR(ret)) {
        printk(KERN_WARNING "[!!] Problem encountered while registring '%s' with the following numbers: (%d, %d) \n", module_code_name, major_number, minor_number);
        return ret;
    }

    // allocate char device 
    cdevice = cdev_alloc(); 

    // initialize char device with the file operations structure 
    cdev_init(cdevice, &fop);

    // set the owner value 
    cdevice->owner = THIS_MODULE; 

    // add a char device to the system
    ret = cdev_add(cdevice, dev, 1); 

    if (IS_ERR(ret)) {
        printk(KERN_WARNING "[!!] Problem encountered while initializing the cdev structure\n");
        return ret; 
    }

    // make a class for the device 
    device_class = class_create(THIS_MODULE, module_code_name); 

    // register the device with sysfs 
    devicefs = device_create(device_class, NULL, dev, NULL, module_code_name); 

    printk(KERN_ALERT "[+] Successfully loaded '%s'\n", module_code_name);

    end:
        return 0; 
}

static void chamur_exit(void) {
    printk("Unloading the %s module\n", module_name);

    // remove the device from the sysfs 
    device_destroy(device_class, dev); 

    // destroy the class 
    class_destroy(device_class);

    // delete the cdev structure from the system 
    cdev_del(cdevice); 

    unregister_chrdev_region(dev, dev_count);

    success: 
        printk(KERN_ALERT "[+] Successfully unloaded '%s'\n", module_code_name);
}

module_init(chamur_init);
module_exit(chamur_exit);
MODULE_AUTHOR("Osamu-KJ 2022"); 
MODULE_DESCRIPTION("Simple hello world module");
MODULE_LICENSE("GPL");