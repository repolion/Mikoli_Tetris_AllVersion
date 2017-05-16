#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <string>
#include <QString>

namespace mikoli {

/*!
 * \brief The SoundPlayer class
 * Each instance of this class is a sound.
 * Through this class, we can handle the sound : play, pause, ...
 */
class SoundPlayer{
private:
    /*!
     * \brief _mediaPlayer
     * The sound's player
     */
    QMediaPlayer _mediaPlayer;

    /*!
     * \brief _mediaPlaylist
     * A playlist for the media player
     */
    QMediaPlaylist _mediaPlaylist;

public:
    /*!
     * \brief SoundPlayer
     * Constructor by default
     */
    SoundPlayer();

    /*!
     * \brief SoundPlayer
     * Constructor with parameter:
     * A string for sound's name
     * A boolean set to true if the sound must play in loop, false otherwise.
     */
    SoundPlayer(std::string, bool);

    ~SoundPlayer();

    /*!
     * \brief play
     * Play the sound.
     */
    void play();

    /*!
     * \brief setVolume
     * Change the volume of the sound.
     */
    void setVolume(int);

    /*!
     * \brief stop
     * Stop the sound.
     */
    void stop();

    /*!
     * \brief switchMute
     * Mute the sound.
     */
    void switchMute();

    /*!
     * \brief reset
     * Replace the sound to the beginning.
     */
    void reset();
};

}
#endif // SOUNDPLAYER_H
