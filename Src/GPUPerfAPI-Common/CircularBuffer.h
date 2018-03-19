//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A circular buffer that can store objects of a templated type.
//==============================================================================

#ifndef _GPA_CIRCULAR_BUFFER_H_
#define _GPA_CIRCULAR_BUFFER_H_

#include <assert.h>
#ifdef _LINUX
    #include <cstddef>
#endif

/// A circular buffer that can store objects of a templated type.
template<class T> class CircularBuffer
{
public:

    /// Initializes a new instance of the CircularBuffer<T> class
    CircularBuffer()
    {
        m_pArray = nullptr;
        initialize();
    }

    /// Deletes the underlying array
    ~CircularBuffer()
    {
        delete[] m_pArray;
    }

    /// Constructor which initializes its members from another circulat buffer.
    /// \param obj The circular buffer to copy
    CircularBuffer(const CircularBuffer<T>& obj)
    {
        if (obj.getSize() == 0)
        {
            m_pArray = nullptr;
        }
        else
        {
            m_pArray = new(std::nothrow) T[obj.getSize()];

            if (nullptr != m_pArray)
            {
                for (int i = 0; i < static_cast<int>(obj.getSize()); i++)
                {
                    m_pArray[i] = obj.get(i);
                }
            }
        }

        m_headIndex = obj.getHeadIndex();
        m_tailIndex = obj.getTailIndex();
        m_size = obj.getSize();         // maximum number of elements in the buffer at any one time
        m_count = obj.getCount();       // current number of elements in the buffer
    }

    /// Equal operator
    /// \param obj The source circular buffer
    /// \return this object is updated based on the values of the source buffer
    CircularBuffer<T>& operator = (const CircularBuffer<T>& obj)
    {
        // assignment means data copy of array
        delete[] m_pArray;
        m_pArray = new(std::nothrow) T[obj.getSize()];

        if (nullptr != m_pArray)
        {
            for (int i = 0; i < static_cast<int>(obj.getSize()); i++)
            {
                m_pArray[i] = obj.get(i);
            }
        }

        return (*this);
    }

    /// Clears the circular buffer
    void clear()
    {
        delete[] m_pArray;
        m_pArray = nullptr;
        initialize();
    }

    /// initializes the buffer
    void initialize()
    {
        m_headIndex = 0;
        m_tailIndex = 0;
        m_size = 0;
        m_count = 0;
    }

    /// Sets the size of the circular buffer.
    /// Needs to be called before using the buffer.
    /// \param size the number of objects this circular buffer should be capable of holding.
    /// \return true if the size could be set, false otherwise
    bool setSize(unsigned int size)
    {
        bool retVal = false;
        initialize();
        delete[] m_pArray;

        m_pArray = new(std::nothrow) T[size];

        if (nullptr != m_pArray)
        {
            retVal = true;
            m_size = size;
        }

        return retVal;
    }

    /// Indicates whether or not this buffer has been initialized
    /// \return True if the buffer was initialized; false otherwise.
    inline bool initialized() const
    {
        if (nullptr != m_pArray)
        {
            return true;
        }

        return false;
    }

    /// allows direct access to next item ( avoids copying )
    /// addLockedItem should be called once it's filled in
    /// \param[out] success flag indicating if function is sucessfully returning the next item
    /// \return the next item
    T& lockNext(bool& success)
    {
        success = true;

        assert(initialized());

        if (full())
        {
            // full so remove one
            success = erase();
        }

        return m_pArray[m_tailIndex];
    }

    /// Add a new item to the front (tail) of the buffer.
    /// \return True if the item can be added; false if the buffer has no size.
    bool addLockedItem()
    {
        // add to tail then increment
        if (m_size == 0)
        {
            return false;
        }

        circularIncrement(m_tailIndex);
        m_count++;
        return true;
    }

    /// Gets the number of items in the circular buffer.
    /// \return the number of items currently in the buffer.
    unsigned int getCount() const
    {
        return m_count;
    }

    /// Gets the size of the circular buffer.
    /// \return the maximum number of items this circular buffer can hold.
    unsigned int getSize() const
    {
        return m_size;
    }

    /// Indicates whether or not the buffer is full.
    /// \return True if the buffer is full; false if it is not.
    bool full() const
    {
        if (m_count == m_size && m_size != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// Indicates whether or not the circular buffer is empty.
    /// \return True if the buffer is empty; false if it has at least one element in it.
    bool empty() const
    {
        if (m_count == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// Adds an item to the tail of the circular buffer.
    /// If the buffer is full, the item at the head will be removed,
    /// then the item will be added to the tail.
    /// \param item The object to add to the circular buffer.
    /// \return True if the item could be added; false if the buffer is not initialized.
    bool add(T& item)
    {
        // add to tail then increment
        if (!initialized())
        {
            return false;
        }

        if (full())
        {
            // need to remove from head first
            erase();
        }

        m_pArray[m_tailIndex] = item;
        circularIncrement(m_tailIndex);
        m_count++;
    }

    /// Gets a reference to the item at the head of the buffer.
    /// The item is not removed.
    /// \return a reference to the item at the head of the buffer.
    T& getHead()
    {
        assert(initialized());

        return m_pArray[m_headIndex];
    }

    /// Removes the item from the head of the buffer and passes back a reference to the item.
    /// \param item [out] A reference to the item at the head of the buffer.
    /// \return True if an item could be returned; false if the buffer is empty.
    bool remove(T& item)
    {
        assert(initialized());

        if (empty())
        {
            // buffer empty
            return false;
        }

        // return head item
        item = m_pArray[m_headIndex];
        circularIncrement(m_headIndex);
        m_count--;

        return true;
    }

    /// Removes the item from the head of the buffer.
    /// \return True if an item was removed from the head of the buffer; false if the buffer was empty.
    bool erase()
    {
        assert(initialized());

        if (empty())
        {
            // buffer empty
            return false;
        }

        // inc head, dec count
        circularIncrement(m_headIndex);
        m_count--;

        return true;
    }

    /// Gets the item at a specified index of the buffer.
    /// \param index An index into the buffer. Must be smaller than the buffer's size.
    /// \return The item at the specified index of the buffer.
    T& get(unsigned int index) const
    {
        assert(index < m_size);
        return m_pArray[index];
    }

    /// Gets the most recently added item from the buffer.
    /// \return A reference to the item most recently added to the buffer.
    T& getLastAdded()
    {
        unsigned int indexOfLastAdded = m_tailIndex;
        circularDecrement(indexOfLastAdded);
        return m_pArray[indexOfLastAdded];
    }

    /// Gets the item at an index in the circular buffer, relative to the head index.
    /// zero is the oldest element in the array, up to count-1
    /// \param index the index of the item to get.
    /// \return A reference to the item at head + index in the buffer.
    T& getRelative(unsigned int index)
    {
        unsigned int adjustedIndex = ((index % m_size) + m_headIndex) % m_size;
        return m_pArray[adjustedIndex];
    }

    /// Calculates an adjusted index relative to the head index.
    /// zero is the oldest element in the array, up to count-1
    /// \param index The offset from the head index that needs to be adjusted.
    /// \return An adjusted index based on the head index and size of the buffer.
    unsigned int getRelativeIndex(unsigned int index)
    {
        unsigned int adjustedIndex = ((index % m_size) + m_headIndex) % m_size;
        return adjustedIndex;
    }

    /// Increments an index, ensuring that it stays within the size of the circular buffer.
    /// \param index The index to increment
    void circularIncrement(unsigned int& index)
    {
        index++;

        if (index == m_size)
        {
            index = 0;
        }
    }

    /// Decrements an index, ensuring that it stays within the size of the circular buffer.
    /// \param index The index to decrement
    void circularDecrement(unsigned int& index)
    {
        if (index == 0)
        {
            index = m_size - 1;
        }
        else
        {
            index--;
        }
    }

protected:

    /// Gets the head index of the circular buffer
    /// \return the index of the head of the buffer.
    unsigned int getHeadIndex() const
    {
        return m_headIndex;
    }

    /// Gets the tail index of the circular buffer
    /// \return the index of the tail of the buffer.
    unsigned int getTailIndex() const
    {
        return m_tailIndex;
    }

    T* m_pArray;               ///< underlying array of this circular buffer
    unsigned int m_headIndex;  ///< index of the head
    unsigned int m_tailIndex;  ///< index of the tail (insertion index)
    unsigned int m_size;       ///< maximum number of elements in the buffer at any one time
    unsigned int m_count;      ///< current number of elements in the buffer
};

#endif //_GPA_CIRCULAR_BUFFER_H_
