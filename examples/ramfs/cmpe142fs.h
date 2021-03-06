#ifndef _LINUX_RAMFS_H
#define _LINUX_RAMFS_H

struct inode *cmpe142_get_inode(struct super_block *sb, const struct inode *dir,
	 umode_t mode, dev_t dev);
extern struct dentry *cmpe142_mount(struct file_system_type *fs_type,
	 int flags, const char *dev_name, void *data);

#ifndef CONFIG_MMU
extern int cmpe142_nommu_expand_for_mapping(struct inode *inode, size_t newsize);
extern unsigned long cmpe142_nommu_get_unmapped_area(struct file *file,
						   unsigned long addr,
						   unsigned long len,
						   unsigned long pgoff,
						   unsigned long flags);

extern int cmpe142_nommu_mmap(struct file *file, struct vm_area_struct *vma);
#endif

extern const struct file_operations cmpe142_file_operations;
extern const struct vm_operations_struct generic_file_vm_ops;
extern int __init init_rootfs(void);

int cmpe142_fill_super(struct super_block *sb, void *data, int silent);

#endif
