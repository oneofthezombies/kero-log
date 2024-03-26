# Kero Log

A memory-safe "asynchronous structured logging system" implementation written in C++.  

## Why I Created This

Memory safety in programming languages is no longer an option. This is an area that must be met.  
However, the status of the C++ programming language in the current compiler industry is absolute. So I wrote the code in C++, but developed it to meet memory safety features.  

## Features

### Non-blocking

When the `LogBuilder`'s `Log()` function is called, the log object is only stored locally in the thread, and heavy `IO` tasks such as `Standard Out` or `File` are performed in the `Runner Thread`.

### Structured Log

You can save key, value using `LogBuilder`'s `Data(key, value)` method without having to include a key, value in the log message.

### Multiple Transport

The abstract class `Transport` can be implemented to add a variety of processing of `Log` objects.

## Diagrams

### Logging Sequence

![log](/resources/log.png)

### Variable Scopes

![context](/resources/context.png)

## For Contributors

This project was developed based on Bazel.  
Please ensure `bazel` command and after calling the `bazel --version` command, check whether the version is higher than `7.0.0`.  

You can get IDE support by running the command below.  

```sh
bazel run @hedron_compile_commands//:refresh_all
```

For more information, please refer to the link below.  

https://github.com/hedronvision/bazel-compile-commands-extractor

## References

[February 2024 Whitehouse Technical Report](https://www.whitehouse.gov/wp-content/uploads/2024/02/Final-ONCD-Technical-Report.pdf)  
