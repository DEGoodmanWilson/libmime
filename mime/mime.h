//
// Created by Don Goodman-Wilson on 07/03/2018.
//

#pragma once

#include <string>

namespace mime
{

#if !defined(MIMEDB_FILE)
#error "No mime-db file provided"
#else
const std::string mimedb_file{MIMEDB_FILE};
#endif

std::string lookup(const std::string &path) throw(std::out_of_range);
bool lookup(const std::string &path, std::string &type) noexcept;

std::string content_type(const std::string &path) throw(std::out_of_range);
bool content_type(const std::string &path, std::string &type) noexcept;

std::string extension(const std::string &type) throw(std::out_of_range);
bool extension(const std::string &type, std::string &extension) noexcept;

std::string charset(const std::string &type) throw(std::out_of_range);
bool charset(const std::string &type, std::string &charset) noexcept;

}