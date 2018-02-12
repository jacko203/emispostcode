// Released under GNU GPL
// Copywrite Rob Jackson


#define EPC_EMIS_ID_LENGTH 36

#define EPC_INITIAL_OUT \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\
<enquiryDocument xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xs=\"http://www.w3.org/2001/XMLSchema\" schemaVersion=\"32.0.0\" version=\"1.0.0\" xmlns=\"http://www.e-mis.com/emisopen\">\
<id>%s</id>\
<creationTime>2018-02-12T15:04:49.4009678+00:00</creationTime>\
<report>\
<id>%s</id>\
<name>Boundary search</name>\
<description />\
<creationTime>2018-02-12T15:04:21.4761241+00:00</creationTime>\
<author><userInRole>%s</userInRole></author>\
<populationType>PATIENT</populationType>\
<folder>%s</folder>\
<parent parentType=\"ACTIVE\" />\
<searchDate>BASELINE</searchDate>\
<population>\
<criteriaGroup>\
<definition>\
<memberOperator>OR</memberOperator>"

#define EPC_LOOP_OUT \
"<criteria>\
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
<value>%s*</value>\
</variable>\
</singleValue>\
</columnValue>\
</filterAttribute>\
</criterion>\
</criteria>"


#define EPC_END_OUT "\
</definition>\
<actionIfTrue>REJECT</actionIfTrue>\
<actionIfFalse>SELECT</actionIfFalse>\
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
