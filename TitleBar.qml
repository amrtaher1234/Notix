import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.1

Rectangle {
	id: window_header
	width: parent.width
	height:25
	color: "#feff9c"

	property QtObject container
	property alias title_text: txt_title.text

	TextField {
		id : txt_title
		height: 25
		width: parent.width-close_btn.width-add_btn.width
		anchors.margins: 3
		anchors.left: window_header.left
		text: "Notix"

		color: "steelblue"
		selectionColor: "steelblue"
		selectedTextColor: "#eee"
		background: Rectangle { color: "#feff9c" }

		onTextChanged: notes_controller.title_changed(uuid, text)
	}

	MouseArea {
		id: titleBarMouseRegion
		property var clickPos
		anchors.fill: parent
		width: parent.width-close_btn.width-add_btn.width
		height: 25
		onPressed: {
			clickPos = { x: mouse.x, y: mouse.y }
		}
		onDoubleClicked: {
			txt_title.focus = true
		}

		onPositionChanged: {
			container.x = mouse_position.cursor_pos().x - clickPos.x
			container.y = mouse_position.cursor_pos().y - clickPos.y
			notes_controller.position_changed(uuid, container.x, container.y)
		}
	}

	Button {
		id: close_btn
		width: 50
		height: 25
		anchors.right: window_header.right
		text: "x"
		background: Rectangle {
			gradient: Gradient {
				GradientStop { position: 0 ; color: close_btn.pressed ? "#fff" : "#feff9c" }
				GradientStop { position: 1 ; color: close_btn.pressed ? "#fff" : "#feff9c" }
			}
		}

		onClicked:
			if (text_area.text.trim() === "")	{
				notes_controller.delete_note(uuid)
				container.close()
			}
			else{
				message_dialog.open()
			}
	}

	MessageDialog {
		id: message_dialog
		title: "Delete Note"
		text: "Are you sure you want to delete this note?"
		standardButtons: StandardButton.Yes | StandardButton.No

		onYes: {
			notes_controller.delete_note(uuid)
			container.close()
		}
		onNo: {

		}

		Component.onCompleted: visible = false
	}

	Button {
		id: add_btn
		width: 50
		height: 25
		anchors.right: close_btn.left

		text: "+"
		background: Rectangle {
			gradient: Gradient {
				GradientStop { position: 0 ; color: add_btn.pressed ? "#fff" : "#feff9c" }
				GradientStop { position: 1 ; color: add_btn.pressed ? "#fff" : "#feff9c" }
			}
		}
		onClicked: {
			notes_controller.create_new_note();
		}
	}
}
