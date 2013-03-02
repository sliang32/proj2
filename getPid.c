#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <asm/uaccess.h>
#include <asm/current.h>
#include <linux/cdev.h>
#include <linux/rcupdate.h>

static struct proc_dir_entry *proc_entry;

static int getPid_read_proc(char *page, char **start, off_t off, int count, int *eof, void *data);

static int getPid_read_proc(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int length = sprintf(page, "sys_brk_total:  %llu\n"
				   "do_fork_total:  %llu\n"
				   "sys_exit_total: %llu\n", current->sys_brk_total, current->do_fork_total, current->sys_exit_total);
  	return length;
}//end getPid_read_proc function

static int __init getPid_module_init(void){
	int rv = 0;
	proc_entry = create_proc_entry("getPid", 0766, NULL);
	if(proc_entry == NULL)
	{
		rv = -ENOMEM;
	}
	else
	{
		proc_entry->owner = THIS_MODULE;
		proc_entry->read_proc = getPid_read_proc;
		printk(KERN_INFO "=====getPid_module_init called. Module now loaded.\n");
	}
	return rv;
}

static void __exit getPid_module_cleanup(void){
	
	remove_proc_entry("getPid", proc_entry);
	printk(KERN_INFO "=====getPid_module_cleanup called. Module unloaded\n");
}

module_init(getPid_module_init);
module_exit(getPid_module_cleanup);

