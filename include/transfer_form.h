#ifndef TRANSFER_FORM_H
#define TRANSFER_FORM_H

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

    /* Forward Declarations */
    class Transaction;

    // Implements a UI form for entering transfers between accounts
    class TransferForm : public Form {
    public:
        TransferForm();
        ~TransferForm();

        virtual void Initialize();
        virtual void Copy(Form *target);

        // Populate transactions given the data in the form fields
        void PopulateTransactions(Transaction *container, Transaction *fromSource, Transaction *toDest);

    protected:
        StringField m_nameField;
        ClassField m_parentClassField;
        ClassField m_childClassField;
        TypeField m_containerType;
        TypeField m_typeField;
        DoubleField m_amountField;
        IntField m_parentIdField;
        AccountField m_overallSourceAccount;
        CounterpartyField m_overallCounterpartyField;
        AccountField m_sourceAccount;
        AccountField m_destinationAccount;
        CounterpartyField m_intermediateAccount;
        DateField m_dateField;
    };

} /* namespace pft */

#endif /* TRANSFER_FORM_H */
