#include "notemodel.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>

QString Note::storage_location = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/Notix/";

Note::Note()
{
	QDir dir;
	if (!dir.exists(storage_location)) dir.mkdir(storage_location);
}

QStringList Note::get_all_note_names()
{
	QDir dir(storage_location);
	return dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);
}

Note Note::load(QString p_id)
{
	QFile file(storage_location + p_id);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	Note note;
	note.id = p_id;
	note.text = file.readAll();
	return note;
}

void Note::save()
{
	QFile file(storage_location + id);
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	file.write(this->text.toLocal8Bit());
}

void Note::remove()
{
	QFile file(storage_location + id);
	file.remove();
}

void Note::archive()
{

}
