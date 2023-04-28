import QtQuick 6.2
import QtQuick.Controls 6.2
import ProtectClient
import com.abeir.protect


Drawer {
    id: drawer

    Column {
        anchors.fill: parent

        ItemDelegate {
            text: 'Account'
            width: parent.width
            visible: MemberManager.isLoggedIn && stackView.currentItem.pageCategory!=='AccountPage'
            onClicked: {
                stackView.push('qrc:/content/AccountPage.qml', {"stackView": stackView})
                drawer.close()
            }
        }

        ItemDelegate {
            text: 'Setting'
            width: parent.width
            visible: stackView.currentItem.pageCategory!=='SettingPage'
            onClicked: {
                stackView.push('qrc:/content/SettingPage.qml', {"stackView": stackView})
                drawer.close()
            }
        }

        ItemDelegate {
            text: 'Logout'
            width: parent.width
            visible: MemberManager.isLoggedIn && stackView.currentItem.pageCategory!=='LogoutPage'
            onClicked: {
                stackView.push('qrc:/content/LogoutPage.qml', {"stackView": stackView})
                drawer.close()
            }
        }
    }
}
