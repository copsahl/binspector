# binspector
A linux command line utility to view information about PE and ELF binaries.

## Usage:
`make`

`./binspector binary.bin -s -S -P <section name> -a`

## libbfd
`sudo apt install binutils-dev`

## Preview of Features

### List Sections (Displays name and size)
![list sections](pics/list_sections.png "list sections")
### Display Section Content
![print section](pics/print_sections.png "print section content")
### List Architecture
![list arch](pics/list_arch.png "List arch")
### List symbols (Labels functions)
![list symbols](pics/list_symbols.png "List symbols")
