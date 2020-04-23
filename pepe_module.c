/* Include the required headers from httpd */
#include "httpd.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_request.h"

/* std lib */
#include <stdio.h>
#include <stdlib.h>

/* Muh macros bruh */
#define TARGET_STRING ("[HASH_TARGET]")

/* Define prototypes of our functions in this module */
static void register_hooks(apr_pool_t *pool);
static int pepe_handler(request_rec *r);

/* Define our module as an entity and assign a function for registering hooks  */

module AP_MODULE_DECLARE_DATA   pepe_module =
{
	STANDARD20_MODULE_STUFF,
	NULL,            // Per-directory configuration handler
	NULL,            // Merge handler for per-directory configurations
	NULL,            // Per-server configuration handler
    NULL,            // Merge handler for per-server configurations
    NULL,            // Any directives we may have for httpd
    register_hooks   // Our hook registering function
};


/* register_hooks: Adds a hook to the httpd process */
static void register_hooks(apr_pool_t *pool) 
{
    
    /* Hook the request handler */
    ap_hook_handler(pepe_handler, NULL, NULL, APR_HOOK_LAST);
}

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
/* The handler function for our module.
 * This is where all the fun happens!
 */

static int pepe_handler(request_rec *r)
{
	/* First off, we need to check if this is a call for the "pepe" handler.
	* If it is, we accept it and do our things, it not, we simply return DECLINED,
	* and Apache will try somewhere else.
	*/
	if (!r->handler || strcmp(r->handler, "pepe-handler")) return (DECLINED);

	char* filename = r->filename;
	char* ip = r->useragent_ip;






	//Read in file to parse
	char * contents; 
	read_file(filename, contents);





	//Outputting html
	ap_set_content_type(r, "text/html");
	
	// The first thing we will do is write a simple "Hello, world!" back to the client.
	ap_rputs("<br>Hello, world!<br/>", r);

	ap_rprintf(r, "<h2> Filename: %s</h2>", filename);
	ap_rprintf(r, "<h2> IP: %s</h2>", ip);

	//Attempt to write out finished file
	//ap_rprintf(r, contents);


	//cleanup
	free(contents);
	return OK;
}
