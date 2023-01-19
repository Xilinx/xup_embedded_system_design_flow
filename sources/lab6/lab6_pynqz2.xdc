# Copyright (C) 2022, Advanced Micro Devices, Inc.
# SPDX-License-Identifier: BSD-3-Clause

########################################################
# LED constraints                                      #
########################################################

set_property IOSTANDARD LVCMOS33 [get_ports {leds[3]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[2]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[1]}]
set_property IOSTANDARD LVCMOS33 [get_ports {leds[0]}]

set_property PACKAGE_PIN M14 [get_ports {leds[3]}]
set_property PACKAGE_PIN N16 [get_ports {leds[2]}]
set_property PACKAGE_PIN P14 [get_ports {leds[1]}]
set_property PACKAGE_PIN R14 [get_ports {leds[0]}]
