
set(SQLITECC_SRCS
    ../include/sqlitecc/Database.h
    ../include/sqlitecc/ResultSet.h
    ../include/sqlitecc/Statement.h
    Database.cc
    Statement.cc
    ResultSet.cc
    )

add_library(sqlitecc ${SQLITECC_SRCS})

