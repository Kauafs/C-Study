# C++ Security & Systems Programming Studies

This repository showcases practical implementations of low-level software security concepts, Windows Internals, process memory analysis, and security mechanics in native C++.

## 📁 Repository Structure

- **`ph10.cpp`**: Real-time process memory inspection engine utilizing Win32 APIs (`Toolhelp32`, `OpenProcess`, `ReadProcessMemory`) for string/signature identification.
- **`ph07.cpp`**: Low-level sandbox implementing stack canary integrity checks and runtime XOR payload obfuscation/deobfuscation.
- 
## 🛠️ Tech Stack & Requirements

- **Language:** C++17 / Native C
- **API Target:** Win32 API / Windows Internals
- **Compilers:** MSVC (Visual Studio) / GCC / Clang
- **OS Focus:** Windows x64 & Linux

## ⚠️ Disclaimer
All code contained in this repository is created strictly for educational purposes, defensive security research, and proof-of-concept analysis.
