/*
 * \file platform_usb_device.h
 * \brief libusb PlatformUsbDevice class header file.
 *
 * Copyright (c) 2013, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_USB_LIBUSB_PLATFORM_USB_DEVICE_H_
#define SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_USB_LIBUSB_PLATFORM_USB_DEVICE_H_

#include <libusb-1.0/libusb.h>
#include <string>

namespace transport_manager {

namespace transport_adapter {

class PlatformUsbDevice {
 public:
  uint8_t bus_number() const {
    return bus_number_;
  }
  uint8_t address() const {
    return address_;
  }
  uint16_t vendor_id() const {
    return vendor_id_;
  }
  uint16_t product_id() const {
    return product_id_;
  }
  std::string GetManufacturer() const;
  std::string GetProductName() const;
  std::string GetSerialNumber() const;
  PlatformUsbDevice(uint8_t bus,
                    uint8_t address,
                    const libusb_device_descriptor& device_descriptor,
                    libusb_device* device_libusb,
                    libusb_device_handle* device_handle_libusb);
  libusb_device_handle* GetLibusbHandle() {
    return libusb_device_handle_;
  }
  libusb_device* GetLibusbDevice() {
    return libusb_device_;
  }

 private:
  std::string GetDescString(uint8_t index) const;

 private:
  uint8_t bus_number_;
  uint8_t address_;
  uint16_t vendor_id_;
  uint16_t product_id_;
  libusb_device_descriptor device_descriptor_;
  libusb_device_handle* libusb_device_handle_;
  libusb_device* libusb_device_;
};

}  // namespace transport_adapter
}  // namespace transport_manager

#endif  // SRC_COMPONENTS_TRANSPORT_MANAGER_INCLUDE_TRANSPORT_MANAGER_USB_LIBUSB_PLATFORM_USB_DEVICE_H_
