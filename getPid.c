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
struct process_id* Proc_ID;

struct process_id{
	int init_pid;
	int this_pid;
	struct list_head pid;
};


/*Added this initialization*/
LIST_HEAD(pid);

static int getPid_read_proc(char *page, char **start, off_t off, int count, int *eof, void *data);
static int getPid_write_proc(struct file *file, const char *buf, unsigned long count, void *data);

static int getPid_read_proc(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	
}//end getPid_read_proc function


static int getPid_write_proc(struct file *file, const char *buf, unsigned long count, void *data)
{
}//end getPid_write_proc function

static int __init getPid_module_init(void){
	int rv = 0;
	struct process_id *new_process;
	proc_entry = create_proc_entry("getPid", 0766, NULL);
	if(proc_entry == NULL)
	{
		rv = -ENOMEM;
	}
	else
	{
		proc_entry->owner = THIS_MODULE;
		proc_entry->read_proc = getPid_read_proc;
		proc_entry->write_proc = getPid_write_proc;
		new_process = vmalloc(sizeof(*new_process));
		ProcID = new_process;
		procID->init_pid = 0;
		printk(KERN_INFO "=====getPid_module_init called. Module now loaded.\n");
	}
	return rv;
}

static void __exit getPid_module_cleanup(void){
	struct list_head *temp_pid;
	struct list_head *next;
	struct process_id *traverse_pid;

	printk(KERN_INFO "=====free the list\n");
	
	list_for_each_safe(temp_pid, next, &procID->pid){
		traverse_pid = list_entry(temp_pid, struct process_id, pid);
		printk(KERN_INFO "=====free pid: %d\n", traverse_pid->this_pid);
		list_del(temp_pid);
		vfree(traverse_pid);
	}
	
	//printk(KERN_INFO "=====free the procID\n");
	//vfree(procID);
	remove_proc_entry("getPid", proc_entry);
	printk(KERN_INFO "=====getPid_module_cleanup called. Module unloaded\n");
}

module_init(getPid_module_init);
module_exit(getPid_module_cleanup);

