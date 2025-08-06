#include<stdio.h>
#include<stdint.h>

#define OFF_SIZE 16

/* Display each byte of 'data' and 'off' in hex. */
void printData(const unsigned char *data, const uint32_t off, size_t nbytes) {
    /* Print offset in 8 digits. */
    fprintf(stdout, "%08X", off);
    printf("  "); 

    /* Print every byte in Hexadecimal. */
    for (int i = 0; i < OFF_SIZE; i++) {
        if (i < nbytes) printf("%02X ", *((uint8_t *)&data[i])); 
        else printf("   ");
    }

    printf(" | ");

    /* Detect printable and non-printable characters. */
    for (size_t i = 0; i < nbytes; i++) {
        int non_printable = (data[i] < 32) || (data[i] > 127);
        char to_print = non_printable ? '.' : data[i];
        fprintf(stdout, "%c", to_print);
    }

    putchar('\n');
}

/* Show a file byte-by-byte in hex format. */
void hexviewer(FILE *f) {
    /* Show each OFF_SIZE bytes. */
    unsigned char data[OFF_SIZE]; 
    uint32_t off = 0;
    size_t nbytes;

    /* Read up to 16 bytes. */
    while ((nbytes = fread(data, 1, OFF_SIZE, f))) {
        printData(data, off, nbytes);
        off += nbytes;
    }
}

int main(int argc, char **argv) {
    /* Use stdin as file descriptor as default. */
    FILE *f = stdin;
    if (argc > 2) {
        fputs("Usage: ./hexviewer <filename>\n", stderr);
        return -1;
    } else if (argc == 2) {
        f = fopen(argv[1], "rb");
        if (!f) {
            fprintf(stderr, "Error while opening file: %s", argv[1]);
            return -1;
        }
    }

    hexviewer(f);
    
    if (f != stdin) fclose(f);
    return 0;
}
