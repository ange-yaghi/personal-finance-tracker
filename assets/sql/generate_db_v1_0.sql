CREATE TABLE IF NOT EXISTS "ACCOUNTS" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"NAME"	TEXT,
	"LOCATION"	TEXT,
	"NOTES"	TEXT,
	"PARENT_ID"	INTEGER
);

CREATE TABLE IF NOT EXISTS "CLASSES" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"NAME"	TEXT,
	"PARENT_ID"	INTEGER,
	"DESCRIPTION" TEXT
);

CREATE TABLE IF NOT EXISTS "TRANSACTIONS" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"NAME"	TEXT,
	"TYPE_ID"	INTEGER,
	"CLASS_ID"	INTEGER,
	"PARENT_ENTITY_ID"	INTEGER,
	"SOURCE_ACCOUNT_ID"	INTEGER,
	"AMOUNT"	INTEGER,
	"DATE"	TEXT,
	"TARGET_ACCOUNT_ID"	INTEGER,
	"NOTES"	TEXT
);

CREATE TABLE IF NOT EXISTS  "TYPES" (
	"ID"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"NAME"	TEXT,
	"DESCRIPTION"	TEXT
);
