import QtQuick 2.0
import QtQuick.Controls 2.3

Rectangle {
	id: window_header
	width: parent.width
	color: "#feff9c" // just random one

	property QtObject container

	MouseArea {
		id: titleBarMouseRegion
		property var clickPos
		anchors.fill: parent
		onPressed: {
			clickPos = { x: mouse.x, y: mouse.y }
		}
		onPositionChanged: {
			container.x = mouse_position.cursor_pos().x - clickPos.x
			container.y = mouse_position.cursor_pos().y - clickPos.y
		}
	}

	Button {
		id: close_btn
		anchors.left: parent.left
		anchors.bottom: parent.bottom
		anchors.top: parent.top

		text: "x"
		onClicked: container.close()
	}

	Button {
		anchors.left: close_btn.right
		anchors.bottom: parent.bottom
		anchors.top: parent.top

		text: qsTr("+")

		onClicked: {
			var component = Qt.createComponent("main.qml")
			var window    = component.createObject(root)
			window.show()
		}
	}
}
