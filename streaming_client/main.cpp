//
// Created by juliofgx on 12/23/23.
//

#include <vlc/vlc.h>
#include <iostream>

int main() {
    libvlc_instance_t* vlcInstance;
    libvlc_media_player_t* mediaPlayer;
    libvlc_media_t* media;

    const char* vlcArgs[] = {
        "-vvv", // Be verbose for debugging purposes
    };

    // Load the VLC engine
    vlcInstance = libvlc_new(sizeof(vlcArgs) / sizeof(vlcArgs[0]), vlcArgs);

    if (vlcInstance == nullptr) {
        std::cerr << "libVLC initialization failed!" << std::endl;
        return -1;
    }

    // Create a new media player
    mediaPlayer = libvlc_media_player_new(vlcInstance);

    // Load the media (DASH MPD URL)
    media = libvlc_media_new_location(vlcInstance, "http://0.0.0.0:18080/media/10/chunks/mpd");
    libvlc_media_player_set_media(mediaPlayer, media);

    // Play the media
    libvlc_media_player_play(mediaPlayer);

    // Keep the application running to allow video playback
    // This might be replaced by your application's event loop
    std::cout << "Streaming... Press Enter to exit." << std::endl;
    std::cin.get();

    // Cleanup on exit
    libvlc_media_release(media);
    libvlc_media_player_release(mediaPlayer);
    libvlc_release(vlcInstance);

    return 0;
}
