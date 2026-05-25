CFLAGS += -w
KBUILD_CFLAGS += -w
CC=gcc -w

# Build all hammer2 sources as a single multi-file module.
# Files that don't compile yet are commented out; uncomment as each
# is ported and starts building cleanly.
obj-m += hammer2.o
# Files that compile cleanly with the current shim layer.
# Move entries up from the "PENDING" block as each is ported.
hammer2-y := \
	hammer2_cluster.o \
	hammer2_admin.o \
	hammer2_subr.o \
	hammer2_lz4.o \
	hammer2_freemap.o \
	hammer2_chain.o \
	hammer2_xops.o \
	hammer2_flush.o \
	hammer2_bulkfree.o \
	hammer2_io.o \
	hammer2_ondisk.o \
	hammer2_ioctl.o \
	hammer2_strategy.o \
	hammer2_inode.o

# PENDING -- these need substantial Linux-native rewrites, not just shims:
#	hammer2_vfsops.o   (mount path: struct mount -> struct super_block,
#	                    file_system_type, fs_context, mount_bdev)
#	hammer2_vnops.o    (vnode ops: VOP_* -> struct file_operations /
#	                    inode_operations, dentry walk, page cache)

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
