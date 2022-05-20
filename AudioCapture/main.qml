import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Window 2.12
import AudioCapturePlayer 1.0

Window {
    width: 640
    height: 480
    visible: true
    ColumnLayout {
        anchors.fill: parent

        Item {
            Layout.fillHeight: false;
            Layout.fillWidth: true;
            Layout.preferredHeight: 100;
            OutputVolumeCtrl {
                id: outputVolumeCtrl
                anchors.fill: parent
            }
        }
        //        Item {
        //            Layout.fillHeight: false;
        //            Layout.fillWidth: true;
        //            Layout.preferredHeight: 100;
        //            Item {
        //                anchors.fill: parent
        //                Connections {
        //                    target:AudioCapturePlayer
        //                    function onAudioInputDataChanged() {
        //                        audioInputCanvas.requestPaint()
        //                        console.log(AudioCapturePlayer.audioInputData)
        //                    }
        //                }
        //                Text {
        //                    text:AudioCapturePlayer.audioInputData
        //                }

        //                Canvas {
        //                    id:audioInputCanvas
        //                    anchors.fill: parent
        //                    onPaint: {
        //                        var ctx = getContext('2d')

        //                    }
        //                }
        //            }
        //        }

        Item {
            Layout.fillHeight: true;
            Layout.fillWidth: true;
            RowLayout {
                anchors.fill: parent

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Rectangle {
                        anchors.fill: parent
                        color:"skyblue"
                    }

                    AudioInputListView {
                        anchors.fill: parent
                    }
                }
                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    AudioOutputListView {
                        anchors.fill: parent
                    }
                }
            }

        }
    }

}
