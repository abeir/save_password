import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts

Dialog {
    id: confirmDialog
    anchors.centerIn: parent
    modal: true

    title: ''

    property alias contentText: ctntText.text
    property var value: null

    signal okClicked(var value)
    signal canncelClicked

    contentItem: Text {
        id: ctntText
        text: 'delete account?'
        wrapMode: Text.WordWrap
    }

    footer: DialogButtonBox {
        IconButton {
            id: okBtn
            color: '#d6d742'
            icon.source: 'qrc:/content/images/submit.png'
            DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
            onClicked: okClicked(confirmDialog.value)
        }
        IconButton {
            id: cancelBtn
            color: '#52cc52'
            icon.source: 'qrc:/content/images/close.png'
            DialogButtonBox.buttonRole: DialogButtonBox.RejectRole
            onClicked: canncelClicked()
        }

    }
}
