#include "notesadder.h"
#include "notesmodel.h"
#include <QDebug>

NotesAdder::NotesAdder(QQmlEngine* engine) : QObject(nullptr), m_engine(engine)
{

}

void NotesAdder::create_new_note()
{
	QQmlComponent component(m_engine, QUrl("qrc:/main.qml"));
	if( component.status() != component.Ready )
	{
		if( component.status() == component.Error )
			qInfo() << "Error: "+ component.errorString();
		return;
	}
	QObject* note = component.create();
	note->setProperty("uuid", NotesModel::generate_id());
}
