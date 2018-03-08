#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include "../mime/mime.h"

namespace mime
{
namespace private_
{
std::string ext_from_string_(std::string path);
}
}

TEST_CASE("We can properly extract extensions from paths")
{
    REQUIRE(mime::private_::ext_from_string_("hello.gif") == "gif");
    REQUIRE(mime::private_::ext_from_string_("hello.old.gif") == "gif");
    REQUIRE(mime::private_::ext_from_string_("HELLO.GIF") == "gif");
    REQUIRE(mime::private_::ext_from_string_("/foobar/hello.gif") == "gif");
    REQUIRE(mime::private_::ext_from_string_("/.foobar/hello.gif") == "gif");
    REQUIRE(mime::private_::ext_from_string_("/foo.foobar/hello.gif") == "gif");
    REQUIRE(mime::private_::ext_from_string_("gif") == "gif");
    REQUIRE(mime::private_::ext_from_string_(".gif") == "gif");
    REQUIRE(mime::private_::ext_from_string_("C:\\path\\to\\PAGE.HTML") == "html");
    REQUIRE(mime::private_::ext_from_string_("/path/to/.json") == "");
    REQUIRE(mime::private_::ext_from_string_("/path/to/.config.json") == "json");
    REQUIRE(mime::private_::ext_from_string_(".config.json") == "json");
}

SCENARIO("mime")
{
    GIVEN("::lookup(extension)")
    {
        THEN("it should return mime type for '.html'")
        {
            REQUIRE(mime::lookup(".html") == "text/html");
        }

        THEN("it should return mime type for '.js'")
        {
            REQUIRE(mime::lookup(".js") == "application/javascript");
        }

        THEN("it should return mime type for '.json'")
        {
            REQUIRE(mime::lookup(".json") == "application/json");
        }

        THEN("it should return mime type for '.rtf'")
        {
            REQUIRE(mime::lookup(".rtf") == "application/rtf");
        }

        THEN("it should return mime type for '.txt'")
        {
            REQUIRE(mime::lookup(".txt") == "text/plain");
        }

        THEN("it should return mime type for '.xml'")
        {
            REQUIRE(mime::lookup(".xml") == "application/xml");
        }

        THEN("it should work without the leading dot")
        {
            REQUIRE(mime::lookup("html") == "text/html");
            REQUIRE(mime::lookup("xml") == "application/xml");
        }

        THEN("it should be case insensitive")
        {
            REQUIRE(mime::lookup("HTML") == "text/html");
            REQUIRE(mime::lookup(".Xml") == "application/xml");
        }

        THEN("it should throw an exception for unknown extension")
        {
            REQUIRE_THROWS(mime::lookup(".bogus"));
            REQUIRE_THROWS(mime::lookup("bogus"));
        }
    }

    GIVEN(".lookup(path)")
    {
        THEN("it should return mime type for file name")
        {
            REQUIRE(mime::lookup("page.html") == "text/html");
        }

        THEN("it should return mime type for relative path")
        {
            REQUIRE(mime::lookup("path/to/page.html") == "text/html");
            REQUIRE(mime::lookup("path\\to\\page.html") == "text/html");
        }

        THEN("it should return mime type for absolute path")
        {
            REQUIRE(mime::lookup("/path/to/page.html") == "text/html");
            REQUIRE(mime::lookup("C:\\path\\to\\page.html") == "text/html");
        }

        THEN("it should be case insensitive")
        {
            REQUIRE(mime::lookup("/path/to/PAGE.HTML") == "text/html");
            REQUIRE(mime::lookup("C:\\path\\to\\PAGE.HTML") == "text/html");
        }

        THEN("it should throw for unknown extension")
        {
            REQUIRE_THROWS(mime::lookup("/path/to/file.bogus"));
        }

        THEN("it should throw for path without extension")
        {
            REQUIRE_THROWS(mime::lookup("/path/to/json"));
        }

        GIVEN("path with dotfile")
        {
            THEN("it should throw when extension-less")
            {
                REQUIRE_THROWS(mime::lookup("/path/to/.json"));
            }

            THEN("it should return mime type when there is extension")
            {
                REQUIRE(mime::lookup("/path/to/.config.json") == "application/json");
            }

            THEN("it should return mime type when there is extension, but no path")
            {
                REQUIRE(mime::lookup(".config.json") == "application/json");
            }
        }
    }
}