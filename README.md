# MySPIM — Single-Cycle MIPS Simulator  
CDA3103: Computer Logic & Organization

**Author:** Brayden Coggin

This repository contains an implementation of the **MySPIM single-cycle MIPS processor simulator**, developed for the University of Central Florida CDA3103 course. MySPIM simulates a simplified single-cycle MIPS processor using the provided datapath and control logic.

---

## 📁 Project Structure

| File | Description |
|------|-------------|
| `project.c` | Student implementation of the datapath, ALU logic, control signals, memory access, branching, and PC update logic. |
| `spimcore.c` | Simulator driver responsible for loading `.asc` files, stepping through instructions, and handling user commands. |
| `spimcore.h` | Header file containing function prototypes and the `struct_controls` definition. |
| `Makefile` | Build script for compiling the simulator. |

---

## ⚙️ Compilation

The simulator is compiled using **GCC** via the provided Makefile:

```bash
make
```

This produces an executable named `spim`.

---

## ▶️ Running the Simulator

Run MySPIM with a `.asc` file containing MIPS machine code:

```bash
./spim program.asc
```

Once running, MySPIM behaves like an interactive debugger.

---

## 🐞 Debugger Commands

The simulator supports the following interactive commands:

| Command | Description |
|---------|-------------|
| `r` | Dump register contents |
| `m` | Dump memory contents |
| `s[n]` | Step *n* instructions (default = 1) |
| `c` | Continue execution until program halts |
| `h` | Check halt status |
| `d [addr1] [addr2]` | Hex dump of a memory range |
| `i` | Print memory size |
| `p` | Print the loaded `.asc` file |
| `g` | Display control signals for the last executed instruction |
| `q` | Quit the simulator |

### Example usage
```
s 10   # step 10 cycles
m 4096 # dump memory near text segment
r      # print registers
g      # show control signals
```

---

## 🧠 Implementation Notes

The following functions are implemented in `project.c`:

- `ALU`
- `instruction_fetch`
- `instruction_partition`
- `instruction_decode`
- `read_register`
- `sign_extend`
- `ALU_operations`
- `rw_memory`
- `write_register`
- `PC_update`

### Constraints and assumptions
- Memory accesses are **word-aligned**
- Memory is indexed using `address >> 2`
- `ALUOp = 7` indicates an R-type instruction and requires decoding via the `funct` field
- Debug output is handled by the simulator driver

---

## 📚 ALU Control Reference

| ALUControl | Operation |
|-----------|-----------|
| `000` | A + B |
| `001` | A − B |
| `010` | (signed) A < B → 1 |
| `011` | (unsigned) A < B → 1 |
| `100` | A & B |
| `101` | A \| B |
| `110` | B << 16 |
| `111` | ~A |

---

## 📜 License

This project was developed for academic use in CDA3103. Starter files and project specifications are provided by the University of Central Florida and/or their original authors.
