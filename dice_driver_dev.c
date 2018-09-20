#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/random.h>
#include <asm/uaccess.h>


static ssize_t dice_roll(struct file * file, char * buf, 
			  size_t count, loff_t *ppos)
{
	int random; 
	int length = 1;
	get_random_bytes(&random,sizeof(int));
	random = (random % 5) + 1;
	if (random < 0)
		random *= - 1;
	if (count < sizeof(int)) 
		return -EINVAL;
	if (*ppos != 0) 
		return 0;
	if (copy_to_user(buf, &random, sizeof(int)))
		return -EINVAL;
	*ppos = sizeof(int);
	return sizeof(int);
}


static const struct file_operations dice_fops = {
	.owner		= THIS_MODULE,
	.read		= dice_roll,
};


static struct miscdevice dice_driver_dev = {
	MISC_DYNAMIC_MINOR,
	"dice",
	&dice_fops
};

static int __init
dice_init(void)
{
	int ret;
	ret = misc_register(&dice_driver_dev);
	if (ret)
		printk(KERN_ERR
		       "Unable to register \"Dice Driver!\" misc device\n");

	return ret;
}

module_init(dice_init);

static void __exit
dice_exit(void)
{
	misc_deregister(&dice_driver_dev);
}

module_exit(dice_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sundar Sampath");
MODULE_DESCRIPTION("Dice Driver");
MODULE_VERSION("dev");
