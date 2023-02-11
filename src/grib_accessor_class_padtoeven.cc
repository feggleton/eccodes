/*
 * (C) Copyright 2005- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
 * virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
 */

/**************************************
 *  Enrico Fucile
 **************************************/


#include "grib_api_internal.h"
/*
   This is used by make_class.pl

   START_CLASS_DEF
   CLASS      = accessor
   SUPER      = grib_accessor_class_padding
   IMPLEMENTS = init;preferred_size
   MEMBERS=const char*  section_offset
   MEMBERS=const char*  section_length
   END_CLASS_DEF

 */

/* START_CLASS_IMP */

/*

Don't edit anything between START_CLASS_IMP and END_CLASS_IMP
Instead edit values between START_CLASS_DEF and END_CLASS_DEF
or edit "accessor.class" and rerun ./make_class.pl

*/

static void init(grib_accessor*, const long, grib_arguments*);
static void init_class(grib_accessor_class*);
static size_t preferred_size(grib_accessor*, int);

typedef struct grib_accessor_padtoeven
{
    grib_accessor att;
    /* Members defined in gen */
    /* Members defined in bytes */
    /* Members defined in padding */
    /* Members defined in padtoeven */
    const char*  section_offset;
    const char*  section_length;
} grib_accessor_padtoeven;

extern grib_accessor_class* grib_accessor_class_padding;

static grib_accessor_class _grib_accessor_class_padtoeven = {
    &grib_accessor_class_padding,                      /* super */
    "padtoeven",                      /* name */
    sizeof(grib_accessor_padtoeven),  /* size */
    0,                           /* inited */
    &init_class,                 /* init_class */
    &init,                       /* init */
    0,                  /* post_init */
    0,                    /* free mem */
    0,                       /* describes himself */
    0,                /* get length of section */
    0,              /* get length of string */
    0,                /* get number of values */
    0,                 /* get number of bytes */
    0,                /* get offset to bytes */
    0,            /* get native type */
    0,                /* get sub_section */
    0,               /* grib_pack procedures long */
    0,                 /* grib_pack procedures long */
    0,                  /* grib_pack procedures long */
    0,                /* grib_unpack procedures long */
    0,                /* grib_pack procedures double */
    0,              /* grib_unpack procedures double */
    0,                /* grib_pack procedures string */
    0,              /* grib_unpack procedures string */
    0,          /* grib_pack array procedures string */
    0,        /* grib_unpack array procedures string */
    0,                 /* grib_pack procedures bytes */
    0,               /* grib_unpack procedures bytes */
    0,            /* pack_expression */
    0,              /* notify_change */
    0,                /* update_size */
    &preferred_size,             /* preferred_size */
    0,                     /* resize */
    0,      /* nearest_smaller_value */
    0,                       /* next accessor */
    0,                    /* compare vs. another accessor */
    0,      /* unpack only ith value */
    0,  /* unpack a given set of elements */
    0,     /* unpack a subarray */
    0,                      /* clear */
    0,                 /* clone accessor */
};


grib_accessor_class* grib_accessor_class_padtoeven = &_grib_accessor_class_padtoeven;


static void init_class(grib_accessor_class* c)
{
    c->dump    =    (*(c->super))->dump;
    c->next_offset    =    (*(c->super))->next_offset;
    c->string_length    =    (*(c->super))->string_length;
    c->value_count    =    (*(c->super))->value_count;
    c->byte_count    =    (*(c->super))->byte_count;
    c->byte_offset    =    (*(c->super))->byte_offset;
    c->get_native_type    =    (*(c->super))->get_native_type;
    c->sub_section    =    (*(c->super))->sub_section;
    c->pack_missing    =    (*(c->super))->pack_missing;
    c->is_missing    =    (*(c->super))->is_missing;
    c->pack_long    =    (*(c->super))->pack_long;
    c->unpack_long    =    (*(c->super))->unpack_long;
    c->pack_double    =    (*(c->super))->pack_double;
    c->unpack_double    =    (*(c->super))->unpack_double;
    c->pack_string    =    (*(c->super))->pack_string;
    c->unpack_string    =    (*(c->super))->unpack_string;
    c->pack_string_array    =    (*(c->super))->pack_string_array;
    c->unpack_string_array    =    (*(c->super))->unpack_string_array;
    c->pack_bytes    =    (*(c->super))->pack_bytes;
    c->unpack_bytes    =    (*(c->super))->unpack_bytes;
    c->pack_expression    =    (*(c->super))->pack_expression;
    c->notify_change    =    (*(c->super))->notify_change;
    c->update_size    =    (*(c->super))->update_size;
    c->resize    =    (*(c->super))->resize;
    c->nearest_smaller_value    =    (*(c->super))->nearest_smaller_value;
    c->next    =    (*(c->super))->next;
    c->compare    =    (*(c->super))->compare;
    c->unpack_double_element    =    (*(c->super))->unpack_double_element;
    c->unpack_double_element_set    =    (*(c->super))->unpack_double_element_set;
    c->unpack_double_subarray    =    (*(c->super))->unpack_double_subarray;
    c->clear    =    (*(c->super))->clear;
    c->make_clone    =    (*(c->super))->make_clone;
}

/* END_CLASS_IMP */

static size_t preferred_size(grib_accessor* a, int from_handle)
{
    grib_accessor_padtoeven* self = (grib_accessor_padtoeven*)a;
    long offset                   = 0;
    long length                   = 0;
    long seclen;

    grib_get_long_internal(grib_handle_of_accessor(a), self->section_offset, &offset);
    grib_get_long_internal(grib_handle_of_accessor(a), self->section_length, &length);

    if ((length % 2) && from_handle) {
#if 0
        grib_context_log(a->context,
                GRIB_LOG_ERROR,"GRIB message has an odd length section (%ld, %s)",
                (long)length,a->name);
#endif
        return 0;
    }

    /* printf("EVEN %ld %ld\n",(long) a->offset,(long) offset);*/
    seclen = a->offset - offset;

    return (seclen % 2) ? 1 : 0;
}

static void init(grib_accessor* a, const long len, grib_arguments* args)
{
    grib_accessor_padtoeven* self = (grib_accessor_padtoeven*)a;

    self->section_offset = grib_arguments_get_name(grib_handle_of_accessor(a), args, 0);
    self->section_length = grib_arguments_get_name(grib_handle_of_accessor(a), args, 1);

    a->length = preferred_size(a, 1);
}