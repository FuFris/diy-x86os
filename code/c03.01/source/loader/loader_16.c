/**
 * 自己动手写操作系统
 *
 * 16位引导代码
 * 二级引导，负责进行硬件检测，进入保护模式，然后加载内核，并跳转至内核运行
 *
 * 创建时间：2021年8月5日
 * 作者：李述铜
 * 联系邮箱: 527676163@qq.com
 */

// 16位代码，必须加上放在开头，以便有些io指令生成为32位
__asm__(".code16gcc");

/**
 * BIOS下显示字符串
 * @param msg
 */
static void show_msg (const char * msg) {
	char c;

	// 使用bios写显存，持续往下写
	// 参考资料：https://blog.csdn.net/qq_40169767/article/details/101511805
	while ((c = *msg++) != '\0') {
		__asm__ __volatile__(
				"mov $0xe, %%ah\n\t"
				"mov %0, %%al\n\t"
				"mov $0x3, %%bx\n\t"
				"int $0x10"::"r"(c));
	}
}

void loader_entry(void) {
    show_msg("....loading.....");
    for(;;) {}
}


