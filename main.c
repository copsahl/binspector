#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Forced to redefine PACKAGE and PACKAGE_VERSION to pass check */
#define PACKAGE 1
#define PACKAGE_VERSION 1
#include <bfd.h>

#undef PACKAGE
#undef PACKAGE_VERSION

void print_section_names(bfd *file);
void print_section_content(bfd *file, char *name);
void printBytes(char *string);
void print_symbol_table(bfd *file, int funcsOnly);

int main(int argc, char **argv){

	bfd_init();
	bfd *binary;
	const bfd_arch_info_type *archInfo;
	int i;

	// Checking arguments
	// Need at least 3 for real output. 
	if(argc <= 2){
		printf("Usage: %s <binary file> -s -S -P <section> -a\n", argv[0]);
		exit(-1);
	}

	// Open our binary file in read mode
	if((binary = bfd_openr(argv[1], NULL)) == NULL){
		printf("Failed to open binary!\n");
		exit(-1);
	}

	// Checking to see if the file is a binary_object
	// bfd_object may contain data, symbols, relocations, and debug info.	
	if(!bfd_check_format(binary, bfd_object)){
		printf("Failed to open binary file!\n");
		exit(-1);
	}

	// Display name of current file. 
	printf("[loaded binary] -> %s\n", argv[1]);

	// Parse Arguments
	/*  
	    We loop through each argument and execute their specific
	    functionality when we come across the arguments. 
	*/
	for(i = 2; i < argc; i++){
		if(strncmp(argv[i], "-s", 2) == 0){
			printf("[listing sections]\n");
			print_section_names(binary);
			printf("\n");
		}
		if(strncmp(argv[i], "-P", 2) == 0){
			int length = strlen(argv[i + 1]);
			argv[i+1][length] = '\0';	
			printf("[%s content]\n", argv[i+1]);
			print_section_content(binary, argv[i+1]);
			printf("\n");
		}
		if(strncmp(argv[i], "-a", 2) == 0){
			printf("[architecture info]\n");
			archInfo = bfd_get_arch_info(binary);
			printf("Architecture:\t%s\n", archInfo->printable_name);
			printf("\n");
		}
		if(strncmp(argv[i], "-S", 2) == 0){
			printf("[symbol list]\n");
			print_symbol_table(binary, 0);
			printf("\n");
		}
		if(strncmp(argv[i], "-f", 2) == 0){
			printf("[function list]\n");
			print_symbol_table(binary, 1);
			printf("\n");
		}
	}

	// Close the binary, be nice to the computer :) 
	bfd_close(binary);

	return 0;
}

void print_section_names(bfd *file){
	
	/* 
	    Switched sectionParse type to asection from `struct bfd_section`
	    because struct bfd_section is deprecated.
	*/
	asection *sectionParse = file->sections;
	while(sectionParse != NULL){
		printf("%-20s\t%8ld %10s\n", sectionParse->name, sectionParse->size, "BYTES");
		sectionParse = sectionParse->next;
	}
}

void print_section_content(bfd *file, char *name){

	int x;
	int upperBound = 10;
	int lowerBound = 0;
	unsigned char *memory = NULL;
	asection *currSec;

	if((currSec = bfd_get_section_by_name(file, name)) == NULL){
		printf("Section not found!\n");
		exit(-1);
	}

	memory = malloc(sizeof(unsigned char) * currSec->size);
	bfd_get_section_contents(file, currSec, memory, 0, currSec->size);

	// Print out hex and ascii character values 
	while((long unsigned int)lowerBound < currSec->size){
		for(x = lowerBound; x < upperBound; x++){
			printf("%02x ", memory[x]);
		}
		printf("\t");
		for(x = lowerBound; x < upperBound; x++){
			if(memory[x] <= 0x20 || memory[x] >= 0x7f){	// Exclude non-printable characters
				printf(". ");
				continue;
			}
			printf("%c ", memory[x]);
		}

		lowerBound = upperBound;
		upperBound += 10;
		printf("\n");
	}

}

void print_symbol_table(bfd *file, int funcsOnly){
	long storage_needed;
	asymbol **symbol_table;
	long number_of_symbols;
	long i;

	storage_needed = bfd_get_symtab_upper_bound(file);

	if(storage_needed < 0){
		printf("Failed to retrieve symbol table!\n");
		return;
	}
	if(storage_needed == 0){
		return;
	}

	symbol_table = (asymbol **)malloc(storage_needed);
	if(symbol_table == NULL){
		printf("Failed to retrieve symbol table!\n");
		return;
	}

	number_of_symbols = bfd_canonicalize_symtab(file, symbol_table);
	if(number_of_symbols < 0){
		printf("Failed to retrieve symbol table!\n");
		return;
	}

	for(i = 0; i < number_of_symbols; i++){
		if(!funcsOnly){
			printf("%-30s\t", symbol_table[i]->name);
			if(symbol_table[i]->flags & BSF_FUNCTION){
				printf("FUNC");
			}
			printf("\n");
		}else{
			if(symbol_table[i]->flags & BSF_FUNCTION){
				printf("%-30s\n", symbol_table[i]->name);
			}
		}
	}

}

void printBytes(char *string){
	size_t x;
	for(x = 0; x < strlen(string); x++){
		printf("%x ", string[x]);
	}
	printf("\n");
}

