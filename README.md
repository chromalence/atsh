# atsh
a tiny shell. not suited for daily use
# install and compile
git clone https://github.com/chromalence/atsh &&
cd atsh && 
gcc -Os -nostdlib -static -fno-asynchronous-unwind-tables -fno-stack-protecto
r \
    -Wl,--build-id=none -Wl,-nmagic -s main.c -o atsh
# install 
git clone https://github.com/chromalence/atsh &&
cd atsh
# compile 
gcc -Os -nostdlib -static -fno-asynchronous-unwind-tables -fno-stack-protecto
r \
    -Wl,--build-id=none -Wl,-nmagic -s main.c -o atsh
