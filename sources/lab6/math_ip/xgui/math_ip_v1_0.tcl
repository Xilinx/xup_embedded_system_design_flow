# Copyright (C) 2022, Advanced Micro Devices, Inc.

# SPDX-License-Identifier: BSD-3-Clause
#Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
	set Page0 [ ipgui::add_page $IPINST  -name "Page 0" -layout vertical]
	set Component_Name [ ipgui::add_param  $IPINST  -parent  $Page0  -name Component_Name ]
}

