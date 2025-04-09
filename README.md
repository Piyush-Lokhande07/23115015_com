# 🔧 Simple Expression Compiler with Custom Instruction (macOS)

This project is a **simple compiler** that detects a specific arithmetic expression:

```c
z = (a + b) * (a - b);
```

It replaces this expression with a **custom instruction** called `diffsquare`, which is internally represented by the **custom opcode `0F AA`**.

You can then disassemble the generated output to view this custom instruction in action, making this project a perfect exercise in understanding:

- Instruction selection
- Opcode emission
- Pattern recognition
- Custom disassembly

---

## 🚀 Quick Start

### 1. Clone the Repository

```bash
git clone https://github.com/Piyush-Lokhande07/23115015_com
cd 23115015_com
```

---

### 2. Clean Previous Builds (if any)

```bash
rm -rf out out.o out.s .internal/result.log
```

---

### 3. Edit the Source Code

Open the main compiler logic and make your changes:

```bash
nano main.c
```

You can modify your logic, expression handling, or add more pattern recognition if needed.

---

### 4. Build and Run

Just run the build script provided:

```bash
./build.sh
```

This will:
- Compile your custom compiler
- Run it and generate `out.s`
- Assemble it to `out.o`
- Link it into an executable `out`
- Run `.internal/pass2_stage_exec` to simulate disassembly
- Show final output with disassembly and result

---

## 🧾 Sample Output

```bash
✅ Generated 'out.s' with a=8, b=5

🔍 Disassembly:
100003fab: b8 08 00 00 00               movl    $8, %eax
100003fb0: bb 05 00 00 00               movl    $5, %ebx
100003fb5: 0f aa                        diffsquare %eax, %ebx
100003fb7: c3                           retq

Result: 39
```

---

## 🛠 Dependencies

- macOS with Command Line Tools (`xcode-select --install`)
- `as` (assembler) and `ld` (linker) are macOS built-in
- `objdump` or `otool` if you want deeper disassembly

---

## 📁 Project Structure

```
.
├── main.c                       # Compiler source
├── build.sh                     # Build automation script
├── out.s                        # Generated assembly
├── out.o                        # Object file
├── out                          # Final binary
├── .internal/
│   ├── pass2_stage_exec         # Custom disassembler
│   └── result.log               # Output log
└── README.md                    # You're reading it!
```

---

## 👨‍💻 Author
Name: Arshil Yusuf
Roll Number: 23115015
Compiler Desgin Assignment
Department of Computer Science and Engineering