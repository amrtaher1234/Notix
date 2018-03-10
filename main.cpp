#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QVector>

#include "notesmodel.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);
	NotesModel notes_model;

	QStringList note_names = notes_model.get_all_note_names();
	QVector<QObject*> notes;


	// Using QQmlComponent
	QQmlEngine engine;
	engine.rootContext()->setContextProperty("notes_model", new NotesModel);

	for(QString note_name : note_names)
	{
		QQmlComponent component(&engine, QUrl("qrc:/main.qml"));
		QObject *note = component.create();
		note->setProperty("uuid", note_name);
		note->setProperty("text", notes_model.load_note(note_name));
		notes.push_back(note);
	}

	if(!notes.size())
	{
		QQmlComponent component(&engine, QUrl("qrc:/main.qml"));
		QObject* note = component.create();
		note->setProperty("uuid", notes_model.generate_id());
		notes.push_back(note);
	}

	return app.exec();
}
