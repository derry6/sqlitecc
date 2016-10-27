/**
 * Copyright (c) 2012-2016 Derry (deyolu@yeah.net)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "sqlitecc/ResultSet.h"

#include <sqlite3.h>
#include <string.h>

using namespace sqlitecc;

ResultSet::~ResultSet() {
}

bool ResultSet::next() const  {
    return ( sqlite3_step(stmt_) == SQLITE_ROW );
}

std::string ResultSet::getString(int colIndex) {
    if( colIndex > 0 ) {
        const unsigned char* data = sqlite3_column_text(stmt_, colIndex);
        if( data ) {
            return std::string(reinterpret_cast<const char*>(data));
        }
    }
    return std::string();
}

int ResultSet::getInt(int colIndex) {
    return sqlite3_column_int(stmt_, colIndex);
}

double ResultSet::getDouble(int colIndex) {
    return sqlite3_column_double(stmt_, colIndex);
}

int ResultSet::getBlob(int colIndex, const void** data) {
    if( colIndex > 0 ) {
        int col_type = sqlite3_column_type(stmt_, colIndex);
        if (col_type == SQLITE_BLOB ) {
            if( data ) {
                *data = sqlite3_column_blob(stmt_, colIndex);
            }
            return sqlite3_column_bytes(stmt_, colIndex);
        }
    }
    return -1;
}

int ResultSet::findColumn(const char* colName) {
    int colIndex = -1;
    if( colName == NULL )
        return colIndex;
    int colsCount = sqlite3_data_count(stmt_);
    for( int i = 0; i < colsCount; ++i ) {
        const char* name = sqlite3_column_name(stmt_, i);
        if( name && strcmp(name, colName) == 0 ) {
            colIndex = i;
            break;
        }
    }
    return colIndex;
}


