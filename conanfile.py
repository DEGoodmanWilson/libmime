# coding: utf-8
#
#   .__  ._____.
#   |  | |__\_ |__
#   |  | |  || __ \
#   |  |_|  || \_\ \     .__
#   |____/__||___  /____ |__| _____   ____
#                \/     \|  |/     \_/ __ \
#                |  Y Y  \  |  Y Y  \  ___/
#                |__|_|  /__|__|_|  /\___  >
#                      \/         \/     \/
#
#   libmime
#   A C++ library for inferring MIME content-types from pathnames
#
#   Copyright © 2018 D.E. Goodman-Wilson
#

from conans import ConanFile, CMake, tools

class LibmimeConan(ConanFile):
    name = "libmime"
    version = "0.1.0"
    generators = "cmake"
    author = "DEGoodmanWilson"
    url = "https:/github.com/{0}/conan-{1}".format(author, name)
    description = "Mimeythings"
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = ["CMakeLists.txt", "mime/mime_impl.cpp", "mime/mime_impl.h", "mime/mime.h", "tests/CMakeLists.txt", "tests/main.cpp"]
    options = {"shared": [True, False]}
    default_options = "shared=False"
    requires = "jsonformoderncpp/[~= 3.1]@vthiery/stable", "mime-db/[~= 1.33]@DEGoodmanWilson/stable"
    build_requires = "Catch/1.9.6@bincrafters/stable"

    def build(self):
        cmake = CMake(self)
        cmake.definitions["MIMEDB_FILE"] = "\"{0}/db.json\"".format(self.deps_cpp_info["mime-db"].res_paths[0])
        cmake.configure()
        cmake.build()
        # cmake.test()
        self.run('ctest . --verbose')

    def package(self):
        self.copy("*.h", dst="include/mime", src="mime")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
        self.cpp_info.defines.append("MIMEDB_FILE=\"{0}/db.json\"".format(self.deps_cpp_info["mime-db"].res_paths[0]))
