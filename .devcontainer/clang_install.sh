#!/usr/bin/env bash

set -e

# wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -

# clang-17
# add-apt-repository "deb http://apt.llvm.org/mantic/ llvm-toolchain-mantic-17 main"
# apt-get install clang-17 clang-tools-17 clang-17-doc libclang-common-17-dev libclang-17-dev libclang1-17 clang-format-17 python3-clang-17 clangd-17 clang-tidy-17

#apt-get -y purge --auto-remove clang
cd /tmp
wget https://apt.llvm.org/llvm.sh
chmod +x ./llvm.sh
./llvm.sh 17 all

update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-17 100
update-alternatives --install /usr/bin/clang clang /usr/bin/clang-17 100
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-17 100


#wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | sudo tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc
#apt-get install clang-17 clang-tools-17 clang-17-doc libclang-common-17-dev libclang-17-dev libclang1-17 clang-format-17 python3-clang-17 clangd-17 clang-tidy-17