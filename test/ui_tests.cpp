#include "gtest/gtest.h"

#include "config.h"

#include "../include/mock_database.h"
#include "../include/mock_io.h"
#include "../include/transaction.h"
#include "../include/command_interface.h"
using namespace pft;

TEST(UiTests, UiTestSanityCheck) {
    MockDatabase mockDatabase;
    
    MockIo mockIo;
    mockIo.addInput("exit");

    CommandInterface cmd;
    cmd.SetIoLayer(&mockIo);
    cmd.SetDatabase(&mockDatabase);
    EXPECT_FALSE(cmd.RunCommand());
}
