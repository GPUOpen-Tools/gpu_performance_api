//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  A circular buffer that can store objects of a templated type.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_CIRCULAR_BUFFER_H_
#define GPU_PERF_API_COMMON_CIRCULAR_BUFFER_H_

#include <assert.h>
#ifdef _LINUX
#include <cstddef>
#endif

/// @brief A circular buffer that can store objects of a templated type.
template <class T>
class CircularBuffer
{
public:
    /// @brief Initializes a new instance of the CircularBuffer<T> class.
    CircularBuffer()
    {
        array_ = nullptr;
        Initialize();
    }

    /// @brief Deletes the underlying array.
    ~CircularBuffer()
    {
        delete[] array_;
    }

    /// @brief Constructor which initializes its members from another circular buffer.
    ///
    /// @param [in] obj The circular buffer to copy.
    CircularBuffer(const CircularBuffer<T>& obj)
    {
        if (obj.GetSize() == 0)
        {
            array_ = nullptr;
        }
        else
        {
            array_ = new (std::nothrow) T[obj.GetSize()];

            if (nullptr != array_)
            {
                for (int i = 0; i < static_cast<int>(obj.GetSize()); i++)
                {
                    array_[i] = obj.get(i);
                }
            }
        }

        head_index_ = obj.GetHeadIndex();
        tail_index_ = obj.GetTailIndex();
        size_       = obj.GetSize();   // Maximum number of elements in the buffer at any one time.
        count_      = obj.GetCount();  // Current number of elements in the buffer.
    }

    /// @brief Equal operator.
    ///
    /// @param [in] obj The source circular buffer.
    ///
    /// @return This object is updated based on the values of the source buffer.
    CircularBuffer<T>& operator=(const CircularBuffer<T>& obj)
    {
        // Assignment means data copy of array.
        delete[] array_;
        array_ = new (std::nothrow) T[obj.GetSize()];

        if (nullptr != array_)
        {
            for (int i = 0; i < static_cast<int>(obj.GetSize()); i++)
            {
                array_[i] = obj.get(i);
            }
        }

        return (*this);
    }

    /// @brief Clears the circular buffer.
    void Clear()
    {
        delete[] array_;
        array_ = nullptr;
        Initialize();
    }

    /// @brief Initializes the buffer.
    void Initialize()
    {
        head_index_ = 0;
        tail_index_ = 0;
        size_       = 0;
        count_      = 0;
    }

    /// @brief Sets the size of the circular buffer.
    ///
    /// Needs to be called before using the buffer.
    ///
    /// @param [in] size The number of objects this circular buffer should be capable of holding.
    ///
    /// @return True if the size could be set, false otherwise.
    bool SetSize(unsigned int size)
    {
        bool ret_val = false;
        Initialize();
        delete[] array_;

        array_ = new (std::nothrow) T[size];

        if (nullptr != array_)
        {
            ret_val = true;
            size_   = size;
        }

        return ret_val;
    }

    /// @brief Indicates whether or not this buffer has been Initialized.
    ///
    /// @return True if the buffer was Initialized; false otherwise.
    inline bool Initialized() const
    {
        if (nullptr != array_)
        {
            return true;
        }

        return false;
    }

    /// @brief Allows direct access to next item ( avoids copying ).
    ///
    /// AddLockedItem should be called once it's filled in.
    ///
    /// @param [out] success Flag indicating if function is successfully returning the next item.
    ///
    /// @return The next item.
    T& LockNext(bool& success)
    {
        success = true;

        assert(Initialized());

        if (Full())
        {
            // Full, so remove one.
            success = Erase();
        }

        return array_[tail_index_];
    }

    /// @brief Add a new item to the front (tail) of the buffer.
    ///
    /// @return True if the item can be added; false if the buffer has no size.
    bool AddLockedItem()
    {
        // Add to tail then increment.
        if (size_ == 0)
        {
            return false;
        }

        CircularIncrement(tail_index_);
        count_++;
        return true;
    }

    /// @brief Gets the number of items in the circular buffer.
    ///
    /// @return The number of items currently in the buffer.
    unsigned int GetCount() const
    {
        return count_;
    }

    /// @brief Gets the size of the circular buffer.
    ///
    /// @return The maximum number of items this circular buffer can hold.
    unsigned int GetSize() const
    {
        return size_;
    }

    /// @brief Indicates whether or not the buffer is full.
    ///
    /// @return True if the buffer is full; false if it is not.
    bool Full() const
    {
        if (count_ == size_ && size_ != 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// @brief Indicates whether or not the circular buffer is empty.
    ///
    /// @return True if the buffer is empty; false if it has at least one element in it.
    bool Empty() const
    {
        if (count_ == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /// @brief Adds an item to the tail of the circular buffer.
    ///
    /// If the buffer is full, the item at the head will be removed,
    /// then the item will be added to the tail.
    ///
    /// @param [in] item The object to add to the circular buffer.
    ///
    /// @return True if the item could be added; false if the buffer is not Initialized.
    bool Add(T& item)
    {
        // Add to tail then increment.
        if (!Initialized())
        {
            return false;
        }

        if (Full())
        {
            // Need to remove from head first.
            Erase();
        }

        array_[tail_index_] = item;
        CircularIncrement(tail_index_);
        count_++;
        return true;
    }

    /// @brief Gets a reference to the item at the head of the buffer.
    ///
    /// The item is not removed.
    ///
    /// @return A reference to the item at the head of the buffer.
    T& GetHead()
    {
        assert(Initialized());

        return array_[head_index_];
    }

    /// @brief Removes the item from the head of the buffer and passes back a reference to the item.
    ///
    /// @param [out] item A reference to the item at the head of the buffer.
    ///
    /// @return True if an item could be returned; false if the buffer is empty.
    bool Remove(T& item)
    {
        assert(Initialized());

        if (Empty())
        {
            // Buffer empty.
            return false;
        }

        // Return head item.
        item = array_[head_index_];
        CircularIncrement(head_index_);
        count_--;

        return true;
    }

    /// @brief Removes the item from the head of the buffer.
    ///
    /// @return True if an item was removed from the head of the buffer; false if the buffer was empty.
    bool Erase()
    {
        assert(Initialized());

        if (Empty())
        {
            // Buffer empty.
            return false;
        }

        // Increment head, decrement count.
        CircularIncrement(head_index_);
        count_--;

        return true;
    }

    /// @brief Gets the item at a specified index of the buffer.
    ///
    /// @param [in] index An index into the buffer. Must be smaller than the buffer's size.
    ///
    /// @return The item at the specified index of the buffer.
    T& Get(unsigned int index) const
    {
        assert(index < size_);
        return array_[index];
    }

    /// @brief Gets the most recently added item from the buffer.
    ///
    /// @return A reference to the item most recently added to the buffer.
    T& GetLastAdded()
    {
        unsigned int index_of_last_added = tail_index_;
        CircularDecrement(index_of_last_added);
        return array_[index_of_last_added];
    }

    /// @brief Gets the item at an index in the circular buffer, relative to the head index.
    ///
    /// Zero is the oldest element in the array, up to count-1.
    ///
    /// @param [in] index The index of the item to get.
    ///
    /// @return A reference to the item at head + index in the buffer.
    T& GetRelative(unsigned int index)
    {
        unsigned int adjusted_index = ((index % size_) + head_index_) % size_;
        return array_[adjusted_index];
    }

    /// @brief Calculates an adjusted index relative to the head index.
    ///
    /// Zero is the oldest element in the array, up to count-1.
    ///
    /// @param [in] index The offset from the head index that needs to be adjusted.
    ///
    /// @return An adjusted index based on the head index and size of the buffer.
    unsigned int GetRelativeIndex(unsigned int index)
    {
        unsigned int adjusted_index = ((index % size_) + head_index_) % size_;
        return adjusted_index;
    }

    /// @brief Increments an index, ensuring that it stays within the size of the circular buffer.
    ///
    /// @param [in] index The index to increment.
    void CircularIncrement(unsigned int& index)
    {
        index++;

        if (index == size_)
        {
            index = 0;
        }
    }

    /// @brief Decrements an index, ensuring that it stays within the size of the circular buffer.
    ///
    /// @param [in] index The index to decrement.
    void CircularDecrement(unsigned int& index)
    {
        if (index == 0)
        {
            index = size_ - 1;
        }
        else
        {
            index--;
        }
    }

protected:
    /// @brief Gets the head index of the circular buffer.
    ///
    /// @return The index of the head of the buffer.
    unsigned int GetHeadIndex() const
    {
        return head_index_;
    }

    /// @brief Gets the tail index of the circular buffer.
    ///
    /// @return The index of the tail of the buffer.
    unsigned int GetTailIndex() const
    {
        return tail_index_;
    }

    T*           array_;       ///< Underlying array of this circular buffer.
    unsigned int head_index_;  ///< Index of the head.
    unsigned int tail_index_;  ///< Index of the tail (insertion index).
    unsigned int size_;        ///< Maximum number of elements in the buffer at any one time.
    unsigned int count_;       ///< Current number of elements in the buffer.
};

#endif  // GPU_PERF_API_COMMON_CIRCULAR_BUFFER_H_
