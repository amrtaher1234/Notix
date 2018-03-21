#include "notescontroller.h"
#include <QDebug>
#include <QUuid>

size_t NotesController::last_x		= 550;
size_t NotesController::last_y		= 200;
size_t NotesController::pos_offset  = 20;

NotesController::NotesController(QObject *parent) : QObject(parent)
{
	QStringList note_names = get_all_note_names();

	m_qml_engine.rootContext()->setContextProperty("notes_controller", this);
	m_qml_engine.rootContext()->setContextProperty("mouse_position", &mouse_pos_provider);

	for(QString note_name : note_names)
	{
		Note note = Note::load(note_name);

		if (note.text.trimmed().isEmpty()){
			delete_note(note.id);
			continue;
		}

		notes[note.id] = note;
		create_new_note_view(note);
	}

	if(!note_names.size())
	{
		create_new_note();
	}
}

void NotesController::text_changed(const QString& uuid, const QString& new_text)
{
	Note note = notes[uuid];
	note.text = new_text;
	note.save();
}

void NotesController::title_changed(const QString& uuid, const QString& new_title)
{
	Note note = notes[uuid];
	note.title = new_title;
	note.save();
}

void NotesController::position_changed(const QString& uuid, size_t new_x, size_t new_y)
{
	Note note = notes[uuid];
	note.x = new_x;
	note.y = new_y;
	note.save();
}

QString NotesController::generate_id()
{
	return QUuid::createUuid().toString();
}

QStringList NotesController::get_all_note_names()
{
	return Note::get_all_note_names();
}

int NotesController::get_next_x_pos()
{
	last_x += pos_offset;
	return last_x;
}

int NotesController::get_next_y_pos()
{
	last_y += pos_offset;
	return last_y;
}

void NotesController::delete_note(const QString& uuid)
{
	notes[uuid].remove(); // delete from disk
	notes.remove(uuid); // delete from memory
	// be forgotten forever
}

void NotesController::create_new_note()
{
	Note note;
	note.id = generate_id();
	notes[note.id] = note;
	create_new_note_view(note);
}

void NotesController::create_new_note_view(Note note)
{
	QQmlComponent component(&m_qml_engine, QUrl("qrc:/NoteView.qml"));
	if( component.status() != component.Ready )
	{
		if( component.status() == component.Error )
			qInfo() << "Error: "+ component.errorString();
		return;
	}

	QObject* note_view = component.create();
	note_view->setProperty("uuid", note.id);
	note_view->setProperty("text", note.text);
}
