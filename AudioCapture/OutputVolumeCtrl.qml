import QtQuick 2.12
import QtQuick.Controls 2.12
import InOutStreamControl 1.0

Slider {
    id:outputVolumeCtrl
    from : 0
    to : 1
    onPressedChanged:  {
        InOutStreamControl.outputVolume = this.value
    }

    onValueChanged:  {
        InOutStreamControl.outputVolume = this.value
    }

    Connections{
        target: InOutStreamControl
        function onOutputVolumeChanged () {
            if (!outputVolumeCtrl.pressed) {
                outputVolumeCtrl.value = InOutStreamControl.outputVolume
            }
        }
    }
}
