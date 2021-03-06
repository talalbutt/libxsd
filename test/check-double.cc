/* This is free and unencumbered software released into the public domain. */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "catch.hpp"

#include <xsd++/double.h> /* for xsd::double */

#include <cmath>          /* for std::isinf(), std::isnan() */

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing empty literals") {
  GIVEN("the empty string") {
    REQUIRE_THROWS_AS(xsd::double_::parse(""), std::invalid_argument);
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("parsing literals representing special values") {
  GIVEN("positive zero (+0.0)") {
    REQUIRE(xsd::double_::parse("0.0").value() == 0.0f);
    REQUIRE(xsd::double_::parse("+0.0").value() == 0.0f);
  }
  GIVEN("negative zero (-0.0)") {
    REQUIRE(xsd::double_::parse("-0.0").value() == -0.0f);
  }
  GIVEN("positive infinity (+INF)") {
    REQUIRE(std::isinf(xsd::double_::parse("INF").value()));
    REQUIRE(std::isinf(xsd::double_::parse("+INF").value()));
  }
  GIVEN("negative infinity (-INF)") {
    REQUIRE(std::isinf(xsd::double_::parse("-INF").value()));
  }
  GIVEN("not a number (NaN)") {
    REQUIRE(std::isnan(xsd::double_::parse("NaN").value()));
  }
}

////////////////////////////////////////////////////////////////////////////////

SCENARIO("canonicalizing literals representing special values") {
  std::string literal;
  GIVEN("positive zero (+0.0)") {
    REQUIRE(xsd::double_::canonicalize(literal = "0.0") == true);
    REQUIRE(literal == "0.0E0");
    REQUIRE(xsd::double_::canonicalize(literal = "+0.0") == true);
    REQUIRE(literal == "0.0E0");
  }
  GIVEN("negative zero (-0.0)") {
    REQUIRE(xsd::double_::canonicalize(literal = "-0.0") == true);
    REQUIRE(literal == "0.0E0");
  }
  GIVEN("positive infinity (+INF)") {
    REQUIRE(xsd::double_::canonicalize(literal = "INF") == false);
    REQUIRE(literal == "INF");
    REQUIRE(xsd::double_::canonicalize(literal = "+INF") == true);
    REQUIRE(literal == "INF");
  }
  GIVEN("negative infinity (-INF)") {
    REQUIRE(xsd::double_::canonicalize(literal = "-INF") == false);
    REQUIRE(literal == "-INF");
  }
  GIVEN("not a number (NaN)") {
    REQUIRE(xsd::double_::canonicalize(literal = "NaN") == false);
    REQUIRE(literal == "NaN");
  }
}
