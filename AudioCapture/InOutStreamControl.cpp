#include "InOutStreamControl.h"

#include <QDebug>


InOutStreamControl::InOutStreamControl(QObject *parent) : QObject(parent)
{
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

// CLASS AudioDevice ===========================================================
// AudioDevice property getter -------------------------------------------------
/**
 * @brief AudioDevice::channel
 * @return
 */
int AudioDevice::channel() const
{
    return m_audioFormat.channelCount();

}

/**
 * @brief AudioDevice::sampleRate
 * @return
 */
int AudioDevice::sampleRate() const
{
    return m_audioFormat.sampleRate();
}

/**
 * @brief AudioDevice::sampleSize
 * @return
 */
int AudioDevice::sampleSize() const
{
    return m_audioFormat.sampleSize();
}

/**
 * @brief AudioDevice::sampleType
 * @return
 */
QAudioFormat::SampleType AudioDevice::sampleType() const
{
    return m_audioFormat.sampleType();
}

/**
 * @brief AudioDevice::codec
 * @return
 */
const QString AudioDevice::codec() const
{
    return m_audioFormat.codec();
}

// AudioDevice property setter -------------------------------------------------
/**
 * @brief AudioDevice::setChannel
 * @param newChannel
 */
void AudioDevice::setChannel(int newChannel)
{
    m_audioFormat.setChannelCount(newChannel);
    return;
}

/**
 * @brief AudioDevice::setSampleRate
 * @param newSampleRate
 */
void AudioDevice::setSampleRate(int newSampleRate)
{
    m_audioFormat.setSampleRate(newSampleRate);
    return;
}

/**
 * @brief AudioDevice::setSampleSize
 * @param newSampleSize
 */
void AudioDevice::setSampleSize(int newSampleSize)
{
    m_audioFormat.setSampleSize(newSampleSize);
    return;
}

/**
 * @brief AudioDevice::setSampleType
 * @param newSampleType
 */
void AudioDevice::setSampleType(QAudioFormat::SampleType newSampleType)
{
    m_audioFormat.setSampleType(newSampleType);
    return;
}

/**
 * @brief AudioDevice::setCodec
 * @param newCodec
 */
void AudioDevice::setCodec(const QString newCodec)
{
    m_audioFormat.setCodec(newCodec);
    return;
}

/**
 * @brief AudioDevice::supportedChannelCounts
 * @return
 */
const QList<int> AudioDevice::supportedChannelCounts() const
{
    return m_deviceInfo.supportedChannelCounts();
}

/**
 * @brief AudioDevice::supportedSampleRates
 * @return
 */
const QList<int> AudioDevice::supportedSampleRates() const
{
    return m_deviceInfo.supportedSampleRates();
}

/**
 * @brief AudioDevice::supportedSampleSizes
 * @return
 */
const QList<int> AudioDevice::supportedSampleSizes() const
{
    return m_deviceInfo.supportedSampleSizes();
}

/**
 * @brief AudioDevice::supportedSampleTypes
 * @return
 */
const QList<QAudioFormat::SampleType> AudioDevice::supportedSampleTypes() const
{
    return m_deviceInfo.supportedSampleTypes();
}

/**
 * @brief AudioDevice::supportedCodecs
 * @return
 */
const QStringList AudioDevice::supportedCodecs() const
{
    return m_deviceInfo.supportedCodecs();
}

// AudioDevice property functions ----------------------------------------------
/**
 * @brief AudioDevice::readoutSamples
 * @param isOK
 * @return
 */
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

/**
 * @brief AudioDevice::writeSamples
 * @param samples
 * @param isOK
 */
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

/**
 * @brief AudioDevice::_byteArrayFromSamples
 * @param samples
 * @return
 */
QByteArray &AudioDevice::_byteArrayFromSamples(const QVector<double> &samples) const
{
    // TODO CONVERT実装.
    Q_UNUSED(samples)
    static QByteArray temp;
    return temp;
}

/**
 * @brief AudioDevice::_samplesFromBytesArray
 * @param bytes
 * @return
 */
QVector<double> &AudioDevice::_samplesFromBytesArray(const QByteArray &bytes) const
{
    // TODO CONVERT実装.
    Q_UNUSED(bytes)
    static QVector<double>temp;
    return temp;
}

/**
 * @brief AudioDevice::_requestApplyCurrentFormat
 */
void AudioDevice::_requestApplyCurrentFormat()
{
    if (m_setttingChangePollingTimer.isActive()){
        return;
    }
    else {
        connect(&m_setttingChangePollingTimer, &QTimer::timeout, this, [=]() {
            disconnect(&m_setttingChangePollingTimer, &QTimer::timeout, this, nullptr);
            this->_execApplyCurrentFormat();
        });
        m_setttingChangePollingTimer.start(1000);
    }
}

void AudioDevice::_execApplyCurrentFormat()
{
    qDebug() << __func__;
}

