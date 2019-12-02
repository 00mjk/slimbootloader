/** @file
  Header file for container library implementation.

  Copyright (c) 2019, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/
#ifndef _CONTAINER_LIB_H_
#define _CONTAINER_LIB_H_

#include <Library/PcdLib.h>

#define CONTAINER_LIST_SIGNATURE SIGNATURE_32('C','T','N', 'L')

#define PROGESS_ID_LOCATE             1
#define PROGESS_ID_COPY               2
#define PROGESS_ID_AUTHENTICATE       3
#define PROGESS_ID_DECOMPRESS         4

#define AUTH_TYPE_NONE                0
#define AUTH_TYPE_SHA2_256            1
#define AUTH_TYPE_SHA2_384            2
#define AUTH_TYPE_SIG_RSA2048_SHA256  3
#define AUTH_TYPE_SIG_RSA3072_SHA384  4

#define CONTAINER_BOOT_SIGNATURE      SIGNATURE_32 ('B', 'O', 'O', 'T')
#define CONTAINER_MONO_SIGN_SIGNATURE SIGNATURE_32 ('_', 'S', 'G', '_')

// Flags for CONTAINER_HDR
#define CONTAINER_HDR_FLAG_MONO_SIGNING     BIT0

// Attributes for COMPONENT_ENTRY
#define COMPONENT_ENTRY_ATTR_RESERVED       BIT7

typedef VOID (*LOAD_COMPONENT_CALLBACK) (UINT32 ProgressId);

typedef struct {
  UINT32           Signature;
  UINT32           HeaderCache;
  UINT32           Base;
  UINT32           Reserved;
} CONTAINER_ENTRY;

typedef struct {
  UINT32           Signature;
  UINT32           Reserved;
  UINT32           TotalLength;
  UINT32           Count;
  CONTAINER_ENTRY  Entry[0];
} CONTAINER_LIST;

typedef struct {
  UINT32           Signature;
  UINT16           Version;
  UINT16           DataOffset;
  UINT32           DataSize;
  UINT8            AuthType;
  UINT8            ImageType;
  UINT8            Flags;
  UINT8            Count;
} CONTAINER_HDR;

typedef struct {
  UINT32           Name;
  UINT32           Offset;
  UINT32           Size;
  UINT8            Attribute;
  UINT8            Alignment;
  UINT8            AuthType;
  UINT8            HashSize;
  UINT8            HashData[0];
} COMPONENT_ENTRY;


/**
  Load a component from a container or flahs map to memory and call callback
  function at predefined point.

  @param[in]     ContainerSig    Container signature or component type.
  @param[in]     ComponentName   Component name.
  @param[in,out] Buffer          Pointer to receive component base.
  @param[in,out] Length          Pointer to receive component size.
  @param[in]     CallbackFunc    Callback function pointer.

  @retval EFI_UNSUPPORTED          Unsupported AuthType.
  @retval EFI_NOT_FOUND            Cannot locate component.
  @retval EFI_BUFFER_TOO_SMALL     Specified buffer size is too small.
  @retval EFI_SECURITY_VIOLATION   Authentication failed.
  @retval EFI_SUCCESS              Authentication succeeded.

**/
EFI_STATUS
EFIAPI
LoadComponentWithCallback (
  IN     UINT32                   ContainerSig,
  IN     UINT32                   ComponentName,
  IN OUT VOID                   **Buffer,
  IN OUT UINT32                  *Length,
  IN     LOAD_COMPONENT_CALLBACK  LoadComponentCallback
  );

/**
  Locate a component region information from a container or flash map.

  @param[in]      ContainerSig    Container signature or component type.
  @param[in]      ComponentName   component name.
  @param[in, out] Buffer          Pointer to receive component base.
  @param[in, out] Length          Pointer to receive component size.

  @retval EFI_UNSUPPORTED          Unsupported AuthType.
  @retval EFI_NOT_FOUND            Cannot locate component.
  @retval EFI_SECURITY_VIOLATION   Authentication failed.
  @retval EFI_SUCCESS              Authentication succeeded.

**/
EFI_STATUS
EFIAPI
LocateComponent (
  IN     UINT32    ContainerSig,
  IN     UINT32    ComponentName,
  IN OUT VOID    **Buffer,
  IN OUT UINT32   *Length
  );

/**
  Load a component from a container or flash map to memory.

  @param[in] ContainerSig    Container signature or component type.
  @param[in] ComponentName   Component name.
  @param[in,out] Buffer          Pointer to receive component base.
  @param[in,out] Length          Pointer to receive component size.

  @retval EFI_UNSUPPORTED          Unsupported AuthType.
  @retval EFI_NOT_FOUND            Cannot locate component.
  @retval EFI_BUFFER_TOO_SMALL     Specified buffer size is too small.
  @retval EFI_SECURITY_VIOLATION   Authentication failed.
  @retval EFI_SUCCESS              Authentication succeeded.

**/
EFI_STATUS
EFIAPI
LoadComponent (
  IN     UINT32    ContainerSig,
  IN     UINT32    ComponentName,
  IN OUT VOID    **Buffer,
  IN OUT UINT32   *Length
  );

/**
  Locate a component information from a container.

  @param[in]     ContainerSig       Container signature.
  @param[in]     ComponentName      Component name.
  @param[in,out] ContainerEntryPtr  Pointer to receive container entry info.
  @param[in,out] ComponentEntryPtr  Pointer to receive component entry info.

  @retval EFI_UNSUPPORTED          Unsupported AuthType.
  @retval EFI_NOT_FOUND            Cannot locate component.
  @retval EFI_SECURITY_VIOLATION   Authentication failed.
  @retval EFI_SUCCESS              component region is located successfully.

**/
EFI_STATUS
LocateComponentEntry (
  IN      UINT32                  ContainerSig,
  IN      UINT32                  ComponentName,
  IN OUT  CONTAINER_ENTRY       **ContainerEntryPtr,
  IN OUT  COMPONENT_ENTRY       **ComponentEntryPtr
  );

/**
  Get Next Component in a container.

  @param[in]       ContainerSig    Container signature or component type.
  @param[in, out]  ComponentName   Pointer to receive next component name.

  @retval EFI_INVALID_PARAMETER    ComponentName is NULL.
  @retval EFI_NOT_FOUND            Cannot find next component.
  @retval EFI_SUCCESS              Next component was found successfully.

**/
EFI_STATUS
EFIAPI
GetNextAvailableComponent (
  IN     UINT32     ContainerSig,
  IN     UINT32    *ComponentName
);

/**
  This function registers a container.

  @param[in]  ContainerBase      Container base address to register.

  @retval EFI_NOT_READY          Not ready for register yet.
  @retval EFI_BUFFER_TOO_SMALL   Insufficant max container entry number.
  @retval EFI_OUT_OF_RESOURCES   No space to add new container.
  @retval EFI_SUCCESS            The container has been registered successfully.

**/
EFI_STATUS
RegisterContainer (
  IN  UINT32   ContainerBase
  );

/**
  This function unregisters a container with given signature.

  @param[in]  Signature      Container signature.

  @retval EFI_NOT_READY          Not ready for unregister yet.
  @retval EFI_NOT_FOUND          Not container available for unregisteration.
  @retval EFI_SUCCESS            The container has been unregistered successfully.

**/
EFI_STATUS
UnregisterContainer (
  IN  UINT32   Signature
  );


#endif
