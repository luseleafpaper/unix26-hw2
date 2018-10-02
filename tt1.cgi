#!/bin/sh
#
# cgi program to generate text tables from local Unix commands
#
echo "Content-Type: text/plain"
echo ""
echo "Here are the current internet connections:"
netstat -A inet
echo "Here are the current files:"
ls -l
echo "Here is fstab:"
cat /etc/fstab
