/**
 * Copyright (c) 2012-2016 Derry (deyolu@yeah.net)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef _SQLITECC_RESULTSET_H_
#define _SQLITECC_RESULTSET_H_

#include <string>

struct sqlite3_stmt;

namespace sqlitecc {

class ResultSet {
    public:
        explicit ResultSet(sqlite3_stmt* stmt)
            : stmt_(stmt)
        {
            // constructor
        }

        ~ResultSet();

        bool next() const ;

        std::string getString(int colIndex);
        std::string getString(const char* colName) {
            return getString(findColumn(colName));
        }

        int getInt(int colIndex);
        int getInt(const char* colName) {
            return getInt(findColumn(colName));
        }

        double getDouble(int colIndex);
        double getDouble(const char* colName) {
            return getDouble(findColumn(colName));
        }

        // return size of column bytes or -1 on failed.
        int getBlob(int colIndex, const void** data);
        int getBlob(const char* colName, const void** data) {
            int index = findColumn(colName);
            return getBlob(index, data);
        }

        int findColumn(const char* name);

    private:
        sqlite3_stmt* stmt_;
};

}



#endif // _SQLITECC_RESULTSET_H_

