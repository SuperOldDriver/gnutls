/* File generated by GAA 1.6.2
 */
#define GAA_NO_WIN32
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef GAA_NO_WIN32
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(WINDOWS)
#define GAA_WIN32
#endif
#endif

void* gaa_malloc( size_t size) {
void* ret;
	ret = malloc(size);
	if (ret==NULL) {
		fprintf(stderr, "gaa: could not allocate memory");
		exit(1);
	}
	return ret;
}

void __gaa_helpsingle(char short_name, char *name, 
	char *arg_desc, char *opt_help)
{
     int col1, col3, col4, tabsize = 3, curr;
     int i;

     col1 = 5; /* Default values */
     col3 = 30;
     col4 = 70;

     curr = 0;
     for(i = 0; i < col1; i++)
        {
        printf(" ");
        curr++;
        }
     if(short_name)
        {
        if(name && *name)
          {
            printf("-%c, ", short_name);
            curr += 4;
          }
        else
          {
            printf("-%c ", short_name);
            curr += 3;
          }
        }
     if(name && *name)
        {
          printf("--%s ", name);
          curr += 3 + strlen(name);
        }
     if(arg_desc && *arg_desc)
        {
          printf("%s ", arg_desc);
          curr += 1 + strlen(arg_desc);
        }
     if(curr >= col3)
        {
          printf("\n");
          curr = 0;
        }
     if(opt_help) /* let's print the option's help body */
        {
        const char *str = opt_help;
        while(*str)
          {
             while(curr < col3)
               {
                 printf(" ");
                 curr++;
               }
             switch(*str)
               {
                 case '\n':
                     printf("\n");
                     curr = 0;
                     break;
                 case '\t':
                     do
                        {
                        printf(" ");
                        curr++;
                        }
                     while((curr - col3) % tabsize != 0 && curr < col4);
                 case ' ':
                     if(*str == ' ')
                        {
                        curr++;
                        printf(" ");
                        }
                     for(i = 1; str[i] && str[i] != ' ' && str[i] != '\n'
                        && str[i] != '\t'; i++);
                     if(curr + i - 1 >= col4)
                        curr = col4;
                     break;
                default:
                     printf("%c", *str);
                     curr++;
               }
             if(curr >= col4)
               {
                 printf("\n");
                 curr = 0;
               }
             str++;
          }
        }
     printf("\n");
}

void gaa_help(void)
{
	printf("Certtool help\nUsage : certtool [options]\n");
	__gaa_helpsingle('s', "generate-self-signed", "", "Generate a self-signed certificate.");
	__gaa_helpsingle('c', "generate-certificate", "", "Generate a signed certificate.");
	__gaa_helpsingle('p', "generate-privkey", "", "Generate a private key.");
	__gaa_helpsingle('q', "generate-request", "", "Generate a PKCS #10 certificate request.");
	__gaa_helpsingle('e', "verify-chain", "", "Verify a certificate chain. The last certificate in the chain must be a self signed one.");
	__gaa_helpsingle(0, "load-privkey", "FILE ", "Private key file to use.");
	__gaa_helpsingle(0, "load-ca-privkey", "FILE ", "Certificate authority's private key file to use.");
	__gaa_helpsingle(0, "load-ca-cert", "FILE ", "Certificate authority's certificate file to use.");
	__gaa_helpsingle('i', "cert-info", "", "Print information on a certificate.");
	__gaa_helpsingle('k', "key-info", "", "Print information on a private key.");
	__gaa_helpsingle('8', "pkcs8", "", "Use PKCS #8 format for private keys.");
	__gaa_helpsingle(0, "bits", "BITS ", "specify the number of bits for key generation.");
	__gaa_helpsingle('d', "debug", "LEVEL ", "specify the debug level. Default is 1.");
	__gaa_helpsingle('h', "help", "", "shows this help text");
	__gaa_helpsingle('v', "version", "", "shows the program version");

#line 100 "gaa.skel"
}
/* Copy of C area */

#line 104 "gaa.skel"
/* GAA HEADER */
#ifndef GAA_HEADER_POKY
#define GAA_HEADER_POKY

typedef struct _gaainfo gaainfo;

struct _gaainfo
{
#line 34 "certtool.gaa"
	int debug;
#line 31 "certtool.gaa"
	int bits;
#line 28 "certtool.gaa"
	int pkcs8;
#line 20 "certtool.gaa"
	char *ca;
#line 17 "certtool.gaa"
	char *ca_privkey;
#line 14 "certtool.gaa"
	char *privkey;
#line 3 "certtool.gaa"
	int action;

#line 114 "gaa.skel"
};

#ifdef __cplusplus
extern "C"
{
#endif

    int gaa(int argc, char *argv[], gaainfo *gaaval);

    void gaa_help(void);
    
    int gaa_file(char *name, gaainfo *gaaval);
    
#ifdef __cplusplus
}
#endif


#endif

#line 135 "gaa.skel"

/* C declarations */

#define GAAERROR(x)    \
{                   \
gaa_error = 1;      \
return x;        \
}

char *gaa_current_option;
int gaa_error = 0;

/* Generated by gaa */

#include <string.h>
#include <stdlib.h>


#define GAA_OK                       -1

#define GAA_ERROR_NOMATCH            0
#define GAA_ERROR_NOTENOUGH_ARGS     1
#define GAA_ERROR_INVALID_ARG        2
#define GAA_ERROR_UNKNOWN            3

#define GAA_NOT_AN_OPTION       0
#define GAA_WORD_OPTION         1
#define GAA_LETTER_OPTION       2
#define GAA_MULTIPLE_OPTION     3

#define GAA_REST                0
#define GAA_NB_OPTION           15
#define GAAOPTID_version	1
#define GAAOPTID_help	2
#define GAAOPTID_debug	3
#define GAAOPTID_bits	4
#define GAAOPTID_pkcs8	5
#define GAAOPTID_key_info	6
#define GAAOPTID_cert_info	7
#define GAAOPTID_load_ca_cert	8
#define GAAOPTID_load_ca_privkey	9
#define GAAOPTID_load_privkey	10
#define GAAOPTID_verify_chain	11
#define GAAOPTID_generate_request	12
#define GAAOPTID_generate_privkey	13
#define GAAOPTID_generate_certificate	14
#define GAAOPTID_generate_self_signed	15

#line 168 "gaa.skel"

#define GAA_CHECK1STR(a,b)      \
if(a[0] == str[0])              \
{                               \
    gaa_current_option = a;     \
    return b;                   \
}

#define GAA_CHECKSTR(a,b)                \
if(strcmp(a,str) == 0)                   \
{                                        \
    gaa_current_option = a;              \
    return b;                            \
}

#define GAA_TESTMOREARGS                                                  \
if(!OK)                                                                     \
{                                  \
while((gaa_last_non_option != gaa_index) && (gaa_arg_used[gaa_index] == 1)) \
    gaa_index++;                                                            \
if(gaa_last_non_option == gaa_index)                                        \
    return GAA_ERROR_NOTENOUGH_ARGS; \
}

#define GAA_TESTMOREOPTIONALARGS                                                  \
if(!OK) \
{ \
while((gaa_last_non_option != gaa_index) && (gaa_arg_used[gaa_index] == 1)) \
    gaa_index++;                                                            \
if(gaa_last_non_option == gaa_index)                                        \
    OK = 1; \
}

#define GAA_FILL_2ARGS(target, func)           \
target = func(GAAargv[gaa_index]);       \
gaa_arg_used[gaa_index] = 1;             \
if(gaa_error == 1)                       \
{                                        \
    gaa_error = 0;                       \
    return GAA_ERROR_INVALID_ARG;        \
} 



#define GAA_FILL(target, func, num)           \
if(!OK) \
{ \
target = func(GAAargv[gaa_index]);       \
gaa_arg_used[gaa_index] = 1;             \
if(gaa_error == 1)                       \
{                                        \
    gaa_error = 0;                       \
    return GAA_ERROR_INVALID_ARG;        \
} \
num = 1;  \
} \
else \
{ \
num = 0; \
}

#define GAA_LIST_FILL(target, func, type ,num)                      \
if(!OK) \
{ \
num = 0;                                                            \
target = NULL;                                                      \
if ( gaa_last_non_option - gaa_index > 0)                           \
  target = gaa_malloc((gaa_last_non_option - gaa_index) * sizeof(type));\
for(; gaa_index < gaa_last_non_option; gaa_index++)                 \
{                                                                   \
    if(gaa_arg_used[gaa_index] == 0)                                \
    {                                                               \
        GAA_FILL_2ARGS(target[num], func);                          \
        num++;                                                      \
    }                                                               \
}                                                                   \
if(num == 0)                                                        \
    return GAA_ERROR_NOTENOUGH_ARGS; \
}

#define GAA_OPTIONALLIST_FILL(target, func, type ,num)                      \
if(!OK) \
{ \
num = 0;                                                            \
target = NULL;                                                      \
if ( gaa_last_non_option - gaa_index > 0)                           \
  target = gaa_malloc((gaa_last_non_option - gaa_index) * sizeof(type));\
for(; gaa_index < gaa_last_non_option; gaa_index++)                 \
{                                                                   \
    if(gaa_arg_used[gaa_index] == 0)                                \
    {                                                               \
        GAA_FILL_2ARGS(target[num], func);                                \
        num++;                                                      \
    }                                                               \
} \
}

#define GAA_OBLIGAT(str)                                            \
k = 0;                                                              \
for(i = 0; i < strlen(str); i++)                                    \
{                                                                   \
    j = gaa_get_option_num(str + i, GAA_LETTER_OPTION);           \
    if(j == GAA_ERROR_NOMATCH)                                       \
    {                                                               \
        printf("Error: invalid 'obligat' set\n");                  \
        exit(-1);                                                   \
    }                                                               \
    if(opt_list[j] == 1)                                            \
        k = 1;                                                      \
}                                                                    \
if(k == 0)                                                            \
{                                                                      \
    if(strlen(str) == 1)                                                \
        printf("You must give the -%s option\n", str);                     \
    else                                                                  \
        printf("You must give at least one option of '%s'\n", str);          \
    return 0;         \
}
        
#define GAA_INCOMP(str)                                                \
k = 0;                                                              \
for(i = 0; i < strlen(str); i++)                                    \
{                                                                   \
    j = gaa_get_option_num(str + i, GAA_LETTER_OPTION);           \
    if(j == GAA_ERROR_NOMATCH)                                      \
    {                                                               \
        printf("Error: invalid 'obligat' set\n");                  \
        exit(-1);                                                   \
    }                                                               \
    if(opt_list[j] == 1)                                            \
        k++;                                                      \
}                   \
if(k > 1)                                                            \
{                                                                      \
    printf("The options '%s' are incompatible\n", str);              \
    return 0;                                                          \
}
        

char **GAAargv;
int GAAargc;
char *gaa_arg_used;
int gaa_processing_file = 0;
int inited = 0;

int gaa_getint(char *arg)
{
    int tmp;
    char a;
    if(sscanf(arg, "%d%c", &tmp, &a) != 1)
    {
        printf("Option %s: '%s' isn't an integer\n", gaa_current_option, arg);
        GAAERROR(-1);
    }
    return tmp;
}

char gaa_getchar(char *arg)
{
    if(strlen(arg) != 1)
    {
        printf("Option %s: '%s' isn't an character\n", gaa_current_option, arg);
        GAAERROR(-1);
    }
    return arg[0];
}

char* gaa_getstr(char *arg)
{
    return arg;
}
float gaa_getfloat(char *arg)
{
    float tmp;
    char a;
    if(sscanf(arg, "%f%c", &tmp, &a) != 1)
    {
        printf("Option %s: '%s' isn't a float number\n", gaa_current_option, arg);
        GAAERROR(-1);
    }
    return tmp;
}
/* option structures */

struct GAAOPTION_debug 
{
	int arg1;
	int size1;
};

struct GAAOPTION_bits 
{
	int arg1;
	int size1;
};

struct GAAOPTION_load_ca_cert 
{
	char* arg1;
	int size1;
};

struct GAAOPTION_load_ca_privkey 
{
	char* arg1;
	int size1;
};

struct GAAOPTION_load_privkey 
{
	char* arg1;
	int size1;
};
         
#line 349 "gaa.skel"
int gaa_is_an_argument(char *str)
{
#ifdef GAA_WIN32
    if(str[0] == '/' && str[1] != 0)
	return GAA_MULTIPLE_OPTION;
#endif
    if(str[0] != '-')
        return GAA_NOT_AN_OPTION;
    if(str[1] == 0)
        return GAA_NOT_AN_OPTION;
    if(str[1] == '-')
    {
        if(str[2] != 0)
            return GAA_WORD_OPTION;
        else
            return GAA_NOT_AN_OPTION;
    }
    if(str[2] == 0)
        return GAA_LETTER_OPTION;
    else
        return GAA_MULTIPLE_OPTION;
}

int gaa_get_option_num(char *str, int status)
{
    switch(status)
        {
        case GAA_LETTER_OPTION:
			GAA_CHECK1STR("d", GAAOPTID_debug);
			GAA_CHECK1STR("", GAAOPTID_bits);
			GAA_CHECK1STR("", GAAOPTID_load_ca_cert);
			GAA_CHECK1STR("", GAAOPTID_load_ca_privkey);
			GAA_CHECK1STR("", GAAOPTID_load_privkey);
        case GAA_MULTIPLE_OPTION:
#line 375 "gaa.skel"
			GAA_CHECK1STR("v", GAAOPTID_version);
			GAA_CHECK1STR("h", GAAOPTID_help);
			GAA_CHECK1STR("8", GAAOPTID_pkcs8);
			GAA_CHECK1STR("k", GAAOPTID_key_info);
			GAA_CHECK1STR("i", GAAOPTID_cert_info);
			GAA_CHECK1STR("e", GAAOPTID_verify_chain);
			GAA_CHECK1STR("q", GAAOPTID_generate_request);
			GAA_CHECK1STR("p", GAAOPTID_generate_privkey);
			GAA_CHECK1STR("c", GAAOPTID_generate_certificate);
			GAA_CHECK1STR("s", GAAOPTID_generate_self_signed);

#line 277 "gaa.skel"
        break;
        case GAA_WORD_OPTION:
			GAA_CHECKSTR("version", GAAOPTID_version);
			GAA_CHECKSTR("help", GAAOPTID_help);
			GAA_CHECKSTR("debug", GAAOPTID_debug);
			GAA_CHECKSTR("bits", GAAOPTID_bits);
			GAA_CHECKSTR("pkcs8", GAAOPTID_pkcs8);
			GAA_CHECKSTR("key-info", GAAOPTID_key_info);
			GAA_CHECKSTR("cert-info", GAAOPTID_cert_info);
			GAA_CHECKSTR("load-ca-cert", GAAOPTID_load_ca_cert);
			GAA_CHECKSTR("load-ca-privkey", GAAOPTID_load_ca_privkey);
			GAA_CHECKSTR("load-privkey", GAAOPTID_load_privkey);
			GAA_CHECKSTR("verify-chain", GAAOPTID_verify_chain);
			GAA_CHECKSTR("generate-request", GAAOPTID_generate_request);
			GAA_CHECKSTR("generate-privkey", GAAOPTID_generate_privkey);
			GAA_CHECKSTR("generate-certificate", GAAOPTID_generate_certificate);
			GAA_CHECKSTR("generate-self-signed", GAAOPTID_generate_self_signed);

#line 281 "gaa.skel"
	break;
        default: break;
        }
    return GAA_ERROR_NOMATCH;
}

int gaa_try(int gaa_num, int gaa_index, gaainfo *gaaval, char *opt_list)
{
    int OK = 0;
    int gaa_last_non_option;
	struct GAAOPTION_debug GAATMP_debug;
	struct GAAOPTION_bits GAATMP_bits;
	struct GAAOPTION_load_ca_cert GAATMP_load_ca_cert;
	struct GAAOPTION_load_ca_privkey GAATMP_load_ca_privkey;
	struct GAAOPTION_load_privkey GAATMP_load_privkey;

#line 393 "gaa.skel"
#ifdef GAA_REST_EXISTS
    struct GAAREST GAAREST_tmp;
#endif

    opt_list[gaa_num] = 1;
    
    for(gaa_last_non_option = gaa_index;
        (gaa_last_non_option != GAAargc) && (gaa_is_an_argument(GAAargv[gaa_last_non_option]) == GAA_NOT_AN_OPTION);
        gaa_last_non_option++);

    if(gaa_num == GAA_REST)
    {
        gaa_index = 1;
        gaa_last_non_option = GAAargc;
    }
    
    switch(gaa_num)
    {
	case GAAOPTID_version:
	OK = 0;
#line 39 "certtool.gaa"
{ certtool_version(); exit(0); ;};

		return GAA_OK;
		break;
	case GAAOPTID_help:
	OK = 0;
#line 37 "certtool.gaa"
{ gaa_help(); exit(0); ;};

		return GAA_OK;
		break;
	case GAAOPTID_debug:
	OK = 0;
		GAA_TESTMOREARGS;
		GAA_FILL(GAATMP_debug.arg1, gaa_getint, GAATMP_debug.size1);
		gaa_index++;
#line 35 "certtool.gaa"
{ gaaval->debug = GAATMP_debug.arg1 ;};

		return GAA_OK;
		break;
	case GAAOPTID_bits:
	OK = 0;
		GAA_TESTMOREARGS;
		GAA_FILL(GAATMP_bits.arg1, gaa_getint, GAATMP_bits.size1);
		gaa_index++;
#line 32 "certtool.gaa"
{ gaaval->bits = GAATMP_bits.arg1 ;};

		return GAA_OK;
		break;
	case GAAOPTID_pkcs8:
	OK = 0;
#line 29 "certtool.gaa"
{ gaaval->pkcs8=1 ;};

		return GAA_OK;
		break;
	case GAAOPTID_key_info:
	OK = 0;
#line 25 "certtool.gaa"
{ gaaval->action = 6; ;};

		return GAA_OK;
		break;
	case GAAOPTID_cert_info:
	OK = 0;
#line 23 "certtool.gaa"
{ gaaval->action = 2; ;};

		return GAA_OK;
		break;
	case GAAOPTID_load_ca_cert:
	OK = 0;
		GAA_TESTMOREARGS;
		GAA_FILL(GAATMP_load_ca_cert.arg1, gaa_getstr, GAATMP_load_ca_cert.size1);
		gaa_index++;
#line 21 "certtool.gaa"
{ gaaval->ca = GAATMP_load_ca_cert.arg1 ;};

		return GAA_OK;
		break;
	case GAAOPTID_load_ca_privkey:
	OK = 0;
		GAA_TESTMOREARGS;
		GAA_FILL(GAATMP_load_ca_privkey.arg1, gaa_getstr, GAATMP_load_ca_privkey.size1);
		gaa_index++;
#line 18 "certtool.gaa"
{ gaaval->ca_privkey = GAATMP_load_ca_privkey.arg1 ;};

		return GAA_OK;
		break;
	case GAAOPTID_load_privkey:
	OK = 0;
		GAA_TESTMOREARGS;
		GAA_FILL(GAATMP_load_privkey.arg1, gaa_getstr, GAATMP_load_privkey.size1);
		gaa_index++;
#line 15 "certtool.gaa"
{ gaaval->privkey = GAATMP_load_privkey.arg1 ;};

		return GAA_OK;
		break;
	case GAAOPTID_verify_chain:
	OK = 0;
#line 12 "certtool.gaa"
{ gaaval->action=5; ;};

		return GAA_OK;
		break;
	case GAAOPTID_generate_request:
	OK = 0;
#line 10 "certtool.gaa"
{ gaaval->action=3; ;};

		return GAA_OK;
		break;
	case GAAOPTID_generate_privkey:
	OK = 0;
#line 8 "certtool.gaa"
{ gaaval->action=1; ;};

		return GAA_OK;
		break;
	case GAAOPTID_generate_certificate:
	OK = 0;
#line 6 "certtool.gaa"
{ gaaval->action=4; ;};

		return GAA_OK;
		break;
	case GAAOPTID_generate_self_signed:
	OK = 0;
#line 4 "certtool.gaa"
{ gaaval->action=0; ;};

		return GAA_OK;
		break;

#line 413 "gaa.skel"
    default: break;
    }
    return GAA_ERROR_UNKNOWN;
}

int gaa(int argc, char **argv, gaainfo *gaaval)
{
    int tmp1, tmp2;
    int i, j;
    char *opt_list;

    GAAargv = argv;
    GAAargc = argc;

    opt_list = (char*) gaa_malloc(GAA_NB_OPTION + 1);

    for(i = 0; i < GAA_NB_OPTION + 1; i++)
        opt_list[i] = 0;
    /* initialization */
    if(inited == 0)
    {

#line 41 "certtool.gaa"
{ gaaval->bits = 1024; gaaval->pkcs8 = 0; gaaval->privkey = NULL; gaaval->ca=NULL; gaaval->ca_privkey = NULL; 
	gaaval->debug=1; ;};

    }
    inited = 1;
#line 438 "gaa.skel"
    gaa_arg_used = NULL;

    if (argc > 0) {
      gaa_arg_used = gaa_malloc(argc * sizeof(char));
    }

    for(i = 1; i < argc; i++)
        gaa_arg_used[i] = 0;
    for(i = 1; i < argc; i++)
    {
        if(gaa_arg_used[i] == 0)
        {
            j = 0;
            tmp1 = gaa_is_an_argument(GAAargv[i]);
            switch(tmp1)
            {
            case GAA_WORD_OPTION:
                j++;
            case GAA_LETTER_OPTION:
                j++;
                tmp2 = gaa_get_option_num(argv[i]+j, tmp1);
                if(tmp2 == GAA_ERROR_NOMATCH)
                {
                    printf("Invalid option '%s'\n", argv[i]+j);
                    return 0;
                }
                switch(gaa_try(tmp2, i+1, gaaval, opt_list))
                {
                case GAA_ERROR_NOTENOUGH_ARGS:
                    printf("'%s': not enough arguments\n",gaa_current_option);
                    return 0;
                case GAA_ERROR_INVALID_ARG:
                    printf("Invalid arguments\n");
                    return 0;
                case GAA_OK:
                    break;
                default:
                    printf("Unknown error\n");
                }
                gaa_arg_used[i] = 1;
                break;
            case GAA_MULTIPLE_OPTION:
                for(j = 1; j < strlen(argv[i]); j++)
                {
                    tmp2 = gaa_get_option_num(argv[i]+j, tmp1);
                    if(tmp2 == GAA_ERROR_NOMATCH)
                    {
                        printf("Invalid option '%c'\n", *(argv[i]+j));
                        return 0;
                    }
                    switch(gaa_try(tmp2, i+1, gaaval, opt_list))
                    {
                    case GAA_ERROR_NOTENOUGH_ARGS:
                        printf("'%s': not enough arguments\n",gaa_current_option);
                        return 0;
                    case GAA_ERROR_INVALID_ARG:
                        printf("Invalid arguments\n");
                        return 0;
                    case GAA_OK:
                        break;
                    default:
                        printf("Unknown error\n");
                    }
                }
                gaa_arg_used[i] = 1;
                break;
            default: break;
            }
        }
    }
if(gaa_processing_file == 0)
{

#line 507 "gaa.skel"
#ifdef GAA_REST_EXISTS
    switch(gaa_try(GAA_REST, 1, gaaval, opt_list))
    {
    case GAA_ERROR_NOTENOUGH_ARGS:
        printf("Rest: not enough arguments\n");
        return 0;
    case GAA_ERROR_INVALID_ARG:
        printf("Invalid arguments\n");
        return 0;
    case GAA_OK:
        break;
    default:
        printf("Unknown error\n");
    }
#endif
}
    for(i = 1; i < argc; i++)
    {
        if(gaa_arg_used[i] == 0)
        {
            printf("Too many arguments\n");
            return 0;
        }
    }
    free(gaa_arg_used);
    free(opt_list);
    return -1;
}

struct gaastrnode
{
    char *str;
    struct gaastrnode *next;
};

typedef struct gaastrnode gaa_str_node;

int gaa_internal_get_next_str(FILE *file, gaa_str_node *tmp_str, int argc)
{
    int pos_ini;
    char a;
    int i = 0, len = 0, newline = 0;

    if(argc == 1) {
        newline = 1;
        len = 2;
    }
    
    if(fscanf(file,"%c", &a) != 1) return 0;

    while(a == ' ' || a == 9 || a == '\n')
    {
        if(a == '\n')
        {
            newline=1;
            len = 2;
        }
        if(fscanf(file,"%c", &a) != 1) return 0;
    }

    pos_ini = ftell(file) - 1;

    while(a != ' ' && a != 9 && a != '\n')
    {

        len++;
        if(fscanf(file,"%c", &a) != 1) a = ' ';
    }

    len += 1;
    tmp_str->str = gaa_malloc((len) * sizeof(char));

    if(newline == 1)
    {
        tmp_str->str[0] = '-';
        tmp_str->str[1] = '-';
        i = 2;
    }
    else
    {
        i = 0;
    }

    fseek(file,pos_ini, SEEK_SET);
    do
    {
        if(fscanf(file, "%c", &a) != 1)
        {
            i+=2;
            break;
        }
        tmp_str->str[i] = a;
        i++;
    }
    while(a != ' ' && a != 9 && a != '\n' && i < len);

    tmp_str->str[i - 1] = 0;

    fseek(file,- 1, SEEK_CUR);
/*    printf("%d\n", ftell(file)); */
    
    return -1;
}

int gaa_file(char *name, gaainfo *gaaval)
{
    gaa_str_node *first_str, **tmp_str, *tmp_str2;
    int rval, i;
    char **argv;
    int argc = 0;
    FILE *file;

    gaa_processing_file = 1;
    
    if((file = fopen(name, "r")) == NULL)
    {
        printf("Couldn't open '%s' configuration file for reading\n", name);
        return 0;
    }
    
    tmp_str = &first_str;
    do
    {
        argc++;
        *tmp_str = gaa_malloc(sizeof(gaa_str_node));

        (*tmp_str)->str = NULL;
        (*tmp_str)->next = NULL;

        rval = gaa_internal_get_next_str(file, *tmp_str, argc);
        tmp_str = &((*tmp_str)->next);
    }
    while(rval == -1);
    
    if(rval == 1)
        return 0;
    
    argv = gaa_malloc((1 + argc) * sizeof(char*));

    tmp_str2 = first_str;
    argv[0] = "cfg";
    for(i = 1; i < argc; i++)
    {
        argv[i] = tmp_str2->str;
        tmp_str2 = tmp_str2->next;
    }

    rval = gaa(argc, argv, gaaval);
    gaa_processing_file = 0;
    return rval;
}
