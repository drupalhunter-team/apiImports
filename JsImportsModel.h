#ifndef JSIMPORTSMODEL_H
#define JSIMPORTSMODEL_H

#include <QAbstractTableModel>
#include "JsImportInfo.h"

class JsImportsModel : public QAbstractTableModel
{
public:
    enum {
        HidName = 0,
        HidFile,
        HidFunction,
    };

    enum {
        ImportInfoRole = Qt::UserRole + 1,
    };

public:
    JsImportsModel( const QList<JsImportInfo*>& imports, QObject* parent = 0 );

    virtual int rowCount( const QModelIndex& parent = QModelIndex() ) const;
    virtual int columnCount( const QModelIndex& parent = QModelIndex() ) const;

    virtual QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;

private:
    QList<JsImportInfo*> Imports;
};

#endif // JSIMPORTSMODEL_H
