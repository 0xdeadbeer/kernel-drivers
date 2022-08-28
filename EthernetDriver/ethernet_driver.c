#include <linux/init.h>
#include <linux/module.h>
#include <linux/etherdevice.h>
#include <linux/netdevice.h>

struct net_device *netdev; 

static int netdev_open(struct net_device *dev) {
  printk("SUP");
  return 0; 
}

static int netdev_close(struct net_device *dev) {
  printk("AYO SUP");
  return 0; 
}

static netdev_tx_t netdev_transfer(struct sk_buff *skb, struct net_device *netdev) {


  return NETDEV_TX_OK; 
}

static const struct net_device_ops netdev_ops = {
  .ndo_open = netdev_open, 
  .ndo_stop = netdev_close,
  .ndo_start_xmit = netdev_transfer,
};

static void netdev_init(struct net_device *dev) {


  ether_setup(dev);
  dev->netdev_ops = &netdev_ops; 

  dev->flags |= IFF_NOARP; 
  dev->features |= NETIF_F_HW_CSUM;
}

static int __init ether_init(void) {
  int result = 0; 
  printk("LOADING THE MODULE!\n");
  char *mask = "kinterface%d";

  netdev = alloc_netdev(0, mask, NET_NAME_UNKNOWN, netdev_init); 

  result = register_netdev(netdev); 

  end: 
    return 0;
}

static void ether_exit(void) { 
  printk("UNLOADING THE MODULE!\n");

  unregister_netdev(netdev);
  free_netdev(netdev);
}

module_init(ether_init);
module_exit(ether_exit);
MODULE_LICENSE("GPL v2");