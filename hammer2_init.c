/*
 * hammer2_init.c -- minimal module entry point for the Linux port of the
 * DragonFlyBSD HAMMER2 filesystem.
 *
 * The full Linux VFS wiring (struct file_system_type, mount/kill_sb,
 * file_operations / inode_operations / address_space_operations) lives in
 * hammer2_vnops.c, which is still pending rewrite.  Until that lands, this
 * file's only job is to satisfy modpost's MODULE_LICENSE requirement and
 * provide a no-op init/exit pair so the .ko links and loads.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

/* Provide concrete storage for the BSD-VFS extern symbols referenced by
 * hammer2_vnops.c's vop_vector initializers.  These are never invoked at
 * runtime until the Linux VFS dispatcher is wired up, so zero-init is OK. */
#include "hammer2.h"
#include "hammer2_bsdvfs.h"

const struct vop_vector default_vnodeops;
const struct vop_vector fifo_specops;
int vop_stdfdatasync_buf(struct vop_fsync_args *ap)
{
	(void)ap;
	return 0;
}
int hammer2_vop_panic(void *ap)
{
	(void)ap;
	pr_err("hammer2: VOP_PANIC slot invoked -- VFS dispatch not wired\n");
	return -EIO;
}

static int __init hammer2_module_init(void)
{
	pr_info("hammer2: module loaded (VFS dispatch not yet wired up)\n");
	return 0;
}

static void __exit hammer2_module_exit(void)
{
	pr_info("hammer2: module unloaded\n");
}

module_init(hammer2_module_init);
module_exit(hammer2_module_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("DragonFlyBSD HAMMER2 filesystem port");
MODULE_AUTHOR("HAMMER2 contributors");
