/* SPDX-License-Identifier: LGPL-2.1 */
/*
 *
 *   Copyright (c) International Business Machines  Corp., 2002,2004
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 */
#include <linux/rbtree.h>

#ifndef _CIFS_FS_SB_H
#define _CIFS_FS_SB_H

#include <linux/backing-dev.h>

#define CIFS_MOUNT_NO_PERM      1 /* do not do client vfs_perm check */
#define CIFS_MOUNT_SET_UID      2 /* set current's euid in create etc. */
#define CIFS_MOUNT_SERVER_INUM  4 /* inode numbers from uniqueid from server  */
#define CIFS_MOUNT_DIRECT_IO    8 /* do not write nor read through page cache */
#define CIFS_MOUNT_NO_XATTR     0x10  /* if set - disable xattr support       */
#define CIFS_MOUNT_MAP_SPECIAL_CHR 0x20 /* remap illegal chars in filenames   */
#define CIFS_MOUNT_POSIX_PATHS  0x40  /* Negotiate posix pathnames if possible*/
#define CIFS_MOUNT_UNX_EMUL     0x80  /* Network compat with SFUnix emulation */
#define CIFS_MOUNT_NO_BRL       0x100 /* No sending byte range locks to srv   */
#define CIFS_MOUNT_CIFS_ACL     0x200 /* send ACL requests to non-POSIX srv   */
#define CIFS_MOUNT_OVERR_UID    0x400 /* override uid returned from server    */
#define CIFS_MOUNT_OVERR_GID    0x800 /* override gid returned from server    */
#define CIFS_MOUNT_DYNPERM      0x1000 /* allow in-memory only mode setting   */
#define CIFS_MOUNT_NOPOSIXBRL   0x2000 /* mandatory not posix byte range lock */
#define CIFS_MOUNT_NOSSYNC      0x4000 /* don't do slow SMBflush on every sync*/
#define CIFS_MOUNT_FSCACHE	0x8000 /* local caching enabled */
#define CIFS_MOUNT_MF_SYMLINKS	0x10000 /* Minshall+French Symlinks enabled */
#define CIFS_MOUNT_MULTIUSER	0x20000 /* multiuser mount */
#define CIFS_MOUNT_STRICT_IO	0x40000 /* strict cache mode */
#define CIFS_MOUNT_RWPIDFORWARD	0x80000 /* use pid forwarding for rw */
#define CIFS_MOUNT_POSIXACL	0x100000 /* mirror of SB_POSIXACL in mnt_cifs_flags */
#define CIFS_MOUNT_CIFS_BACKUPUID 0x200000 /* backup intent bit for a user */
#define CIFS_MOUNT_CIFS_BACKUPGID 0x400000 /* backup intent bit for a group */
#define CIFS_MOUNT_MAP_SFM_CHR	0x800000 /* SFM/MAC mapping for illegal chars */
#define CIFS_MOUNT_USE_PREFIX_PATH 0x1000000 /* make subpath with unaccessible
					      * root mountable
					      */
#define CIFS_MOUNT_UID_FROM_ACL 0x2000000 /* try to get UID via special SID */
#define CIFS_MOUNT_NO_HANDLE_CACHE 0x4000000 /* disable caching dir handles */
#define CIFS_MOUNT_NO_DFS 0x8000000 /* disable DFS resolving */
#define CIFS_MOUNT_MODE_FROM_SID 0x10000000 /* retrieve mode from special ACE */
#define CIFS_MOUNT_RO_CACHE	0x20000000  /* assumes share will not change */
#define CIFS_MOUNT_RW_CACHE	0x40000000  /* assumes only client accessing */
#define CIFS_MOUNT_SHUTDOWN	0x80000000

struct cifs_sb_info {
	struct rb_root tlink_tree;
	struct list_head tcon_sb_link;
	spinlock_t tlink_tree_lock;
	struct tcon_link *master_tlink;
	struct nls_table *local_nls;
	struct smb3_fs_context *ctx;
	atomic_t active;
	unsigned int mnt_cifs_flags;
	struct delayed_work prune_tlinks;
	struct rcu_head rcu;

	/* only used when CIFS_MOUNT_USE_PREFIX_PATH is set */
	char *prepath;

	/*
	 * Indicate whether serverino option was turned off later
	 * (cifs_autodisable_serverino) in order to match new mounts.
	 */
	bool mnt_cifs_serverino_autodisabled;
	/*
	 * Available once the mount has completed.
	 */
	struct dentry *root;
};
#endif				/* _CIFS_FS_SB_H */
