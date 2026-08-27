/*-----------------------------------------------------------------------------
 * Umicom Operations Module
 * File: include/umicom/operations/application.h
 *
 * PURPOSE:
 *   Expose the thin application composition over Framework-owned experience metadata and services.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_OPERATIONS_APPLICATION_H
#define UMICOM_OPERATIONS_APPLICATION_H

#include "umicom/application/experience.h"
#include "umicom/application/experience_status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UMI_OPERATIONS_MODULE_API_VERSION 1U

const char *umi_operations_application_id(void);

const UmiApplicationExperienceDefinition *
umi_operations_application_experience(void);

UmiStatus umi_operations_application_status(
    UmiApplicationExperienceStatus *out_status);

#ifdef __cplusplus
}
#endif

#endif
