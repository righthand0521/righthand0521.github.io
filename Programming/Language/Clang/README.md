# [Clang: a C language family frontend for LLVM](https://clang.llvm.org/)

## C

- [Makefile cheatsheet](https://devhints.io/makefile)
- [Google C++ Style Guide 繁體中文版](http://www.slmt.tw/google-cpp-style-guide-zh-tw/index.html)

## C++

- [cplusplus.com](https://cplusplus.com/)
- [cppreference.com](https://en.cppreference.com/w/)

## Tool

### [gdb - The GNU Debugger](https://www.sourceware.org/gdb/)

### gprof - display call graph profile data

```bash
apt install graphviz -y
pip install gprof2dot

gcc -Wall -pg -lc -o <exe> <src>.c -DDEBUG=1 -g3
./<ext>
gprof -b <exe> gmon.out
gprof -b -A <exe> gmon.out
gprof -b <exe> gmon.out | gprof2dot | dot -T png -o output.png
```

### perf - Performance analysis tools for Linux

```bash
apt install linux-tools-generic -y

perf record <exe>
perf report
```

#### Windows Subsystem for Linux

```bash
apt install flex bison -y
git clone https://github.com/microsoft/WSL2-Linux-Kernel --depth 1
cd WSL2-Linux-Kernel/tools/perf
make -j8
cp perf /usr/local/bin
```

### [ddd - The Data Display Debugger](https://www.gnu.org/software/ddd/)

```bash
apt install ddd -y
```

### [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html)

```bash
apt install clang-format -y

clang-format -version
clang-format --style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 120}"
```
