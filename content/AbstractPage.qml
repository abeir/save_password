import QtQuick 6.2
import QtQuick.Controls 6.2

Page {
    property bool showMenuButton: false
    property string menuButtonIcon: ''
    property var pageCategory: null

    property StackView stackView: null

    function clickMenuButton() {

    }

    Popup {
        id: popup
        property int popupHeight: 50

        width: parent.width
        padding: 0
        margins: 0
        closePolicy: Popup.CloseOnEscape

        enter: Transition {
            ParallelAnimation {
                NumberAnimation { property: "height"; from: 0; to: popup.popupHeight }
                NumberAnimation { target: popupContent; property: "opacity"; from: 0; to: 1 }
            }
        }
        exit: Transition {
            ParallelAnimation {
                NumberAnimation { property: "height"; from: popup.height; to: 0 }
                NumberAnimation { target: popupContent; property: "opacity"; from: 1; to: 0 }
            }
        }
        background: Rectangle {
            id: popupBackground
            color: '#000000'
            opacity: 0.4
        }

        contentItem: Text {
            id: popupContent
            color: '#ffffff'
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        onOpened: {
            popupTimer.restart()
        }

        Timer {
            id: popupTimer
            interval: 2000
            running: false
            onTriggered: {
                popup.close()
            }
        }
    }

    /**
      弹出消息框
      message: 消息文本
      options: 额外配置
        options.height: 消息框高度
        options.color: 消息框颜色
        options.duration: 持续时间
      */
    function toast(message, options){
        if(!message){
            console.log('toast message is empty');
            return;
        }
        if(popup.opened){
            popupTimer.stop()
            popup.close()
        }
        if(options){
            popup.popupHeight = options.height ? options.height : 50;
            popupBackground.color = options.color ? options.color : '#000000';
            popupTimer.interval = options.duration ? options.duration : 2000;
        }
        popupContent.text = message;
        popup.open();
    }

    function toastError(message){
        toast(message, {'color': '#ff0000'})
    }

    function toastSuccess(message){
        toast(message, {'color': '#48d148'})
    }
}
