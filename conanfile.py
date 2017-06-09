from conans import ConanFile, CMake, tools

class LambertConan(ConanFile):
    name = "lambert"
    version = "2.0.1"
    license = "MIT"
    url = "https://github.com/yageek/lambert"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    description = "A simple C library to convert Lambert coordinates to GPS WGS84 coordinates."

    def configure(self):
        del self.settings.compiler.libcxx

    def source(self):
        self.run("git clone https://github.com/yageek/lambert.git")
        self.run("cd lambert && git checkout 2.0.1")
        # This small hack might be useful to guarantee proper /MT /MD linkage in MSVC
        # if the packaged project doesn't have variables to set it properly
        tools.replace_in_file("lambert/CMakeLists.txt", "project(lambert)", '''project(lambert)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()''')

    def build(self):
        cmake = CMake(self)
        shared = "-DBUILD_SHARED_LIBS=ON" if self.options.shared else ""
        self.run('cmake lambert %s %s' % (cmake.command_line, shared))
        self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include", src="lambert/src")
        self.copy("*lambert.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["lambert"]
        if self.settings.os == "Linux":
            self.cpp_info.libs.append("m")
