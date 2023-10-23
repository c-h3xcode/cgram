LLVM_VERSION=$1

echo "Installing LLVM ${LLVM_VERSION}"

# Install tools
export DEBIAN_FRONTEND=noninteractive
apt update -y
apt install -y lsb-release wget software-properties-common gnupg

# Setup LLVM
wget -O /tmp/llvm.sh https://apt.llvm.org/llvm.sh
chmod +x /tmp/llvm.sh
/tmp/llvm.sh ${LLVM_VERSION}
rm /tmp/llvm.sh

# Install Clang
apt install -y clang-${LLVM_VERSION} lldb-${LLVM_VERSION} lld-${LLVM_VERSION} clangd-${LLVM_VERSION} clang-format-${LLVM_VERSION} clang-tidy-${LLVM_VERSION}

# Remove unused packages
apt autoremove -y

# Update alternatives to use latest LLVM tools
update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-${LLVM_VERSION} 100
update-alternatives --install /usr/bin/clang clang /usr/bin/clang-${LLVM_VERSION} 100
update-alternatives --install /usr/bin/lldb lldb /usr/bin/lldb-${LLVM_VERSION} 100
update-alternatives --install /usr/bin/lld lld /usr/bin/lld-${LLVM_VERSION} 100
update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-${LLVM_VERSION} 100
update-alternatives --install /usr/bin/clang-format clang-format /usr/bin/clang-format-${LLVM_VERSION} 100
update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-${LLVM_VERSION} 100
