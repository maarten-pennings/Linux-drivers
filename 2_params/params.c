// params.c - Linux driver with parameters
#include<linux/module.h>
#include<linux/init.h>
#include<linux/moduleparam.h>

#define MOD_NAME "params" 

// permission macros: S_I (W|R|X) (USR|GRP)
int param_int;
module_param(param_int, int, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP );
MODULE_PARM_DESC(param_int, "An integer parameter");

char *param_charp;
module_param(param_charp, charp, S_IWUSR | S_IRUSR );
MODULE_PARM_DESC(param_charp, "A string parameter");

int param_short;
module_param(param_short, int, 0 ); // access is 0
MODULE_PARM_DESC(param_short, "An short parameter");

bool param_bools[4];   // module_param_array computes the array size itself
int param_bools_count; // when we pass NULL for &param_bools_count, user can still write 4 or less, but we don't know
module_param_array(param_bools, bool, &param_bools_count, S_IWUSR | S_IRUSR ); 
MODULE_PARM_DESC(param_bools, "A boolean array of size 4");

static int __init mod_init(void)
{
	param_int = 7; // some funny initial value
	pr_info(MOD_NAME ": inserted successfully...\n");
	return 0;  // A non-zero return would mean that the module couldn't be loaded.
}

static void __exit mod_exit(void)
{
	int ix;
	pr_info(MOD_NAME ": param_int = %d\n", param_int);
	pr_info(MOD_NAME ": param_short = %hd\n", param_short);
	pr_info(MOD_NAME ": param_charp = \"%s\"\n", param_charp);
	pr_info(MOD_NAME ": param_bools_count = %d\n", param_bools_count);
	for( ix=0; ix<param_bools_count; ix++ ) 
		pr_info(MOD_NAME ": param_bool[%d]=%d\n", ix,param_bools[ix]);
	pr_info(MOD_NAME ": removed successfully...\n");
}
 
module_init(mod_init);
module_exit(mod_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maarten");
MODULE_DESCRIPTION("A Linux driver with parameters");
MODULE_VERSION("0:1.0");
