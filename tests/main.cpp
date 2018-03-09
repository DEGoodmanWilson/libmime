#define CATCH_CONFIG_MAIN

#include <catch.hpp>

const std::string mimedb_file = MIMEDB_FILE;

#include <mime/mime.h>

TEST_CASE("We can properly extract extensions from paths")
{
    REQUIRE(mime::impl::get_extension_from_path("hello.gif") == "gif");
    REQUIRE(mime::impl::get_extension_from_path("hello.old.gif") == "gif");
    REQUIRE(mime::impl::get_extension_from_path("HELLO.GIF") == "gif");
    REQUIRE(mime::impl::get_extension_from_path("/foobar/hello.gif") == "gif");
    REQUIRE(mime::impl::get_extension_from_path("/.foobar/hello.gif") == "gif");
    REQUIRE(mime::impl::get_extension_from_path("/foo.foobar/hello.gif") == "gif");
    REQUIRE(mime::impl::get_extension_from_path("gif") == "gif");
    REQUIRE(mime::impl::get_extension_from_path(".gif") == "gif");
    REQUIRE(mime::impl::get_extension_from_path("C:\\path\\to\\PAGE.HTML") == "html");
    REQUIRE(mime::impl::get_extension_from_path("/path/to/.json") == "");
    REQUIRE(mime::impl::get_extension_from_path("/path/to/.config.json") == "json");
    REQUIRE(mime::impl::get_extension_from_path(".config.json") == "json");
}

SCENARIO("mime")
{
    GIVEN("::charset(type)")
    {
        THEN("it should return 'UTF-8' for 'application/json'")
        {
            REQUIRE(mime::charset("application/json") == "UTF-8");
        }

        THEN("it should return 'UTF-8' for 'application/json; foo=bar'")
        {
            REQUIRE(mime::charset("application/json; foo=bar") == "UTF-8");
        }

        THEN("it should return 'UTF-8' for 'application/javascript'")
        {
            REQUIRE(mime::charset("application/javascript") == "UTF-8");
        }

        THEN("it should return 'UTF-8' for 'application/JavaScript'")
        {
            REQUIRE(mime::charset("application/JavaScript") == "UTF-8");
        }

        THEN("it should return 'UTF-8' for 'text/html'")
        {
            REQUIRE(mime::charset("text/html") == "UTF-8");
        }

        THEN("it should return 'UTF-8' for 'TEXT/HTML'")
        {
            REQUIRE(mime::charset("TEXT/HTML") == "UTF-8");
        }

        THEN("it should return 'UTF-8' for any text/*")
        {
            REQUIRE(mime::charset("text/x-bogus") == "UTF-8");
        }

        THEN("it should throw for unknown types")
        {
            REQUIRE_THROWS(mime::charset("application/x-bogus"));
        }

        THEN("it should throw for any application/octet-stream")
        {
            REQUIRE_THROWS(mime::charset("application/octet-stream"));
        }
    }

    GIVEN("::content_type(extension)")
    {
        THEN("it should return content-type for 'html'")
        {
            REQUIRE(mime::content_type("html") == "text/html; charset=utf-8");
        }

        THEN("it should return content-type for '.html'")
        {
            REQUIRE(mime::content_type(".html") == "text/html; charset=utf-8");
        }

        THEN("it should return content-type for 'jade'")
        {
            REQUIRE(mime::content_type("jade") == "text/jade; charset=utf-8");
        }

        THEN("it should return content-type for 'json'")
        {
            REQUIRE(mime::content_type("json") == "application/json; charset=utf-8");
        }

        THEN("it should throw for unknown extensions")
        {
            REQUIRE_THROWS(mime::content_type("bogus"));
        }
    }

    GIVEN("::content_type(type)")
    {
        THEN("it should attach charset to 'application/json'")
        {
            REQUIRE(mime::content_type("application/json") == "application/json; charset=utf-8");
        }

        THEN("it should attach charset to 'application/json; foo=bar'")
        {
            REQUIRE(mime::content_type("application/json; foo=bar") == "application/json; foo=bar; charset=utf-8");
        }

        THEN("it should attach charset to 'TEXT/HTML'")
        {
            REQUIRE(mime::content_type("TEXT/HTML") == "TEXT/HTML; charset=utf-8");
        }

        THEN("it should attach charset to 'text/html'")
        {
            REQUIRE(mime::content_type("text/html") == "text/html; charset=utf-8");
        }

        THEN("it should not alter 'text/html; charset=iso-8859-1'")
        {
            REQUIRE(mime::content_type("text/html; charset=iso-8859-1") == "text/html; charset=iso-8859-1");
        }

        THEN("it should return type for unknown types")
        {
            REQUIRE(mime::content_type("application/x-bogus") == "application/x-bogus");
        }
    }

    GIVEN("::extension(type)")
    {
        THEN("it should return extension for mime type")
        {
            REQUIRE(mime::extension("text/html") == "html");
            REQUIRE(mime::extension(" text/html") == "html");
            REQUIRE(mime::extension("text/html ") == "html");
        }

        THEN("it should throw for unknown type")
        {
            REQUIRE_THROWS(mime::extension("application/x-bogus"));
        }

        THEN("it should throw for non-type string")
        {
            REQUIRE_THROWS(mime::extension("bogus"));
        }

        THEN("it should return extension for mime type wTHENh it parameters")
        {
            REQUIRE(mime::extension("text/html;charset=UTF-8") == "html");
            REQUIRE(mime::extension("text/HTML; charset=UTF-8") == "html");
            REQUIRE(mime::extension("text/html; charset=UTF-8") == "html");
            REQUIRE(mime::extension("text/html; charset=UTF-8 ") == "html");
            REQUIRE(mime::extension("text/html ; charset=UTF-8") == "html");
        }
    }

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