#!/bin/bash

echo "========== FILESYSTEM EXPLORATION =========="

echo
echo "[1] CURRENT DIRECTORY"
pwd

echo
echo "[2] CREATE DIRECTORY"
mkdir -p demo_fs/docs

echo
echo "[3] CREATE FILE"
echo "Hello Linux Filesystem" > demo_fs/file1.txt

echo
echo "[4] SHOW FILE CONTENT"
cat demo_fs/file1.txt

echo
echo "[5] COPY FILE"
cp demo_fs/file1.txt demo_fs/file2.txt

echo
echo "[6] MOVE FILE"
mv demo_fs/file2.txt demo_fs/docs/backup.txt

echo
echo "[7] SHOW FILE METADATA"
stat demo_fs/file1.txt

echo
echo "[8] CHANGE PERMISSION"
chmod 600 demo_fs/file1.txt

echo
echo "[9] CREATE HARDLINK"
ln demo_fs/file1.txt demo_fs/hardlink.txt

echo
echo "[10] CREATE SYMBOLIC LINK"
ln -s demo_fs/file1.txt demo_fs/symlink.txt

echo
echo "[11] SHOW INODE"
ls -li demo_fs

echo
echo "[12] DIRECTORY TREE"
tree demo_fs

echo
echo "[13] DISK USAGE"
du -sh demo_fs

echo
echo "[14] FILESYSTEM INFO"
df -h

echo
echo "[15] ACTIVE MOUNT"
mount | head

echo
echo "[16] FIND TXT FILE"
find demo_fs -name "*.txt"

echo
echo "[17] OPEN FILES"
lsof | head

echo
echo "[18] DELETE FILE"
rm demo_fs/docs/backup.txt

echo
echo "[19] FINAL STRUCTURE"
tree demo_fs

echo
echo "========== FINISHED =========="
