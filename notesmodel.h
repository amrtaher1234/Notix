#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <QObject>
#include <QString>

class NotesModel : public QObject
{
	Q_OBJECT

	QString storage_location;
public:
	explicit NotesModel(QObject *parent = nullptr);
	Q_INVOKABLE void text_changed(const QString& uuid, const QString& new_text);
	Q_INVOKABLE QString generate_id();
	QStringList get_all_note_names();
	Q_INVOKABLE QString load_note(const QString& uuid);

signals:

public slots:
};

#endif // NOTESMODEL_H
