This is Tri-Boolean Logic Project

The requirements are:

* CMake 3.11 or better; 3.14+ highly recommended.
* A C++17 compatible compiler
* Git
* Doxygen (optional)

To configure:

```bash
cmake -S . -B build
```

To build:

```bash
cmake --build build
```


To test (`--target` can be written as `-t` in CMake 3.15+):

```bash
cmake --build build --target test
```

To build docs (requires Doxygen, output in `build/docs/html`):

```bash
cmake --build build --target docs
```

Reference

 [Improving Binary Search Algorithm by Three Boolean Logic](https://www.codeproject.com/Tips/5284126/Improving-Binary-Search-Algorithm-by-Three-Boolean).

