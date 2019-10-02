#include "../include/check_balance_form.h"

#include "../include/transaction.h"
#include "../include/transaction_class.h"
#include "../include/account.h"
#include "../include/transaction_type.h"

#include "../include/database_layer.h"

pft::CheckBalanceForm::CheckBalanceForm() {
    /* void */
}

pft::CheckBalanceForm::~CheckBalanceForm() {
    /* void */
}

void pft::CheckBalanceForm::Initialize() {
    Form::Initialize();

    m_accountField.SetFieldName(std::string("ACCOUNT"));
    m_accountField.SetInputType(FieldInput::INPUT_LOOKUP);

    m_typeField.SetFieldName(std::string("TYPE"));
    m_typeField.SetInputType(FieldInput::INPUT_LOOKUP);

    m_dateField.SetFieldName(std::string("DATE"));
    m_dateField.SetInputType(FieldInput::INPUT_SHORT_STRING);

    /* Register all fields*/
    RegisterField(&m_dateField);
    RegisterField(&m_typeField);
    RegisterField(&m_accountField);
}

void pft::CheckBalanceForm::Copy(Form *target) {
    // UNIMPLEMENTED
}
