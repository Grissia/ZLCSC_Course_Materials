#!/usr/bin/env bash

# Author: Grissia
# This script sets up a development environment for reverse engineering and binary exploitation.
# Specifically, it installs necessary system packages, creates a Python virtual environment, and installs pwntools and pwndbg.
# It is designed to be run on Debian-based Linux distributions.

set -Eeuo pipefail

if [[ "${EUID}" -eq 0 ]]; then
    echo "Please run this script as a non-root user; system package steps will use sudo automatically." >&2
    exit 1
fi

if ! sudo -n -v; then
    echo "Non-interactive execution requires passwordless sudo (NOPASSWD) or a cached sudo credential." >&2
    exit 1
fi

run_as_root() {
    sudo -n "$@"
}

export DEBIAN_FRONTEND=noninteractive

packages=(
    curl wget git vim tmux btop neofetch
    python3 python3-pip python3-venv
    gdb gcc cmake build-essential nasm binutils
)

run_as_root apt-get update -y
run_as_root apt-get upgrade -y \
    -o Dpkg::Options::="--force-confdef" \
    -o Dpkg::Options::="--force-confold"
run_as_root apt-get install -y "${packages[@]}"

VENV_DIR="${HOME}/pwn"
python3 -m venv "${VENV_DIR}"
# shellcheck disable=SC1091
source "${VENV_DIR}/bin/activate"
pip install -U pwntools uv

# https://pwndbg.re/stable/setup/#system-gdb-but-not-like-that
PY_VER=$(gdb -nx --batch -iex 'py import sysconfig; print(sysconfig.get_config_var("VERSION"))')
uv tool install --python=$PY_VER  git+https://github.com/pwndbg/pwndbg
echo "source $(uv tool dir)/pwndbg/share/pwndbg/gdbinit.py" >> ~/.gdbinit
