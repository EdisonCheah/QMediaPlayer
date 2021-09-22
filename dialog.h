#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QDebug>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QList>
#include <QStandardItem>
#include <QStringList>
#include <QList>
#include <QFileInfo>
#include <QComboBox>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_sliderProgress_sliderMoved(int position);

    void on_sliderVolume_sliderMoved(int position);

    void on_StartButton_clicked();

    void on_StopButton_clicked();

    void on_positionChanged(qint64 position);

    void on_durationChanged(qint64 position);

    void on_ContinueButton_clicked();

    void on_sliderPlaybackRate_sliderMoved(int position);

    void on_ResetButton_clicked();

    void on_SkipButton_clicked();

    void on_ShuffleButton_clicked();

    void on_AddSongButton_clicked();

    void on_ClearButton_clicked();

    void on_currentMediaChanged();

//    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QComboBox *comboBox;
    void IsPlaylistEmpty();

};
#endif // DIALOG_H
