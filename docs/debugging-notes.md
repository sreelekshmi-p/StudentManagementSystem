# Student Management System Debugging Checklist

Use these questions to narrow down a defect before changing code. Record the steps that reproduce it and the evidence for the root cause.

## Understanding Existing Code

- [ ] What behavior is expected, and what behavior actually occurs?
- [ ] Can I reproduce the issue reliably? What exact inputs and menu actions trigger it?
- [ ] Which function or class owns the behavior, and how does control flow reach it?
- [ ] How are students represented, stored, retrieved, updated, and removed?
- [ ] What assumptions do the surrounding code and existing tests make?
- [ ] Could the behavior be intentional or relied upon elsewhere?

## Compiler and Linker Errors

- [ ] What is the first diagnostic, and does it point to the root cause rather than a later cascading error?
- [ ] Are declarations, definitions, includes, and namespaces consistent?
- [ ] Do function signatures and class declarations match their definitions and call sites?
- [ ] Is each required source file included in the build, and is each non-inline function defined exactly once?
- [ ] Are the compiler and build settings configured for C++17?

## Runtime Crashes

- [ ] What exact input or operation occurs immediately before the crash?
- [ ] Does a debugger identify the failing line and show the relevant call stack?
- [ ] Could the code access an invalid index, dereference a null pointer, or use an object after its lifetime?
- [ ] Are empty collections, missing students, and failed input operations handled?
- [ ] Can I reduce the reproduction to the smallest sequence of actions?

## Undefined Behavior

- [ ] Is every variable initialized before it is read?
- [ ] Are array, vector, and string indices within bounds?
- [ ] Are iterators, references, and pointers still valid after modifying a container?
- [ ] Are objects accessed only while alive and through compatible types?
- [ ] Could signed integer overflow, invalid shifts, or invalidated references occur?
- [ ] Can compiler warnings or sanitizers expose the suspected behavior?

## Memory Leaks and Dangling Pointers

- [ ] Who owns each dynamically allocated object, and where is that ownership released?
- [ ] Can ownership be expressed with a value, `std::unique_ptr`, or `std::shared_ptr` instead of an owning raw pointer?
- [ ] Could an exception or early return skip cleanup?
- [ ] Do stored pointers or references outlive the objects they point to?
- [ ] Can deleting or replacing a student leave another part of the program holding a stale pointer or reference?

## Multi-File Dependency Problems

- [ ] Does each header include the declarations it uses and avoid unnecessary includes?
- [ ] Are include guards or `#pragma once` preventing repeated inclusion?
- [ ] Are declarations in headers consistent with definitions in source files?
- [ ] Are dependencies included in a clear direction, without circular includes?
- [ ] Does the build compile and link every required source file after a clean rebuild?

## Static Analysis

- [ ] Have I enabled relevant compiler warnings and reviewed new warnings?
- [ ] Does a static analyzer report suspicious control flow, unchecked input, or unsafe lifetime behavior?
- [ ] Are analyzer findings reproducible and relevant to this code path?
- [ ] Have I addressed the underlying cause instead of suppressing a useful diagnostic?

## Testing After Applying a Fix

- [ ] Does the original reproduction now behave as expected?
- [ ] Do normal add, list, search, update, and remove workflows still work?
- [ ] Have I tested boundary cases, such as empty input, invalid input, missing records, and repeated operations?
- [ ] Does the complete project compile and link with the intended C++17 settings?
- [ ] Does the application execute successfully, and do existing tests still pass?
- [ ] If the fix concerns memory safety or undefined behavior, have I run an appropriate sanitizer or analysis tool?
