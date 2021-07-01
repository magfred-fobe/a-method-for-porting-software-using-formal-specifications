# Reimplementation in rust based on the tla+ spec

Contains the rust source files of the implementation, and the source files to build the library for the verification.
This directory contains 2 versions of the linked list, and Foreign Function interfaces for these. 

#### Prerequisites
- Rust: Cargo, Rustc. See [Rust install guide](https://www.rust-lang.org/tools/install)
- cbindgen: Necessary to generate C-header files. (automatically installed when running gen_lib_bindings.sh)

#### Directory structure \
└─/ - scripts: gen_lib_bindings, config files  \
&nbsp;&nbsp;&nbsp;&nbsp;├─src - the main module, containing the FFI \
&nbsp;&nbsp;&nbsp;&nbsp;└─singly_linked_list - module containing linked list implemntations

- Running the tests (with output in order):
```
$ cd singly_linked_list && cargo test --nocapture --test-threads=1
```
- Building the library (done automatically by the verification tests):

```
$ cargo build --lib
```
- Generating C-header for library (done automatically by the verification tests):
```
$ cbindgen --config cbindgen.toml --crate singly_linked_list_rust --output OUTPUT_FILE
```
A .so or .lib should be located in ./target/debug

