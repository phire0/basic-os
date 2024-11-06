# basic-os

A basic x86 Assembly bootloader with an even more basic C based kernel.

Just experimenting and following some tutorials over at https://wiki.osdev.org

## Available Functionality:

**16-Bit Real Mode**

| Function | Purpose | Calling Instructions |
| - | - | - |
| rm_print | Print ASCII text | Load string into BX register and call function. |
| rm_print_nl | Print a new line & carriage return | N/A |
| rm_print_hex| Print a hexadecimal value | Load hexadecimal value into DX register and call function. |
| switch_to_protected_mode | Enter 32-Bit Protected Mode | Expects a 32 bit label 'begin_protected_mode' as PMODE entry point. |

---
**32-Bit Protected Mode**

| Function | Purpose | Calling Instructions |
| - | - | - |
| pm_print | Print ASCII text | Load string into EBX register and call function. |