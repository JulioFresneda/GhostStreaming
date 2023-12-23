#include <iostream>
#include <boost/filesystem.hpp>
#include <vector>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
}

#include "MetadataDB.h"
#include "api_endpoint.h"


int main() {
    MetadataDB db("/home/juliofgx/MetadataDB/metadata.db");
    APIEndpoint api_endpoint = APIEndpoint(db);


    return 0;
}
