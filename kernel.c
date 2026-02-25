void kmain(void) {
    char *vga_buffer = (char*) 0xb8000;
    vga_buffer[0] = 'H';
    vga_buffer[1] = 0x0B;
    vga_buffer[2] = 'e';
    vga_buffer[3] = 0x0B;
    vga_buffer[4] = 'l';
    vga_buffer[5] = 0x0B;
    vga_buffer[6] = 'l';
    vga_buffer[7] = 0x0B;
    vga_buffer[8] = 'o';
    vga_buffer[9] = 0x0B;
    vga_buffer[10] = '_'; 
    vga_buffer[11] = 0x0B;
    vga_buffer[12] = 'W';
    vga_buffer[13] = 0x0B;
    vga_buffer[14] = 'o';
    vga_buffer[15] = 0x0B;
    vga_buffer[16] = 'r';
    vga_buffer[17] = 0x0B;
    vga_buffer[18] = 'l';
    vga_buffer[19] = 0x0B;
    vga_buffer[20] = 'd';
    vga_buffer[21] = 0x0B;
}
