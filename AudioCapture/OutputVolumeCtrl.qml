import QtQuick 2.12
import QtQuick.Controls 2.12
import AudioCapturePlayer 1.0

Slider {
    id:outputVolumeCtrl
    from : 0
    to : 1
    onPressedChanged:  {
        AudioCapturePlayer.outputVolume = this.value
    }

    onValueChanged:  {
        AudioCapturePlayer.outputVolume = this.value
    }

    Connections{
        target: AudioCapturePlayer
        function onOutputVolumeChanged () {
            if (!outputVolumeCtrl.pressed) {
                outputVolumeCtrl.value = AudioCapturePlayer.outputVolume
            }
        }
    }
}
