from conans import ConanFile, CMake, tools


class LibmimeConan(ConanFile):
    name = "libmime"
    version = "0.1.0"
    license = "<Put the package license here>"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "<Description of Mimetypes here>"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = ["CMakeLists.txt"]
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    requires = "jsonformoderncpp/[~= 3.1]@vthiery/stable", "mime-db/[~= 1.33]@DEGoodmanWilson/stable"
    build_requires = "Catch/1.9.6@bincrafters/stable"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        # cmake.test()
        self.run('ctest . --verbose')

    def source(self):
        return

    def package(self):
        self.copy("*.h", dst="include", src="hello")
        self.copy("*hello.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["hello"]
