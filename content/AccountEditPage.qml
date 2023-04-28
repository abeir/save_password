import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 6.2
import ProtectClient
import com.abeir.protect
import "widgets"

AbstractPage {
    title: "Edit Account"
    pageCategory: 'AccountEditPage'

    property var model: null

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
            text: model ? model.Url : ''
        }

        InputField {
            id: usernameField
            placeholderText: "Input Username"
            labelText: "Username"
            text: model ? model.Username : ''
        }

        InputField {
            id: passwordField
            placeholderText: "Input Password"
            labelText: "Password"
            text: model ? model.Password : ''
        }

        InputField {
            id: commentField
            placeholderText: "Input Comment"
            labelText: "Comment"
            text: model ? model.Comment : ''
        }

        InputField {
            labelText: "CreatedAt"
            text: model ? model.CreatedAt : ''
            readOnly: true
        }

        InputField {
            labelText: "UpdatedAt"
            text: model ? model.UpdatedAt : ''
            readOnly: true
        }

        SubmitField {
            id: submitField
            onSubmitClicked: {
                if(checkEditAccount()){
                    AccountManager.update(model.Id, urlField.text, usernameField.text, passwordField.text, commentField.text)
                }
            }
            onResetClicked: {
                urlField.text = model.Url
                usernameField.text = model.Username
                passwordField.text = model.Password
                commentField.text = model.Comment
            }
        }
    }

    Connections {
        target: AccountManager
        onUpdateSuccess: {
            stackView.pop();
        }
        onUpdateFailed: (msg)=>{
            toastError(msg);
        }
    }

    function checkEditAccount(){
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
