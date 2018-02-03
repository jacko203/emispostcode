// Released under GNU GPL
// Copywrite Rob Jackson
/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emispostcode.h"


int main(int argc, char* argv[])
{
    struct pcode* postcodes;
    char * file;
    char * outfile;
    int commanded_column = 1;

    if (argc == 3)
    {
        file = argv[1];
        outfile = argv[2];
    }

    else if (argc == 4)
    {
        file = argv[1];
        outfile = argv[2];
        commanded_column = (int)strtol(argv[3], NULL, 0);
    }
    else err("no args");

    postcodes = import_file(file, commanded_column);

    if (postcodes) write_postcodes(postcodes, outfile);

    return 0;
}

struct pcode* import_file(char* filename, int commanded_column)
{

    char a;
    int ccount;
    char code[6];
    char *newcode;
    int column = 1;
    struct pcode *return_array, *base_array, *next_array;
    FILE* f;

    base_array = epc_malloc(sizeof(struct pcode));
    return_array = base_array;

    printf("opening file %s, commanded_column=%i\n",filename,commanded_column);

    f = fopen(filename, "r");
        if (!f) err("fopen error");

    do{
        ccount = 0;

        while (1)
        {
            if (column != commanded_column)
            {
              do {
                a = getc(f);
              } while((a != ',') && (a != '\n') && (a != EOF));

              if ((a == EOF) || (a == '\n'))
              {
                column = 1;
                break;
              }
              else column ++;
            }
            else
            {
              a = getc(f);

              if ((a == EOF) || (a=='\n'))
              {
                column = 1;
                break;
              }

              if (a == ',')
              {
                column++;
                a=getc(f); //advance on
              }

              else
              {
                return_array->code[ccount] = a;

                if (ccount <= 6)
                    ccount ++;

                  else err("file read error no comma");
              }

            }
          }
        //test
        printf("out: %s\n",return_array->code);

        if (a != EOF)
        {
            return_array->next = malloc(sizeof(struct pcode));
            return_array = return_array->next;
        }
        else return_array->next = NULL;

    } while (a!= EOF);

    fclose(f);

    return base_array;
}


void err(char * e)
{
    printf("\nError: %s", e);
    exit (0);
}

void write_postcodes(struct pcode* base_array, char* outfile)
{
    FILE* writefile;
    struct pcode* write_array = base_array;
    int a;

    printf("Writing postcodes to %s\n", outfile);

    writefile = fopen(outfile, "w");
    if (writefile == NULL) err("can't write outfile");

    // paste start
    a = fprintf(writefile, EPC_INITIAL_OUT, create_rand_emis_id());
        if (a<0) err("initial write error");

    // loop - insert random into next strings and paste until array 1 off empty (last different)

    do
    {
        a = fprintf(writefile, EPC_LOOP_OUT, create_rand_emis_id(),
                                            create_rand_emis_id(),
                                            write_array->code,
                                            create_rand_emis_id());

        if (a<0) err("loop write error");

        write_array = write_array->next;

    }
    while (write_array->next->next != NULL);

    a = fprintf(writefile, EPC_END_OUT, create_rand_emis_id(),
                                        create_rand_emis_id(),
                                        write_array->code,
                                        create_rand_emis_id());
        if (a<0) err("end write error");

    fclose(writefile);
}

char* create_rand_emis_id(void)
{
    // format = %.8h-%.4h-%.4h-%.4h-%.12h
    int a=0;
    char* string;

    string = epc_malloc(EPC_EMIS_ID_LENGTH);

    a = sprintf(string, "%s-%s-%s-%s-%s", create_rand_hex(8), create_rand_hex(4), create_rand_hex(4), create_rand_hex(4),create_rand_hex(12));
    if (a != EPC_EMIS_ID_LENGTH) err("create error a");

    return string;

    // ideally clean up mallocs from create_rand_hex
}

char* create_rand_hex(int strlength)
{
    char* r_str;
    int a;

    r_str = epc_malloc(strlength);

    for(a = 0; a < strlength ; a++)
        sprintf(r_str + a, "%x", rand() % 16);

    return r_str;
}


void* epc_malloc(int size)
{
    void* m;
    m = malloc(size);
    if(m == NULL) err("malloc err");
    return m;
}
