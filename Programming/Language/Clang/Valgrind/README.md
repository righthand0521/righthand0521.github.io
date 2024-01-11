# Valgrind - a suite of tools for debugging and profiling programs

- [valgrind](https://valgrind.org/)
- [kcachegrind](http://kcachegrind.sourceforge.net/html/Home.html)
- [massif-visualizer](https://apps.kde.org/zh-tw/massif-visualizer/)

```bash
apt install valgrind
apt install kcachegrind
apt install massif-visualizer
```

```bash
gcc -o <exe> <src>.c -g3
```

偵測 runtime 記憶體錯誤與 memory leaks

```bash
valgrind --tool=memcheck --leak-check=full <exe>
valgrind -s --tool=memcheck --leak-check=full <exe>
valgrind -s --tool=memcheck --leak-check=full --max-stackframe=5000000 <exe>
valgrind -v --leak-check=full <exe>
```

提供類似 gprof 的 profiling 功能, 記錄函數被呼叫的次數. 不同的是它可以在 runtime 即時監控.

```bash
valgrind --tool=callgrind <exe>
kcachegrind <callgrind.out.xxx>
```

快取命中的 profiler, 改善快取失誤可以提昇程式效能.

```bash
valgrind --tool=cachegrind <exe>
```

heap 的 profiler, 記錄記憶體使用量.

```bash
valgrind --tool=massif <exe>
ms_print <massif.out.xxx>
massif-visualizer <massif.out.xxx>
```

thread 的 debugger, 主要是用來偵測資料的 race condition.

```bash
valgrind --tool=helgrind <exe>
```
