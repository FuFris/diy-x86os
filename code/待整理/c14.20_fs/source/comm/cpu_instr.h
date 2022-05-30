/**
 * 汇编指令的封装
 *
 * 创建时间：2021年8月5日
 * 作者：李述铜
 * 联系邮箱: 527676163@qq.com
 */
#ifndef CPU_INSTR_H
#define CPU_INSTR_H

#include "types.h"

static inline uint8_t inb(uint16_t  port) {
	uint8_t rv;
	__asm__ __volatile__("inb %1, %0" : "=a" (rv) : "dN" (port));
	return rv;
}

static inline uint16_t inw(uint16_t  port) {
	uint16_t rv;
	__asm__ __volatile__("in %1, %0" : "=a" (rv) : "dN" (port));
	return rv;
}

static inline void insw(uint16_t port, const uint16_t * data, uint32_t cnt) {
   __asm__ __volatile__("cld; rep insw" : "+D" (data), "+c" (cnt) : "d" (port) : "memory");
}

static inline void outb(uint16_t port, uint8_t data) {
	__asm__ __volatile__("outb %1, %0" : : "dN" (port), "a" (data));
}

static inline void outsw(uint16_t port, const uint16_t * data, uint32_t cnt) {
   __asm__ __volatile__ ("cld; rep outsw" : "+S" (data), "+c" (cnt) : "d" (port));
}

static inline void cli() {
	__asm__ __volatile__("cli");
}

static inline void sti() {
	__asm__ __volatile__("sti");
}

static inline void lgdt(uint32_t start, uint32_t size) {
	struct {
		uint16_t limit;
		uint16_t start15_0;
		uint16_t start31_16;
	} gdt;

	gdt.start31_16 = start >> 16;
	gdt.start15_0 = start & 0xFFFF;
	gdt.limit = size - 1;

	__asm__ __volatile__("lgdt %0"::"m"(gdt));
}

static inline uint32_t read_cr0() {
	uint32_t cr0;
	__asm__ __volatile__("mov %%cr0, %0":"=r"(cr0));
	return cr0;
}

static inline void write_cr0(uint32_t v) {
	__asm__ __volatile__("mov %0, %%cr0"::"r"(v));
}

static inline void write_cr3(uint32_t v) {
	__asm__ __volatile__("mov %0, %%cr3"::"r"(v));
}

static inline uint32_t read_cr3() {
	uint32_t cr3;
	__asm__ __volatile__("mov %%cr3, %0":"=r"(cr3));
	return cr3;
}

static inline uint32_t read_cr4() {
	uint32_t cr4;
	__asm__ __volatile__("mov %%cr4, %0":"=r"(cr4));
	return cr4;
}

static inline void write_cr4(uint32_t v) {
	__asm__ __volatile__("mov %0, %%cr4"::"r"(v));
}

static inline void far_jump(uint32_t selector, uint32_t offset) {
	uint32_t addr[] = {offset, selector };
	__asm__ __volatile__("ljmpl *(%0)"::"r"(addr));
}

static inline void lidt(uint32_t start, uint32_t size) {
	struct {
		uint16_t limit;
		uint16_t start15_0;
		uint16_t start31_16;
	} idt;

	idt.start31_16 = start >> 16;
	idt.start15_0 = start & 0xFFFF;
	idt.limit = size - 1;

	__asm__ __volatile__("lidt %0"::"m"(idt));
}

static inline void hlt(void) {
    __asm__ __volatile__("hlt");
}

static inline void write_tr (uint32_t tss_selector) {
    __asm__ __volatile__("ltr %%ax"::"a"(tss_selector));
}

static inline uint32_t read_eflags (void) {
    uint32_t eflags;

    __asm__ __volatile__("pushfl\n\tpopl %%eax":"=a"(eflags));
    return eflags;
}

static inline void write_eflags (uint32_t eflags) {
    __asm__ __volatile__("pushl %%eax\n\tpopfl"::"a"(eflags));
}

#endif
