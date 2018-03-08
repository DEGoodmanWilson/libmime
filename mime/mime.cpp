//
// Created by Don Goodman-Wilson on 07/03/2018.
//

#include "mime.h"
#include <unordered_map>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

// taken straight from https://github.com/jshttp/mime-types/blob/master/index.js

namespace mime
{

namespace private_
{
static bool inited_{false};

struct content_type_t_
{
    enum class source_t
    {
        APACHE,
        IANA,
        NGINX,
        UNKNOWN,
    } source;
    std::vector<std::string> extensions;
    bool compressible;
    std::string charset;

    content_type_t_() : source{source_t::UNKNOWN}, extensions{}, compressible{false}, charset{""}
    {}
};

void from_json(const nlohmann::json &j, content_type_t_ &c)
{
    try
    {
        std::string source = j.at("source").get<std::string>();
        std::transform(source.begin(), source.end(), source.begin(), ::tolower);

        if (source == "apache")
        { c.source = content_type_t_::source_t::APACHE; }
        else if (source == "iana")
        { c.source = content_type_t_::source_t::IANA; }
        else if (source == "nginx") c.source = content_type_t_::source_t::NGINX;
    }
    catch (const nlohmann::json::exception &e)
    {}

    try
    {
        c.extensions = j.at("extensions").get<std::vector<std::string>>();
    }
    catch (const nlohmann::json::exception &e)
    {}

    try
    {
        c.compressible = j.at("compressible").get<bool>();
    }
    catch (const nlohmann::json::exception &e)
    {}

    try
    {
        c.charset = j.at("charset").get<std::string>();
    }
    catch (const nlohmann::json::exception &e)
    {}
}

static std::unordered_map<std::string, content_type_t_> db_;
static std::unordered_map<std::string, std::vector<std::string>> extensions_;
static std::unordered_map<std::string, std::string> types_;

void init_(void)
{
    std::ifstream infile{::mime::mimedb_file};
    nlohmann::json db;
    infile >> db;
    infile.close();

    //TOOD eliminate this

    db_ = db.get<std::unordered_map<std::string, content_type_t_>>();


    // source preference (least -> most)
    std::vector<content_type_t_::source_t> preference{content_type_t_::source_t::NGINX,
                                                      content_type_t_::source_t::APACHE,
                                                      content_type_t_::source_t::UNKNOWN,
                                                      content_type_t_::source_t::IANA};

    for (const auto &kv : db_)
    {
        auto type = kv.first;
        auto mime = kv.second;

        auto exts = mime.extensions;

        if (exts.empty())
        {
            continue;
        }

        // mime -> extensions
        extensions_[type] = exts;

        // extension -> mime
        for (const auto &extension : exts)
        {
            if (types_.count(extension))
            {
                auto from = std::find(std::begin(preference),
                                      std::end(preference),
                                      db_.at(types_.at(extension)).source);
                auto to = std::find(std::begin(preference), std::end(preference), mime.source);
                if (types_.at(extension) != "application/octet-stream" &&
                    (from > to || (from == to && types_.at(extension).substr(0, 12) == "application/")))
                {
                    // skip the remapping
                    continue;
                }
            }

            // set the extension -> mime
            types_[extension] = type;
        }
    }

    inited_ = true;
}


std::string ext_from_filename_(std::string filename)
{
    if (filename.empty()) return "";

    auto dot_pos = filename.find_last_of('.');
    if (dot_pos == std::string::npos) return ""; // no extension on names with a . like foobar

    return filename.substr(dot_pos + 1);
}

std::string ext_from_path_(std::string path)
{
    auto filename(path);
    // strip off any leadings paths.
    auto pos = path.find_last_of('/');
    if (pos != std::string::npos)
    {
        filename = path.substr(pos + 1);
    }
    else
    {
        pos = path.find_last_of('\\');
        if (pos != std::string::npos)
        {
            filename = path.substr(pos + 1);
        }
    }
    auto dot_pos = filename.find_last_of('.');
    if (dot_pos == 0) return ""; // no extension on names with a . like foobar

    return ext_from_filename_(filename);
}

std::string ext_from_string_(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    //is this a _path_, or a _filename_, or an _extension_

    if (str.find('/') != std::string::npos || str.find('\\') != std::string::npos)
    {
        return ext_from_path_(str);
    }

    if (str.find('.') != std::string::npos)
    {
        return ext_from_filename_(str);
    }

    // it's just an extension, use it directly!
    return str;
}
}

std::string lookup(const std::string &str) throw(std::out_of_range)
{
    if (!mime::private_::inited_) mime::private_::init_();

    auto extension = private_::ext_from_string_(str);

    if (extension.empty())
    {
        throw std::out_of_range{"Empty file extension"};
    };

    return private_::types_.at(extension);
}


std::string content_type(const std::string &str) throw(std::out_of_range)
{
    if (!mime::private_::inited_) mime::private_::init_();

    auto mime = (str.find_first_of('/') == std::string::npos) ? lookup(str) : str;

    if (mime.empty())
    {
        return "";
    }

    // TODO: use content-type or other module
    if (mime.find("charset") == std::string::npos)
    {
        auto cs{charset(mime)};
        if (!cs.empty())
        {
            std::transform(cs.begin(), cs.end(), cs.begin(), ::tolower);
            mime += "; charset=" + cs;
        }
    }

    return mime;
}


std::string extension(const std::string &type) throw(std::out_of_range)
{
    if (!mime::private_::inited_) mime::private_::init_();

    // TODO: use media-typer
//    var match = EXTRACT_TYPE_REGEXP.exec(type)
//
//    // get extensions
//    var exts = match && exports.extensions[match[1].toLowerCase()]
//
//    if (!exts || !exts.length) {
//        return false
//    }
//
//    return exts[0]
    return "NOPE";
}


std::string charset(const std::string &type) throw(std::out_of_range)
{
    if (!mime::private_::inited_) mime::private_::init_();


//    // TODO: use media-typer
//    var match = EXTRACT_TYPE_REGEXP.exec(type)
//    var mime = match && db[match[1].toLowerCase()]
//
//    if (mime && mime.charset) {
//        return mime.charset
//    }
//
//    // default text/* to utf-8
//    if (match && TEXT_TYPE_REGEXP.test(match[1])) {
//        return 'UTF-8'
//    }
//
//    return false

    return "NOPE";
}

}
