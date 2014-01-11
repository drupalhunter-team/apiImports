#include "JsImportsModel.h"

JsImportsModel::JsImportsModel( const QList<JsImportInfo*>& imports, QObject* parent )
    : QAbstractTableModel( parent )
{
    Imports = imports;
}

int JsImportsModel::rowCount( const QModelIndex& ) const
{
    return Imports.size();
}

int JsImportsModel::columnCount( const QModelIndex& ) const
{
    return 3;
}

QVariant JsImportsModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( Qt::DisplayRole == role && Qt::Vertical == orientation )
    {
        return QString::number( section );
    }

    if( Qt::DisplayRole == role && Qt::Horizontal == orientation )
    {
        int hid = section;

        if( hid == HidName )     return tr( "Наименование" );
        if( hid == HidFile )     return tr( "Файл с функцией импорта" );
        if( hid == HidFunction ) return tr( "Функция импорта" );
    }

    return QVariant();
}

QVariant JsImportsModel::data( const QModelIndex& index, int role ) const
{
    if( !index.isValid() )
        return QVariant();

    if( Qt::DisplayRole == role )
    {
        int hid = index.column();
        const JsImportInfo* importInfo = Imports[ index.row() ];

        if( hid == HidName )     return importInfo->Name;
        if( hid == HidFile )     return importInfo->File;
        if( hid == HidFunction ) return importInfo->ImportFunction;
    }

    if( ImportInfoRole == role )
        return QVariant::fromValue<QObject*>( Imports[ index.row() ] );

    return QVariant();
}
