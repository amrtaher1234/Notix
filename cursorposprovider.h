#ifndef CURSORPOSPROVIDER_H
#define CURSORPOSPROVIDER_H

#include <QObject>
#include <QCursor>
#include <QDebug>

class CursorPosProvider : public QObject
{
	Q_OBJECT
public:

	explicit CursorPosProvider(QObject *parent = nullptr) : QObject(parent)
	{
	}

	virtual ~CursorPosProvider() = default;

	Q_INVOKABLE QPointF cursor_pos()
	{
		return QCursor::pos();
	}

signals:

public slots:
};

#endif // CURSORPOSPROVIDER_H
