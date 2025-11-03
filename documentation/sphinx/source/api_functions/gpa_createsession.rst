GpaCreateSession
@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GpaStatus GpaCreateSession(
        GpaContextId context_id,
        GpaSessionSampleType sample_type,
        GpaSessionId* session_id);

Description
%%%%%%%%%%%

Creates a session on the specified context. A unique session identifier will be
returned which allows counters to be enabled, samples to be measured, and
stores the results of the profile. The sample type for the session should be
specified by the caller. The requested sample types must be supported by the
supplied context. Use GpaGetSupportedSampleTypes to determine which sample
types are supported by a context.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``context_id``", "Unique identifier of a previously-opened context."
    "``sample_type``", "The sample type which will be created for this session."
    "``session_id``", "On successful execution of this function, this parameter will be set to a GPA-generated unique session identifier. This value can subsequently passed to any GPA function taking a GpaSessionId as an input parameter."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "kGpaStatusOk", "The session was successfully created."
    "kGpaStatusErrorGpaNotInitialized", "GPA was not initialized. Call GpaInitialize before all other entrypoints."
    "kGpaStatusErrorNullPointer", "| The supplied ``context_id`` parameter is NULL.
    | The supplied ``session_id`` parameter is NULL."
    "kGpaStatusErrorContextNotFound", "The supplied ``context_id`` parameter was not recognized as a previously-opened context identifier."
    "kGpaStatusErrorContextNotOpen", "The supplied context is not currently open."
    "kGpaStatusErrorInvalidParameter", "The ``sample_type`` parameter has an invalid value."
    "kGpaStatusErrorIncompatibleSampleTypes", "The ``sample_type`` is incompatible with the context's supported sample type."
    "kGpaStatusErrorFailed", "The session could not be created."
    "kGpaStatusErrorException", "Exception occurred."

