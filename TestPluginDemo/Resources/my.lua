local sqlite3 = require("lsqlite3")

local dbPath = getPath() .. "mydb"

local db = sqlite3.open(  dbPath )

db:exec[[
  CREATE TABLE test (id INTEGER PRIMARY KEY, content);

  INSERT INTO test VALUES (1, 'fdsfdsfsfdf')
  INSERT INTO test VALUES (2, '132132')
]]

for row in db:nrows("SELECT * FROM test") do
    print(row.id, row.content)
end

