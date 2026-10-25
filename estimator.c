/**
 * @file estimator.c
 * @brief Implementation of deterministic state estimator using Padé (2,2) & 5-State FSM.
 * @license Apache-2.0
 */

#include "estimator.h"

/* Minimal inline absolute value without libm dependency */
static inline float est_fabs(float val) {
    return (val < 0.0f) ? -val : val;
}

/* Padé (2,2) rational approximator for matrix exponential state transition */
static inline void pade_22_transition(float dt, float *x, float *v) {
    const float alpha = 1.0f - (0.5f * dt);
    const float beta  = dt * (1.0f - (0.08333333f * dt));
    
    float next_x = *x + (*v * beta);
    float next_v = *v * alpha;
    
    *x = next_x;
    *v = next_v;
}

void est_init(est_handle_t *handle, const est_config_t *config) {
    if (!handle || !config) return;
    handle->config = *config;
    handle->state = EST_STATE_INIT;
    handle->state_x = 0.0f;
    handle->state_v = 0.0f;
    handle->fault_counter = 0;
    handle->consecutive_valid = 0;
    handle->initialized = true;
}

est_status_t est_update(est_handle_t *handle, float raw_measurement, est_output_t *output) {
    if (!handle || !handle->initialized) return EST_STATUS_DROPOUT_HOLD;

    est_status_t status = EST_STATUS_OK;
    const float dt = handle->config.dt;
    const float max_v = handle->config.max_velocity;

    /* 1. Predict step via Padé rational matrix propagation */
    float pred_x = handle->state_x;
    float pred_v = handle->state_v;
    pade_22_transition(dt, &pred_x, &pred_v);

    /* 2. Innovation residual evaluation */
    float residual = raw_measurement - pred_x;
    float abs_res = est_fabs(residual);

    /* 3. 5-State FSM Transition & Outlier Isolation */
    switch (handle->state) {
        case EST_STATE_INIT:
            handle->state_x = raw_measurement;
            handle->state_v = 0.0f;
            handle->state = EST_STATE_ACQUIRE;
            break;

        case EST_STATE_ACQUIRE:
            if (abs_res <= handle->config.outlier_threshold) {
                handle->consecutive_valid++;
                if (handle->consecutive_valid >= 3) {
                    handle->state = EST_STATE_TRACK;
                }
            } else {
                handle->consecutive_valid = 0;
            }
            handle->state_x = raw_measurement;
            break;

        case EST_STATE_TRACK:
            if (abs_res > handle->config.outlier_threshold) {
                status = EST_STATUS_OUTLIER_REJECTED;
                handle->fault_counter++;
                handle->state = EST_STATE_FAULT_CLAMP;
            } else {
                float measured_v = (raw_measurement - handle->state_x) / dt;
                
                if (measured_v > max_v) measured_v = max_v;
                else if (measured_v < -max_v) measured_v = -max_v;

                handle->state_v = pred_v + 0.35f * (measured_v - pred_v);
                handle->state_x = pred_x + 0.45f * residual;
                handle->fault_counter = 0;
            }
            break;

        case EST_STATE_FAULT_CLAMP:
            if (abs_res > handle->config.outlier_threshold) {
                handle->fault_counter++;
                status = EST_STATUS_OUTLIER_REJECTED;
                if (handle->fault_counter >= handle->config.dropout_timeout) {
                    handle->state = EST_STATE_DEGRADED;
                }
            } else {
                handle->state = EST_STATE_TRACK;
                handle->fault_counter = 0;
                handle->state_x = raw_measurement;
                handle->state_v = 0.0f;
            }
            break;

        case EST_STATE_DEGRADED:
            status = EST_STATUS_DROPOUT_HOLD;
            if (abs_res <= handle->config.outlier_threshold) {
                handle->state = EST_STATE_ACQUIRE;
                handle->consecutive_valid = 1;
            }
            break;
    }

    if (output) {
        output->x = handle->state_x;
        output->v = handle->state_v;
        output->residual = residual;
    }

    return status;
}
