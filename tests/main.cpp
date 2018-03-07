#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "../mime/mime.h"

namespace mime
{
namespace private_
{
std::string ext_from_path_(const std::string &path);
}
}

TEST_CASE("We can properly extract extensions from paths")
{
    REQUIRE(mime::private_::ext_from_path_("hello.gif") == "gif");
    REQUIRE(mime::private_::ext_from_path_("/foobar/hello.html") == "html");
    REQUIRE(mime::private_::ext_from_path_("nope") == "");
}