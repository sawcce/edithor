# Edithor

Edithor is a terminal text editor built from the ground up in c using native APIs.
This was started as a project for me to learn c and improve my skills.

# Current status

Edithor is still in its early stages, thus only the windows implementation of the hal is being worked on right now.
All other features should work normally due to the way the project is structured so feel free to open a PR to add linux support!

# How to use

Since there are no pre-built binaries available right now, the only way to use, test and contribute to edithor is to clone the repo.

## Prerequisites
- Have make installed on your pc
- Get a c compiler (gcc, clang...)

## Build
The default compiler is clang but you can use any other compiler with the `CC` flag (`CC=your_compiler`)

```
git clone https://github.com/sawcce/edithor Edithor
cd ./Edithor
make bootstrap build
```

## Run

```
make run
```

# Contributing

Any contribution is welcome! Wether you want to add some features or platform specific support, feel free to open a PR / issue!
