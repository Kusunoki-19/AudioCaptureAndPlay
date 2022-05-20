import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import InOutStreamControl 1.0

ListView {
    id:audioListView
    model: InOutStreamControl.audioInputDevices
    delegate: Item{
        width:audioListView.width
        height:30
        RowLayout {
            anchors.fill: parent
            Item {
                id:indexText
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
                implicitWidth: parent.width - selectBtn.implicitWidth - indexText.implicitWidth - parent.spacing*2
                Text {
                    text:modelData.name
                    wrapMode: Text.WrapAnywhere
                }
            }
            Item {
                id:selectBtn
                Layout.fillHeight: true
                Layout.fillWidth: true
                implicitWidth: 100
                Button {
                    text:"select"
                    onClicked : {
                        InOutStreamControl.selectAudioInputDeviceByIndex(modelData.id)
                    }
                }
            }
        }
    }
}
