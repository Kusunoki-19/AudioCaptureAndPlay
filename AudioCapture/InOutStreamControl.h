#ifndef AUDIOCAPTUREPLAYER_H
#define AUDIOCAPTUREPLAYER_H

#include <QObject>
#include <QTimer>

#include <QVariantList>

#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QAudioInput>
#include <QIODevice>

#include <memory>

class InOutStreamControl;
class AudioDevice;

// 入出力コントロール =============================================================
class InOutStreamControl : public QObject
{
    Q_OBJECT
public:
    explicit InOutStreamControl(QObject *parent = nullptr);

    // デバイス一覧.
    Q_PROPERTY(QList<AudioDevice *> audioDevices READ audioDevices NOTIFY audioDevicesChanged)
    // 入出力デバイス決定.
    Q_PROPERTY(QString inputDeviceName  READ inputDeviceName  NOTIFY inputDeviceNameChanged )
    Q_PROPERTY(QString outputDeviceName READ outputDeviceName NOTIFY outputDeviceNameChanged)
    // 入出力共通設定.
    Q_PROPERTY(int                         commonSampleRate READ commonSampleRate NOTIFY commonSampleRateChanged )
    Q_PROPERTY(int                         commonSampleSize READ commonSampleSize NOTIFY commonSampleSizeChanged )
    Q_PROPERTY(QAudioFormat::SampleType    commonSampleType READ commonSampleType NOTIFY commonSampleTypeChanged )
    Q_PROPERTY(const QString               commonCodec      READ commonCodec      NOTIFY commonCodecChanged      )

    const QList<AudioDevice *> &audioDevices() const;
    const QString &inputDeviceName() const;
    const QString &outputDeviceName() const;
    int commonSampleRate() const;
    int commonSampleSize() const;
    QAudioFormat::SampleType commonSampleType() const;
    const QString &commonCodec() const;

signals:
    void audioDevicesChanged();
    void inputDeviceNameChanged();
    void outputDeviceNameChanged();
    void commonSampleRateChanged();
    void commonSampleSizeChanged();
    void commonSampleTypeChanged();
    void commonCodecChanged();

private:
    QList<AudioDevice *>        m_pAudioDevices     ;
    int                         m_commonSampleRate  ;
    int                         m_commonSampleSize  ;
    QAudioFormat::SampleType    m_commonSampleType  ;
    const QString               m_commonCodec       ;
};


// デバイス単位クラス =============================================================
class AudioDevice : public QObject
{
    Q_OBJECT

    explicit AudioDevice(QAudioDeviceInfo &deviceInfo, QObject *parent = nullptr);

    // FOR QML/CPP.
    enum AudioDeviceType{
        InvalidTypeDevice,
        InputAudioDevice,
        OutputAudioDevice,
    };
    Q_ENUM(AudioDeviceType)

public:
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(AudioDevice::AudioDeviceType deviceMode READ deviceMode NOTIFY deviceModeChanged)
    Q_PROPERTY(QList<int> supportedChannelCounts READ supportedChannelCounts NOTIFY supportedChannelCounts)
    Q_PROPERTY(int channel READ channel WRITE setChannel NOTIFY onChannelChanged)

signals:
    void nameChanged();
    void deviceModeChanged();
    void supportedChannelCounts();
    void onChannelChanged();


public:
    // FOR CPP

    // methods for property.
    // 直近設定.
    const QString                         name()       const;
    AudioDevice::AudioDeviceType          deviceMode() const;
    int                                   channel()    const;
    int                                   sampleRate() const;
    int                                   sampleSize() const;
    QAudioFormat::SampleType              sampleType() const;
    const QString                         codec()     const;

    // 設定変更.
    void                                  setChannel     (int                       newChannel)    ;
    void                                  setSampleRate  (int                       newSampleRate);
    void                                  setSampleSize  (int                       newSampleSize);
    void                                  setSampleType  (QAudioFormat::SampleType  newSampleType);
    void                                  setCodec       (const QString             newCodec)      ;

    // 対応設定リスト.
    const QList<int>                      supportedChannelCounts() const;
    const QList<int>                      supportedSampleRates()   const;
    const QList<int>                      supportedSampleSizes()   const;
    const QList<QAudioFormat::SampleType> supportedSampleTypes()   const;
    const QStringList                     supportedCodecs()        const;

    // methods for read/write.
    QVector<double> readoutSamples(bool &isOK) const;
    void writeSamples(const QVector <double> &samples, bool &isOK);

    QTimer m_setttingChangePollingTimer;

signals:
    void formatChanged();

private:
    // BYTES <--> SamplesList Converts.
    QByteArray &_byteArrayFromSamples(const QVector<double> &samples) const;
    QVector<double> &_samplesFromBytesArray(const QByteArray &bytes) const;
    void _requestApplyCurrentFormat();
    void _execApplyCurrentFormat();

private:
    const QAudioDeviceInfo  m_deviceInfo;
    QAudioFormat            m_audioFormat;
    std::shared_ptr<QIODevice> m_pIODevice;
    std::shared_ptr<QAudioInput> m_pAudioInput;
    std::shared_ptr<QAudioOutput> m_pAudioOutput;
};
#endif // AUDIOCAPTUREPLAYER_H
