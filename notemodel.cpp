#include "notemodel.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

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

	QByteArray byteArray = file.readAll();

	QJsonDocument json_document(QJsonDocument::fromJson(byteArray));
	QJsonObject note_json(json_document.object());

	Note note;
	note.id = p_id;
	note.text = note_json.value("text").toString();
	note.title = note_json.value("title").toString();
	note.x = note_json.value("x").toString().toInt();
	note.y = note_json.value("y").toString().toInt();
	return note;
}

void Note::save()
{
	QJsonObject note_json;
	note_json.insert("title", title);
	note_json.insert("text", text);
	note_json.insert("x", QString::number(x));
	note_json.insert("y", QString::number(y));

	QFile file(storage_location + id);
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	file.write(QJsonDocument(note_json).toJson());
}

void Note::remove()
{
	QFile file(storage_location + id);
	file.remove();
}

void Note::archive()
{

}
