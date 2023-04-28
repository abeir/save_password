import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts
import "widgets"


Rectangle {
    property int listViewWidth: 0
    property int labelWidth: 100
    property int btnGroupWidth: 100

    height: content.height

    RowLayout {
        id: content
        spacing: 6

        ColumnLayout {
            spacing: 5
            Layout.preferredWidth: listViewWidth - btnGroupWidth

            Row {
                Label {
                    width: labelWidth
                    text: "URL"

                }
                TextInput {
                    width: listViewWidth - btnGroupWidth - labelWidth
                    selectByMouse: true
                    text: Url
                }
            }
            Row {
                Label {
                    width: labelWidth
                    text: "Username"
                }
                TextInput {
                    width: listViewWidth - btnGroupWidth - labelWidth
                    selectByMouse: true
                    text: Username
                }
            }
            Row {
                Label {
                    width: labelWidth
                    text: "Password"
                }
                TextInput {
                    width: listViewWidth - btnGroupWidth - labelWidth
                    selectByMouse: true
                    text: Password
                }
            }
            Row {
                Label {
                    width: labelWidth
                    text: "Comment"
                }
                TextInput {
                    width: listViewWidth - btnGroupWidth - labelWidth
                    selectByMouse: true
                    text: Comment
                }
            }

            Rectangle {
                Layout.topMargin: parent.spacing
                Layout.fillWidth: true
                height: 1
                color: "#d9d9d9"
            }
        }

        ColumnLayout {
            IconButton {
                Layout.fillWidth: true
                text: "modify"
                color: "#1aa3ff"
                icon.source: "qrc:/content/images/edit.png"
                onClicked: {
                    stackView.push('qrc:/content/AccountEditPage.qml', {"stackView": stackView, "model": model})
                }
            }

            IconButton {
                Layout.fillWidth: true
                text: "delete"
                color: "#ff5b33"
                icon.source: "qrc:/content/images/remove.png"
                onClicked: {
                    deleteDialog.url = model.Url
                    deleteDialog.username = model.Username
                    deleteDialog.value = model.Id
                    deleteDialog.open()
                }
            }
        }
    }

}
