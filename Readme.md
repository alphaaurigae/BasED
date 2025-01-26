# BasED

- Decode / encode multi executeable repo 

- Template / shared source sample ... busy, fill this readme later


## Deps
```
(all) cli11-dev  -  https://github.com/CLIUtils/CLI11
(base.cpp) libgmp-dev - https://gmplib.org/
```

## Build

- Build OS: "Ubuntu 24.04"

... cmake ...
(g++/clang - Cmakelists "option(USE_CLANG" ON/OFF - default clang)

- ```./build_cmake.sh``` - build
- ```./clean_cmake.sh``` - tidy build

```
// allnum, digit, alpha
$ bin/caesarshift --caesarshift 4 --mode allnum -e -i 2Jh2t79Fzwucef
Encoded: 2Jh2t79Fzwucef

// 16,32,58,62,64,85
$ bin/base --base85 -e -i 'bayzed'
Encoded: @UXP.ARk

$ bin/binary --binary -d -i 00110011001101000011010100110011001100100011010000110101
Decoded: 3453245

$ bin/morse -m -e -i fortune
Encoded: ..-. --- .-. - ..- -. . 

$ bin/hex --hex -e -i abcdef
Encoded: 616263646566

```

## Todo

"allthethings"