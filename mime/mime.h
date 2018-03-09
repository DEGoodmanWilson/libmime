//
//  .__  ._____.
//  |  | |__\_ |__
//  |  | |  || __ \
//  |  |_|  || \_\ \     .__
//  |____/__||___  /____ |__| _____   ____
//               \/     \|  |/     \_/ __ \
//               |  Y Y  \  |  Y Y  \  ___/
//               |__|_|  /__|__|_|  /\___  >
//                     \/         \/     \/
//
//  libmime
//  A C++ library for inferring MIME content-types from pathnames
//
//  Copyright © 2018 D.E. Goodman-Wilson
//

#pragma once

#include <mime/mime_impl.h>

namespace mime
{

#if !defined(MIMEDB_FILE)
#error "No mime-db file provided"
#else
const std::string mimedb_file = MIMEDB_FILE;
#endif

std::string get_extension_from_path(std::string path)
{
    return impl::get_extension_from_path(path);
}

std::string lookup(const std::string &str) throw(std::out_of_range)
{
    impl::init(mimedb_file);
    return impl::lookup(str);
}

std::string content_type(const std::string &str) throw(std::out_of_range)
{
    impl::init(mimedb_file);
    return impl::content_type(str);
}

std::string extension(const std::string &type) throw(std::out_of_range)
{
    impl::init(mimedb_file);
    return impl::extension(type);
}

std::string charset(const std::string &type) throw(std::out_of_range)
{
    impl::init(mimedb_file);
    return impl::charset(type);
}

}