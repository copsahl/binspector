# binspector
A linux command line utility to view information about PE and ELF binaries.

## Usage:
`make`

`./binspector binary.bin -s -f -S -P <section name> -a`

## libbfd
Ubuntu: `sudo apt install binutils-dev`

Arch: `sudo pacman -S binutils`
## Command Line Arguments 

`-s			- List Sections`

`-f			- List Functions`

`-S			- List Symbols`

`-P <section name>	- Print Section content`

`-a			- List arch info`


