#! /usr/bin/bash

function main() {

	if [[ ! -x timer ]]; then
		gcc -ggdb3 *.c -o timer -lpthread
	fi
	./timer

}
main $@
