# Student Management System Tests

Configure and build from the project root:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

CMake fetches Google Test with `FetchContent`. The `StudentTests`
target builds the test files with `Student.cpp`, `StudentManager.cpp`, and
`StudentInput.cpp`; it
intentionally does not include `main.cpp`.
