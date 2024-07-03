#!/bin/bash

# スクリプトがあるディレクトリに移動
cd "$(dirname "$0")"

# DevKitProをダウンロードして展開
wget -O devkitpro.tar.gz https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.2/devkitpro.tar.gz
tar -xzvf devkitpro.tar.gz -C ./devkitpro --strip-components=1

# 環境変数を設定
export DEVKITPRO=$(pwd)/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM

# 環境変数を永続的に設定するためにシェルの設定ファイルに追加
echo "export DEVKITPRO=$(pwd)/devkitpro" >> ~/.bashrc
echo "export DEVKITARM=\$DEVKITPRO/devkitARM" >> ~/.bashrc

# 確認のためにパスを出力
echo "DEVKITPRO set to: $DEVKITPRO"
echo "DEVKITARM set to: $DEVKITARM"

# 完了メッセージ
echo "DevKitPro installation completed."