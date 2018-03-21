#ifndef NOTESCONTROLLER_H
#define NOTESCONTROLLER_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlEngine>
#include <QQmlContext>
#include <QVector>
#include <QDebug>
#include <QObject>
#include <QMap>

#include "notemodel.h"
#include "cursorposprovider.h"

class NotesController : public QObject
{
	Q_OBJECT

	// these three variables are used to avoid having new notes
	// being created in the same exact position as previous ones.
	static size_t last_x;
	static size_t last_y;
	static size_t pos_offset;

	QMap<QString, Note> notes;
	QQmlEngine m_qml_engine;
	CursorPosProvider mouse_pos_provider;

public:
	explicit NotesController(QObject *parent = nullptr);

	Q_INVOKABLE static QString generate_id();
	QStringList get_all_note_names();
	Q_INVOKABLE void delete_note(const QString& uuid);
	Q_INVOKABLE void create_new_note();

	void create_new_note_view(Note note);

	Q_INVOKABLE static int get_next_x_pos();
	Q_INVOKABLE static int get_next_y_pos();

	Q_INVOKABLE void text_changed(const QString& uuid, const QString& new_text);
	Q_INVOKABLE void title_changed(const QString& uuid, const QString& new_title);
	Q_INVOKABLE void position_changed(const QString& uuid, size_t new_x, size_t new_y);

signals:

public slots:
};

#endif // NOTESCONTROLLER_H
