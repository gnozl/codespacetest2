# codespacetest2

This repository contains a simple C++ ToDo list program implementing the UML interactions provided by the user.

Files added:
- `todo.cpp` — single-file C++ implementation with `Task` and `TaskList` classes and an interactive CLI.
- `Makefile` — build file to compile the program with g++.

Build and run
```
make
./todo
```

Try a scripted demo (non-interactive):
```
./todo <<'EOF'
1
Buy milk
1
Walk dog
4
2
Buy milk
4
3
Walk dog
4
5
EOF
```

Next steps: add unit tests, persistence (save/load), or a small GUI.