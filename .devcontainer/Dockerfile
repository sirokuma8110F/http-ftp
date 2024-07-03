FROM devkitpro/devkitarm

# ここに必要なパッケージのインストールや設定を追加
RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    # 他の依存パッケージ

# ユーザーの追加と設定
RUN useradd -ms /bin/bash codespace
USER codespace

WORKDIR /workspace
