/**
 * @file HistoryStack.h
 *
 * ICP project (Class and sequence diagram editor)
 *
 * @author Michal Šmahel (xsmahe01)
 */
#ifndef ICP_PROJECT_HISTORY_STACK_H
#define ICP_PROJECT_HISTORY_STACK_H

#include <cstdint>
#include <deque>
#include <vector>

/**
 * Stack-like structure for storing history records with option to revert pop items
 *
 * @warning As record only classes with non-parametric constructor could be used
 */
template<class T> class HistoryStack
{
    /**
     * Stored history of records
     */
    std::deque<T> records;
    /**
     * Backup of returned records (when reverting from history)
     */
    std::vector<T> returnedRecords;

  public:
    /**
     * Maximum number of stored records (remembered changes)
     */
    const int8_t HISTORY_CAPACITY = 100;

    /**
     * Implicit constructor
     */
    HistoryStack(): records{}, returnedRecords{} {};

    /**
     * Add a record to history "stack"
     *
     * @par When top isn't at newest record, newer records is deleted:
     * <pre>
     * Current state:                New state:
     * | 4th record |                | ---------- |
     * | 3rd record |                | new record | <-- top
     * | 2nd record | <-- top        | 2nd record |
     * | 1st record |                | 1st record |
     * </pre>
     *
     * @par When capacity is exceeded, oldest record is deleted (in example capacity is 4):
     * <pre>
     * Current state:                New state:
     * | 4th record | <-- top        | new record | <-- top
     * | 3rd record |                | 4th record |
     * | 2nd record |                | 3rd record |
     * | 1st record |                | 2nd record |
     * </pre>
     *
     * @param record A new record to add
     */
    void addRecord(T record)
    {
        // Clear (newer) returned records, when not adding to top
        if (!returnedRecords.empty()) {
            returnedRecords.clear();
        }

        // Remove the oldest record when capacity is exceeded
        if (static_cast<uint8_t>(records.size()) >= HISTORY_CAPACITY) {
            records.pop_front();
        }

        records.push_back(record);
    }

    /**
     * Goes back to history and returns a record
     *
     * @par Stack remembers returned record but moves its top:
     * <pre>
     * Current state:                New state:
     * | ---------- |                | ---------- |
     * | 3rd record | <-- top        | 3rd record |
     * | 2nd record |                | 2nd record | <-- top
     * | 1st record |                | 1st record |
     * </pre>
     *
     * @return Stored history record if history isn't empty or new instance of record
     * created with non-parametric constructor, when history is empty
     */
    T back()
    {
        // There is at least one item in history
        if (!records.empty()) {
            T record{records.back()};
            records.pop_back();

            // Add to returned records
            returnedRecords.push_back(record);

            if (!records.empty()) {
                return records.back();
            }

            // There were only 1 item in history --> similar to no items at all
        }

        // There are no items in history
        return T{};
    }

    /**
     * Reverts and returns newer record (goes forward in history)
     *
     * @par Stack uses remembered record and reverts it:
     * <pre>
     * Current state:                New state:
     * | 4th record |                | 4th record |
     * | 3rd record |                | 3rd record | <-- top
     * | 2nd record | <-- top        | 2nd record |
     * | 1st record |                | 1st record |
     * </pre>
     *
     * @return Stored record if there is some newer record than active one
     * or active record, when there is no newer record
     */
    T forward()
    {
        // There is at least 1 item in returned items history
        if (!returnedRecords.empty()) {
            T record{returnedRecords.back()};
            returnedRecords.pop_back();

            // Add back to history
            records.push_back(record);

            return record;
        }

        // There are no items in returned items history
        if (!records.empty()) {
            return records.back();
        } else {
            return T{};
        }
    }

    /**
     * Copy assignment operator
     *
     * @param other Object to copy from
     * @return New copy of object other
     */
    HistoryStack &operator=(HistoryStack &&other) noexcept
    {
        records = std::move(other.records);
        returnedRecords = std::move(other.returnedRecords);

        return *this;
    }
};

#endif //ICP_PROJECT_HISTORY_STACK_H
