#ifndef NOTESADDER_H
#define NOTESADDER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>

/// This whole class is made to have the function create_new_note available in qml
/// it creates a new note :D
class NotesAdder : public QObject
{
	Q_OBJECT

	QQmlEngine* m_engine;
public:
	explicit NotesAdder(QQmlEngine* engine);
	Q_INVOKABLE void create_new_note();

signals:

public slots:
};

#endif // NOTESADDER_H
