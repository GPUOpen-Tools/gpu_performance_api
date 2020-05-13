//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Opaque object definition
//==============================================================================

#ifndef _GPA_UNIQUE_OBJECT_H_
#define _GPA_UNIQUE_OBJECT_H_

// std
#include <vector>
#include <mutex>

// GPA Common
#include "gpa_interface_trait_interface.h"
#include "gpa_common_defs.h"

class IGPAContext;      // forward declaration
class IGPASession;      // forward declaration
class IGPACommandList;  // forward declaration

/// GPAUniqueObject structure
struct GPAUniqueObject
{
    /// Gets the type of the object
    /// \return GPA object type
    virtual GPAObjectType ObjectType() const;

    /// Returns the interface pointer
    /// \return interface object pointer
    IGPAInterfaceTrait* Interface() const;

    /// Destructor
    virtual ~GPAUniqueObject();

protected:
    /// constructor
    GPAUniqueObject();

    IGPAInterfaceTrait* m_pInterface;  ///< GPA Interface trait pointer
};

/// Context Id struct
struct _GPA_ContextId : GPAUniqueObject
{
    /// Constructor
    /// \param[in] pContextId IGPAContext object pointer
    _GPA_ContextId(IGPAInterfaceTrait* pContextId);

    /// Delete default constructor
    _GPA_ContextId() = delete;

    /// Overriding -> operator
    /// \return IGPAContext object pointer
    IGPAContext* operator->() const;

    /// Returns the placeholder interface pointer
    /// \return IGPAContext object pointer
    IGPAContext* Object() const;

    /// Returns the type of the object
    /// \return GPA object type
    GPAObjectType ObjectType() const override;
};

/// Session Id struct
struct _GPA_SessionId : GPAUniqueObject
{
    /// Constructor
    /// \param[in] pSessionId IGPASession object pointer
    _GPA_SessionId(IGPAInterfaceTrait* pSessionId);

    /// Delete default constructor
    _GPA_SessionId() = delete;

    /// Overriding -> operator
    /// \return IGPASession object pointer
    IGPASession* operator->() const;

    /// Returns the placeholder interface pointer
    /// \return IGPASession object pointer
    IGPASession* Object() const;

    /// Returns the type of the object
    /// \return GPA object type
    GPAObjectType ObjectType() const override;
};

/// Command List Id struct
struct _GPA_CommandListId : GPAUniqueObject
{
    /// Constructor
    /// \param[in] pCommandListId IGPACommandList object pointer
    _GPA_CommandListId(IGPAInterfaceTrait* pCommandListId);

    /// Delete default constructor
    _GPA_CommandListId() = delete;

    /// Overriding -> operator
    /// \return IGPACommandList object pointer
    IGPACommandList* operator->() const;

    /// Returns the placeholder interface pointer
    /// \return IGPACommandList object pointer
    IGPACommandList* Object() const;

    /// Returns the type of the object
    /// \return GPA object type
    GPAObjectType ObjectType() const override;
};

/// Singleton class to maintain Unique objects
class GPAUniqueObjectManager
{
public:
    /// Destructor
    ~GPAUniqueObjectManager();

    /// Returns the static instance of the UniqueObject manager
    /// \return the static instance of the UniqueObject manager
    static GPAUniqueObjectManager* Instance();

    /// Add the newly creatd GPA Unique object
    /// \param[in] pInterfaceTrait GPA unique object pointer
    /// \return unique object pointer if created successfully otherwise nullptr
    GPA_THREAD_SAFE_FUNCTION GPAUniqueObject* CreateObject(IGPAInterfaceTrait* pInterfaceTrait);

    /// Remove the newly creatd GPA Unique object
    /// \param[in] pUniqueObject GPA unique object pointer
    GPA_THREAD_SAFE_FUNCTION void DeleteObject(GPAUniqueObject* pUniqueObject);

    /// Remove the newly creatd GPA Unique object
    /// \param[in] pInterfaceTrait GPA unique object pointer
    GPA_THREAD_SAFE_FUNCTION void DeleteObject(const IGPAInterfaceTrait* pInterfaceTrait);

    /// Checks whether the interface exists or not
    /// \param[in] pInterfaceTrait interface trait
    /// \param[out] pIndex index at which the object found otherwise 0
    /// \return true if interface is found otherwise false
    GPA_THREAD_SAFE_FUNCTION bool DoesExist(const IGPAInterfaceTrait* pInterfaceTrait, unsigned int* pIndex = nullptr) const;

    /// Checks whether the object exists or not
    /// \param[in] pUniqueObject unique object pointer
    /// \param[out] pIndex index at which the object is found
    /// \return index at which the object found otherwise -1
    GPA_THREAD_SAFE_FUNCTION bool DoesExist(const GPAUniqueObject* pUniqueObject, unsigned int* pIndex = nullptr) const;

private:
    /// Checks whether the interface exists or not
    /// Assumes that the caller has locked m_mutex.
    /// \param[in] pInterfaceTrait interface trait
    /// \param[out] pIndex index at which the object found otherwise -1
    /// \return true if interface is found otherwise false
    bool DoesExist_NotThreadSafe(const IGPAInterfaceTrait* pInterfaceTrait, unsigned int* pIndex = nullptr) const;

    /// Checks whether the object exists or not
    /// Assumes that the caller has locked m_mutex.
    /// \param[in] pUniqueObject unique object pointer
    /// \param[out] pIndex index at which the object is found
    /// \return index at which the object found otherwise -1
    bool DoesExist_NotThreadSafe(const GPAUniqueObject* pUniqueObject, unsigned int* pIndex = nullptr) const;

    static GPAUniqueObjectManager* ms_pGpaUniqueObjectManger;  ///< static instance of the GPA object manager
    std::vector<GPAUniqueObject*>  m_gpaUniqueObjectList;      ///< List of unique object pointers
    mutable std::mutex             m_mutex;                    ///< Mutex for unique object manager class
};

#endif  // _GPA_UNIQUE_OBJECT_H_
