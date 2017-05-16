#include "soundplayer.h"

namespace mikoli {
//  constructeur par défaut
SoundPlayer::SoundPlayer(){}

//  constructeur avec paramètres
// nameFile : le nom du fichier son à jouer
// inLoop : faut-il jouer le son en boucle ou non
SoundPlayer::SoundPlayer(std::string nameFile, bool inLoop) {
    std::string path = "qrc:/sounds/" + nameFile;
    QString fileName = QString::fromStdString(path);

    _mediaPlaylist.addMedia(QUrl(fileName));
    if(inLoop){
        _mediaPlaylist.setPlaybackMode(QMediaPlaylist::Loop);
    } else {
        _mediaPlaylist.setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
    }
    _mediaPlayer.setPlaylist(&_mediaPlaylist);
    _mediaPlayer.setVolume(100);
}

//  destructeur
SoundPlayer::~SoundPlayer(){}

//  lance le son
void SoundPlayer::play(){
    if(_mediaPlayer.state() == QMediaPlayer::PlayingState){
        _mediaPlayer.setPosition(0);
    } else if (_mediaPlayer.state() == QMediaPlayer::StoppedState) {
        _mediaPlayer.play();
    }
}

//  change le volume du son
void SoundPlayer::setVolume(int vol){
    _mediaPlayer.setVolume(vol);
}

//  stop le son
void SoundPlayer::stop(){
    _mediaPlayer.stop();
}

//  mute le son
void SoundPlayer::switchMute(){
    _mediaPlayer.setMuted(!_mediaPlayer.isMuted());
}

//  repositionne le son au début
void SoundPlayer::reset(){
    _mediaPlayer.setPosition(0);
}

}
