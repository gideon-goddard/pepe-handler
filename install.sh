#!/bin/bash
if [[ $EUID -ne 0 ]]; then
	   echo "This script must be run as root" 
	      exit 1
fi

echo "Compiling/installing"
apxs -i -a -c pepe_module.c
