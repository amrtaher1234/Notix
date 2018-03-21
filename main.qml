import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Window {
	id: root
	property string uuid: ""
	property int xPos: -1
	property int yPos: -1
	property alias text: text_area.text
	flags: Qt.FramelessWindowHint
	visible: true
	width: 300
	height: 300
	x: xPos
	y: yPos
	color: "#feff9c"
	title: qsTr("Notix")

	TitleBar {
		id: title_bar
		anchors.top: parent.top
		height: 25
		container: root
	}

	TextArea {
		id: text_area
		anchors.top: title_bar.bottom
		width: parent.width
		height: parent.height-25
		wrapMode: Text.WrapAnywhere
		frameVisible: false
		Keys.onReleased: notes_controller.text_changed(uuid, this.text)
		style: TextAreaStyle {
			textColor: "#333"
			selectionColor: "steelblue"
			selectedTextColor: "#eee"
			backgroundColor: "#feff9c"
		}
		text: "";


		MouseArea {
			anchors.fill: parent
			acceptedButtons: Qt.RightButton
			onClicked: {

				if (mouse.button === Qt.RightButton)
				{
					contextMenu.menus
				}
			}
		}
	}

	Component.onCompleted: {
		if(uuid == "")
		{
			uuid = notes_controller.generate_id();
		}
		if (xPos == -1)
		{
			x = notes_controller.get_next_x_pos();
		}
		if (yPos == -1)
		{
			yPos = notes_controller.get_next_y_pos();
		}
	}
}
