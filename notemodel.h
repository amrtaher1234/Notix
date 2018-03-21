#ifndef NOTESMODEL_H
#define NOTESMODEL_H

#include <QString>

class Note
{
	static QString storage_location;

public:
	Note();

	QString id = "";
	QString text = "";
	QString title = "Notix";
	size_t x = 0;
	size_t y = 0;

	static QStringList get_all_note_names();
	static Note load(QString p_id);
	void save();
	void remove();
	void archive();
};

#endif // NOTESMODEL_H
