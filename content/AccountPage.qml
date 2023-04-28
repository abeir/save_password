import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts
import Qt5Compat.GraphicalEffects
import ProtectClient
import com.abeir.protect
import "widgets"


AbstractPage {
    title: "Account View"

    pageCategory: 'AccountPage'
    showMenuButton: true
    menuButtonIcon: 'qrc:/content/images/add.png'

    function clickMenuButton() {
        stackView.push('qrc:/content/AccountCreatePage.qml', {"stackView": stackView})
    }

    ListView {
        id: listView
        visible: false
        anchors.fill: parent
        topMargin: 10
        leftMargin: 10
        rightMargin: 10
        spacing: 10
        focus: true
        clip: true
        model: AccountManager.accountModel

        delegate: AccountDelegate {
            listViewWidth: listView.width
            labelWidth: 100
            btnGroupWidth: 80
        }
    }

    Rectangle {
        id: emptyRect
        visible: false
        anchors.fill: parent

        ColumnLayout {
            anchors.centerIn: parent
            Image {
                smooth: true
                fillMode: Image.PreserveAspectFit
                source: 'qrc:/content/images/cry.png'
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter

                ColorOverlay {
                    anchors.fill: parent
                    source: parent
                    color: '#bfbfbf'
                }
            }
            Text {
                text: 'No data'
                horizontalAlignment: Text.AlignHCenter
                Layout.fillWidth: true
            }
        }
    }

    state: AccountManager.empty ? 'empty' : 'no-empty'

    states: [
        State {
            name: "empty"
            PropertyChanges {
                emptyRect.visible: true
            }
        },
        State {
            name: "no-empty"
            PropertyChanges {
                listView.visible: true
            }
        }
    ]

    ConfirmDialog {
        id: deleteDialog
        title: 'delete account?'
        property alias url: urlText.text
        property alias username: usernameText.text

        contentItem: ColumnLayout {
            Text {
                text: 'Are you sure you need to delete the account ?'
                wrapMode: Text.WordWrap
            }

            Text {
                id: urlText
                color: '#e60000'
                font.underline: true
                wrapMode: Text.WrapAnywhere
                Layout.maximumWidth: Constants.width - 60
            }
            Text {
                id: usernameText
                color: '#e60000'
                font.underline: true
                wrapMode: Text.WordWrap
            }
        }

        onOkClicked: (value)=> {
            AccountManager.remove(value);
        }
    }

    Connections {
        target: AccountManager
        onRemoveSuccess: {
            toastSuccess('account removed')
        }
        onRemoveFailed: (msg)=>{
            toastError(msg);
        }
    }

}
