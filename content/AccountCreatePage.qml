import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import ProtectClient
import com.abeir.protect
import "widgets"

AbstractPage {
    title: "Create Account"
    pageCategory: 'AccountCreatePage'

    ColumnLayout {
        id: columnLayout
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: 40
        anchors.leftMargin: 20

        InputField {
            id: urlField
            placeholderText: "Input Url"
            labelText: "Url"
        }

        InputField {
            id: usernameField
            placeholderText: "Input Username"
            labelText: "Username"
        }

        InputField {
            id: passwordField
            placeholderText: "Input Password"
            labelText: "Password"
        }

        InputField {
            id: commentField
            placeholderText: "Input Comment"
            labelText: "Comment"
        }

        SubmitField {
            id: submitField
            onSubmitClicked: {
                if(checkCreateAccount()){
                    AccountManager.create(urlField.text, usernameField.text, passwordField.text, commentField.text)
                }
            }
            onResetClicked: {
                urlField.text = ''
                usernameField.text = ''
                passwordField.text = ''
                commentField.text = ''
            }
        }
    }

    Connections {
        target: AccountManager
        onCreateSuccess: {
            stackView.pop();
        }
        onCreateFailed: (msg)=>{
            toastError(msg);
        }
    }

    function checkCreateAccount(){
        if(!urlField.text){
            urlField.selectInput();
            toastError('url is empty');
            return false;
        }
        if(!usernameField.text){
            usernameField.selectInput();
            toastError('username is empty');
            return false;
        }
        if(!passwordField.text){
            passwordField.selectInput();
            toastError('password is empty');
            return false;
        }
        return true;
    }
}
