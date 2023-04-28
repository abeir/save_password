import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts
import QtQuick.Dialogs
import ProtectClient

RowLayout {
    property alias labelText: label.text
    property alias placeholderText: textFid.placeholderText
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

        MouseArea {
            anchors.fill: parent
            onClicked: {
                folderDialog.open()
            }
        }

        FolderDialog {
            id: folderDialog
            currentFolder: textFid.text
            onAccepted: {
                textFid.text = selectedFolder.toString()
            }
        }
    }

    function selectInput(){
        textFid.focus = true
        textFid.selectAll()
    }
}
