# Reimplementation in rust based on the tla+ spec

Contains the rust source files of the implementation, and the source files to build the library for the verification

Build static library:\
$cargo build --lib

A .so or .lib should be located in ./target/debug

Run property tests on the implementation\
$cd singly_linked_list_unsafe && cargo test

