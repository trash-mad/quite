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
        property int _value: -1
        property bool _initial: true
        onValueChanged: {
            if (_value===value) {
                return;
            } else if (_value===-1) {
                _value=value;
                return;
            } else if (_initial) {
                _initial=false;
                return;
            } else {
                _value=value;
                onElementValueChanged(slider.value.toString())
            }
        }
    }
}
