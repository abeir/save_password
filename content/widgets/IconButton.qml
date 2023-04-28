import QtQuick 6.2
import QtQuick.Controls 6.2

Button {
    id: btn

    property color color: '#d9d9d9'
    property int radius: 4

    icon.color: "#ffffff"
    display: AbstractButton.IconOnly
    background: Rectangle {
        radius: btn.radius
        color: {
            if(btn.down)
                return Qt.lighter(btn.color, 1.1)
            else if(btn.hovered)
                return Qt.darker(btn.color, 1.1)
            else
                return btn.color
        }
    }
}
