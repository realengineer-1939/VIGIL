struct gdt_entry {
    unsigned short limit_low;   /* First part of the zone size */
    unsigned short base_low;    /* First part of the start address */
    unsigned char base_middle;  /* Middle part of the start address */
    unsigned char access;       /* SECURITY KEY: 0x9A for V-Core, 0xFA for Nodes */
    unsigned char granularity;  /* Defines if we measure in Bytes or 4KB Blocks */
    unsigned char base_high;    /* Last part of the start address */
} __attribute__((packed));      /* means: don't add extra space between variables */

struct gdt_ptr {
    unsigned short limit;       /* Total size of the table */
    unsigned int base;          /* The mem address of the table */
} __attribute__((packed));      

// Creating three slots: 0 = Null, 1 = Code, 2 = Data
struct gdt_entry gdt[3];
struct gdt_ptr gp;

void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

extern void gdt_flush(); // this assembly function will live in another file

void gdt_install() {
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (unsigned int)&gdt;

    // 1. NULL SEGMENT: Hardware requirement
    gdt_set_gate(0, 0, 0, 0, 0);

    // 2. V-Core Code: Covers 4GB of RAM(0x9A: switch for Present, Ring 0, Executable
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // 3. V-Core Data: Covers 4GB of RAM(0x92 is the switch for: Present, Ring 0 Read/Write
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_flush();
}

void kmain(void) {
    // Initialize shield
    gdt_install();
    
    // cute little message lol
    char *vga_buffer = (char*) 0xb8000;
    char *msg = "V-CORE: NEURAL-CACHE ACTIVE";

    for(int i = 0; msg[i] != '\0'; i++) {
        vga_buffer[i * 2] = msg[i];
        vga_buffer[i * 2 + 1] = 0x0B;
    }

    while(1);
}
