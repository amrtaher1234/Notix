#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QVector>

#include "notesmodel.h"
#include "cursorposprovider.h"
#include "notesadder.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);
	NotesModel notes_model;
	CursorPosProvider mouse_pos_provider;
	QStringList note_names = notes_model.get_all_note_names();
	QVector<QObject*> notes;


	// Using QQmlComponent
	QQmlEngine engine;
	NotesAdder notes_adder(&engine);

	engine.rootContext()->setContextProperty("notes_model", &notes_model);
	engine.rootContext()->setContextProperty("notes_adder", &notes_adder);
	engine.rootContext()->setContextProperty("mouse_position", &mouse_pos_provider);

	for(QString note_name : note_names)
	{
		QString note_text = notes_model.load_note(note_name);
		if (note_text.trimmed().isEmpty()){
			notes_model.delete_note(note_name);
			continue;
		}

		QQmlComponent component(&engine, QUrl("qrc:/main.qml"));
		QObject *note = component.create();
		note->setProperty("uuid", note_name);
		note->setProperty("text", note_text);
		notes.push_back(note);
	}

	if(!notes.size())
	{
		QQmlComponent component(&engine, QUrl("qrc:/main.qml"));
		QObject* note = component.create();
		note->setProperty("uuid", NotesModel::generate_id());
		notes.push_back(note);
	}

	return app.exec();
}
