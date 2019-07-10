//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Opaque object implementation
//==============================================================================

#include "GPAUniqueObject.h"

// static initialization
GPAUniqueObjectManager* GPAUniqueObjectManager::ms_pGpaUniqueObjectManger = nullptr;

GPAUniqueObject::GPAUniqueObject()
    : m_pInterface(nullptr)
{
}

GPAUniqueObject::~GPAUniqueObject()
{
    m_pInterface = nullptr;
}

GPAObjectType GPAUniqueObject::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_UNDEFINED;
}

IGPAInterfaceTrait* GPAUniqueObject::Interface() const
{
    return m_pInterface;
}

_GPA_ContextId::_GPA_ContextId(IGPAInterfaceTrait* pContextId)
{
    m_pInterface = pContextId;
}

IGPAContext* _GPA_ContextId::operator->() const
{
    return reinterpret_cast<IGPAContext*>(m_pInterface);
}

IGPAContext* _GPA_ContextId::Object() const
{
    return reinterpret_cast<IGPAContext*>(m_pInterface);
}

GPAObjectType _GPA_ContextId::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_CONTEXT;
}

_GPA_SessionId::_GPA_SessionId(IGPAInterfaceTrait* pSessionId)
{
    m_pInterface = pSessionId;
}

IGPASession* _GPA_SessionId::operator->() const
{
    return reinterpret_cast<IGPASession*>(m_pInterface);
}

IGPASession* _GPA_SessionId::Object() const
{
    return reinterpret_cast<IGPASession*>(m_pInterface);
}

GPAObjectType _GPA_SessionId::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_SESSION;
}

_GPA_CommandListId::_GPA_CommandListId(IGPAInterfaceTrait* pCommandListId)
{
    m_pInterface = pCommandListId;
}

IGPACommandList* _GPA_CommandListId::operator->() const
{
    return reinterpret_cast<IGPACommandList*>(m_pInterface);
}

IGPACommandList* _GPA_CommandListId::Object() const
{
    return reinterpret_cast<IGPACommandList*>(m_pInterface);
}

GPAObjectType _GPA_CommandListId::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST;
}

GPAUniqueObjectManager* GPAUniqueObjectManager::Instance()
{
    if (nullptr == ms_pGpaUniqueObjectManger)
    {
        ms_pGpaUniqueObjectManger = new (std::nothrow) GPAUniqueObjectManager();
    }

    return ms_pGpaUniqueObjectManger;
}

GPA_THREAD_SAFE_FUNCTION GPAUniqueObject* GPAUniqueObjectManager::CreateObject(IGPAInterfaceTrait* pInterfaceTrait)
{
    GPAUniqueObject* pRetUniqueObject = nullptr;

    std::lock_guard<std::mutex> lock(m_mutex);

    if (!DoesExist_NotThreadSafe(pInterfaceTrait))
    {
        switch (pInterfaceTrait->ObjectType())
        {
        case GPAObjectType::GPA_OBJECT_TYPE_CONTEXT:
            pRetUniqueObject = new (std::nothrow) _GPA_ContextId(pInterfaceTrait);
            break;

        case GPAObjectType::GPA_OBJECT_TYPE_SESSION:
            pRetUniqueObject = new (std::nothrow) _GPA_SessionId(pInterfaceTrait);
            break;

        case GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST:
            pRetUniqueObject = new (std::nothrow) _GPA_CommandListId(pInterfaceTrait);
            break;

        default:
            pRetUniqueObject = nullptr;
        }

        if (nullptr != pRetUniqueObject)
        {
            m_gpaUniqueObjectList.push_back(pRetUniqueObject);
        }
    }

    return pRetUniqueObject;
}

GPA_THREAD_SAFE_FUNCTION void GPAUniqueObjectManager::DeleteObject(GPAUniqueObject* pUniqueObject)
{
    unsigned int index;

    // lock to protect the m_gpaUniqueObjectList
    std::lock_guard<std::mutex> lock(m_mutex);

    if (DoesExist_NotThreadSafe(pUniqueObject, &index))
    {
        delete pUniqueObject;
        m_gpaUniqueObjectList.erase(m_gpaUniqueObjectList.begin() + index);
        pUniqueObject = nullptr;
    }
}

GPA_THREAD_SAFE_FUNCTION void GPAUniqueObjectManager::DeleteObject(const IGPAInterfaceTrait* pInterfaceTrait)
{
    unsigned int index;

    // lock to protect the m_gpaUniqueObjectList
    std::lock_guard<std::mutex> lock(m_mutex);

    if (DoesExist_NotThreadSafe(pInterfaceTrait, &index))
    {
        GPAUniqueObject* pTemp = *(m_gpaUniqueObjectList.begin() + index);
        delete pTemp;
        m_gpaUniqueObjectList.erase(m_gpaUniqueObjectList.begin() + index);
    }
}

GPA_THREAD_SAFE_FUNCTION bool GPAUniqueObjectManager::DoesExist(const IGPAInterfaceTrait* pInterfaceTrait, unsigned int* pIndex) const
{
    bool objectFound = false;

    // lock to protect the m_gpaUniqueObjectList
    std::lock_guard<std::mutex> lock(m_mutex);

    objectFound = DoesExist_NotThreadSafe(pInterfaceTrait, pIndex);

    return objectFound;
}

bool GPAUniqueObjectManager::DoesExist_NotThreadSafe(const IGPAInterfaceTrait* pInterfaceTrait, unsigned int* pIndex) const
{
    bool         objectFound = false;
    unsigned int localIndex  = 0u;

    if (!m_gpaUniqueObjectList.empty())
    {
        for (std::vector<GPAUniqueObject*>::const_iterator it = m_gpaUniqueObjectList.cbegin(); it != m_gpaUniqueObjectList.cend(); ++it)
        {
            if ((*it)->Interface() == pInterfaceTrait && (*it)->ObjectType() == pInterfaceTrait->ObjectType())
            {
                objectFound = true;
                break;
            }

            localIndex++;
        }
    }

    if (objectFound && nullptr != pIndex)
    {
        *pIndex = static_cast<unsigned int>(localIndex);
    }

    return objectFound;
}

GPA_THREAD_SAFE_FUNCTION bool GPAUniqueObjectManager::DoesExist(const GPAUniqueObject* pUniqueObject, unsigned int* pIndex) const
{
    bool objectFound = false;

    std::lock_guard<std::mutex> lock(m_mutex);

    objectFound = DoesExist_NotThreadSafe(pUniqueObject, pIndex);
    return objectFound;
}

bool GPAUniqueObjectManager::DoesExist_NotThreadSafe(const GPAUniqueObject* pUniqueObject, unsigned int* pIndex) const
{
    bool         objectFound = false;
    unsigned int localIndex  = 0u;

    if (!m_gpaUniqueObjectList.empty())
    {
        for (std::vector<GPAUniqueObject*>::const_iterator it = m_gpaUniqueObjectList.begin(); it != m_gpaUniqueObjectList.end() && !objectFound; ++it)
        {
            if (*it == pUniqueObject)
            {
                objectFound = true;
                break;
            }

            localIndex++;
        }
    }

    if (objectFound && nullptr != pIndex)
    {
        *pIndex = static_cast<unsigned int>(localIndex);
    }

    return objectFound;
}

GPAUniqueObjectManager::~GPAUniqueObjectManager()
{
    delete ms_pGpaUniqueObjectManger;
}
