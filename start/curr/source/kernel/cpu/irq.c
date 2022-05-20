#include "comm/cpu_instr.h"
#include "cpu/irq.h"
#include "cpu/cpu.h"
#include "os_cfg.h"

#define IDE_TABLE_NR        128

void exception_handler_unknown (void);

static gate_desc_t idt_table[IDE_TABLE_NR];

static void do_default_handler (exception_frame_t * frame, const char * message) {
    for (;;) {
        hlt();
    }
}

void do_handler_unknown (exception_frame_t * frame) {
    do_default_handler(frame, "unknown exception");
}

void do_handler_divider (exception_frame_t * frame) {
    do_default_handler(frame, "Divider exception");
}

void do_handler_Debug (exception_frame_t * frame) {
    do_default_handler(frame, "Debug exception");
}

void do_handler_NMI (exception_frame_t * frame) {
    do_default_handler(frame, "NMI exception");
}
void do_handler_breakpoint (exception_frame_t * frame) {
    do_default_handler(frame, "breakpoint exception");
}
void do_handler_overflow (exception_frame_t * frame) {
    do_default_handler(frame, "overflow exception");
}
void do_handler_bound_range (exception_frame_t * frame) {
    do_default_handler(frame, "bound range exception");
}
void do_handler_invalid_opcode (exception_frame_t * frame) {
    do_default_handler(frame, "invalid opcode exception");
}
void do_handler_device_unavabliable (exception_frame_t * frame) {
    do_default_handler(frame, "device unavabliable exception");
}
void do_handler_double_fault (exception_frame_t * frame) {
    do_default_handler(frame, "double fault exception");
}
void do_handler_invalid_tss (exception_frame_t * frame) {
    do_default_handler(frame, "invalid tss exception");
}
void do_handler_segment_not_present (exception_frame_t * frame) {
    do_default_handler(frame, "segment not present exception");
}
void do_handler_stack_segment_fault (exception_frame_t * frame) {
    do_default_handler(frame, "stack segment fault exception");
}
void do_handler_general_protection (exception_frame_t * frame) {
    do_default_handler(frame, "general protection exception");
}
void do_handler_page_fault (exception_frame_t * frame) {
    do_default_handler(frame, "page fault exception");
}
void do_handler_fpu_error (exception_frame_t * frame) {
    do_default_handler(frame, "fpu error exception");
}
void do_handler_aligment_check (exception_frame_t * frame) {
    do_default_handler(frame, "aligment check exception");
}
void do_handler_machine_check (exception_frame_t * frame) {
    do_default_handler(frame, "machine check exception");
}
void do_handler_simd_exception (exception_frame_t * frame) {
    do_default_handler(frame, "simd excetpion exception");
}
void do_handler_virtual_exception (exception_frame_t * frame) {
    do_default_handler(frame, "virtual exception exception");
}
void do_handler_control_exception (exception_frame_t * frame) {
    do_default_handler(frame, "control exception exception");
}

void irq_init (void) {
    for (int i = 0; i < IDE_TABLE_NR; i++) {
        gate_desc_set(idt_table + i, KERNEL_SELECTOR_CS, (uint32_t)exception_handler_unknown, 
        GATE_P_PRESENT | GATE_DPL0 | GATE_TYPE_INT);
    }

    irq_install(IRQ0_DE, (irq_handler_t)exception_handler_divider);
    irq_install(IRQ1_DB, (irq_handler_t)exception_handler_Debug);
    irq_install(IRQ2_NMI, (irq_handler_t)exception_handler_NMI);
    irq_install(IRQ3_BP, (irq_handler_t)exception_handler_breakpoint);
    irq_install(IRQ4_OF, (irq_handler_t)exception_handler_overflow);
    irq_install(IRQ5_BR, (irq_handler_t)exception_handler_bound_range);
    irq_install(IRQ6_UD, (irq_handler_t)exception_handler_invalid_opcode);
    irq_install(IRQ7_NM, (irq_handler_t)exception_handler_device_unavabliable);
    irq_install(IRQ8_DF, (irq_handler_t)exception_handler_double_fault);
    irq_install(IRQ10_TS, (irq_handler_t)exception_handler_invalid_tss);
    irq_install(IRQ11_NP, (irq_handler_t)exception_handler_segment_not_present);
    irq_install(IRQ12_SS, (irq_handler_t)exception_handler_stack_segment_fault);
    irq_install(IRQ13_GP, (irq_handler_t)exception_handler_general_protection);
    irq_install(IRQ14_PF, (irq_handler_t)exception_handler_page_fault);
    irq_install(IRQ16_MF, (irq_handler_t)exception_handler_fpu_error);
    irq_install(IRQ18_MC, (irq_handler_t)exception_handler_machine_check);
    irq_install(IRQ19_XM, (irq_handler_t)exception_handler_simd_exception);
    irq_install(IRQ20_VE, (irq_handler_t)exception_handler_virtual_exception);
    irq_install(IRQ21_CP, (irq_handler_t)exception_handler_control_exception);

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