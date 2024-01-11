// MediaMetadata.cpp

#include "MediaMetadata.h"

// Overload the << operator
std::ostream& operator<<(std::ostream& os, const MediaMetadata& media) {
    os << "MediaMetadata { id: " << media.id
       << ", title: " << media.title
       << " }";
    return os;
}

std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
    size_t start = 0;
    size_t end = s.find(delimiter);
    std::vector<std::string> tokens;

    while (end != std::string::npos) {
        tokens.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }

    tokens.push_back(s.substr(start, end - start));
    return tokens;
}

MediaMetadata::MediaMetadata() : duration(0), groupId(-1) {}

MediaMetadata::MediaMetadata(const std::string& title, const std::string& description,
                             const std::string& releaseDate, int duration, const std::string& genres,
                             float rating, const std::string& path, const std::string& thumbnailPath)
    : id(-1), title(title), description(description), releaseDate(releaseDate),
      duration(duration), genres(genres), rating(rating), path(path), thumbnailPath(thumbnailPath) {




}

std::vector<std::string> MediaMetadata::getGenresSplitted() {
    std::vector<std::string> splitted = split(genres, ", ");
    return splitted;
}




void MediaMetadata::setId(int id) {
    this->id = id;
}









