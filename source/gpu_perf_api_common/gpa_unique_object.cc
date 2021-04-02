//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Opaque object implementation.
//==============================================================================

#include "gpu_perf_api_common/gpa_unique_object.h"

GpaUniqueObjectManager* GpaUniqueObjectManager::kGpaUniqueObjectManger = nullptr;

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

GpaUniqueObjectManager* GpaUniqueObjectManager::Instance()
{
    if (nullptr == kGpaUniqueObjectManger)
    {
        kGpaUniqueObjectManger = new (std::nothrow) GpaUniqueObjectManager();
    }

    return kGpaUniqueObjectManger;
}

GPA_THREAD_SAFE_FUNCTION GpaUniqueObject* GpaUniqueObjectManager::CreateObject(IGpaInterfaceTrait* gpa_interface_trait)
{
    GpaUniqueObject* ret_unique_object = nullptr;

    std::lock_guard<std::mutex> lock(mutex_);

    if (!DoesExistNotThreadSafe(gpa_interface_trait))
    {
        switch (gpa_interface_trait->ObjectType())
        {
        case GpaObjectType::kGpaObjectTypeContext:
            ret_unique_object = new (std::nothrow) _GpaContextId(gpa_interface_trait);
            break;

        case GpaObjectType::kGpaObjectTypeSession:
            ret_unique_object = new (std::nothrow) _GpaSessionId(gpa_interface_trait);
            break;

        case GpaObjectType::kGpaObjectTypeCommandList:
            ret_unique_object = new (std::nothrow) _GpaCommandListId(gpa_interface_trait);
            break;

        default:
            ret_unique_object = nullptr;
        }

        if (nullptr != ret_unique_object)
        {
            gpa_unique_object_list_.push_back(ret_unique_object);
        }
    }

    return ret_unique_object;
}

GPA_THREAD_SAFE_FUNCTION void GpaUniqueObjectManager::DeleteObject(GpaUniqueObject* unique_object)
{
    unsigned int index;

    // Lock to protect the gpa_unique_object_list_.
    std::lock_guard<std::mutex> lock(mutex_);

    if (DoesExistNotThreadSafe(unique_object, &index))
    {
        delete unique_object;
        gpa_unique_object_list_.erase(gpa_unique_object_list_.begin() + index);
        unique_object = nullptr;
    }
}

GPA_THREAD_SAFE_FUNCTION void GpaUniqueObjectManager::DeleteObject(const IGpaInterfaceTrait* gpa_interface_trait)
{
    unsigned int index;

    // Lock to protect the gpa_unique_object_list_.
    std::lock_guard<std::mutex> lock(mutex_);

    if (DoesExistNotThreadSafe(gpa_interface_trait, &index))
    {
        GpaUniqueObject* temp = *(gpa_unique_object_list_.begin() + index);
        delete temp;
        gpa_unique_object_list_.erase(gpa_unique_object_list_.begin() + index);
    }
}

GPA_THREAD_SAFE_FUNCTION bool GpaUniqueObjectManager::DoesExist(const IGpaInterfaceTrait* gpa_interface_trait, unsigned int* index) const
{
    bool object_found = false;

    // Lock to protect the gpa_unique_object_list_.
    std::lock_guard<std::mutex> lock(mutex_);

    object_found = DoesExistNotThreadSafe(gpa_interface_trait, index);

    return object_found;
}

bool GpaUniqueObjectManager::DoesExistNotThreadSafe(const IGpaInterfaceTrait* gpa_interface_trait, unsigned int* index) const
{
    bool         object_found = false;
    unsigned int local_index  = 0u;

    if (!gpa_unique_object_list_.empty())
    {
        for (std::vector<GpaUniqueObject*>::const_iterator it = gpa_unique_object_list_.cbegin(); it != gpa_unique_object_list_.cend(); ++it)
        {
            if ((*it)->Interface() == gpa_interface_trait && (*it)->ObjectType() == gpa_interface_trait->ObjectType())
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
        for (std::vector<GpaUniqueObject*>::const_iterator it = gpa_unique_object_list_.begin(); it != gpa_unique_object_list_.end() && !object_found; ++it)
        {
            if (*it == unique_object)
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

GpaUniqueObjectManager::~GpaUniqueObjectManager()
{
    delete kGpaUniqueObjectManger;
}
