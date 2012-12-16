#!/bin/bash
if [ $# -lt 1 ]; then
	echo "usage:$0 [comment]"
	exit 0
fi
git add CREDITS EXPERIMENTAL config.m4 config.w32 php_ttmp.h tests ttmp.c ttmp.php git_commit.sh README.md .gitignore
git commit -m "$1"
