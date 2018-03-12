#include "notesadder.h"
#include "notesmodel.h"

NotesAdder::NotesAdder(QQmlEngine* engine) : QObject(nullptr), m_engine(engine)
{

}

void NotesAdder::create_new_note()
{
	QQmlComponent component(m_engine, QUrl("qrc:/main.qml"));
	QObject* note = component.create();
	note->setProperty("uuid", NotesModel::generate_id());
}
