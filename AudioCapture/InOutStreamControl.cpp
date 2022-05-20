#include "InOutStreamControl.h"

#include <QDebug>


//const QVariantList &InOutStreamControl::audioInputDevices()
//{
//    m_inputDevicesInfo = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);

//    m_devicesInfoForQML.clear();
//    for (int i = 0; i < m_inputDevicesInfo.length(); i++) {
//        QVariantMap returnListItem;
//        returnListItem["id"] = i;
//        returnListItem["name"] = m_inputDevicesInfo[i].deviceName();
//        m_devicesInfoForQML.append(returnListItem);
//    }
//    return m_devicesInfoForQML;
//}

//const QVariantList &InOutStreamControl::audioOutputDevices()
//{
//    m_outputDevicesInfo = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

//    m_devicesInfoForQML.clear();
//    for (int i = 0; i < m_outputDevicesInfo.length(); i++) {
//        QVariantMap returnListItem;
//        returnListItem["id"] = i;
//        returnListItem["name"] = m_outputDevicesInfo[i].deviceName();
//        m_devicesInfoForQML.append(returnListItem);
//    }
//    return m_devicesInfoForQML;
//}

//void InOutStreamControl::selectAudioInputDeviceByIndex(int index)
//{
//    if (index >= m_inputDevicesInfo.length()) {
//        return;
//    }

//    const QAudioDeviceInfo& selectedDeviceInfo = m_inputDevicesInfo.at(index);
//    qDebug() << "- Input -----------------------------------------------------";
//    qDebug() << "selected deviceName    " << selectedDeviceInfo.deviceName();
//    qDebug() << "supportedSampleRates   " << selectedDeviceInfo.supportedSampleRates();
//    qDebug() << "supportedChannelCounts " << selectedDeviceInfo.supportedChannelCounts();
//    qDebug() << "supportedSampleSizes   " << selectedDeviceInfo.supportedSampleSizes();
//    qDebug() << "supportedSampleTypes   " << selectedDeviceInfo.supportedSampleTypes();
//    qDebug() << "supportedCodecs        " << selectedDeviceInfo.supportedCodecs();
//    qDebug() << "- format ----------------------------------------------------";
//    m_inputAudioFormat = selectedDeviceInfo.nearestFormat(m_outputAudioFormat);
//    qDebug() << "nearest settings       " << m_inputAudioFormat;
//    // デバイス独自設定. (AudioMIDI 設定アプリより)
//    m_inputAudioFormat.setSampleRate(96000);
//    m_inputAudioFormat.setChannelCount(1);
//    m_inputAudioFormat.setSampleSize(32);
//    m_inputAudioFormat.setSampleType(QAudioFormat::SignedInt);
//    //    qDebug() << "rewrite settings       " << m_inputAudioFormat;
//    //    m_inputAudioFormat = selectedDeviceInfo.nearestFormat(m_outputAudioFormat);
//        qDebug() << "current settings       " << m_inputAudioFormat;
//    qDebug() << "-------------------------------------------------------------";

//    if (m_pAudioInput) {
//        m_pAudioInput->deleteLater();
//        m_pAudioInput->disconnect(this);
//        m_pAudioInput = nullptr;
//    }
//    m_pAudioInput = new QAudioInput (selectedDeviceInfo, m_inputAudioFormat);
//    connect(m_pAudioInput, &QAudioInput::stateChanged , this, [=](QAudio::State state) { qDebug() << "QAudioInput::stateChanged:" << state; });

//    qDebug() << "audioInput.start()";
//    m_pInputIO = m_pAudioInput->start();
//    m_pInputIO->open(QIODevice::ReadOnly);
//    connect(m_pInputIO, &QIODevice::readyRead, this, &InOutStreamControl::onReadyRead);
//}

//void InOutStreamControl::selectAudioOutputDeviceByIndex(int index)
//{
//    const QAudioDeviceInfo& selectedDeviceInfo = m_outputDevicesInfo.at(index);


//    qDebug() << "- Output ----------------------------------------------------";
//    qDebug() << "selected deviceName    " << selectedDeviceInfo.deviceName();
//    qDebug() << "supportedSampleRates   " << selectedDeviceInfo.supportedSampleRates();
//    qDebug() << "supportedChannelCounts " << selectedDeviceInfo.supportedChannelCounts();
//    qDebug() << "supportedSampleSizes   " << selectedDeviceInfo.supportedSampleSizes();
//    qDebug() << "supportedSampleTypes   " << selectedDeviceInfo.supportedSampleTypes();
//    qDebug() << "supportedCodecs        " << selectedDeviceInfo.supportedCodecs();
//    qDebug() << "- format ----------------------------------------------------";
//    m_outputAudioFormat = selectedDeviceInfo.nearestFormat(m_outputAudioFormat);
//    qDebug() << "nearest settings       " << m_outputAudioFormat;
//    // デバイス独自設定. (AudioMIDI 設定アプリより)
//    m_outputAudioFormat.setChannelCount(2);
//    m_outputAudioFormat.setSampleSize(32);
//    //    m_outputAudioFormat.setSampleType(QAudioFormat::SignedInt);
//    //    qDebug() << "rewrite settings       " << m_outputAudioFormat;
//    //    m_outputAudioFormat = selectedDeviceInfo.nearestFormat(m_outputAudioFormat);
//    qDebug() << "current settings       " << m_outputAudioFormat;
//    qDebug() << "-------------------------------------------------------------";

//    if (m_pAudioOutput) {
//        m_pAudioOutput->deleteLater();
//        m_pAudioOutput->disconnect(this);
//        m_pAudioOutput = nullptr;
//    }

//    m_pAudioOutput = new QAudioOutput (m_outputAudioFormat, this);
//    connect(m_pAudioOutput, &QAudioOutput::stateChanged , this, [=](QAudio::State state) { qDebug() << "QAudioOutput::stateChanged:" << state; });

//    qDebug() << "audioOutput.start()";
//    m_pOutputIO = m_pAudioOutput->start();
//    m_pOutputIO->open(QIODevice::WriteOnly);
//}

//void InOutStreamControl::onReadyRead()
//{
//    m_audioInputData = m_pInputIO->readAll();

//    static int count;
//    if (count++ > 500) {
//        if (m_audioInputData.toInt() == 0) {
//            qDebug() << "no data";
//        }
//        qDebug().noquote() << m_audioInputData.toHex()/*.mid(0,10)*/;
//        count = 0;
//    }

//    emit audioInputDataChanged();
//    if (m_pOutputIO) {
//        m_pOutputIO->write(m_audioInputData);
//    }

//}


//qreal InOutStreamControl::outputVolume() const
//{
//    if (m_pAudioOutput) {
//        return m_pAudioOutput->volume();

//    } else {
//        return 0;
//    }
//}

//void InOutStreamControl::setOutputVolume(qreal newOutputVolume)
//{
//    if (m_pAudioOutput) {
//        if (qFuzzyCompare(m_pAudioOutput->volume(), newOutputVolume))
//            return;
//        m_pAudioOutput->setVolume(newOutputVolume);
//        emit outputVolumeChanged();
//    } else {
//        return;
//    }
//}

//const QByteArray &InOutStreamControl::audioInputData() const
//{
//    return m_audioInputData;
//}

InOutStreamControl::InOutStreamControl(QObject *parent) : QObject(parent)
{
//    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
//    qDebug() << "-----------------------";
//    qDebug() << "default play deviceName" << info.deviceName();
//    // SETUP audio output device instance.

//    qDebug() << "supportedSampleRates   " << info.supportedSampleRates();
//    qDebug() << "supportedChannelCounts " << info.supportedChannelCounts();
//    qDebug() << "supportedSampleSizes   " << info.supportedSampleSizes();
//    qDebug() << "supportedSampleTypes   " << info.supportedSampleTypes();
//    qDebug() << "supportedCodecs        " << info.supportedCodecs();

//    m_outputAudioFormat.setSampleRate(96000);
//    m_outputAudioFormat.setChannelCount(2); // stereo.
//    m_outputAudioFormat.setSampleSize(64);
//    m_outputAudioFormat.setSampleType(QAudioFormat::Float);
//    m_outputAudioFormat.setByteOrder(QAudioFormat::LittleEndian);
//    m_outputAudioFormat.setCodec("audio/pcm");

//    m_outputAudioFormat = info.nearestFormat(m_outputAudioFormat);
//    qDebug() << "m_outputAudioFormat:" << m_outputAudioFormat;
//    qDebug() << "-----------------------";
}

const QList<AudioDevice *> &InOutStreamControl::audioDevices() const
{
    // TODO 実装.
}

const QString &InOutStreamControl::inputDeviceName() const
{
    // TODO 実装.
}

const QString &InOutStreamControl::outputDeviceName() const
{
    // TODO 実装.
}

int InOutStreamControl::commonSampleRate() const
{
    return m_commonSampleRate;
}

int InOutStreamControl::commonSampleSize() const
{
    return m_commonSampleSize;
}

QAudioFormat::SampleType InOutStreamControl::commonSampleType() const
{
    return m_commonSampleType;
}

const QString &InOutStreamControl::commonCodec() const
{
    return m_commonCodec;
}

AudioDevice::AudioDevice(QAudioDeviceInfo &deviceInfo, QObject *parent)
    : QObject(parent),m_deviceInfo(deviceInfo)
{

}

const QString AudioDevice::name() const
{
    return m_deviceInfo.deviceName();
}

AudioDevice::AudioDeviceType AudioDevice::deviceMode() const
{
    if (QAudioDeviceInfo::availableDevices(QAudio::AudioInput).contains(m_deviceInfo)) {
        return AudioDevice::InputAudioDevice;
    }
    if (QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).contains(m_deviceInfo)) {
        return AudioDevice::OutputAudioDevice;
    }
    return AudioDevice::InvalidTypeDevice;
}

int AudioDevice::channel() const
{

}

int AudioDevice::sampleRate() const
{

}

int AudioDevice::sampleSize() const
{

}

QAudioFormat::SampleType AudioDevice::sampleType() const
{

}

const QString &AudioDevice::codec() const
{

}

bool AudioDevice::setChannel(int newChannel) const
{

}

bool AudioDevice::setSampleRate(int newSampleRate) const
{

}

bool AudioDevice::setSampleSize(int newSampleSize) const
{

}

bool AudioDevice::setSampleType(QAudioFormat::SampleType newSampleType) const
{

}

bool AudioDevice::setCodec(const QString newCodec) const
{

}


const QList<int> &AudioDevice::supportedChannelCounts() const
{
    // TODO 実装.
}

const QList<int> &AudioDevice::supportedSampleRates() const
{
    // TODO 実装.
}

const QList<int> &AudioDevice::supportedSampleSizes() const
{
    // TODO 実装.
}

const QList<QAudioFormat::SampleType> &AudioDevice::supportedSampleTypes() const
{
    // TODO 実装.
}

const QStringList &AudioDevice::supportedCodecs() const
{
    // TODO 実装.
}

QVector<double> AudioDevice::readoutSamples(bool &isOK) const
{
    if (this->deviceMode() == AudioDevice::OutputAudioDevice) {
        // デバイスTYPE違い.
        isOK = false;
        return QVector<double>();
    }

    if (m_pIODevice == nullptr) {
        // IODevice nullptr チェック.
        isOK = false;
        return QVector<double>();
    }

    const QByteArray bytes = m_pIODevice->readAll();
    const QVector<double> samples = _samplesFromBytesArray(bytes);

    isOK = true;
    return samples;
}

void AudioDevice::writeSamples(const QVector<double> &samples, bool &isOK)
{
    if (this->deviceMode() == AudioDevice::InputAudioDevice) {
        // デバイスTYPE違い.
        isOK = false;
        return;
    }

    if (m_pIODevice == nullptr) {
        // IODevice nullptr チェック.
        isOK = false;
        return;
    }

    const QByteArray bytes = _byteArrayFromSamples(samples);
    m_pIODevice->write(bytes);

    isOK = true;
    return;
}

QByteArray &AudioDevice::_byteArrayFromSamples(const QVector<double> &samples) const
{
    // TODO CONVERT実装.
}

QVector<double> &AudioDevice::_samplesFromBytesArray(const QByteArray &bytes) const
{
    // TODO CONVERT実装.
}

