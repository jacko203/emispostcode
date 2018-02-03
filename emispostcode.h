// Released under GNU GPL
// Copywrite Rob Jackson


#define EPC_EMIS_ID_LENGTH 36

#define EPC_INITIAL_OUT \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\
<enquiryDocument xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" schemaVersion=\"32.0.0\" version=\"1.0.0\" xmlns=\"http://www.e-mis.com/emisopen\">\
<id>%s</id>\
<creationTime>2018-01-03T11:29:48.0968914+00:00</creationTime>\
<report>\
<id>82afdd40-fc68-4143-a440-e557a4e062a7</id>\
<name>Boundary search</name>\
<description />\
<creationTime>2018-01-03T11:29:27.4310059+00:00</creationTime>\
<author><userInRole>f3cfb3cf-ddb8-4fd7-85a5-580a0f920a0c</userInRole></author>\
<populationType>PATIENT</populationType>\
<folder>53a1b5ad-3fce-43d5-a888-2a6760c6ae88</folder>\
<parent parentType=\"ACTIVE\" />\
<searchDate>BASELINE</searchDate>\
<population>"

#define EPC_LOOP_OUT \
"<criteriaGroup>\
<definition>\
<memberOperator>AND</memberOperator>\
<criteria>\
<criterion>\
<id>%s</id>\
<table>PATIENTS</table>\
<displayName>Patient Details</displayName>\
<negation>false</negation>\
<filterAttribute>\
<columnValue>\
<id>%s</id>\
<column>POSTCODE</column>\
<displayName>Postcode</displayName>\
<inNotIn>IN</inNotIn>\
<singleValue>\
<variable>\
<value>%s</value>\
</variable>\
</singleValue>\
</columnValue>\
</filterAttribute>\
</criterion>\
</criteria>\
</definition>\
<actionIfTrue>REJECT</actionIfTrue>\
actionIfFalse>NEXT</actionIfFalse>\
<id>%s</id>\
</criteriaGroup>"


#define EPC_END_OUT "\
<criteriaGroup>\
<definition>\
<memberOperator>AND</memberOperator>\
<criteria>\
<criterion>\
<id>%s</id>\
<table>PATIENTS</table>\
<displayName>Patient Details</displayName>\
<negation>false</negation>\
<filterAttribute>\
<columnValue>\
<id>%s</id>\
<column>POSTCODE</column>\
<displayName>Postcode</displayName>\
<inNotIn>IN</inNotIn>\
<singleValue>\
<variable>\
<value>%s</value>\
</variable>\
</singleValue>\
</columnValue>\
</filterAttribute>\
</criterion>\
</criteria>\
</definition>\
<actionIfTrue>REJECT</actionIfTrue>\
<actionIfFalse>NEXT</actionIfFalse>\
<id>%s</id>\
</criteriaGroup>\
</population>\
</report>\
</enquiryDocument>"

struct pcode
{
    char code[6];
    struct pcode *next;
};

struct pcode* import_file(char*, int);
void err(char *);
void write_postcodes(struct pcode*, char*);
char* create_rand_emis_id(void);
char* create_rand_hex(int);
void* epc_malloc(int);
