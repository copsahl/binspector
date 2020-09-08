#include "argparse.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Arguments_t *buildArgStruct(){

	struct Arguments_t *tmp = malloc(sizeof(struct Arguments_t));
	tmp->list_sections = 0;
	tmp->print_section = NULL;
	tmp->list_arch = 0;
	tmp->list_symbols = 0;

	return tmp;
}

void setCliFlags(int argc, char **argv, struct Arguments_t *arguments){
	
	int i;

	for(i = 2; i < argc; i++){
		if(strncmp(argv[i], "-s", 2) == 0){
			arguments->list_sections = 1;
		}
		if(strncmp(argv[i], "-P", 2) == 0){
			int length = strlen(argv[i + 1]);
			arguments->print_section = malloc(sizeof(char) * length);
			strncpy(arguments->print_section, argv[i + 1], length);
			arguments->print_section[length] = '\0';	
		}
		if(strncmp(argv[i], "-a", 2) == 0){
			arguments->list_arch = 1;
		}
		if(strncmp(argv[i], "-S", 2) == 0){
			arguments->list_symbols = 1;
	
		}
	}
}

