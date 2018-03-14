#ifndef TRANSACTION_FORM_H
#define TRANSACTION_FORM_H

#include <form.h>

#include <string_field.h>
#include <type_field.h>
#include <class_field.h>
#include <counterparty_field.h>
#include <int_field.h>
#include <account_field.h>
#include <double_field.h>
#include <date_field.h>

namespace pft {

    /* Forward declarations */
    class Transaction;

    // Implements a UI form for entering generic transactions
    class TransactionForm : public Form {
    public:
        TransactionForm();
        ~TransactionForm();

        virtual void Initialize();
        virtual void Copy(Form *target);

        // Populate all fields using a transaction as a reference
        void PopulateFields(Transaction *transaction);

        // Populate a transaction using the data entered in the form fields
        void PopulateTransaction(Transaction *target);

    protected:
        StringField m_nameField;
        TypeField m_typeField;
        ClassField m_classField;
        CounterpartyField m_counterpartyField;
        IntField m_parentIdField;
        AccountField m_accountField;
        DoubleField m_amountField;
        DateField m_dateField;
    };

} /* namespace pft */

#endif /* TRANSACTION_FORM_H */
