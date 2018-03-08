//
// Created by Don Goodman-Wilson on 07/03/2018.
//

#pragma once

#include <string>
#include <stdexcept>

namespace mime
{

#if !defined(MIMEDB_FILE)
#error "No mime-db file provided"
#else
const std::string mimedb_file = MIMEDB_FILE;
#endif

std::string lookup(const std::string &str) throw(std::out_of_range);

std::string content_type(const std::string &str) throw(std::out_of_range);

std::string extension(const std::string &type) throw(std::out_of_range);

std::string charset(const std::string &type) throw(std::out_of_range);

}