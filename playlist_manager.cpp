#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

// Structure for a Song
struct Song {
    std::string title;
    std::string artist;
};

// Structure for a Playlist
struct Playlist {
    std::string name;
    std::vector<Song> songs;
};

std::vector<Playlist> playlists;
std::deque<Song> recentlyPlayedSongs;

void savePlaylistsToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        // Save playlists to the file
        for (const auto& playlist : playlists) {
            file << playlist.name << std::endl;
            for (const auto& song : playlist.songs) {
                file << song.title << "," << song.artist << std::endl;
            }
            file << std::endl;
        }
        file.close();
        std::cout << "Playlists saved to file." << std::endl;
    } else {
        std::cout << "Unable to save playlists to file." << std::endl;
    }
}

void loadPlaylistsFromFile(const std::string& filename) {
    playlists.clear();
    std::ifstream file(filename);
    if (file.is_open()) {
        Playlist playlist;
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) {
                playlists.push_back(playlist);
                playlist = Playlist();
            } else if (playlist.name.empty()) {
                playlist.name = line;
            } else {
                size_t pos = line.find(',');
                if (pos != std::string::npos) {
                    Song song;
                    song.title = line.substr(0, pos);
                    song.artist = line.substr(pos + 1);
                    playlist.songs.push_back(song);
                }
            }
        }
        file.close();
        std::cout << "Playlists loaded from file." << std::endl;
    } else {
        std::cout << "Unable to load playlists from file." << std::endl;
    }
}

void createPlaylist() {
    std::string name;
    std::cout << "Enter the name of the playlist: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    playlists.push_back({name, {}});
    std::cout << "Playlist created." << std::endl;
}

void deletePlaylist() {
    int index;
    std::cout << "Enter the index of the playlist to delete: ";
    std::cin >> index;
    if (index >= 0 && index < playlists.size()) {
        playlists.erase(playlists.begin() + index);
        std::cout << "Playlist deleted." << std::endl;
    } else {
        std::cout << "Invalid playlist index." << std::endl;
    }
}

void addSongToPlaylist() {
    int playlistIndex;
    std::cout << "Enter the index of the playlist to add the song: ";
    std::cin >> playlistIndex;
    if (playlistIndex >= 0 && playlistIndex < playlists.size()) {
        std::string title, artist;
        std::cout << "Enter the song title: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        std::cout << "Enter the artist name: ";
        std::getline(std::cin, artist);
        Song song = {title, artist};
        playlists[playlistIndex].songs.push_back(song);
        std::cout << "Song added to the playlist." << std::endl;
    } else {
        std::cout << "Invalid playlist index." << std::endl;
    }
}

void deleteSongFromPlaylist() {
    int playlistIndex;
    std::cout << "Enter the index of the playlist to delete the song from: ";
    std::cin >> playlistIndex;
    if (playlistIndex >= 0 && playlistIndex < playlists.size()) {
        int songIndex;
        std::cout << "Enter the index of the song to delete: ";
        std::cin >> songIndex;
        if (songIndex >= 0 && songIndex < playlists[playlistIndex].songs.size()) {
            playlists[playlistIndex].songs.erase(playlists[playlistIndex].songs.begin() + songIndex);
            std::cout << "Song deleted from the playlist." << std::endl;
        } else {
            std::cout << "Invalid song index." << std::endl;
        }
    } else {
        std::cout << "Invalid playlist index." << std::endl;
    }
}

void playSong() {
    int playlistIndex, songIndex;
    std::cout << "Enter the index of the playlist: ";
    std::cin >> playlistIndex;
    if (playlistIndex >= 0 && playlistIndex < playlists.size()) {
        std::cout << "Enter the index of the song to play: ";
        std::cin >> songIndex;
        if (songIndex >= 0 && songIndex < playlists[playlistIndex].songs.size()) {
            Song song = playlists[playlistIndex].songs[songIndex];
            recentlyPlayedSongs.push_back(song);
            std::cout << "Playing song: " << song.title << " - " << song.artist << std::endl;
        } else {
            std::cout << "Invalid song index." << std::endl;
        }
    } else {
        std::cout << "Invalid playlist index." << std::endl;
    }
}

void displayPlaylists() {
    if (playlists.empty()) {
        std::cout << "No playlists found." << std::endl;
    } else {
        std::cout << "Playlists:" << std::endl;
        for (size_t i = 0; i < playlists.size(); ++i) {
            std::cout << i << ". " << playlists[i].name << std::endl;
        }
    }
}

void displaySongsInPlaylist() {
    int playlistIndex;
    std::cout << "Enter the index of the playlist to display the songs: ";
    std::cin >> playlistIndex;
    if (playlistIndex >= 0 && playlistIndex < playlists.size()) {
        const std::vector<Song>& songs = playlists[playlistIndex].songs;
        if (songs.empty()) {
            std::cout << "No songs found in the playlist." << std::endl;
        } else {
            std::cout << "Songs in the playlist:" << std::endl;
            for (size_t i = 0; i < songs.size(); ++i) {
                std::cout << i << ". " << songs[i].title << " - " << songs[i].artist << std::endl;
            }
        }
    } else {
        std::cout << "Invalid playlist index." << std::endl;
    }
}

void displayRecentlyPlayedSongs() {
    if (recentlyPlayedSongs.empty()) {
        std::cout << "No songs have been recently played." << std::endl;
    } else {
        std::cout << "Recently played songs:" << std::endl;
        for (const auto& song : recentlyPlayedSongs) {
            std::cout << song.title << " - " << song.artist << std::endl;
        }
    }
}

void displayLastPlayedSong() {
    if (recentlyPlayedSongs.empty()) {
        std::cout << "No songs have been recently played." << std::endl;
    } else {
        const Song& lastSong = recentlyPlayedSongs.back();
        std::cout << "Last played song: " << lastSong.title << " - " << lastSong.artist << std::endl;
    }
}

int main() {
    std::string filename = "playlists.txt";
    loadPlaylistsFromFile(filename);

    int choice;
    do {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Create Playlist" << std::endl;
        std::cout << "2. Delete Playlist" << std::endl;
        std::cout << "3. Add Song to Playlist" << std::endl;
        std::cout << "4. Delete Song from Playlist" << std::endl;
        std::cout << "5. Play Song" << std::endl;
        std::cout << "6. Display Playlists" << std::endl;
        std::cout << "7. Display Songs in Playlist" << std::endl;
        std::cout << "8. Display Recently Played Songs" << std::endl;
        std::cout << "9. Display Last Played Song" << std::endl;
        std::cout << "0. Save and Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                createPlaylist();
                break;
            case 2:
                deletePlaylist();
                break;
            case 3:
                addSongToPlaylist();
                break;
            case 4:
                deleteSongFromPlaylist();
                break;
            case 5:
                playSong();
                break;
            case 6:
                displayPlaylists();
                break;
            case 7:
                displaySongsInPlaylist();
                break;
            case 8:
                displayRecentlyPlayedSongs();
                break;
            case 9:
                displayLastPlayedSong();
                break;
            case 0:
                savePlaylistsToFile(filename);
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
