import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.3
import ProtectClient
import com.abeir.protect
import "widgets"

AbstractPage {
    title: "Logout"
    pageCategory: 'LogoutPage'

    ColumnLayout {
        id: columnLayout
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.leftMargin: 30

        Text {
            id: textItem
            text: "Are you sure you need to logout?"
            wrapMode: Text.WordWrap
            font.family: Constants.largeFont.family
            font.pixelSize: Constants.largeFont.pixelSize
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        SubmitField {
            submitText: qsTr("Submit")
            resetVisible: false

            onSubmitClicked: {
                logout()
            }
        }
    }

    Connections {
        target: MemberManager
        onLogoutSuccess: {
            stackView.replace(null, 'qrc:/content/LoginPage.qml', {'stackView': stackView})
        }
    }

    function logout(){
        MemberManager.logout();
    }

}
