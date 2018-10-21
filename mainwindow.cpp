#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_audio_input = nullptr;
    m_recorder = nullptr;

    button_start = new QPushButton("Record", this);
    button_stop = new QPushButton("Stop", this);

    connect(button_start, &QPushButton::clicked, this, &MainWindow::startRecording);
    connect(button_stop, &QPushButton::clicked, this, &MainWindow::stopRecording);

    button_stop->setEnabled(false);

    QWidget *widget = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout(widget);

    layout->addWidget(button_start);
    layout->addWidget(button_stop);

    setCentralWidget(widget);

    setFixedSize(sizeHint());
}

MainWindow::~MainWindow()
{

}

void MainWindow::startRecording()
{
    button_start->setEnabled(false);
    button_stop->setEnabled(true);

    QAudioFormat format;
    format.setSampleRate(88200);
    format.setChannelCount(1);
    format.setSampleSize(24);
    format.setCodec("Audio/PCM");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    m_audio_input = new AudioInput(this);
    SETTONULLPTR(m_audio_input);

    connect(m_audio_input, &AudioInput::formatReady, this, &MainWindow::started);

    if (!m_audio_input->start(QAudioDeviceInfo::defaultInputDevice(), format))
    {
        stopRecording();
        QMessageBox::critical(this, "Error", "Failed to open input audio device");
        return;
    }
}

void MainWindow::stopRecording()
{
    if (m_audio_input)
        m_audio_input->deleteLater();

    if (m_recorder)
        m_recorder->deleteLater();

    button_start->setEnabled(true);
    button_stop->setEnabled(false);
}

void MainWindow::started(const QAudioFormat &format)
{
    m_recorder = new AudioRecorder("audio.wav", format, this);
    SETTONULLPTR(m_recorder);

    if (!m_recorder->open())
    {
        stopRecording();
        QMessageBox::critical(this, "Error", m_recorder->errorString());
        return;
    }

    connect(m_audio_input, &AudioInput::readyRead, m_recorder, &AudioRecorder::write);
}
