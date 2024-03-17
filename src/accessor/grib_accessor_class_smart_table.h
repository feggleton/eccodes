/*
 * (C) Copyright 2005- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
 * virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
 */

/*****************************************
 *  Enrico Fucile
 ****************************************/


#pragma once

#include "../grib_api_internal.h"
#include "grib_accessor_class_unsigned.h"
#include <cctype>


class grib_accessor_smart_table_t : public grib_accessor_unsigned_t
{
public:
    const char* values;
    const char* tablename;
    const char* masterDir;
    const char* localDir;
    const char* extraDir;
    const char* extraTable;
    int widthOfCode;
    long* tableCodes;
    size_t tableCodesSize;
    grib_smart_table* table;
    int dirty;
};


class grib_accessor_class_smart_table_t : public grib_accessor_class_unsigned_t
{
public:
    grib_accessor_class_smart_table_t(const char* name) : grib_accessor_class_unsigned_t(name) {}
    grib_accessor* create_empty_accessor() override { return new grib_accessor_smart_table_t{}; }
    int get_native_type(grib_accessor*) override;
    int unpack_long(grib_accessor*, long* val, size_t* len) override;
    int unpack_string(grib_accessor*, char*, size_t* len) override;
    int value_count(grib_accessor*, long*) override;
    void destroy(grib_context*, grib_accessor*) override;
    void dump(grib_accessor*, grib_dumper*) override;
    void init(grib_accessor*, const long, grib_arguments*) override;
};
