#include "dialog.h"
#include "ui_dialog.h"
#include "commonvars.h"
#include "empty.h"

QStringList songs;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    comboBox = new QComboBox(this);
    ui->gridLayout_2->addWidget(comboBox, 3, 0);
    comboBox->addItem("Playlist");
    playlist->setCurrentIndex(0);
    connect(player, &QMediaPlayer::positionChanged, this, &Dialog::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &Dialog::on_durationChanged);
    connect(player, &QMediaPlayer::currentMediaChanged, this, &Dialog::on_currentMediaChanged);
    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){ /* ... */ });
    ui->label_3->setText("Playback Rate: 1x");
    ui->label_4->setText("Playing:");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::IsPlaylistEmpty()  {
    if (playlist->isEmpty())    {
        Empty page;
        page.setModal(true);
        page.exec();
    }
    else    {
    }
}

void Dialog::on_sliderProgress_sliderMoved(int position)
{
    player->setPosition(position);
}


void Dialog::on_sliderVolume_sliderMoved(int position)
{
    player->setVolume(position);
}


void Dialog::on_StartButton_clicked()
{
    //player->setMedia(QUrl::fromLocalFile("/Users/edison/Desktop/Code2College/Work/Opp Stoppa.mp3"));
    if (songs.size() != 0)  {
        player->setPlaylist(playlist);
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        player->play();
        QFileInfo song(songs[playlist->currentIndex()]);
        ui->label_4->setText("Playing: " + song.fileName());
        qDebug() << player->errorString();
    }
    else    {
        Empty page;
        page.setModal(true);
        page.exec();
    }
}


void Dialog::on_StopButton_clicked()
{
    player->pause();
}

void Dialog::on_positionChanged(qint64 position)
{
    ui->sliderProgress->setValue(position);
}

void Dialog::on_durationChanged(qint64 position)
{
    ui->sliderProgress->setMaximum(position);
}

void Dialog::on_currentMediaChanged()
{
    QFileInfo song(songs[playlist->currentIndex()]);
    ui->label_4->setText("Playing: " + song.fileName());
}


void Dialog::on_ContinueButton_clicked()
{
    IsPlaylistEmpty();
    player->play();
}


void Dialog::on_sliderPlaybackRate_sliderMoved(int position)
{
    ui->sliderPlaybackRate->setValue(position);
    float playbackRate = position*0.02;
    ui->label_3->setText("Playback Rate: " + QString::number(playbackRate) + "x");
    player->setPlaybackRate(playbackRate);
}


void Dialog::on_ResetButton_clicked()
{
    ui->sliderVolume->setValue(100);
    ui->sliderPlaybackRate->setValue(50);
    ui->label_3->setText("Playback Rate: 1x");
    player->setVolume(100);
    player->setPlaybackRate(1);
}


void Dialog::on_SkipButton_clicked()
{
    IsPlaylistEmpty();
    if (playlist->mediaCount() > 0)    {
        if (playlist->currentIndex() < playlist->nextIndex())   {
            playlist->next();
        }
        else    {
            playlist->setCurrentIndex(0);
        }
        QFileInfo song(songs[playlist->currentIndex()]);
        ui->label_4->setText("Playing: " + song.fileName());
    }
}


void Dialog::on_ShuffleButton_clicked()
{
    IsPlaylistEmpty();
    playlist->shuffle();
}


void Dialog::on_AddSongButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Add Songs"), "/Users/edison/Desktop/Code2College/Lesson 13 Songs", tr("Audio Files (*.mp3)"));
    for (int x = 0; x < files.size(); x += 1)    {
        playlist->addMedia(QUrl::fromLocalFile(files[x]));
        songs.append(files[x]);
        QFileInfo song(songs[x]);
        comboBox->addItem(song.fileName());
    }
}


void Dialog::on_ClearButton_clicked()
{
    playlist->clear();
    ui->label_4->setText("Playing: ");
//    comboBox->clear();
//    comboBox->addItem("Remove Song");
}

//void Dialog::on_comboBox_currentIndexChanged(int index) //problem here because when the playlist is cleared there is no index
//{
//    if (index != 0) {
//        comboBox->clear();
//        songs.removeAt(index);
//        playlist->removeMedia(index);
//        for (int x = 0; x < songs.size(); x++) {
//            QFileInfo song(songs[x]);
//            comboBox->addItem(song.fileName());
//            songs.removeAt(x);
//        }
//    }
//}

