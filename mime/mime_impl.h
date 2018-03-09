//
// Created by Don Goodman-Wilson on 07/03/2018.
//

#pragma once

#include <string>
#include <stdexcept>

namespace mime
{
namespace impl
{

void init(const std::string &db_name) throw(std::runtime_error);

std::string get_extension_from_path(std::string path);

std::string lookup(const std::string &str) throw(std::out_of_range);

std::string content_type(const std::string &str) throw(std::out_of_range);

std::string extension(const std::string &type) throw(std::out_of_range);

std::string charset(const std::string &type) throw(std::out_of_range);

}
}