//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Opaque object implementation.
//==============================================================================

#include "gpu_perf_api_common/gpa_unique_object.h"

GpaUniqueObject::GpaUniqueObject()
    : interface_pointer(nullptr)
{
}

GpaUniqueObject::~GpaUniqueObject()
{
    interface_pointer = nullptr;
}

GpaObjectType GpaUniqueObject::ObjectType() const
{
    return GpaObjectType::kGpaObjectTypeUndefined;
}

IGpaInterfaceTrait* GpaUniqueObject::Interface() const
{
    return interface_pointer;
}

_GpaContextId::_GpaContextId(IGpaInterfaceTrait* gpa_context_id)
{
    interface_pointer = gpa_context_id;
}

IGpaContext* _GpaContextId::operator->() const
{
    return reinterpret_cast<IGpaContext*>(interface_pointer);
}

IGpaContext* _GpaContextId::Object() const
{
    return reinterpret_cast<IGpaContext*>(interface_pointer);
}

GpaObjectType _GpaContextId::ObjectType() const
{
    return GpaObjectType::kGpaObjectTypeContext;
}

_GpaSessionId::_GpaSessionId(IGpaInterfaceTrait* gpa_session_id)
{
    interface_pointer = gpa_session_id;
}

IGpaSession* _GpaSessionId::operator->() const
{
    return reinterpret_cast<IGpaSession*>(interface_pointer);
}

IGpaSession* _GpaSessionId::Object() const
{
    return reinterpret_cast<IGpaSession*>(interface_pointer);
}

GpaObjectType _GpaSessionId::ObjectType() const
{
    return GpaObjectType::kGpaObjectTypeSession;
}

_GpaCommandListId::_GpaCommandListId(IGpaInterfaceTrait* gpa_command_list_id)
{
    interface_pointer = gpa_command_list_id;
}

IGpaCommandList* _GpaCommandListId::operator->() const
{
    return reinterpret_cast<IGpaCommandList*>(interface_pointer);
}

IGpaCommandList* _GpaCommandListId::Object() const
{
    return reinterpret_cast<IGpaCommandList*>(interface_pointer);
}

GpaObjectType _GpaCommandListId::ObjectType() const
{
    return GpaObjectType::kGpaObjectTypeCommandList;
}

GPA_THREAD_SAFE_FUNCTION GpaUniqueObject* GpaUniqueObjectManager::CreateObject(IGpaInterfaceTrait* gpa_interface_trait)
{
    std::lock_guard<std::mutex> lock(mutex_);

    // Check if the object already exists.
    if (GpaUniqueObject* object = FindObjectNotThreadSafe(gpa_interface_trait); object != nullptr)
    {
        return object;
    }

    std::unique_ptr<GpaUniqueObject> ret_unique_object;

    switch (gpa_interface_trait->ObjectType())
    {
    case GpaObjectType::kGpaObjectTypeContext:
        ret_unique_object = std::make_unique<_GpaContextId>(gpa_interface_trait);
        break;
    case GpaObjectType::kGpaObjectTypeSession:
        ret_unique_object = std::make_unique<_GpaSessionId>(gpa_interface_trait);
        break;
    case GpaObjectType::kGpaObjectTypeCommandList:
        ret_unique_object = std::make_unique<_GpaCommandListId>(gpa_interface_trait);
        break;
    default:
        ret_unique_object = nullptr;
    }

    return gpa_unique_object_list_.emplace_back(std::move(ret_unique_object)).get();
}

GPA_THREAD_SAFE_FUNCTION void GpaUniqueObjectManager::DeleteObject(GpaUniqueObject* unique_object)
{
    unsigned int index;

    // Lock to protect the gpa_unique_object_list_.
    std::lock_guard<std::mutex> lock(mutex_);

    if (DoesExistNotThreadSafe(unique_object, &index))
    {
        gpa_unique_object_list_.erase(gpa_unique_object_list_.begin() + index);
        unique_object = nullptr;
    }
}

GPA_THREAD_SAFE_FUNCTION void GpaUniqueObjectManager::DeleteObject(const IGpaInterfaceTrait* gpa_interface_trait)
{
    // Lock to protect the gpa_unique_object_list_.
    std::lock_guard<std::mutex> lock(mutex_);

    unsigned int index = 0;
    if (FindObjectNotThreadSafe(gpa_interface_trait, &index) != nullptr)
    {
        gpa_unique_object_list_.erase(gpa_unique_object_list_.begin() + index);
    }
}

GPA_THREAD_SAFE_FUNCTION bool GpaUniqueObjectManager::DoesExist(const IGpaInterfaceTrait* gpa_interface_trait, unsigned int* index) const
{
    // Lock to protect the gpa_unique_object_list_.
    std::lock_guard<std::mutex> lock(mutex_);

    const bool object_found = (FindObjectNotThreadSafe(gpa_interface_trait, index) != nullptr);
    return object_found;
}

GpaUniqueObject* GpaUniqueObjectManager::FindObjectNotThreadSafe(const IGpaInterfaceTrait* gpa_interface_trait, unsigned int* index) const
{
    if (!gpa_unique_object_list_.empty())
    {
        unsigned int local_index = 0u;
        for (auto const& object : gpa_unique_object_list_)
        {
            if (object->Interface() == gpa_interface_trait && object->ObjectType() == gpa_interface_trait->ObjectType())
            {
                if (index != nullptr)
                {
                    *index = local_index;
                }
                return object.get();
            }

            local_index++;
        }
    }
    return nullptr;
}

GPA_THREAD_SAFE_FUNCTION bool GpaUniqueObjectManager::DoesExist(const GpaUniqueObject* unique_object, unsigned int* index) const
{
    bool object_found = false;

    std::lock_guard<std::mutex> lock(mutex_);

    object_found = DoesExistNotThreadSafe(unique_object, index);
    return object_found;
}

bool GpaUniqueObjectManager::DoesExistNotThreadSafe(const GpaUniqueObject* unique_object, unsigned int* index) const
{
    bool         object_found = false;
    unsigned int local_index  = 0u;

    if (!gpa_unique_object_list_.empty())
    {
        for (auto const& object : gpa_unique_object_list_)
        {
            if (object.get() == unique_object)
            {
                object_found = true;
                break;
            }

            local_index++;
        }
    }

    if (object_found && nullptr != index)
    {
        *index = static_cast<unsigned int>(local_index);
    }

    return object_found;
}
