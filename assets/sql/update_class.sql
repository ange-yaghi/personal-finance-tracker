UPDATE "CLASSES" SET
		NAME = $NAME,
		DESCRIPTION = $DESCRIPTION,
		PARENT_ID = $PARENT_ID

		WHERE ID = $ID;
