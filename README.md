# MySPIM-Single-Cycle-MIPS-Simulator
CDA3103: Computer Logic & Organization

Authors: Brayden Coggin & Daniel Henriquez

This repository contains our implementation of the MySPIM single-cycle MIPS processor simulator, following the University of Central Florida CDA3103 project guidelines. MySPIM simulates a simplified, single-cycle MIPS processor using the provided datapath and control logic.

📁 Project Structure
File	Description
project.c	Implementation of the ALU, datapath, control unit logic, memory access, branch/jump behavior, and PC update logic. (This is the only file we modify.)
spimcore.c	Provided driver — loads .asc files, steps through instructions, prints registers/memory, and manages the simulation loop.
spimcore.h	Provided header with function prototypes and the struct_controls definition.
ProjectFAQ.pdf	Official FAQ with clarifications about memory alignment, control signals, ALU behavior, and branching rules.
ProjectGuideline.pdf	Full project description, diagrams, required instructions, and datapath explanation.
⚙️ Compilation
Use GCC to compile the simulator:

gcc -o spimcore spimcore.c project.c
A binary named spimcore will be produced upon successful compilation.

▶️ Running the Simulator
Run MySPIM with a .asc file containing MIPS machine code:

./spimcore program.asc
Once running, MySPIM acts like a debugger. You may use the commands below.

🐞 Debugger Commands
MySPIM includes several commands that allow interactive debugging during execution:

Command	Description
r	Dump register contents
m	Dump memory contents
s[n]	Step n instructions (default = 1)
c	Continue execution until program halts
h	Check if the program has halted
d [addr1] [addr2]	Hex dump of memory range
i	Print memory size
p	Print the input .asc file
g	Display all control signals for the last executed instruction
q	Quit the simulator
Example usage:
s 10   # step 10 cycles
m 4096 # dump memory around text segment
r      # print registers
g      # show control signals
🧠 Implementation Notes
The project requires implementing the following functions in project.c:

ALU
instruction_fetch
instruction_partition
instruction_decode
read_register
sign_extend
ALU_operations
rw_memory
write_register
PC_update
Important constraints:
Do not modify spimcore.c or spimcore.h.
Do not use print statements in project.c.
All memory accesses must be word-aligned.
Memory array is indexed using address >> 2.
ALUOp = 7 means the instruction is R-type and must be decoded using the funct field.
📚 ALU Control Reference
ALUControl	Operation
000	A + B
001	A − B
010	(signed) A < B → 1
011	(unsigned) A < B → 1
100	A & B
101	A | B
110	B << 16
111	~A
📜 License
This project is for academic use in CDA3103. All provided starter files belong to the University of Central Florida and/or their original authors.
