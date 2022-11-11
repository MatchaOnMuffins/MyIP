# MyIP
A simple command line tool to get your public IP address and other information.

## Quickstart

```bash
$ myip
  123.456.789.012 # your public IP address
```

## Arguments
A list of arguments can be found by running `myip --help`.

## Installation
Use make to build and install the binary.
libcurl is required to build the binary.

To install libcurl on Ubuntu:
```bash
$ sudo apt-get install libcurl4-openssl-dev
```

To install libcurl on macOS:
```bash
$ brew install curl
```

To build and install the binary:
```bash
$ mkdir build
$ cd build
$ ../configure
$ make
$ sudo make install
```