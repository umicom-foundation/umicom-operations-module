/*-----------------------------------------------------------------------------
 * Umicom Operations Module
 * File: include/umicom/operations/runtime.h
 *
 * PURPOSE:
 *   Bind the thin product to the Framework-owned application workspace runtime without duplicating services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_OPERATIONS_RUNTIME_H
#define UMICOM_OPERATIONS_RUNTIME_H

#include "umicom/application/runtime/runtime.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialise operations runtime from caller-provided values so later operations receive a
 * known state.
 */
UmiStatus umi_operations_runtime_init(
    UmiApplicationWorkspaceRuntime *out_runtime);
/**
 * Provide the operations runtime health operation used by this module and its client
 * applications.
 */
UmiStatus umi_operations_runtime_health(
    UmiApplicationCapabilityProbe probe,
    void *user_data,
    UmiApplicationRuntimeHealth *out_health);
/**
 * Provide the operations runtime experience operation used by this module and its client
 * applications.
 */
const UmiApplicationExperienceDefinition *umi_operations_runtime_experience(void);

#ifdef __cplusplus
}
#endif

#endif
