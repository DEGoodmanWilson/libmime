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

#include <string>
#include <stdexcept>


namespace mime
{

std::string get_extension_from_path(std::string path);

std::string lookup(const std::string &str);

std::string content_type(const std::string &str);

std::string extension(const std::string &type);

std::string charset(const std::string &type);

}