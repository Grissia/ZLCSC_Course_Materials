#!/bin/sh

exec 2>/dev/null
cd /home/chal
gcc chal.c -o /tmp/chal -std=c17 < /dev/null
chmod 755 /tmp/chal
exec /tmp/chal
