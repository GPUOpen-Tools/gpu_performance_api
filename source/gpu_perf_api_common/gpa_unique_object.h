//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Opaque object definition.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_UNIQUE_OBJECT_H_
#define GPU_PERF_API_COMMON_GPA_UNIQUE_OBJECT_H_

#include <vector>
#include <mutex>

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_context_interface.h"
#include "gpu_perf_api_common/gpa_interface_trait_interface.h"
#include "gpu_perf_api_common/gpa_session_interface.h"

/// @brief GpaUniqueObject structure.
struct GpaUniqueObject
{
    /// @brief Gets the type of the object.
    ///
    /// @return GPA object type.
    virtual GpaObjectType ObjectType() const;

    /// @brief Returns the interface pointer.
    ///
    /// @return interface object pointer.
    IGpaInterfaceTrait* Interface() const;

    /// @brief Virtual destructor.
    virtual ~GpaUniqueObject();

protected:
    /// @brief Constructor.
    GpaUniqueObject();

    IGpaInterfaceTrait* interface_pointer;  ///< GPA Interface trait pointer.
};

/// @brief Context Id struct.
struct _GpaContextId : GpaUniqueObject
{
    /// @brief Constructor.
    ///
    /// @param [in] gpa_context_id IGpaContext object pointer.
    _GpaContextId(IGpaInterfaceTrait* gpa_context_id);

    /// @brief Delete default constructor.
    _GpaContextId() = delete;

    /// @brief Overriding -> operator.
    ///
    /// @return IGpaContext object pointer.
    IGpaContext* operator->() const;

    /// @brief Returns the placeholder interface pointer.
    ///
    /// @return IGpaContext object pointer.
    IGpaContext* Object() const;

    /// @brief Returns the type of the object.
    ///
    /// @return GPA object type.
    GpaObjectType ObjectType() const override;
};

/// @brief Session Id struct.
struct _GpaSessionId : GpaUniqueObject
{
    /// @brief Constructor.
    ///
    /// @param [in] gpa_session_id IGpaSession object pointer.
    _GpaSessionId(IGpaInterfaceTrait* gpa_session_id);

    /// @brief Delete default constructor.
    _GpaSessionId() = delete;

    /// @brief Overriding -> operator.
    ///
    /// @return IGpaSession object pointer.
    IGpaSession* operator->() const;

    /// @brief Returns the placeholder interface pointer.
    ///
    /// @return IGpaSession object pointer.
    IGpaSession* Object() const;

    /// @brief Returns the type of the object.
    ///
    /// @return GPA object type.
    GpaObjectType ObjectType() const override;
};

/// @brief Command List Id struct.
struct _GpaCommandListId : GpaUniqueObject
{
    /// @brief Constructor.
    ///
    /// @param [in] gpa_command_list_id IGpaCommandList object pointer.
    _GpaCommandListId(IGpaInterfaceTrait* gpa_command_list_id);

    /// @brief Delete default constructor.
    _GpaCommandListId() = delete;

    /// @brief Overriding -> operator.
    ///
    /// @return IGpaCommandList object pointer.
    IGpaCommandList* operator->() const;

    /// @brief Returns the placeholder interface pointer.
    ///
    /// @return IGpaCommandList object pointer.
    IGpaCommandList* Object() const;

    /// @brief Returns the type of the object.
    ///
    /// @return GPA object type.
    GpaObjectType ObjectType() const override;
};

/// @brief Singleton class to maintain Unique objects.
class GpaUniqueObjectManager
{
public:
    /// @brief Destructor.
    ~GpaUniqueObjectManager();

    /// @brief Returns the static instance of the UniqueObject manager.
    ///
    /// @return The static instance of the UniqueObject manager.
    static GpaUniqueObjectManager* Instance();

    /// Add the newly created GPA Unique object.
    ///
    /// @param [in] gpa_interface_trait GPA unique object pointer.
    ///
    /// @return Unique object pointer if created successfully otherwise nullptr.
    GPA_THREAD_SAFE_FUNCTION GpaUniqueObject* CreateObject(IGpaInterfaceTrait* gpa_interface_trait);

    /// @brief Remove the newly created GPA Unique object.
    ///
    /// @param [in] unique_object GPA unique object pointer.
    GPA_THREAD_SAFE_FUNCTION void DeleteObject(GpaUniqueObject* unique_object);

    /// @brief Remove the newly created GPA Unique object.
    ///
    /// @param [in] gpa_interface_trait GPA unique object pointer.
    GPA_THREAD_SAFE_FUNCTION void DeleteObject(const IGpaInterfaceTrait* gpa_interface_trait);

    /// @brief Checks whether the interface exists or not.
    ///
    /// @param [in] gpa_interface_trait Interface trait.
    /// @param [out] index Index at which the object found otherwise 0.
    ///
    /// @return True if interface is found otherwise false.
    GPA_THREAD_SAFE_FUNCTION bool DoesExist(const IGpaInterfaceTrait* gpa_interface_trait, unsigned int* index = nullptr) const;

    /// @brief Checks whether the object exists or not.
    ///
    /// @param [in] unique_object Unique object pointer.
    /// @param [out] index Index at which the object is found.
    ///
    /// @return Index at which the object found otherwise -1.
    GPA_THREAD_SAFE_FUNCTION bool DoesExist(const GpaUniqueObject* unique_object, unsigned int* index = nullptr) const;

private:
    /// @brief Checks whether the interface exists or not.
    ///
    /// Assumes that the caller has locked mutex_.
    ///
    /// @param [in] gpa_interface_trait Interface trait.
    /// @param [out] index Index at which the object found otherwise -1.
    ///
    /// @return True if interface is found otherwise false.
    bool DoesExistNotThreadSafe(const IGpaInterfaceTrait* gpa_interface_trait, unsigned int* index = nullptr) const;

    /// @brief Checks whether the object exists or not.
    ///
    /// Assumes that the caller has locked mutex_.
    ///
    /// @param [in] unique_object Unique object pointer.
    /// @param [out] index Index at which the object is found.
    ///
    /// @return Index at which the object found otherwise -1.
    bool DoesExistNotThreadSafe(const GpaUniqueObject* unique_object, unsigned int* index = nullptr) const;

    static GpaUniqueObjectManager* kGpaUniqueObjectManger;   ///< Static instance of the GPA object manager.
    std::vector<GpaUniqueObject*>  gpa_unique_object_list_;  ///< List of unique object pointers.
    mutable std::mutex             mutex_;                   ///< Mutex for unique object manager class.
};

#endif  // GPU_PERF_API_COMMON_GPA_UNIQUE_OBJECT_H_
