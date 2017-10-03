/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <assert.h>
#include <string.h>

#include "sysinit/sysinit.h"
#include "os/os.h"
#include "bsp/bsp.h"
#include "hal/hal_gpio.h"

/* Include for nrf52 PWM driver implementation */
#include <pwm_nrf52/pwm_nrf52.h>

#define NOT_ZERO(x) (x == 0 ? 1 : x)

/* OS device */
static struct os_dev dev;
/* PWM device */
struct pwm_dev *pwm;
/* Max value for PWM */
uint16_t max_val;

int
main(int argc, char **argv)
{
    /* Set up channel config  for blink pin */ 
    struct pwm_chan_cfg chan_conf = {
        .pin = LED_BLINK_PIN,
        .inverted = false,
        .data = NULL
    };
    uint32_t base_freq;

    sysinit();
    
    /* Create PWM device */
    os_dev_create(&dev,
                  "pwm0",
                  OS_DEV_INIT_KERNEL,
                  OS_DEV_INIT_PRIO_DEFAULT,
                  nrf52_pwm_dev_init,
                  NULL);
    pwm = (struct pwm_dev *) os_dev_open("pwm0", 0, NULL);

    /* Set the PWM frequency */
    pwm_set_frequency(pwm, 10000);
    base_freq = pwm_get_clock_freq(pwm);
    max_val = (uint16_t) (base_freq / 10000);

    /* Configure a PWM channel */
    pwm_chan_config(pwm, 0, &chan_conf);
    pwm_enable_duty_cycle(pwm, 0, max_val);
    
    uint16_t div = 1;
    while (1) {
        /* Wait 1/10 seconds */
        os_time_delay(OS_TICKS_PER_SEC/20);
        /* div will cycle by powers of 2 between 1 and 2^15 */
        div = div * 2;
        div = NOT_ZERO(div);
        /* Re-enable duty cycle */ 
        pwm_enable_duty_cycle(pwm, 0, max_val / div);
    }
    assert(0);
    return(0);
}

