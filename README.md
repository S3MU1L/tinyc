# tinyc 🐜

*A minimal C-like compiler built on top of LLVM IR.*

---

## 🚀 Overview
**tinyc** is a toy compiler that implements a **small but expressive subset of the C language**.  
It’s designed as a learning project: you write programs in tinyc, the compiler lowers them into **LLVM IR**, and then LLVM handles optimization and machine code generation.

This project demonstrates:
- Compiler front-end design (lexer, parser, AST, semantic analysis).
- Mapping C constructs to LLVM IR (types, functions, control flow).
- Interoperability with system libraries (e.g., calling `printf`).

---

## ✨ Features
- **Types**
    - `int` (32-bit), `char` (8-bit), `void`
    - Pointers (`T*`)
    - Arrays (`T[N]`, decays to pointer in expressions)
    - `struct` (record types, field access)
    - `union` (overlapping storage, accessed via casts)

- **Expressions**
    - Arithmetic: `+ - * / %`
    - Comparisons: `< <= > >= == !=`
    - Boolean: `&& || !`
    - Unary: `-`, `&`, `*`
    - Member access: `p.x`, `p->x`
    - Array indexing: `a[i]`

- **Control Flow**
    - `if` / `else`
    - `while`, `for`
    - `return`

- **Functions**
    - Definition and calls
    - Parameters passed by value (scalars/pointers)
    - Structs/unions passed **by pointer only**

- **Runtime Interop**
    - Uses LLVM’s C calling convention
    - Works with standard C library (e.g., `printf`, `getchar`, `putchar`)

---

## 📖 Example

```c
struct Point {
    int x;
    int y;
};

int square(int x) {
    return x * x;
}

int main() {
    struct Point p;
    p.x = 5;
    p.y = square(p.x);

    if (p.y > 20) {
        p.y = p.y - 1;
    }

    return p.y;
}
