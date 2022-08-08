/*
 * $Id: hello.c,v 1.5 2004/10/26 03:32:21 corbet Exp $ 
 */
// https://github.com/hansonchar/ldd3
// Chapter 2 p.16 of https://lwn.net/Kernel/LDD3/
#include <linux/init.h>
#include <linux/module.h>

// Chapter 2 p.22
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");

// Example: insmod hello howmany=10 whom="Mom"
static char *whom = "world";
static int howmany = 1;
module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO);

// Why __init (which is optional)?
// The module loader drops the initialization function
// after the module is loaded, making its memory available for other uses.
static int __init hello_init(void)
{
    int i;
    for (i=0; i < howmany; i++) {
        printk(KERN_ALERT "Hello, %s for %d\n", whom, i);
    }
    // Chapter 2 p.22
    printk(KERN_INFO "The process is \"%s\" (pid %i)\n",
             current->comm, current->pid);
    return 0;
}

// The __exit modifier marks the code as being for module unload only
// (by causing the compiler to place it in a special ELF section).
static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
    // Chapter 2 p.22
    printk(KERN_INFO "The process is \"%s\" (pid %i)\n",
             current->comm, current->pid);
}

module_init(hello_init);
module_exit(hello_exit);
