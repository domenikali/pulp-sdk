/**
* @brief Phase Change Memory (PCM) module drivers
* 
* This header file defines the PCM module drivers for the PULP platform.
* It includes the necessary structures and function declarations for PCM operations.
* @author Leonardo Domenicali (leonardo.domenicali@studio.unibo.it | leonardo.domenicali@gmail.com)
*/
#ifndef __BSP_PCM_H__
#define __BSP_PCM_H__

#include "pmsis.h"

enum class CMD_SETTINGS : uint32_t{
    CMD_SETTINGS_SECTORS = 0x10000000,
    CMD_SETTINGS_TWO_STEP_U = 0x11000000,
    CMD_SETTINGS_TWO_STEP_U_DOUBLE_WEIGHT = 0x12000000,
    CMD_SETTINGS_T_STEP_S = 0x13000000,
    CMD_SETTINGS_TWO_STEP_S_DOUBLE_WEIGHT = 0x14000000,
    CMD_SETTINGS_SINGLE_STEP = 0x15000000,
    CMD_SETTINGS_FAST_SINGLE_STEP = 0x16000000,
    CMD_SETTINGS_INPUT_PRECISION = 0x17000000,
    CMD_SETTINGS_BL = 0x18000000,
    CMD_SETTINGS_MASK = 0xFF000000
};

enum class CMD : uint32_t{
    CMD_MASK = 0xF0000000,
    CMD_COMPUTE = 0x00000000,
    CMD_PARAM = 0x10000000,
    CMD_ABORT = 0x40000000
};

/**
 * @brief PCM configuration api structure.
 * this structure contains the api pointer to the PCM methods.
 */
typedef struct{
  int (*open)(pi_device_t *device);
  void (*close)(pi_device_t *device);
  void (*compute)(pi_device_t *device, uint32_t aimc_addr, uint32_t cmd, uint32_t size);
  void (*set_parameters)(pi_device_t *device, uint32_t aimc_addr, uint32_t cmd, uint32_t size);
  void (*set_vector)(pi_device_t *device, uint32_t vector_addr, void *data, uint32_t size);
  void (*read)(pi_device_t *device, uint32_t pcm_addr, void *data, uint32_t size);
  void (*write)(pi_device_t *device, uint32_t pcm_addr, const void *data, uint32_t size);
}pi_pcm_api_t;


typedef struct{
  pi_pcm_api_t *api;
}pi_pcm_conf;

/**
 * @brief Open a PCM device.
 * This function must be called before the PCM device can be used.
 * It will do all the needed configuration to make it usable and initialize
 */
inline int pi_pcm_open(pi_device_t *device)
{
    struct pi_pcm_conf *conf = (struct pi_pcm_conf *)device->config;
    pi_pcm_api_t *api = (pi_pcm_api_t *)conf->api;
    device->api = (struct pi_device_api *)api;
    return api->open(device);
}
/**
 * @brief Close an opened PCM device.
 * This function can be called to close an opened PCM device 
 */
static inline void pi_close_close(struct pi_device *device)
{
  pi_pcm_api_t *api = (pi_pcm_api_t *)device->api;
  api->close(device);
}

/**
 * @brief Set PCM parameters.
 * This function starts the PCM AIMC computation with the specified parameters.
 * 
 * @param device The device structure of the PCM.
 * @param aimc_addr The address of the AIMC.
 * @param cmd The command to set the parameters.
 */
static inline void pi_pcm_compute(pi_device_t *device, uint32_t aimc_addr, uint32_t cmd)
{
  pi_pcm_api_t *api = (pi_pcm_api_t *)device->api;
  api->compute(device, aimc_addr, (uint8_t*)&cmd, sizeof(uint32_t));
}

static inline void pi_pcm_set_parameters(pi_device_t *device, uint32_t aimc_addr, uint32_t cmd)
{
  pi_pcm_api_t *api = (pi_pcm_api_t *)device->api;
  api->set_parameters(device, aimc_addr, (uint8_t*)&cmd, sizeof(uint32_t));
}




#endif /* __BSP_PCM_H__ */
