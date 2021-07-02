#!/bin/sh
if [ -d ~/.config/dime ]; then
  mkdir -p $HOME/.config/dime
  mkdir -p $HOME/.local/share/dime

  touch $HOME/.config/dime/tasklist
  touch $HOME/.local/share/dime/state
  touch $HOME/.local/share/dime/log
  echo "Place files"
fi

cp ./a.out /bin/dime
echo "Installed"
