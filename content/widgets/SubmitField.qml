import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts
import ProtectClient

GridLayout {
    property string submitText: qsTr("Submit")
    property string resetText: qsTr("Reset")
    property bool resetVisible: true

    property int buttonWidth: 65

    property alias submitButton: submitBtn
    property alias resetButton: resetBtn

    signal submitClicked
    signal resetClicked

    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
    columnSpacing: 20
    columns: 2
    rows: 1

    IconButton {
        id: submitBtn
        Layout.preferredWidth: buttonWidth
        text: submitText
        color: '#52cc52'
        icon.source: 'qrc:/content/images/submit.png'
        onClicked: submitClicked()
    }

    IconButton {
        id: resetBtn
        Layout.preferredWidth: buttonWidth
        visible: resetVisible
        text: resetText
        color: '#d6d742'
        icon.source: 'qrc:/content/images/reset.png'
        onClicked: resetClicked()
    }

}
