/*
 * (C) Copyright 2005- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
 * virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
 */

#pragma once

#include "grib_api_internal.h"
#include "step.h"
#include <optional>

std::optional<Step> get_step(grib_handle* h, const char* value_key, const char* unit_key);
bool is_future_output_enabled(grib_handle* h);
int set_step(grib_handle* h, const std::string& value_key, const std::string& unit_key, const Step& step);
