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
    exports_sources = ["CMakeLists.txt", "mime/mime.cpp", "mime/mime.h", "tests/CMakeLists.txt", "tests/main.cpp"]
    options = {"shared": [True, False]}
    default_options = "shared=False"
    requires = "jsonformoderncpp/[~= 3.1]@vthiery/stable", "mime-db/[~= 1.33]@DEGoodmanWilson/stable"
    build_requires = "Catch/1.9.6@bincrafters/stable"

    def build(self):
        cmake = CMake(self)
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
        self.cpp_info.defines = ["MIMEDB_FILE={0}".format(self.cpp_info["mime-db"].resdirs[0])]
        print self.cpp_info.defines
