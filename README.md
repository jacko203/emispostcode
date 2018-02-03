# emispostcode

INSTALLING
Create binary compiling C source code.

USAGE
emispostcode inputfile.csv outputfile.xml [column_number]

where emispostcode is the binary
inputfile.csv is the file containing postcodes in column format (no duplicates)
outputfile.xml is the search file that can be loaded into EMIS
column_number is optional and denotes the column which the postcodes are in, leftmost being 1.

The CSV file must not have column headers (first line is first postcode).
