#ifndef AUDIOINPUT_H
#define AUDIOINPUT_H

#include <QtCore>
#include <QtMultimedia>

class AudioInput : public QObject
{
    Q_OBJECT
public:
    explicit AudioInput(QObject *parent = nullptr);

signals:
    void error(QString);
    void formatReady(QAudioFormat);
    void readyRead(QByteArray);

public slots:
    bool start(const QAudioDeviceInfo &devinfo, const QAudioFormat &format);

private slots:
    void readyReadPrivate();

private:
    QAudioInput *m_audio_input;
    QIODevice *m_device;
    QAudioFormat m_format;
};

#endif // AUDIOINPUT_H
