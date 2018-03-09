# libmime

[![Download][conan-image]][conan-url]
[![Build Status][travis-image]][travis-url]

A port to C++ of the node.js module mime-types https://github.com/jshttp/mime-types

It takes a filename, and gives you a mime type :D

## Install
	
libmime installs with [Conan](http://docs.conan.io/en/latest/)

    $ conan install libmime/[~= 0.1]@DEGoodmanWilson/stable

### Project setup

If you handle multiple dependencies in your project is better to add a *conanfile.txt*

    [requires]
    libmime/[~= 0.1]@DEGoodmanWilson/stable

    [generators]
    txt

Complete the installation of requirements for your project running:

    $ mkdir build && cd build && conan install ..

Note: It is recommended that you run conan install from a build directory and not the root of the project directory.  This is because conan generates *conanbuildinfo* files specific to a single build configuration which by default comes from an autodetected default profile located in ~/.conan/profiles/default .  If you pass different build configuration options to conan install, it will generate different *conanbuildinfo* files.  Thus, they should not be added to the root of the project, nor committed to git.


## Adding Types

All mime types are based on [mime-db](https://www.npmjs.com/package/mime-db),
so open a PR there if you"d like to add mime types.

## API

```cpp
#include <mime/mime.h>
```

All functions throw `std::out_of_range` if input is invalid or not found.

### mime::lookup(path)

Lookup the content-type associated with a file.

```cpp
mime::lookup("json");             // "application/json"
mime::lookup(".md");              // "text/markdown"
mime::lookup("file.html");        // "text/html"
mime::lookup("folder/file.js");   // "application/javascript"
mime::lookup("folder/.htaccess"); // throws std::out_of_range

mime::lookup("cats"); // throws std::out_of_range
```

### mime::contentType(type)

Create a full content-type header given a content-type or extension. If you need to pull the extension off of a full path, you can call `mime::get_extension_from_path()` first.

```cpp
mime::contentType("markdown");  // "text/x-markdown; charset=utf-8"
mime::contentType("file.json"); // "application/json; charset=utf-8"

// from a full path
mime::contentType(mime::get_extension_from_path("/path/to/file.json")); // "application/json; charset=utf-8"
```

### mime::extension(type)

Get the default extension for a content-type.

```cpp
mime::extension("application/octet-stream"); // "bin"
```

### mime::charset(type)

Lookup the implied default charset of a content-type.

```cpp
mime::charset("text/markdown"); // "UTF-8"
```

## License

[MIT](LICENSE)

[conan-image]: https://api.bintray.com/packages/degoodmanwilson/opensource/libmime%3ADEGoodmanWilson/images/download.svg
[conan-url]: https://bintray.com/degoodmanwilson/opensource/libmime%3ADEGoodmanWilson/_latestVersion
[travis-image]: https://img.shields.io/travis/DEGoodmanWilson/libmime/master.svg
[travis-url]: https://travis-ci.org/DEGoodmanWilson/libmime