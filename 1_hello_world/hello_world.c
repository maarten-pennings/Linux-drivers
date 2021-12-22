// hello_world.c - Simple hello world Linux driver
#include <linux/module.h>
#include <linux/init.h> // Needed for __init, __exit, module_init, module_exit

#define MOD_NAME "hello_world" 

static int __init mod_init(void)
{
	pr_info(MOD_NAME ": inserted successfully...\n");
	return 0;  // A non-zero return would mean that the module couldn't be loaded.
}

static void __exit mod_exit(void)
{
	pr_info(MOD_NAME ": removed successfully...\n");
}

module_init(mod_init); 
module_exit(mod_exit); 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maarten");
MODULE_DESCRIPTION("A 'hello world' Linux driver");
MODULE_VERSION("0:1.0");
