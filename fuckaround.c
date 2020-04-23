#include <stdio.h>
#include <stdlib.h>
static char * read_file(char* filename, char* output_buffer) {
	output_buffer = NULL;
	FILE *fp = fopen(filename, "r");
	if (fp != NULL) {
	    /* Go to the end of the file. */
	    if (fseek(fp, 0L, SEEK_END) == 0) {
		/* Get the size of the file. */
		long bufsize = ftell(fp);
		if (bufsize == -1) { /* Error */ }

		/* Allocate our buffer to that size. */
		output_buffer = malloc(sizeof(char) * (bufsize + 1));

		/* Go back to the start of the file. */
		if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

		/* Read the entire file into memory. */
		size_t newLen = fread(output_buffer, sizeof(char), bufsize, fp);
		if ( ferror( fp ) != 0 ) {
		    fputs("Error reading file", stderr);
		} else {
		    output_buffer[newLen++] = '\0'; /* Just to be safe. */
		}
	    }
	    fclose(fp);
	}
	return output_buffer;
}

int main(int argv, char * argc) {
	printf("hello world");
}
