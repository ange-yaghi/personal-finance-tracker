#include <database_layer.h>
#include <command_interface.h>

#include <iostream>

int main()
{
    pft::DatabaseLayer dbLayer;
    dbLayer.OpenDatabase();

    pft::CommandInterface cmd;
    cmd.SetDatabase(&dbLayer);
    cmd.Run();
    
    return 0;
}
