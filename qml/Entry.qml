import QtQuick.Controls 2.5
import QtQuick 2.0

Item {
    id: item
    property alias placeholder: field.placeholderText
    property string text: field.text
    TextField {
        id: field
        onTextEdited: {

        }
    }
}
