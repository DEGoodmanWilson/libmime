//
// Created by Don Goodman-Wilson on 07/03/2018.
//

#include "mime.h"
#include <unordered_map>
#include <nlohmann/json.hpp>

namespace mime
{

namespace private_
{
static bool inited_{false};

struct content_type_t_
{
    std::string type;
    std::string charset;
};

static std::unordered_map<std::string, content_type_t_> ext_to_type_;
static std::unordered_map<std::string, std::string> type_to_ext_;

void init_(void)
{
    inited_ = true;
}

std::string ext_from_path_(const std::string &path)
{
    const auto ext_begin = path.find_last_of(".");
    if(ext_begin == std::string::npos)
        return "";
    return path.substr(ext_begin + 1);
}
}

std::string lookup(const std::string &path) throw(std::out_of_range)
{
    std::string ext{private_::ext_from_path_(path)};
    return private_::ext_to_type_.at(ext).type;
}

bool lookup(const std::string &path, std::string &type) noexcept
{
    return false;
}

std::string content_type(const std::string &path) throw(std::out_of_range)
{
    return "";

}

bool content_type(const std::string &path, std::string &type) noexcept
{
    return false;

}

std::string extension(const std::string &type) throw(std::out_of_range)
{
    return "";

}

bool extension(const std::string &type, std::string &extension) noexcept
{
    return false;

}

std::string charset(const std::string &type) throw(std::out_of_range)
{
    return "";
}

bool charset(const std::string &type, std::string &charset) noexcept
{
    return false;

}
}
