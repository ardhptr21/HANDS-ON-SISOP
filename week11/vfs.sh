#!/bin/bash

echo "========== VIRTUAL FILESYSTEM EXPLORATION =========="

echo
echo "[1] CPU INFORMATION"
head -5 /proc/cpuinfo

echo
echo "[2] MEMORY INFORMATION"
head -5 /proc/meminfo

echo
echo "[3] SYSTEM UPTIME"
cat /proc/uptime

echo
echo "[4] MOUNTED FILESYSTEM"
mount | head

echo
echo "[5] AVAILABLE FILESYSTEM TYPES"
cat /proc/filesystems

echo
echo "[6] CURRENT PROCESS STATUS"
cat /proc/self/status | head

echo
echo "[7] FILE DESCRIPTORS"
ls -l /proc/self/fd

echo
echo "[8] DEVICE FILES"
ls -l /dev/null
ls -l /dev/zero
ls -l /dev/random

echo
echo "[9] WRITE TO /dev/null"
echo "THIS WILL DISAPPEAR" > /dev/null

echo "Data written to /dev/null"

echo
echo "[10] READ RANDOM DATA"
head -c 20 /dev/urandom

echo
echo
echo "[11] NETWORK INTERFACE"
ls /sys/class/net

echo
echo "[12] BLOCK DEVICES"
ls /sys/block

echo
echo "[13] PROCESS ENVIRONMENT"
cat /proc/self/environ | tr '\0' '\n' | head

echo
echo "========== FINISHED =========="
