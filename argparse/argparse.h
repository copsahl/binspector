#ifndef ARGPARSE_H
#define ARGPARSE_H

/*
unsigned int LIST_SECTIONS = 0;
*/

struct Arguments_t{
	int list_sections;
	char *print_section;
	int list_arch;
	int list_symbols;
	int list_strings;
};

struct Arguments_t *buildArgStruct();
void setCliFlags(int argc, char **argv, struct Arguments_t *arguments);

#endif
