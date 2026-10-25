/**
 * @file estimator.h
 * @brief Deterministic, zero-heap C99 state estimation operator without libm.
 * @author Ye, Qiang (Peter)
 * @license Apache-2.0
 * @doi 10.5281/zenodo.23631889
 */

#ifndef ESTIMATOR_H
#define ESTIMATOR_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    EST_STATE_INIT = 0,
    EST_STATE_ACQUIRE,
    EST_STATE_TRACK,
    EST_STATE_FAULT_CLAMP,
    EST_STATE_DEGRADED
} est_fsm_state_t;

typedef enum {
    EST_STATUS_OK = 0,
    EST_STATUS_OUTLIER_REJECTED,
    EST_STATUS_DROPOUT_HOLD,
    EST_STATUS_RATE_SATURATED
} est_status_t;

typedef struct {
    float x;        /* Estimated position/signal */
    float v;        /* Estimated rate of change */
    float residual; /* Innovation error */
} est_output_t;

typedef struct {
    float dt;                 /* Sampling period in seconds */
    float max_velocity;       /* Physical velocity hard clamp (e.g. 5.0f) */
    float outlier_threshold;  /* Residual threshold for rejection (e.g. 3.0f) */
    uint32_t dropout_timeout; /* Maximum cycles to hold state (e.g. 15) */
} est_config_t;

typedef struct {
    est_config_t config;
    est_fsm_state_t state;
    float state_x;
    float state_v;
    uint32_t fault_counter;
    uint32_t consecutive_valid;
    bool initialized;
} est_handle_t;

/**
 * @brief Initialize the deterministic state estimator.
 */
void est_init(est_handle_t *handle, const est_config_t *config);

/**
 * @brief Step update the causal state estimator.
 * Guaranteed WCET without dynamic allocation or unbounded iterations.
 */
est_status_t est_update(est_handle_t *handle, float raw_measurement, est_output_t *output);

#ifdef __cplusplus
}
#endif

#endif /* ESTIMATOR_H */
