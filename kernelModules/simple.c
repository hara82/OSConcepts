#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/jiffies.h>

/*This function is called when the module is loaded.*/
int num_interrupt;
int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n"); // printfのkernel version. kernel 空間だから、printf is not possible. KERN_INFOはprint内容の重大性を示すpriority flag.

    /*additional project 1*/
    printk(KERN_INFO "hash constant:%lu\n",GOLDEN_RATIO_PRIME);
	printk(KERN_INFO "number of interrupt:%lu\n",jiffies);
	printk(KERN_INFO "tick rate:%d\n",HZ);
	num_interrupt = jiffies;
    return 0;
}

/*This function is called when the module is removed.*/
void simple_exit(void)
{
    printk(KERN_INFO "Removing Module\n");
    /*additional project 2*/
    printk(KERN_INFO "%lu\n", gcd((unsigned long)3300, (unsigned)24));
	printk("number of interrupt:%lu\n",jiffies);
    /*kernelが何秒間ロードされていたか*/
	num_interrupt = jiffies - num_interrupt;
	printk("This module was loaded for %d seconds\n",num_interrupt/HZ);
}

/*Macros for registering module entry and exit points.*/
module_init(simple_init);//entryポイントの指定。エントリポイントというのは、c言語のmain関数みたいに、最初に実行されるもののこと。
module_exit(simple_exit); // exit pointはentry pointの反対で、終了時に実行される。

/*Below are included as a standard practice in developing kernel modules.*/
MODULE_LICENSE("GPL"); //represent details regarding the software license
MODULE_DESCRIPTION("Simple Module"); //software description
MODULE_AUTHOR("SGG"); //author
