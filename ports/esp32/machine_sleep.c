/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdio.h>

#include "esp_system.h"
#include "esp_err.h"

#include "py/runtime.h"
#include "modmachine.h"

#if 0
#include "mphalport.h"
#include "rom/ets_sys.h"
#endif

// Forward dec'l
extern const mp_obj_type_t machine_sleep_type;

typedef struct _esp32_sleep_obj_t {
    mp_obj_base_t base;
} esp32_sleep_obj_t;


/******************************************************************************/

// MicroPython bindings for SLEEP

STATIC void esp32_sleep_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    esp32_sleep_obj_t *self = MP_OBJ_TO_PTR(self_in);

    mp_printf(print, "SLEEP()");
	
	// print member data

}


STATIC mp_obj_t esp32_sleep_make_new(const mp_obj_type_t *type,
        size_t n_args, size_t n_kw, const mp_obj_t *args) {

	// no args expected just yet but here's how to check
    mp_arg_check_num(n_args, n_kw, 0, MP_OBJ_FUN_ARGS_MAX, true);

    // create PWM object from the given pin
    esp32_sleep_obj_t *self = m_new_obj(esp32_sleep_obj_t);
    self->base.type = &machine_sleep_type;

    return MP_OBJ_FROM_PTR(self);
}

// --------------------------- fms ---------------------------------------------------------

STATIC mp_obj_t esp32_sleep_deep_sleep_start( mp_obj_t self_in) {
    // esp32_sleep_obj_t *self = MP_OBJ_TO_PTR(self_in);

	esp_deep_sleep_start();
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(esp32_sleep_deep_sleep_start_obj, esp32_sleep_deep_sleep_start);

STATIC mp_obj_t esp32_sleep_get_wakeup_cause(mp_obj_t self_in) {
    return mp_obj_new_int(esp_sleep_get_wakeup_cause());
}
MP_DEFINE_CONST_FUN_OBJ_1(esp32_sleep_get_wakeup_cause_obj, esp32_sleep_get_wakeup_cause);

STATIC mp_obj_t esp32_sleep_enable_ext0_wakeup(mp_obj_t self_in, mp_obj_t gpio_num, mp_obj_t level) {
	return mp_obj_new_int( esp_sleep_enable_ext0_wakeup(mp_obj_get_int(gpio_num), mp_obj_get_int(level) ) );
}
MP_DEFINE_CONST_FUN_OBJ_3(esp32_sleep_enable_ext0_wakeup_obj, esp32_sleep_enable_ext0_wakeup);

STATIC mp_obj_t esp32_sleep_enable_ext1_wakeup(mp_obj_t self_in, mp_obj_t mask_h32, mp_obj_t mask_l32, mp_obj_t mode) {
    uint32_t h32 = mp_obj_get_int(mask_h32);
    uint32_t l32 = mp_obj_get_int(mask_l32);
	uint64_t mask = ((uint64_t)h32)<<32 | l32;

	return mp_obj_new_int(esp_sleep_enable_ext1_wakeup(mask, mp_obj_get_int(mode)));
}
MP_DEFINE_CONST_FUN_OBJ_4(esp32_sleep_enable_ext1_wakeup_obj, esp32_sleep_enable_ext1_wakeup);


STATIC mp_obj_t esp32_sleep_get_ext1_wakeup_status(mp_obj_t self_in) {
	uint64_t status = esp_sleep_get_ext1_wakeup_status();

	mp_obj_t status_obj = mp_obj_new_bytearray(sizeof(uint64_t), &status);
    return status_obj;
}
MP_DEFINE_CONST_FUN_OBJ_1(esp32_sleep_get_ext1_wakeup_status_obj, esp32_sleep_get_ext1_wakeup_status);

STATIC mp_obj_t esp32_sleep_get_touchpad_wakeup_status(mp_obj_t self_in) {
    return mp_obj_new_int(esp_sleep_get_touchpad_wakeup_status());
}
MP_DEFINE_CONST_FUN_OBJ_1(esp32_sleep_get_touchpad_wakeup_status_obj, esp32_sleep_get_touchpad_wakeup_status);

STATIC mp_obj_t esp32_sleep_enable_touchpad_wakeup(mp_obj_t self_in) {
    return mp_obj_new_int(esp_sleep_enable_touchpad_wakeup());
}
MP_DEFINE_CONST_FUN_OBJ_1(esp32_sleep_enable_touchpad_wakeup_obj, esp32_sleep_enable_touchpad_wakeup);

STATIC mp_obj_t esp32_sleep_enable_timer_wakeup(mp_obj_t self_in, mp_obj_t high32, mp_obj_t low32) {
    uint32_t h32 = mp_obj_get_int(high32);
    uint32_t l32 = mp_obj_get_int(low32);
	uint64_t time_in_us = ((uint64_t)h32)<<32 | l32;

	return mp_obj_new_int(esp_sleep_enable_timer_wakeup(time_in_us));
}
MP_DEFINE_CONST_FUN_OBJ_3(esp32_sleep_enable_timer_wakeup_obj, esp32_sleep_enable_timer_wakeup);

STATIC mp_obj_t esp32_sleep_enable_ulp_wakeup(mp_obj_t self_in) {
    return mp_obj_new_int(esp_sleep_enable_ulp_wakeup());
}
MP_DEFINE_CONST_FUN_OBJ_1(esp32_sleep_enable_ulp_wakeup_obj, esp32_sleep_enable_ulp_wakeup);

STATIC mp_obj_t esp32_sleep_light_sleep_start(mp_obj_t self_in) {
    return mp_obj_new_int(esp_light_sleep_start());
}
MP_DEFINE_CONST_FUN_OBJ_1(esp32_sleep_light_sleep_start_obj, esp32_sleep_light_sleep_start);

// --------------------------- fms ---------------------------------------------------------

STATIC const mp_rom_map_elem_t esp32_sleep_locals_dict_table[] = {
	
    { MP_ROM_QSTR(MP_QSTR_deep_sleep_start), MP_ROM_PTR(&esp32_sleep_deep_sleep_start_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_wakeup_cause), MP_ROM_PTR(&esp32_sleep_get_wakeup_cause_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_ext1_wakeup_status), MP_ROM_PTR(&esp32_sleep_get_ext1_wakeup_status_obj) },
    { MP_ROM_QSTR(MP_QSTR_get_touchpad_wakeup_status), MP_ROM_PTR(&esp32_sleep_get_touchpad_wakeup_status_obj) },
    { MP_ROM_QSTR(MP_QSTR_enable_touchpad_wakeup), MP_ROM_PTR(&esp32_sleep_enable_touchpad_wakeup_obj) },
    { MP_ROM_QSTR(MP_QSTR_enable_ulp_wakeup), MP_ROM_PTR(&esp32_sleep_enable_ulp_wakeup_obj) },
    { MP_ROM_QSTR(MP_QSTR_enable_timer_wakeup), MP_ROM_PTR(&esp32_sleep_enable_timer_wakeup_obj) },
    { MP_ROM_QSTR(MP_QSTR_enable_ext0_wakeup), MP_ROM_PTR(&esp32_sleep_enable_ext0_wakeup_obj) },
    { MP_ROM_QSTR(MP_QSTR_enable_ext1_wakeup), MP_ROM_PTR(&esp32_sleep_enable_ext1_wakeup_obj) },
    { MP_ROM_QSTR(MP_QSTR_light_sleep_start), MP_ROM_PTR(&esp32_sleep_light_sleep_start_obj) },
	
};

STATIC MP_DEFINE_CONST_DICT(esp32_sleep_locals_dict,
    esp32_sleep_locals_dict_table);

const mp_obj_type_t machine_sleep_type = {
    { &mp_type_type },
    .name = MP_QSTR_SLEEP,
    .print = esp32_sleep_print,
    .make_new = esp32_sleep_make_new,
    .locals_dict = (mp_obj_dict_t*)&esp32_sleep_locals_dict,
};
