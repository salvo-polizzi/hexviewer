# Hexviewer

This is a simple program that emulates what "hexdump" does, e.g. reading a file byte-by-byte and display the binary content in hexadecimal format.

## Usage

Currently, the program accepts the file to read as argument:
```shell
./hexviewer <filename>
```

## Internals

Basically, the program is very simple. The main function is `hexviewer()` and does the following things:
- Uses `fread()` to read **chunks** of 16 bytes
- Print every byte in hexadecimal format using the formatting provided by `printf()`
- Print the ASCII printable characters on the right.


