# 1 Hello world 
Inspiration from [The Linux Kernel Module Programming Guide](https://sysprog21.github.io/lkmpg/)
and [embetronicx](https://embetronicx.com/linux-device-driver-tutorials/),
[module](https://embetronicx.com/tutorials/linux/device-drivers/linux-device-driver-tutorial-part-2-first-device-driver/).

## Building
 - get kernel headers `sudo apt-get install raspberrypi-kernel-headers`
 - make with `sudo make`
 
## Test inserting
```
$ dmesg
...
[   93.282533] Bluetooth: RFCOMM socket layer initialized
[   93.282568] Bluetooth: RFCOMM ver 1.11
$ sudo insmod hello_world.ko
$ dmesg
...
[   93.282533] Bluetooth: RFCOMM socket layer initialized
[   93.282568] Bluetooth: RFCOMM ver 1.11
[10360.945237] hello_world: kernel module inserted successfully...
```

## Test sys
After adding a kernel module it appears in `/proc/modules`

```
$ sudo cat /proc/modules | grep hello
hello_world 16384 0 - Live 0x7f500000 (O)
```

Each module has aspects of it mapped into the file system at `/sys/module`

```
$ ls -d /sys/module/h*
/sys/module/hci_uart  /sys/module/hello_world  /sys/module/hid
```

An obvious one is the module version

```
$ ls /sys/module/hello_world/
coresize  initsize   notes   sections    taint   version
holders   initstate  refcnt  srcversion  uevent
$ cat /sys/module/hello_world/version
0:1.0
```

## Test removing
```
$ dmesg
...
[   93.282533] Bluetooth: RFCOMM socket layer initialized
[   93.282568] Bluetooth: RFCOMM ver 1.11
[10360.945237] hello_world: kernel module inserted successfully...
$ sudo rmmod hello_world.ko
$ dmesg
...
[   93.282533] Bluetooth: RFCOMM socket layer initialized
[   93.282568] Bluetooth: RFCOMM ver 1.11
[10360.945237] hello_world: kernel module inserted successfully...
[10553.446665] hello_world: kernel module removed successfully...
```

## Observations

### init/exit

In the past, a typical kernel module had

```
#include <linux/module.h>

int  init_module   (void) { ... }
void cleanup_module(void) { ... }
```

but it seems that we the preferred way these days is

```
#include <linux/module.h>
#include <linux/init.h> // Needed for __init, __exit, module_init, module_exit

static int  __init mod_init(void) { ... }
static void __exit mod_exit(void) { ... {
 
module_init(mod_init);
module_exit(mod_exit);
```

where the function names `mod_init` and `mod_exit` are free and their scope `static`.

### printk

In the past, we saw calls to `printk`
```
  printk(KERN_INFO  "text\n" );
```

but that is simplified to

```
  pr_info("text\n");
```

(end)

