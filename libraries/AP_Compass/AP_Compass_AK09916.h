/*
 * This file is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_HAL/I2CDevice.h>
#include <AP_Math/AP_Math.h>

#include "AP_Compass.h"
#include "AP_Compass_Backend.h"

#ifndef HAL_COMPASS_AK09916_I2C_ADDR
# define HAL_COMPASS_AK09916_I2C_ADDR 0x0C
#endif

class AP_Compass_AK09916 : public AP_Compass_Backend
{
public:
    static AP_Compass_Backend *probe(Compass &compass,
                                     AP_HAL::OwnPtr<AP_HAL::I2CDevice> dev,
                                     bool force_external = false,
                                     enum Rotation rotation = ROTATION_NONE);

    void read() override;

    static constexpr const char *name = "AK09916";

private:
    AP_Compass_AK09916(Compass &compass, AP_HAL::OwnPtr<AP_HAL::Device> dev,
                       bool force_external,
                       enum Rotation rotation);

    AP_HAL::OwnPtr<AP_HAL::Device> dev;
    
    /**
     * Device periodic callback to read data from the sensor.
     */
    bool init();
    bool timer();

    uint8_t compass_instance;
    Vector3f accum;
    uint16_t accum_count;
    enum Rotation rotation;
    bool force_external;
};
