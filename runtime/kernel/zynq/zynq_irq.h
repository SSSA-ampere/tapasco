/*
 * Copyright (c) 2014-2020 Embedded Systems and Applications, TU Darmstadt.
 *
 * This file is part of TaPaSCo 
 * (see https://github.com/esa-tu-darmstadt/tapasco).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
//! @file	zynq_irq.c
//! @brief	IRQ handlers.
//! @authors	J. Korinth, TU Darmstadt (jk@esa.cs.tu-darmstadt.de)
//!
#ifndef ZYNQ_IRQ_H__
#define ZYNQ_IRQ_H__

#include <linux/interrupt.h>
#include "tlkm_control.h"
#include "zynq_device.h"

void zynq_irq_exit(struct tlkm_device *dev);

int zynq_irq_init(struct tlkm_device *dev, struct list_head *interrupts);

int zynq_irq_request_platform_irq(struct tlkm_device *dev,
				  struct tlkm_irq_mapping *mapping);
void zynq_irq_release_platform_irq(struct tlkm_device *dev,
				   struct tlkm_irq_mapping *mapping);

#endif /* ZYNQ_IRQ_H__ */
