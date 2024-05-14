a small c program to print the raw data of a file to the cli\
currently only limited to linux

# dependencies (debian and derivatives)
```sh
apt install build-essentials
```

# dependencies (arch and derivatives)
```sh
pacman -S glibc gcc
```

# makefile options
```sh
# to compile the program in the repo directory (the one you installed)
make

# to clean up all object files (and the program itself)
make clean
```
