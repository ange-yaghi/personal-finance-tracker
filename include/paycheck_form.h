#ifndef PAYCHECK_FORM_H
#define PAYCHECK_FORM_H

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

    // Implements a UI form for entering paychecks
    class PaycheckForm : public Form {
    public:
        PaycheckForm();
        ~PaycheckForm();

        virtual void Initialize();
        virtual void Copy(Form *target);

        // Populate a transaction given the values inputted by the user
        void PopulateTransactions(Transaction *container, Transaction *basePay, Transaction *cit, Transaction *cpp, Transaction *ei,
            Transaction *directDeposit, Transaction *directDepositReciprocal,
            Transaction *postTaxDeductions, Transaction *preTaxAllocations);

    protected:
        StringField m_nameField;
        ClassField m_parentClassField;
        ClassField m_basePayClass;
        ClassField m_citClass;
        ClassField m_cppClass;
        ClassField m_eiClass;
        ClassField m_afterTaxDeductionsClass;
        ClassField m_directDepositClass;
        ClassField m_preTaxAllocationsClass;
        TypeField m_containerType;
        TypeField m_typeField;
        DoubleField m_amountField;
        DoubleField m_basePayAmount;
        DoubleField m_citAmount;
        DoubleField m_cppAmount;
        DoubleField m_eiAmount;
        DoubleField m_afterTaxDeductionsAmount;
        DoubleField m_preTaxAllocationsAmount;
        IntField m_parentIdField;
        CounterpartyField m_intermediateCounterparty;
        AccountField m_intermediateAccount;
        AccountField m_destinationAccount;
        CounterpartyField m_taxCounterparty;
        CounterpartyField m_employer;
        DateField m_dateField;
    };

} /* namespace pft */

#endif /* TRANSFER_FORM_H */
