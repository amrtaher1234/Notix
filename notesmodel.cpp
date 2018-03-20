#include "notesmodel.h"

#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QUuid>

int NotesModel::x = 550;
int NotesModel::y = 200;
int NotesModel::pos_offset = 10;

NotesModel::NotesModel(QObject *parent) : QObject(parent)
{
	QString config_location = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + '/';
	storage_location = config_location + "Notix/";

	QDir dir;
	if (!dir.exists(storage_location)) dir.mkdir(storage_location);
}

void NotesModel::text_changed(const QString& uuid, const QString& new_text)
{
	QFile file(storage_location + uuid);
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	file.write(new_text.toLocal8Bit());
}

QString NotesModel::generate_id()
{
	return QUuid::createUuid().toString();
}

QStringList NotesModel::get_all_note_names()
{
	QDir dir(storage_location);
	return dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);;
}

int NotesModel::get_next_x_pos()
{
	int to_return = x + pos_offset;
	x += pos_offset;
	return to_return;
}

int NotesModel::get_next_y_pos()
{
	int to_return = y + pos_offset;
	y += pos_offset;
	return to_return;
}

QString NotesModel::load_note(const QString& uuid)
{
	QFile file(storage_location + uuid);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	return file.readAll();
}

void NotesModel::delete_note(const QString& uuid)
{
	QFile file(storage_location + uuid);
	file.remove();
}
