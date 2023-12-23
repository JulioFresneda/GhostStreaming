#include <iostream>
#include <boost/filesystem.hpp>
#include <vector>

extern "C" {
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/avutil.h>
}

#include "MetadataDB.h"


std::vector<std::string> findMediaFiles(const boost::filesystem::path& root) {
    std::vector<std::string> files;
    if (boost::filesystem::exists(root) && boost::filesystem::is_directory(root)) {
        for (const auto& entry : boost::filesystem::recursive_directory_iterator(root)) {
            if (boost::filesystem::is_regular_file(entry) && boost::filesystem::extension(entry) == ".mp4") { // Change or add more extensions as needed
                files.push_back(entry.path().string());
            }
        }
    }
    return files;
}

void extractMetadata(const std::string& filePath) {
    AVFormatContext* formatContext = avformat_alloc_context();

    if (avformat_open_input(&formatContext, filePath.c_str(), NULL, NULL) != 0) {
        std::cerr << "ERROR: Could not open file: " << filePath << std::endl;
        return;
    }

    if (avformat_find_stream_info(formatContext, NULL) < 0) {
        std::cerr << "ERROR: Could not retrieve stream info from file: " << filePath << std::endl;
        return;
    }

    // Output basic metadata here
    std::cout << "Metadata for file: " << filePath << std::endl;
    std::cout << "Format: " << formatContext->iformat->long_name << ", Duration: " << formatContext->duration << std::endl;

    avformat_close_input(&formatContext);
}

int main() {

    boost::filesystem::path rootPath = "/home/juliofgx/Videos";
    auto mediaFiles = findMediaFiles(rootPath);

    for (const auto& file : mediaFiles) {
        extractMetadata(file);
    }

    MetadataDB db("metadata.db");

    return 0;
}
