/*
 *      Copyright (C) 2001 Nikos Mavroyanopoulos
 *
 * This file is part of GNUTLS.
 *
 * GNUTLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GNUTLS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include <defines.h>
#include "gnutls_int.h"
#include "gnutls_extensions.h"
#include "gnutls_errors.h"

#include "ext_srp.h"

/* Key Exchange Section */
#define GNUTLS_EXTENSION_ENTRY(type, ext_func_recv, ext_func_send) \
	{ #type, type, ext_func_recv, ext_func_send }

typedef struct {
	char *name;
	int type;
	int (*gnutls_ext_func_recv)( GNUTLS_STATE, const opaque*, int); /* recv data */
	int (*gnutls_ext_func_send)( GNUTLS_STATE, opaque**); /* send data */
} gnutls_extension_entry;

#define MAX_EXT 256 /* maximum supported extension */
static gnutls_extension_entry extensions[] = {
	GNUTLS_EXTENSION_ENTRY(GNUTLS_EXTENSION_SRP, NULL, NULL),
	{0}
};

#define GNUTLS_EXTENSION_LOOP2(b) \
        gnutls_extension_entry *p; \
                for(p = extensions; p->name != NULL; p++) { b ; }

#define GNUTLS_EXTENSION_LOOP(a) \
                        GNUTLS_EXTENSION_LOOP2( if(p->type == type) { a; break; } )


/* EXTENSION functions */

void* _gnutls_ext_func_recv(int type)
{
	void* ret=NULL;
	GNUTLS_EXTENSION_LOOP(ret = p->gnutls_ext_func_recv);
	return ret;

}
void* _gnutls_ext_func_send(int type)
{
	void* ret=NULL;
	GNUTLS_EXTENSION_LOOP(ret = p->gnutls_ext_func_send);
	return ret;

}

void _gnutls_tolow(char *str, int size);
char *_gnutls_extension_get_name(int type)
{
	char *ret = NULL;
	char *pointerTo_;

	/* avoid prefix */
	GNUTLS_EXTENSION_LOOP(ret = strdup(p->name + sizeof("EXTENSION_") - 1));

	if (ret != NULL) {
		_gnutls_tolow(ret, strlen(ret));
		pointerTo_ = strchr(ret, '_');

		while (pointerTo_ != NULL) {
			*pointerTo_ = '-';
			pointerTo_ = strchr(ret, '_');
		}
	}
	return ret;
}

int _gnutls_parse_extensions( GNUTLS_STATE state, const opaque* data, int data_size) {
int next, size, pos=0;
int type;
const opaque* sdata;
int (*ext_func_recv)( GNUTLS_STATE, const opaque*, int);

	if (data_size < 2) return 0;
	next = *((uint16*) &data);
	if (data_size < next) return 0;
	
	pos+=2;
	
	do {
		next--; if (next < 0) return 0;
		type = *((uint8*)&data[pos]);
		pos++;

		next-=2; if (next < 0) return 0;
		size = *((uint16*)&data[pos]);
		pos+=2;
		
		sdata = &data[pos];
		pos+=size;
		next-=size; if (next < 0) return 0;
		
		ext_func_recv = _gnutls_ext_func_recv(type);
		if (ext_func_recv == NULL) continue;
		ext_func_recv( state, sdata, size);
		
	} while(next > 2);

	return 0;

}

int _gnutls_gen_extensions( GNUTLS_STATE state, opaque** data) {
int next, size;
uint16 pos=0;
opaque* sdata;
int (*ext_func_send)( GNUTLS_STATE, opaque**);


	(*data) = gnutls_malloc(2); /* allocate size for size */
	pos+=2;
	
	next = MAX_EXT; /* maximum supported extensions */
	do {
		next--;
		ext_func_send = _gnutls_ext_func_send(next);
		if (ext_func_send == NULL) continue;
		size = ext_func_send( state, &sdata);
		if (size > 0) {
			(*data) = gnutls_realloc( (*data), pos+size);
			memcpy( &(*data)[pos], sdata, size);
			pos+=size;
			gnutls_free(sdata);
		}
		
	} while(next >= 0);

	size = pos;
	pos-=2; /* remove the size of the size header! */
#ifndef WORDS_BIGENDIAN
	pos = byteswap16(pos);
#endif
	memcpy( (*data), &pos, sizeof(uint16));

	if (size==2) { /* empty */
		size = 0;
		gnutls_free(*data);
		(*data) = NULL;
	}
	return size;

}
