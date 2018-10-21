#include "audioinput.h"

AudioInput::AudioInput(QObject *parent) : QObject(parent)
{
    m_audio_input = nullptr;
    m_device = nullptr;
}

bool AudioInput::start(const QAudioDeviceInfo &devinfo, const QAudioFormat &format)
{
    m_format = format;

    //Check if format is supported by the choosen input device
    if (!devinfo.isFormatSupported(m_format))
        m_format = devinfo.nearestFormat(m_format);

    //Initialize the audio input device
    m_audio_input = new QAudioInput(devinfo, m_format, this);

    m_device = m_audio_input->start();

    if (!m_device)
        return false;

    emit formatReady(m_format);

    //Call the readyReadPrivate function when data are available in the input device
    connect(m_device, &QIODevice::readyRead, this, &AudioInput::readyReadPrivate);

    return true;
}

void AudioInput::readyReadPrivate()
{
    //Read sound samples from input device to buffer
    QByteArray data = m_device->readAll();

    //Expose the input data to worker class
    emit readyRead(data);
}
