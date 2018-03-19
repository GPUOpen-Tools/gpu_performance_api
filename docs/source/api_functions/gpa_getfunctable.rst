.. Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.

GPA_GetFuncTable
@@@@@@@@@@@@@@@@

Syntax
%%%%%%

.. code-block:: c++

    GPA_Status GPA_GetFuncTable(
        void* pGPAFuncTable);

Description
%%%%%%%%%%%

Gets the GPA API function table. ``pGPAFuncTable`` is both an input and output
parameter, whose type is ``GPAFunctionTable*``. Prior to calling this function
the ``m_majorVer`` and ``m_minorVer`` should be set by the caller. When
compiling in C++ mode, these will be set automatically. When compiling in C
mode, they will need to be set manually to
GPA_FUNCTION_TABLE_MAJOR_VERSION_NUMBER and
GPA_FUNCTION_TABLE_MINOR_VERSION_NUMBER, respectively. After execution of this
function, the ``m_majorVer`` and ``m_minorVer`` members will be set to the
major and minor version of the GPUPerfAPI library that is loaded. If the
versions are determined to be incompatible, the function will return an error.

The minor version of the function table is calculated as the size of the
function table structure. This allows for additional functions to be added to
the end of the table in future versions, while still maintaining
backwards-compatibility. If the minor version number specified by the caller is
lower than the minor version number of the GPUPerfAPI library, GPA_GetFuncTable
will assign the function pointers of the input structure up to the size of the
structure (as specified by the minor version). The caller can detect this
situation by checking the value of ``m_minorVer`` after successful execution.
If the value is larger than the original value, the caller can infer that the
version of the GPUPerfAPI library loaded has some additional API functions
available that were not present in older versions of the library. The caller
can recompile using the newer GPUPerfAPI header files to gain access to the new
functions.

If non-backwards compatible changes are ever made in a new version of
GPUPerfAPI, the major version of the API table will be incremented. Examples of
non-backwards compatible changes would be removal of a public function or
changing the signature of a public function. In the case where the major
version number specified by the caller differs from the major version number
of the GPUPerfAPI library, this function will set the ``m_majorVer`` member to
the major version of the GPUPerfAPI library that was loaded and return an error.

Parameters
%%%%%%%%%%

.. csv-table::
    :header: "Name", "Description"
    :widths: 35, 65

    "``pGPAFuncTable``", "Pointer to the GPA function table structure."

Return value
%%%%%%%%%%%%

.. csv-table::
    :header: "Return value", "Description"
    :widths: 35, 65

    "GPA_STATUS_OK", "The function table was successfully retrieved."
    "GPA_STATUS_ERROR_NULL_POINTER", "The supplied ``pGPAFuncTable`` parameter is NULL."
    "GPA_STATUS_ERROR_LIB_LOAD_MAJOR_VERSION_MISMATCH", "The major version specified by the caller is different from the major version of the GPUPerfAPI library that was loaded."
    "GPA_STATUS_ERROR_LIB_LOAD_MINOR_VERSION_MISMATCH", "The minor version specified by the caller is greater than the major version of the GPUPerfAPI library that was loaded."
