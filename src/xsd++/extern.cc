/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "base64.h"   /* for xsd::base64   */
#include "boolean.h"  /* for xsd::boolean  */
#include "date.h"     /* for xsd::date     */
#include "datetime.h" /* for xsd::datetime */
#include "decimal.h"  /* for xsd::decimal  */
#include "double.h"   /* for xsd::double   */
#include "duration.h" /* for xsd::duration */
#include "extern.h"   /* for xsd_*()       */
#include "float.h"    /* for xsd::float    */
#include "integer.h"  /* for xsd::integer  */
#include "string.h"   /* for xsd::string   */
#include "time.h"     /* for xsd::time     */

#include <cassert>    /* for assert()  */
#include <cerrno>     /* for E*, errno */
#include <cstring>    /* for strdup()  */
#include <new>        /* for std::bad_alloc */
#include <stdexcept>  /* for std::invalid_argumen */
#include <typeinfo>   /* for std::bad_cast */

////////////////////////////////////////////////////////////////////////////////

template<typename T>
static bool
canonicalize(char** literal) {
  try {
    T value{*literal};
    if (value.canonicalize()) {
      free(*literal);
      *literal = strdup(value.c_str());
      return true;
    }
  }
  catch (const std::bad_alloc& error) {
    errno = ENOMEM; /* Out of memory */
  }
  catch (const std::invalid_argument& error) {
    errno = EINVAL; /* Invalid argument */
  }
  return false;
}

template<typename T, typename U>
static T
safe_cast(const char* literal) {
  try {
    return static_cast<T>(U{literal});
  }
  catch (const std::bad_cast& error) {
    errno = EINVAL; /* Invalid argument */
    return static_cast<T>(0);
  }
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_base64_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::base64{literal}.validate();
}

bool
xsd_base64_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::base64>(literal);
}

const char*
xsd_base64_value(const char* literal) {
  assert(literal != nullptr);

  return literal;
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_boolean_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::boolean{literal}.validate();
}

bool
xsd_boolean_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::boolean>(literal);
}

bool
xsd_boolean_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<bool, xsd::boolean>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_date_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::date{literal}.validate();
}

bool
xsd_date_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::date>(literal);
}

int64_t
xsd_date_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<int64_t, xsd::date>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_datetime_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::datetime{literal}.validate();
}

bool
xsd_datetime_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::datetime>(literal);
}

int64_t
xsd_datetime_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<int64_t, xsd::datetime>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_decimal_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::decimal{literal}.validate();
}

bool
xsd_decimal_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::decimal>(literal);
}

double
xsd_decimal_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<double, xsd::decimal>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_double_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::double_{literal}.validate();
}

bool
xsd_double_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::double_>(literal);
}

double
xsd_double_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<double, xsd::double_>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_duration_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::duration{literal}.validate();
}

bool
xsd_duration_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::duration>(literal);
}

// TODO: xsd_duration_value(const char* literal);

////////////////////////////////////////////////////////////////////////////////

bool
xsd_float_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::float_{literal}.validate();
}

bool
xsd_float_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::float_>(literal);
}

float
xsd_float_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<float, xsd::float_>(literal);
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_integer_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::integer{literal}.validate();
}

bool
xsd_integer_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::integer>(literal);
}

std::intmax_t
xsd_integer_value(const char* literal,
                  const std::intmax_t min_value,
                  const std::intmax_t max_value) {
  assert(literal != nullptr);

  std::error_condition error;
  const auto value = xsd::integer::parse(literal, min_value, max_value, error);
  if (error) errno = error.value();
  return value;
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_string_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::string{literal}.validate();
}

bool
xsd_string_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::string>(literal);
}

const char*
xsd_string_value(const char* literal) {
  assert(literal != nullptr);

  return literal;
}

////////////////////////////////////////////////////////////////////////////////

bool
xsd_time_validate(const char* const literal) {
  assert(literal != nullptr);

  return xsd::time{literal}.validate();
}

bool
xsd_time_canonicalize(char** literal) {
  assert(literal != nullptr);
  assert(*literal != nullptr);

  return canonicalize<xsd::time>(literal);
}

int64_t
xsd_time_value(const char* literal) {
  assert(literal != nullptr);

  return safe_cast<int64_t, xsd::time>(literal);
}
