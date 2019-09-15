import QtQuick.Controls 2.5
import QtQuick 2.0

Item {
    id: item

    property alias from: slider.from
    property alias to: slider.to
    property alias step: slider.stepSize
    property alias value: slider.value

    Slider {
        id: slider
        live: false
        onValueChanged: {
            onElementValueChanged(slider.value.toString())
        }
    }
}
