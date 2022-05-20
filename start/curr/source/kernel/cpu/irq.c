#include "comm/cpu_instr.h"
#include "cpu/irq.h"
#include "cpu/cpu.h"
#include "os_cfg.h"

#define IDE_TABLE_NR        128

void exception_handler_unknown (void);

static gate_desc_t idt_table[IDE_TABLE_NR];

static void do_default_handler (exception_frame_t * frame, const char * message) {
    for (;;) {}
}

void do_handler_unknown (exception_frame_t * frame) {
    do_default_handler(frame, "unknown exception");
}

void do_handler_divider (exception_frame_t * frame) {
    do_default_handler(frame, "Divider exception");
}

void irq_init (void) {
    for (int i = 0; i < IDE_TABLE_NR; i++) {
        gate_desc_set(idt_table + i, KERNEL_SELECTOR_CS, (uint32_t)exception_handler_unknown, 
        GATE_P_PRESENT | GATE_DPL0 | GATE_TYPE_INT);
    }

    irq_install(IRQ0_DE, (irq_handler_t)exception_handler_divider);

    lidt((uint32_t)idt_table, sizeof(idt_table));
}

int irq_install (int irq_num, irq_handler_t handler) {
    if (irq_num >= IDE_TABLE_NR) {
        return -1;
    }

    gate_desc_set(idt_table + irq_num, KERNEL_SELECTOR_CS,
     (uint32_t)handler, GATE_P_PRESENT | GATE_DPL0 | GATE_TYPE_INT);
     return 0;
}