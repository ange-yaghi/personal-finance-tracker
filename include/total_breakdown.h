#ifndef PFT_TOTAL_BREAKDOWN_H
#define PFT_TOTAL_BREAKDOWN_H

namespace pft {

    class TotalBreakdown {
    public:
        TotalBreakdown();
        ~TotalBreakdown();

        void InitializeChildren(int count) { m_children = new TotalBreakdown[count]; m_childCount = count; }
        int GetChildCount() const { return m_childCount; }

        void InitializeAmounts(int count) { m_amounts = new int[count]; m_budgets = new int[count];  m_typeCount = count; }
        int GetTypeCount() const { return m_typeCount; }

        TotalBreakdown *GetChild(int index) { return &m_children[index]; }

        void SetClass(int tClass) { m_class = tClass; }
        int GetClass() const { return m_class; }

        void SetAmount(int amount, int index) { m_amounts[index] = amount; }
        int GetAmount(int index) const { return m_amounts[index]; }

        void SetBudget(int amount, int index) { m_budgets[index] = amount; }
        int GetBudget(int index) const { return m_budgets[index]; }

    protected:
        TotalBreakdown *m_children;
        int m_childCount;
        int m_typeCount;

        int *m_amounts;
        int *m_budgets;
        int m_class;
    };

} /* namespace pft */

#endif /* PFT_TOTAL_BREAKDOWN_H */
