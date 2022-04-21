# 写boot区，定位到磁盘开头，写1个块：512字节
dd if=boot.bin of=disk1.vhd bs=512 conv=notrunc count=1 

# 写loader区，定位到磁盘第2个块，写1个块：512字节
dd if=loader.bin of=disk1.vhd bs=512 conv=notrunc seek=1

# 写kernel区，定位到磁盘第100个块
dd if=kernel.elf of=disk1.vhd bs=512 conv=notrunc seek=100

# 写应用程序init，临时使用
#dd if=init.elf of=dis1.vhd bs=512 conv=notrunc seek=5000
dd if=shell.elf of=disk1.vhd bs=512 conv=notrunc seek=5000
