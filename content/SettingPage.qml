import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import ProtectClient
import com.abeir.protect
import "widgets"

AbstractPage {
    title: "Setting"
    pageCategory: 'SettingPage'
    focus: true

    ColumnLayout {
        id: flowItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.leftMargin: 20
        spacing: 20

        FolderField {
            id: dataInput
            labelText: qsTr("Data Location")
            placeholderText: qsTr("Set data storage location")
            text: SettingManager.dataLocation
        }

        SubmitField {
            submitText: qsTr("Submit")
            resetText: qsTr("Reset")

            onSubmitClicked: {
                confirmDialog.locationText = dataInput.text;
                confirmDialog.value = dataInput.text;
                confirmDialog.open();
            }

            onResetClicked: {
                dataInput.text = SettingManager.dataLocation
            }
        }
    }

    ConfirmDialog {
        id: confirmDialog
        title: 'change data location?'
        property alias locationText: lctText.text

        contentItem: ColumnLayout {
            Text {
                text: 'Are you sure you need to change the data location?'
                wrapMode: Text.WordWrap
            }

            Text {
                id: lctText
                color: '#e60000'
                font.underline: true
                wrapMode: Text.WrapAnywhere
                Layout.maximumWidth: Constants.width - 60
            }
        }

        onOkClicked: (value)=> {
            SettingManager.dataLocation = value;
        }
    }

    Connections {
        target: SettingManager
        onSetSuccess: {
            stackView.pop()
        }
        onSetFailed: (msg)=>{
            toastError(msg)
        }
    }
}
