#include <database_layer.h>
#include <command_interface.h>

#include <iostream>

int main() {
    pft::DatabaseLayer dbLayer;
	dbLayer.SetHomePath("../../");
    dbLayer.OpenDatabase("FinanceDatabase.db");

    pft::CommandInterface cmd;
    cmd.SetDatabase(&dbLayer);
    cmd.Run();
    
    return 0;
}
