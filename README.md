# **TREX** – Terminal Regex Engine
TREX is a terminal-based regular expression engine built from scratch. It includes a tokenizer, parser, an AST-to-NFA converter, NFA-to-DFA conversion, and full DFA simulation for pattern matching.
## Requirements
- CMake ≥ 4.0
- C++ Compiler with C++23 support.
## Installation 
Follow the steps below to build and run **TREX**:
```sh
git clone https://github.com/yourusername/trex.git
cd trex
mkdir build && cd build
cmake ..
cmake --build .
```
## Usage
Once built, you can run the engine:
```
./trex <RegEx Pattern> <Text>
```
*Example:*
```
./trex "a(b|c)*d" "abcbcd"
```

