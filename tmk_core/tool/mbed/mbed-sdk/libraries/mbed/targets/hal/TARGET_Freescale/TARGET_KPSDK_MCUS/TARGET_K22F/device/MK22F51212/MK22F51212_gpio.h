/*
** ###################################################################
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**
**     Reference manual:    K22P121M120SF7RM, Rev. 1, March 24, 2014
**     Version:             rev. 2.5, 2014-05-06
**     Build:               b140604
**
**     Abstract:
**         Extension to the CMSIS register access layer header.
**
**     Copyright (c) 2014 Freescale Semiconductor, Inc.
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.freescale.com
**     mail:                 support@freescale.com
**
**     Revisions:
**     - rev. 1.0 (2013-07-23)
**         Initial version.
**     - rev. 1.1 (2013-09-17)
**         RM rev. 0.4 update.
**     - rev. 2.0 (2013-10-29)
**         Register accessor macros added to the memory map.
**         Symbols for Processor Expert memory map compatibility added to the memory map.
**         Startup file for gcc has been updated according to CMSIS 3.2.
**         System initialization updated.
**     - rev. 2.1 (2013-10-30)
**         Definition of BITBAND macros updated to support peripherals with 32-bit acces disabled.
**     - rev. 2.2 (2013-12-20)
**         Update according to reference manual rev. 0.6,
**     - rev. 2.3 (2014-01-13)
**         Update according to reference manual rev. 0.61,
**     - rev. 2.4 (2014-02-10)
**         The declaration of clock configurations has been moved to separate header file system_MK22F51212.h
**     - rev. 2.5 (2014-05-06)
**         Update according to reference manual rev. 1.0,
**         Update of system and startup files.
**         Module access macro module_BASES replaced by module_BASE_PTRS.
**
** ###################################################################
*/

/*
 * WARNING! DO NOT EDIT THIS FILE DIRECTLY!
 *
 * This file was generated automatically and any changes may be lost.
 */
#ifndef __HW_GPIO_REGISTERS_H__
#define __HW_GPIO_REGISTERS_H__

#include "MK22F51212.h"
#include "fsl_bitaccess.h"

/*
 * MK22F51212 GPIO
 *
 * General Purpose Input/Output
 *
 * Registers defined in this header file:
 * - HW_GPIO_PDOR - Port Data Output Register
 * - HW_GPIO_PSOR - Port Set Output Register
 * - HW_GPIO_PCOR - Port Clear Output Register
 * - HW_GPIO_PTOR - Port Toggle Output Register
 * - HW_GPIO_PDIR - Port Data Input Register
 * - HW_GPIO_PDDR - Port Data Direction Register
 *
 * - hw_gpio_t - Struct containing all module registers.
 */

#define HW_GPIO_INSTANCE_COUNT (5U) /*!< Number of instances of the GPIO module. */
#define HW_GPIOA (0U) /*!< Instance number for GPIOA. */
#define HW_GPIOB (1U) /*!< Instance number for GPIOB. */
#define HW_GPIOC (2U) /*!< Instance number for GPIOC. */
#define HW_GPIOD (3U) /*!< Instance number for GPIOD. */
#define HW_GPIOE (4U) /*!< Instance number for GPIOE. */

/*******************************************************************************
 * HW_GPIO_PDOR - Port Data Output Register
 ******************************************************************************/

/*!
 * @brief HW_GPIO_PDOR - Port Data Output Register (RW)
 *
 * Reset value: 0x00000000U
 *
 * This register configures the logic levels that are driven on each
 * general-purpose output pins. Do not modify pin configuration registers associated with
 * pins not available in your selected package. All unbonded pins not available in
 * your package will default to DISABLE state for lowest power consumption.
 */
typedef union _hw_gpio_pdor
{
    uint32_t U;
    struct _hw_gpio_pdor_bitfields
    {
        uint32_t PDO : 32;             /*!< [31:0] Port Data Output */
    } B;
} hw_gpio_pdor_t;

/*!
 * @name Constants and macros for entire GPIO_PDOR register
 */
/*@{*/
#define HW_GPIO_PDOR_ADDR(x)     ((x) + 0x0U)

#define HW_GPIO_PDOR(x)          (*(__IO hw_gpio_pdor_t *) HW_GPIO_PDOR_ADDR(x))
#define HW_GPIO_PDOR_RD(x)       (HW_GPIO_PDOR(x).U)
#define HW_GPIO_PDOR_WR(x, v)    (HW_GPIO_PDOR(x).U = (v))
#define HW_GPIO_PDOR_SET(x, v)   (HW_GPIO_PDOR_WR(x, HW_GPIO_PDOR_RD(x) |  (v)))
#define HW_GPIO_PDOR_CLR(x, v)   (HW_GPIO_PDOR_WR(x, HW_GPIO_PDOR_RD(x) & ~(v)))
#define HW_GPIO_PDOR_TOG(x, v)   (HW_GPIO_PDOR_WR(x, HW_GPIO_PDOR_RD(x) ^  (v)))
/*@}*/

/*
 * Constants & macros for individual GPIO_PDOR bitfields
 */

/*!
 * @name Register GPIO_PDOR, field PDO[31:0] (RW)
 *
 * Register bits for unbonded pins return a undefined value when read.
 *
 * Values:
 * - 0 - Logic level 0 is driven on pin, provided pin is configured for
 *     general-purpose output.
 * - 1 - Logic level 1 is driven on pin, provided pin is configured for
 *     general-purpose output.
 */
/*@{*/
#define BP_GPIO_PDOR_PDO     (0U)          /*!< Bit position for GPIO_PDOR_PDO. */
#define BM_GPIO_PDOR_PDO     (0xFFFFFFFFU) /*!< Bit mask for GPIO_PDOR_PDO. */
#define BS_GPIO_PDOR_PDO     (32U)         /*!< Bit field size in bits for GPIO_PDOR_PDO. */

/*! @brief Read current value of the GPIO_PDOR_PDO field. */
#define BR_GPIO_PDOR_PDO(x)  (HW_GPIO_PDOR(x).U)

/*! @brief Format value for bitfield GPIO_PDOR_PDO. */
#define BF_GPIO_PDOR_PDO(v)  ((uint32_t)((uint32_t)(v) << BP_GPIO_PDOR_PDO) & BM_GPIO_PDOR_PDO)

/*! @brief Set the PDO field to a new value. */
#define BW_GPIO_PDOR_PDO(x, v) (HW_GPIO_PDOR_WR(x, v))
/*@}*/

/*******************************************************************************
 * HW_GPIO_PSOR - Port Set Output Register
 ******************************************************************************/

/*!
 * @brief HW_GPIO_PSOR - Port Set Output Register (WORZ)
 *
 * Reset value: 0x00000000U
 *
 * This register configures whether to set the fields of the PDOR.
 */
typedef union _hw_gpio_psor
{
    uint32_t U;
    struct _hw_gpio_psor_bitfields
    {
        uint32_t PTSO : 32;            /*!< [31:0] Port Set Output */
    } B;
} hw_gpio_psor_t;

/*!
 * @name Constants and macros for entire GPIO_PSOR register
 */
/*@{*/
#define HW_GPIO_PSOR_ADDR(x)     ((x) + 0x4U)

#define HW_GPIO_PSOR(x)          (*(__O hw_gpio_psor_t *) HW_GPIO_PSOR_ADDR(x))
#define HW_GPIO_PSOR_RD(x)       (HW_GPIO_PSOR(x).U)
#define HW_GPIO_PSOR_WR(x, v)    (HW_GPIO_PSOR(x).U = (v))
/*@}*/

/*
 * Constants & macros for individual GPIO_PSOR bitfields
 */

/*!
 * @name Register GPIO_PSOR, field PTSO[31:0] (WORZ)
 *
 * Writing to this register will update the contents of the corresponding bit in
 * the PDOR as follows:
 *
 * Values:
 * - 0 - Corresponding bit in PDORn does not change.
 * - 1 - Corresponding bit in PDORn is set to logic 1.
 */
/*@{*/
#define BP_GPIO_PSOR_PTSO    (0U)          /*!< Bit position for GPIO_PSOR_PTSO. */
#define BM_GPIO_PSOR_PTSO    (0xFFFFFFFFU) /*!< Bit mask for GPIO_PSOR_PTSO. */
#define BS_GPIO_PSOR_PTSO    (32U)         /*!< Bit field size in bits for GPIO_PSOR_PTSO. */

/*! @brief Format value for bitfield GPIO_PSOR_PTSO. */
#define BF_GPIO_PSOR_PTSO(v) ((uint32_t)((uint32_t)(v) << BP_GPIO_PSOR_PTSO) & BM_GPIO_PSOR_PTSO)

/*! @brief Set the PTSO field to a new value. */
#define BW_GPIO_PSOR_PTSO(x, v) (HW_GPIO_PSOR_WR(x, v))
/*@}*/

/*******************************************************************************
 * HW_GPIO_PCOR - Port Clear Output Register
 ******************************************************************************/

/*!
 * @brief HW_GPIO_PCOR - Port Clear Output Register (WORZ)
 *
 * Reset value: 0x00000000U
 *
 * This register configures whether to clear the fields of PDOR.
 */
typedef union _hw_gpio_pcor
{
    uint32_t U;
    struct _hw_gpio_pcor_bitfields
    {
        uint32_t PTCO : 32;            /*!< [31:0] Port Clear Output */
    } B;
} hw_gpio_pcor_t;

/*!
 * @name Constants and macros for entire GPIO_PCOR register
 */
/*@{*/
#define HW_GPIO_PCOR_ADDR(x)     ((x) + 0x8U)

#define HW_GPIO_PCOR(x)          (*(__O hw_gpio_pcor_t *) HW_GPIO_PCOR_ADDR(x))
#define HW_GPIO_PCOR_RD(x)       (HW_GPIO_PCOR(x).U)
#define HW_GPIO_PCOR_WR(x, v)    (HW_GPIO_PCOR(x).U = (v))
/*@}*/

/*
 * Constants & macros for individual GPIO_PCOR bitfields
 */

/*!
 * @name Register GPIO_PCOR, field PTCO[31:0] (WORZ)
 *
 * Writing to this register will update the contents of the corresponding bit in
 * the Port Data Output Register (PDOR) as follows:
 *
 * Values:
 * - 0 - Corresponding bit in PDORn does not change.
 * - 1 - Corresponding bit in PDORn is cleared to logic 0.
 */
/*@{*/
#define BP_GPIO_PCOR_PTCO    (0U)          /*!< Bit position for GPIO_PCOR_PTCO. */
#define BM_GPIO_PCOR_PTCO    (0xFFFFFFFFU) /*!< Bit mask for GPIO_PCOR_PTCO. */
#define BS_GPIO_PCOR_PTCO    (32U)         /*!< Bit field size in bits for GPIO_PCOR_PTCO. */

/*! @brief Format value for bitfield GPIO_PCOR_PTCO. */
#define BF_GPIO_PCOR_PTCO(v) ((uint32_t)((uint32_t)(v) << BP_GPIO_PCOR_PTCO) & BM_GPIO_PCOR_PTCO)

/*! @brief Set the PTCO field to a new value. */
#define BW_GPIO_PCOR_PTCO(x, v) (HW_GPIO_PCOR_WR(x, v))
/*@}*/

/*******************************************************************************
 * HW_GPIO_PTOR - Port Toggle Output Register
 ******************************************************************************/

/*!
 * @brief HW_GPIO_PTOR - Port Toggle Output Register (WORZ)
 *
 * Reset value: 0x00000000U
 */
typedef union _hw_gpio_ptor
{
    uint32_t U;
    struct _hw_gpio_ptor_bitfields
    {
        uint32_t PTTO : 32;            /*!< [31:0] Port Toggle Output */
    } B;
} hw_gpio_ptor_t;

/*!
 * @name Constants and macros for entire GPIO_PTOR register
 */
/*@{*/
#define HW_GPIO_PTOR_ADDR(x)     ((x) + 0xCU)

#define HW_GPIO_PTOR(x)          (*(__O hw_gpio_ptor_t *) HW_GPIO_PTOR_ADDR(x))
#define HW_GPIO_PTOR_RD(x)       (HW_GPIO_PTOR(x).U)
#define HW_GPIO_PTOR_WR(x, v)    (HW_GPIO_PTOR(x).U = (v))
/*@}*/

/*
 * Constants & macros for individual GPIO_PTOR bitfields
 */

/*!
 * @name Register GPIO_PTOR, field PTTO[31:0] (WORZ)
 *
 * Writing to this register will update the contents of the corresponding bit in
 * the PDOR as follows:
 *
 * Values:
 * - 0 - Corresponding bit in PDORn does not change.
 * - 1 - Corresponding bit in PDORn is set to the inverse of its existing logic
 *     state.
 */
/*@{*/
#define BP_GPIO_PTOR_PTTO    (0U)          /*!< Bit position for GPIO_PTOR_PTTO. */
#define BM_GPIO_PTOR_PTTO    (0xFFFFFFFFU) /*!< Bit mask for GPIO_PTOR_PTTO. */
#define BS_GPIO_PTOR_PTTO    (32U)         /*!< Bit field size in bits for GPIO_PTOR_PTTO. */

/*! @brief Format value for bitfield GPIO_PTOR_PTTO. */
#define BF_GPIO_PTOR_PTTO(v) ((uint32_t)((uint32_t)(v) << BP_GPIO_PTOR_PTTO) & BM_GPIO_PTOR_PTTO)

/*! @brief Set the PTTO field to a new value. */
#define BW_GPIO_PTOR_PTTO(x, v) (HW_GPIO_PTOR_WR(x, v))
/*@}*/

/*******************************************************************************
 * HW_GPIO_PDIR - Port Data Input Register
 ******************************************************************************/

/*!
 * @brief HW_GPIO_PDIR - Port Data Input Register (RO)
 *
 * Reset value: 0x00000000U
 *
 * Do not modify pin configuration registers associated with pins not available
 * in your selected package. All unbonded pins not available in your package will
 * default to DISABLE state for lowest power consumption.
 */
typedef union _hw_gpio_pdir
{
    uint32_t U;
    struct _hw_gpio_pdir_bitfields
    {
        uint32_t PDI : 32;             /*!< [31:0] Port Data Input */
    } B;
} hw_gpio_pdir_t;

/*!
 * @name Constants and macros for entire GPIO_PDIR register
 */
/*@{*/
#define HW_GPIO_PDIR_ADDR(x)     ((x) + 0x10U)

#define HW_GPIO_PDIR(x)          (*(__I hw_gpio_pdir_t *) HW_GPIO_PDIR_ADDR(x))
#define HW_GPIO_PDIR_RD(x)       (HW_GPIO_PDIR(x).U)
/*@}*/

/*
 * Constants & macros for individual GPIO_PDIR bitfields
 */

/*!
 * @name Register GPIO_PDIR, field PDI[31:0] (RO)
 *
 * Reads 0 at the unimplemented pins for a particular device. Pins that are not
 * configured for a digital function read 0. If the Port Control and Interrupt
 * module is disabled, then the corresponding bit in PDIR does not update.
 *
 * Values:
 * - 0 - Pin logic level is logic 0, or is not configured for use by digital
 *     function.
 * - 1 - Pin logic level is logic 1.
 */
/*@{*/
#define BP_GPIO_PDIR_PDI     (0U)          /*!< Bit position for GPIO_PDIR_PDI. */
#define BM_GPIO_PDIR_PDI     (0xFFFFFFFFU) /*!< Bit mask for GPIO_PDIR_PDI. */
#define BS_GPIO_PDIR_PDI     (32U)         /*!< Bit field size in bits for GPIO_PDIR_PDI. */

/*! @brief Read current value of the GPIO_PDIR_PDI field. */
#define BR_GPIO_PDIR_PDI(x)  (HW_GPIO_PDIR(x).U)
/*@}*/

/*******************************************************************************
 * HW_GPIO_PDDR - Port Data Direction Register
 ******************************************************************************/

/*!
 * @brief HW_GPIO_PDDR - Port Data Direction Register (RW)
 *
 * Reset value: 0x00000000U
 *
 * The PDDR configures the individual port pins for input or output.
 */
typedef union _hw_gpio_pddr
{
    uint32_t U;
    struct _hw_gpio_pddr_bitfields
    {
        uint32_t PDD : 32;             /*!< [31:0] Port Data Direction */
    } B;
} hw_gpio_pddr_t;

/*!
 * @name Constants and macros for entire GPIO_PDDR register
 */
/*@{*/
#define HW_GPIO_PDDR_ADDR(x)     ((x) + 0x14U)

#define HW_GPIO_PDDR(x)          (*(__IO hw_gpio_pddr_t *) HW_GPIO_PDDR_ADDR(x))
#define HW_GPIO_PDDR_RD(x)       (HW_GPIO_PDDR(x).U)
#define HW_GPIO_PDDR_WR(x, v)    (HW_GPIO_PDDR(x).U = (v))
#define HW_GPIO_PDDR_SET(x, v)   (HW_GPIO_PDDR_WR(x, HW_GPIO_PDDR_RD(x) |  (v)))
#define HW_GPIO_PDDR_CLR(x, v)   (HW_GPIO_PDDR_WR(x, HW_GPIO_PDDR_RD(x) & ~(v)))
#define HW_GPIO_PDDR_TOG(x, v)   (HW_GPIO_PDDR_WR(x, HW_GPIO_PDDR_RD(x) ^  (v)))
/*@}*/

/*
 * Constants & macros for individual GPIO_PDDR bitfields
 */

/*!
 * @name Register GPIO_PDDR, field PDD[31:0] (RW)
 *
 * Configures individual port pins for input or output.
 *
 * Values:
 * - 0 - Pin is configured as general-purpose input, for the GPIO function.
 * - 1 - Pin is configured as general-purpose output, for the GPIO function.
 */
/*@{*/
#define BP_GPIO_PDDR_PDD     (0U)          /*!< Bit position for GPIO_PDDR_PDD. */
#define BM_GPIO_PDDR_PDD     (0xFFFFFFFFU) /*!< Bit mask for GPIO_PDDR_PDD. */
#define BS_GPIO_PDDR_PDD     (32U)         /*!< Bit field size in bits for GPIO_PDDR_PDD. */

/*! @brief Read current value of the GPIO_PDDR_PDD field. */
#define BR_GPIO_PDDR_PDD(x)  (HW_GPIO_PDDR(x).U)

/*! @brief Format value for bitfield GPIO_PDDR_PDD. */
#define BF_GPIO_PDDR_PDD(v)  ((uint32_t)((uint32_t)(v) << BP_GPIO_PDDR_PDD) & BM_GPIO_PDDR_PDD)

/*! @brief Set the PDD field to a new value. */
#define BW_GPIO_PDDR_PDD(x, v) (HW_GPIO_PDDR_WR(x, v))
/*@}*/

/*******************************************************************************
 * hw_gpio_t - module struct
 ******************************************************************************/
/*!
 * @brief All GPIO module registers.
 */
#pragma pack(1)
typedef struct _hw_gpio
{
    __IO hw_gpio_pdor_t PDOR;              /*!< [0x0] Port Data Output Register */
    __O hw_gpio_psor_t PSOR;               /*!< [0x4] Port Set Output Register */
    __O hw_gpio_pcor_t PCOR;               /*!< [0x8] Port Clear Output Register */
    __O hw_gpio_ptor_t PTOR;               /*!< [0xC] Port Toggle Output Register */
    __I hw_gpio_pdir_t PDIR;               /*!< [0x10] Port Data Input Register */
    __IO hw_gpio_pddr_t PDDR;              /*!< [0x14] Port Data Direction Register */
} hw_gpio_t;
#pragma pack()

/*! @brief Macro to access all GPIO registers. */
/*! @param x GPIO module instance base address. */
/*! @return Reference (not a pointer) to the registers struct. To get a pointer to the struct,
 *     use the '&' operator, like <code>&HW_GPIO(GPIOA_BASE)</code>. */
#define HW_GPIO(x)     (*(hw_gpio_t *)(x))

#endif /* __HW_GPIO_REGISTERS_H__ */
/* EOF */
