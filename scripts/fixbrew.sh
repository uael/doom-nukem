#!/usr/bin/env bash

brew search sdl2 &>/dev/null
[[ $? == 0 ]] && exit 0

echo "Installing a healthy homebrew"
rm -rf ~/.brew
git clone https://github.com/Homebrew/brew.git --depth=1 ~/.brew

rm -rf ~/Library/Caches ~/.brew/Library/Locks;
mkdir -p "/tmp/${USER}/Homebrew/Caches" "/tmp/${USER}/Homebrew/Temp" \
    "/tmp/${USER}/Homebrew/Locks" > ~/.zprofile
ln -s /tmp/${USER}/Homebrew/Locks ~/.brew/Library/Locks
echo "export HOMEBREW_CACHE=/tmp/\${USER}/Homebrew/Caches" >> ~/.zprofile
echo "export HOMEBREW_TEMP=/tmp/\${USER}/Homebrew/Temp" >> ~/.zprofile
echo "export TMP_DIR=\"/Volumes/Storage/goinfre/${USER}\"" >> ~/.zprofile
echo "export PATH=~/.brew/bin:\$PATH" >> ~/.zprofile
echo "export LD_LIBRARY_PATH=~/.brew/lib:\${LD_LIBRARY_PATH}" >> ~/.zprofile
echo "export LD_INCLUDE_PATH=~/.brew/include:\${LD_LIBRARY_PATH}" >> ~/.zprofile

echo "Updating brew"
~/.brew/bin/brew update
