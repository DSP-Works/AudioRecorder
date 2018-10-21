#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "audioinput.h"
#include "audiorecorder.h"

#define SETTONULLPTR(obj) QObject::connect(obj, &QObject::destroyed, [&]{obj = nullptr;})

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startRecording();
    void stopRecording();
    void started(const QAudioFormat &format);

private:
    QPushButton *button_start;
    QPushButton *button_stop;

    AudioInput *m_audio_input;
    AudioRecorder *m_recorder;
};

#endif // MAINWINDOW_H
