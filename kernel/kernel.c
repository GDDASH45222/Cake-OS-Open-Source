// CASM/kernel/kernel.c

typedef unsigned short uint16_t;

#define VGA_MEMORY ((uint16_t*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static int cursor_x = 0;
static int cursor_y = 0;

void clear_screen()
{
    for(int y = 0; y < VGA_HEIGHT; y++)
    {
        for(int x = 0; x < VGA_WIDTH; x++)
        {
            VGA_MEMORY[y * VGA_WIDTH + x] = 0x0720;
        }
    }

    cursor_x = 0;
    cursor_y = 0;
}

void putchar(char c)
{
    if(c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    VGA_MEMORY[cursor_y * VGA_WIDTH + cursor_x] =
        (uint16_t)c | 0x0700;

    cursor_x++;

    if(cursor_x >= VGA_WIDTH)
    {
        cursor_x = 0;
        cursor_y++;
    }
}

void print(const char* str)
{
    while(*str)
    {
        putchar(*str);
        str++;
    }
}

void kernel_main()
{
    clear_screen();

    print("Cake OS Kernel v0.1\n");
    print("Starting system...\n");
    print("Hello from kernel.c!");

    while(1)
    {
        asm volatile("hlt");
    }
}
