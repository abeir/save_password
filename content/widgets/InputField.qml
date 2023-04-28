import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts
import ProtectClient

RowLayout {
    property alias labelText: label.text
    property alias placeholderText: textFid.placeholderText
    property alias echoMode: textFid.echoMode
    property alias validator: textFid.validator

    property alias text: textFid.text
    property alias readOnly: textFid.readOnly

    spacing: 15

    Layout.leftMargin: 0
    Layout.rightMargin: 0

    Label {
        id: label
        horizontalAlignment: Text.AlignRight
        Layout.minimumWidth: 80
        Layout.preferredWidth: 100

    }

    TextField {
        id: textFid
        selectByMouse: true
        Layout.fillWidth: true
    }

    function selectInput(){
        textFid.focus = true
        textFid.selectAll()
    }
}
