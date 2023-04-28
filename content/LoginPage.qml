import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import ProtectClient
import com.abeir.protect
import "widgets"

AbstractPage {
    title: "Login"
    pageCategory: 'LoginPage'
    focus: true

    ColumnLayout {
        id: flowItem
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.leftMargin: 20
        spacing: 20

        InputField {
            id: usernameInput
            labelText: qsTr("Username")
            placeholderText: qsTr("Input Username")
        }

        InputField {
            id: passwordInput
            echoMode: TextInput.Password
            labelText: qsTr("Password")
            placeholderText: qsTr("Input Password")
        }

        SubmitField {
            submitText: qsTr("Submit")
            resetText: qsTr("Reset")

            onSubmitClicked: {
                login()
            }

            onResetClicked: {
                usernameInput.text = ''
                passwordInput.text = ''
            }
        }

    }

    Keys.onReleased: (event)=> {
        if(event.key === Qt.Key_Enter || event.key === Qt.Key_Return){
            login();
        }
    }

    Connections {
        target: MemberManager
        onLoginSuccess: {
            stackView.replace('qrc:/content/AccountPage.qml', {"stackView": stackView})
        }
        onLoginFailed: (msg)=>{
            toastError(msg)
        }
    }

    function login(){
        if(!usernameInput.text){
            usernameInput.selectInput()
            toastError('username is empty')
            return;
        }
        if(!passwordInput.text){
            passwordInput.selectInput()
            toastError('password is empty')
            return;
        }
        MemberManager.login(usernameInput.text, passwordInput.text)
    }
}
