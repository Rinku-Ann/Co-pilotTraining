# Student Management System Debugging Checklist

## Understanding Existing Code
- What is the expected behavior, and how does the observed behavior differ?
- Which functions, classes, and files participate in this feature?
- What assumptions do the existing code and its callers make about inputs and state?
- Can the issue be reproduced with a small, specific example?
- What changed recently in the relevant code or build configuration?

## Compiler and Linker Errors
- What is the first diagnostic, and does it identify the root error or a follow-on error?
- Does the code use valid C++17 syntax and types?
- Are declarations, definitions, includes, and namespaces consistent?
- Are all required source files included in the build?
- Do linker errors indicate a missing definition, duplicate definition, or mismatched signature?

## Runtime Crashes
- What exact action and input trigger the crash?
- Where does execution fail, and what are the values and object lifetimes at that point?
- Could an index, iterator, reference, or pointer be invalid?
- Is input checked before it is parsed or used?
- Can a debugger or sanitizer provide a stack trace or identify the invalid access?

## Undefined Behavior
- Could the code access an object outside its lifetime or an array outside its bounds?
- Are uninitialized values, invalid casts, or invalidated iterators involved?
- Could signed integer overflow or an invalid shift occur?
- Are all control paths valid, including functions that must return a value?
- Does the issue disappear or change under different optimization or compiler settings?

## Memory Leaks and Dangling Pointers
- Who owns each dynamically allocated resource, and where is that ownership released?
- Could an exception or early return skip cleanup?
- Can a pointer or reference outlive the object it refers to?
- Is ownership represented with RAII and smart pointers where appropriate?
- Do copies or moves leave multiple owners or stale pointers?

## Multi-File Dependency Problems
- Does each file include the declarations it directly uses?
- Are declarations and definitions consistent across headers and source files?
- Are include guards or `#pragma once` preventing repeated inclusion?
- Are source files and libraries correctly listed in the build configuration?
- Could include order, circular dependencies, or inconsistent macros change declarations?

## Static Analysis
- What do compiler warnings and static-analysis diagnostics report?
- Are warnings enabled, and are relevant warnings treated seriously?
- Do diagnostics point to unchecked input, unsafe lifetime, or suspicious control flow?
- Can a sanitizer or static-analysis tool confirm the suspected issue?
- Is each warning understood rather than simply suppressed?

## Testing After Applying a Fix
- Does the original reproducer now pass?
- Do related normal, boundary, and invalid-input cases behave correctly?
- Do existing application workflows still work as expected?
- Does the project compile and link cleanly with its intended C++17 configuration?
- Have relevant tests, static analysis, and available sanitizers been run?
