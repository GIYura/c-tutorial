#### Compile

1. Specify macro 'EXPECT' in the makefile
2. Run
```
make
```

3. Store disassembly in a file
```
gdb -batch -ex "disassemble/m main" ./test > test_0
gdb -batch -ex "disassemble/m main" ./test > test_1
```

4. Compare
```
git diff test_0 test_1
```

NOTE: [reference](https://tbrindus.ca/how-builtin-expect-works/)

