import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import AudioCapturePlayer 1.0

ListView {
    id:audioListView
    model: AudioCapturePlayer.audioInputDevices

    delegate: Item{
        width:audioListView.width
        height:30
        RowLayout {
            anchors.fill: parent
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                implicitWidth: 10
                Text {
                    text:modelData.id
                    wrapMode: Text.WrapAnywhere
                }
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Text {
                    text:modelData.name
                    wrapMode: Text.WrapAnywhere
                }
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
                implicitWidth: 100
                Button {
                    text:"select"
                    onClicked : {
                        AudioCapturePlayer.selectAudioInputDeviceByIndex(modelData.id)
                    }
                }
            }

        }
    }
}
