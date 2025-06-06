/*
 * Copyright 2020 NXP
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_adapter_rng.h"

hal_rng_status_t HAL_RngInit(void)
{
    return KStatus_HAL_RngNotSupport;
}

void HAL_RngDeinit(void)
{
    return;
}

hal_rng_status_t HAL_RngHwGetData(void *pRandomNo, uint32_t dataSize)
{
    (void)pRandomNo;
    (void)dataSize;
    return KStatus_HAL_RngNotSupport;
}

hal_rng_status_t HAL_RngGetData(void *pRandomNo, uint32_t dataSize)
{
    if (NULL == pRandomNo)
    {
        return kStatus_HAL_RngNullPointer;
    }
    for (uint32_t i = 0; i < dataSize; i++)
    {
        ((uint8_t *)pRandomNo)[i] = (uint8_t)((uint8_t)rand() & 0xFFU);
    }
    return kStatus_HAL_RngSuccess;
}

hal_rng_status_t HAL_RngSetSeed(uint32_t seed)
{
    srand(seed);
    return kStatus_HAL_RngSuccess;
}
