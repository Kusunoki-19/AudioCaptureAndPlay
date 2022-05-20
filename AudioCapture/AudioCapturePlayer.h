#ifndef AUDIOCAPTUREPLAYER_H
#define AUDIOCAPTUREPLAYER_H

#include <QObject>

#include <QVariantList>

#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QAudioInput>
#include <QIODevice>

class AudioCapturePlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioCapturePlayer(QObject *parent = nullptr);

    // properties.
    // devices info.
    Q_PROPERTY(QVariantList audioInputDevices READ audioInputDevices NOTIFY audioDevicesChanged)
    const QVariantList &audioInputDevices() ;

    Q_PROPERTY(QVariantList audioOutputDevices READ audioOutputDevices NOTIFY audioDevicesChanged)
    const QVariantList &audioOutputDevices() ;

    // others.
    Q_PROPERTY(QByteArray audioInputData READ audioInputData NOTIFY audioInputDataChanged)
    const QByteArray &audioInputData() const;

    Q_PROPERTY(qreal outputVolume READ outputVolume WRITE setOutputVolume NOTIFY outputVolumeChanged)
    qreal outputVolume() const;
    void setOutputVolume(qreal newOutputVolume);


    // functions.
    Q_INVOKABLE void selectAudioInputDeviceByIndex(int index);
    Q_INVOKABLE void selectAudioOutputDeviceByIndex(int index);


signals:
    void audioDevicesChanged();
    void outputVolumeChanged();
    void audioInputDataChanged();

protected:

private slots:
    void onReadyRead();

private:
    QList<QAudioDeviceInfo> m_inputDevicesInfo;
    QList<QAudioDeviceInfo> m_outputDevicesInfo;
    QVariantList m_devicesInfoForQML;

    QIODevice* m_pInputIO = nullptr;
    QIODevice* m_pOutputIO = nullptr;
    QAudioInput* m_pAudioInput = nullptr;
    QAudioOutput* m_pAudioOutput = nullptr;
    QAudioFormat m_outputAudioFormat;
    QAudioFormat m_inputAudioFormat;

    QVariantList m_audioDevices = QVariantList();


    QByteArray m_audioInputData;
    QVariantList m_audioOutputDevices;
};

#endif // AUDIOCAPTUREPLAYER_H
